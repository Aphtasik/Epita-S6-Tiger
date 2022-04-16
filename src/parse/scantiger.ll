/* -*- C++ -*- */
%option c++
%option nounput
%option debug
%option batch

%{

#include <cerrno>
#include <climits>
#include <regex>
#include <string>

#include <boost/lexical_cast.hpp>

#include <misc/contract.hh>
  // Using misc::escape is very useful to quote non printable characters.
  // For instance
  //
  //    std::cerr << misc::escape('\n') << '\n';
  //
  // reports about `\n' instead of an actual new-line character.
#include <misc/escape.hh>
#include <misc/symbol.hh>
#include <parse/parsetiger.hh>
#include <parse/tiger-parser.hh>


    // FIXME: Some code was deleted here.
    std::string dynamic_string;

// Convenient shortcuts.
#define TOKEN_VAL(Type, Value)                  \
  parser::make_ ## Type(Value, tp.location_)

#define TOKEN(Type)                             \
  parser::make_ ## Type(tp.location_)


// Flex uses `0' for end of file.  0 is not a token_type.
#define yyterminate() return TOKEN(EOF)

# define CHECK_EXTENSION()                              \
  do {                                                  \
    if (!tp.enable_extensions_p_)                       \
      tp.error_ << misc::error::error_type::scan        \
                << tp.location_                         \
                << ": invalid identifier: `"            \
                << misc::escape(yytext) << "'\n";       \
  } while (false)

YY_FLEX_NAMESPACE_BEGIN
%}

%x SC_COMMENT SC_STRING

/* Abbreviations.  */
int             [0-9]+
SPACE           [ \t]
XNUMBER         \\x[0-7][0-9A-F]
NUMBER          \\[0-3][0-7][0-7]
ID              ([a-zA-Z][a-zA-Z0-9_]*|_main)      
EOL             (\n\r|\r\n|\n|\r)
BACKSLASH       \\[^\\abfnrtv]

/* FIXME: Some code was deleted here. */
%%
%{
  // FIXME: Some code was deleted here (Local variables).
    uint nbcomments = 0;

  // Each time yylex is called.
  tp.location_.step();
%}

 /* The rules.  */
"/*"            {
    nbcomments = 1;
    BEGIN(SC_COMMENT);
                }

<SC_COMMENT>{
<<eof>>         {
      tp.error_ << misc::error::error_type::scan        \
                << tp.location_                         \
                << ": unexpected end of file in a comment\n";            \
                BEGIN(INITIAL);
                }
{EOL}           {}
"/*"            { nbcomments++; }
"*/"            {
    nbcomments--;
    if (nbcomments == 0)
        BEGIN(INITIAL);
                }
.               {}
}


"\""            {
        dynamic_string.clear();
        BEGIN(SC_STRING);
                }
<SC_STRING>{
<<eof>>         {
        tp.error_ << misc::error::error_type::scan        \
                << tp.location_                         \
                << ": unexpected end of file in a string\n";            \
                BEGIN(INITIAL);
                }

{EOL}           {
        tp.location_.lines(yyleng); tp.location_.step();
                }

{NUMBER}       {
        dynamic_string += strtol(yytext + 1, 0, 8);
                }

{XNUMBER}       {
        dynamic_string += strtol(yytext + 2, 0, 16);
                }

"\\\""          {
        dynamic_string += yytext;
                }
"\""            {
        BEGIN(INITIAL);
        return TOKEN_VAL(STRING, dynamic_string);
                }
{BACKSLASH}     {
      tp.error_ << misc::error::error_type::scan        \
                << tp.location_                         \
                << ": invalid identifier: `"            \
                << misc::escape(yytext) << "'\n";       \
                BEGIN(INITIAL);
                }
.               {
        dynamic_string += yytext;
                }
}


","	        { return TOKEN(COMMA); }
":"	        { return TOKEN(COLON); }
";"	        { return TOKEN(SEMI); }
"("	        { return TOKEN(LPAREN); }
")"	        { return TOKEN(RPAREN); }
"["	        { return TOKEN(LBRACK); }
"]"	        { return TOKEN(RBRACK); }
"{"	        { return TOKEN(LBRACE); }
"}"	        { return TOKEN(RBRACE); }
"."	        { return TOKEN(DOT); }

"+"	        { return TOKEN(PLUS); }
"-"	        { return TOKEN(MINUS); }
"*"	        { return TOKEN(TIMES); }
"/"	        { return TOKEN(DIVIDE); }

"="	        { return TOKEN(EQ); }
"<>"	    { return TOKEN(NE); }
"<"	        { return TOKEN(LT); }
"<="	    { return TOKEN(LE); }
">"	        { return TOKEN(GT); }
">="	    { return TOKEN(GE); }
"&"	        { return TOKEN(AND); }
"|"	        { return TOKEN(OR); }
":="	    { return TOKEN(ASSIGN); }


"array"     { return TOKEN(ARRAY); }
"if"        { return TOKEN(IF); }
"then"      { return TOKEN(THEN); }
"else"      { return TOKEN(ELSE); }
"while"     { return TOKEN(WHILE); }
"for"  	    { return TOKEN(FOR); }
"to"  	    { return TOKEN(TO); }
"do"  	    { return TOKEN(DO); }
"let"  	    { return TOKEN(LET); }
"in"  	    { return TOKEN(IN); }
"end"  	    { return TOKEN(END); }
"of"  	    { return TOKEN(OF); }
"break"  	{ return TOKEN(BREAK); }
"nil"  	    { return TOKEN(NIL); }
"function"  { return TOKEN(FUNCTION); }
"var"       { return TOKEN(VAR); }
"type"      { return TOKEN(TYPE); }
"import"    { return TOKEN(IMPORT); }
"primitive" { return TOKEN(PRIMITIVE); }

"class"     { CHECK_EXTENSION(); return TOKEN(CLASS); }
"extends"   { CHECK_EXTENSION(); return TOKEN(EXTENDS); }
"method"    { CHECK_EXTENSION(); return TOKEN(METHOD); }
"new"       { CHECK_EXTENSION(); return TOKEN(NEW); }

"_chunks"   { return TOKEN(CHUNKS); }
"_exp"      { return TOKEN(EXP); }
"_lvalue"     { return TOKEN(LVALUE); }
"_namety"   { return TOKEN(NAMETY); }

{int}       {
    int val = 0;
    val = strtoul(yytext, nullptr, 10);
    if (errno == ERANGE)
    {
      tp.error_ << misc::error::error_type::scan        \
                << tp.location_                         \
                << ": invalid identifier: `"            \
                << misc::escape(yytext) << "'\n";       \
    }
    else
        return TOKEN_VAL(INT, val);
    // FIXME: Some code was deleted here (Decode, and check the value).
            }

{SPACE}     {
    tp.location_.step();
    continue;
            }
{EOL}       { tp.location_.lines(yyleng); }

{ID}        {
    misc::symbol symbol(yytext);
    return TOKEN_VAL(ID, symbol);
            }

{XNUMBER}           {
      tp.error_ << misc::error::error_type::scan        \
                << tp.location_                         \
                << ": invalid identifier: `"            \
                << misc::escape(yytext) << "'\n";       \
                }

<<eof>>     { return TOKEN(EOF); }
.           {
    tp.error_ << misc::error::error_type::scan        \
        << tp.location_                         \
        << ": invalid identifier: `"            \
        << misc::escape(yytext) << "'\n";       \
            }
%%

// Do not use %option noyywrap, because then flex generates the same
// definition of yywrap, but outside the namespaces, so it defines it
// for ::yyFlexLexer instead of ::parse::yyFlexLexer.
int yyFlexLexer::yywrap() { return 1; }

void
yyFlexLexer::scan_open_(std::istream& f)
{
  yypush_buffer_state(YY_CURRENT_BUFFER);
  yy_switch_to_buffer(yy_create_buffer(&f, YY_BUF_SIZE));
}

void
yyFlexLexer::scan_close_()
{
  yypop_buffer_state();
}

YY_FLEX_NAMESPACE_END
