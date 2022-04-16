/**
 ** \file ast/pretty-printer.cc
 ** \brief Implementation of ast::PrettyPrinter.
 */

#include <ast/all.hh>
#include <ast/libast.hh>
#include <ast/pretty-printer.hh>
#include <misc/escape.hh>
#include <misc/indent.hh>
#include <misc/separator.hh>

namespace ast
{
  // Anonymous namespace: these functions are private to this file.
  namespace
  {
    /// Output \a e on \a ostr.
    inline std::ostream& operator<<(std::ostream& ostr, const Escapable& e)
    {
      if (escapes_display(ostr)
          // FIXME: Some code was deleted here.
      )
        ostr << "/* escaping */ ";

      return ostr;
    }

    /// \brief Output \a e on \a ostr.
    ///
    /// Used to factor the output of the name declared,
    /// and its possible additional attributes.
    inline std::ostream& operator<<(std::ostream& ostr, const Dec& e)
    {
      // ostr << e.name_get();
      // if (bindings_display(ostr))
        ostr << " /* " << &e << " */ ";
      return ostr;
    }
  } // namespace

  PrettyPrinter::PrettyPrinter(std::ostream& ostr)
    : ostr_(ostr)
  {}

  void PrettyPrinter::operator()(const SimpleVar& e)
  {
    ostr_ << e.name_get();
    if (bindings_display(ostr_)) // 
      ostr_ << " /* " << e.def_get() << " */";
  }

  void PrettyPrinter::operator()(const FieldVar& e)
  {
    // FIXME: Some code was deleted here.
    ostr_ << e.var_get() << "." << e.symb_get();
  }

  /* Foo[10]. */
  void PrettyPrinter::operator()(const SubscriptVar& e)
  {
    ostr_ << e.var_get() << '[' << misc::incindent << e.index_get()
          << misc::decindent << ']';
  }

  void PrettyPrinter::operator()(const CastExp& e)
  {
    ostr_ << "_cast(" << e.exp_get() << ", " << e.ty_get() << ')';
  }

  // FIXME: Some code was deleted here.
  void PrettyPrinter::operator()(const FunctionDec& e)
  {
    if (e.body_get() == nullptr)
      ostr_ << "primitive ";
    else
      ostr_ << "function ";
    ostr_ << e.name_get();
    if (bindings_display(ostr_))
        ostr_ << dynamic_cast<const Dec&>(e);
    ostr_ << "(";
    e.formals_get().accept(*this);
    ostr_ << ")";

    if (e.result_get() != nullptr)
      {
        ostr_ << " : " << *e.result_get();
      }
    if (e.body_get() != nullptr)
      ostr_ << " =" << misc::incendl << "(" << *e.body_get() << ')';
    else
      ostr_ << misc::iendl;
  }

  void PrettyPrinter::operator()(const MethodDec& e) {} //TODO

  void PrettyPrinter::operator()(const TypeDec& e)
  {
    ostr_ << "type " << e.name_get();
    if(bindings_display(ostr_))
        ostr_ << dynamic_cast<const Dec&>(e);
    ostr_ << "=" << e.ty_get() << misc::iendl;
  }
  void PrettyPrinter::operator()(const VarDec& e)
  {
    if (e.init_get() == nullptr)
      {
        ostr_ << e.name_get();
        if (bindings_display(ostr_))
          ostr_ << dynamic_cast<const Dec&>(e);
        if (e.type_name_get() != nullptr)
          ostr_ << " : " << *e.type_name_get();
      }
    else
      {
        ostr_ << "var " << e.name_get();
        if (bindings_display(ostr_))
          ostr_ << dynamic_cast<const Dec&>(e);
        if (e.type_name_get() != nullptr)
          ostr_ << " : " << *e.type_name_get();
        ostr_ << " := " << *e.init_get();
      }
  }
  void PrettyPrinter::operator()(const VarChunk& e)
  {
    ostr_ << misc::separate(e, ", ");
  }
  void PrettyPrinter::operator()(const ArrayExp& e)
  {
    ostr_ << e.arr_type_get() << "[" << e.arr_length_get() << "] of "
          << e.arr_val_get();
  }
  void PrettyPrinter::operator()(const AssignExp& e)
  {
    ostr_ << e.var_get() << " := " << e.exp_get() << misc::iendl;
  }
  void PrettyPrinter::operator()(const BreakExp& e)
  {
    ostr_ << "break";
    if (bindings_display(ostr_))
        ostr_ << " /* " << e.def_get() << " */";
    ostr_ << misc::iendl;
  }
  void PrettyPrinter::operator()(const CallExp& e)
  {
    ostr_ << e.name_get();
    if (bindings_display(ostr_))
      ostr_ << dynamic_cast<const Dec&>(*e.def_get());
    ostr_ << "(" << misc::separate(e.exps_get(), ", ");
    ostr_ << ")";
  }
  void PrettyPrinter::operator()(const MethodCallExp& e) {} //TODO
  void PrettyPrinter::operator()(const ForExp& e)
  {
    ostr_ << "for "; //TODO: binding print
    if (bindings_display(ostr_))
      ostr_ << " /* " << &e << " */ ";
    ostr_ << e.vardec_get().name_get();
    ostr_ << " := " << *e.vardec_get().init_get();
    ostr_ << " to " << e.hi_get() << " do " << misc::incindent << e.body_get()
          << misc::decindent;
  }
  void PrettyPrinter::operator()(const IfExp& e)
  {
    ostr_ << "if (" << *e.test_get() << ")" << misc::incendl << "then "
          << *e.thenclause_get() << misc::decendl;
    if (e.elseclause_get())
      ostr_ << "else (" << misc::incendl << *e.elseclause_get() << misc::decendl << ")" << misc::iendl;
  }
  void PrettyPrinter::operator()(const IntExp& e) { ostr_ << e.value_get(); }
  void PrettyPrinter::operator()(const LetExp& e)
  {
    ostr_ << "let" << misc::incendl << e.chunklist_get() << misc::iendl << "in "
          << e.exp_get() << "end" << misc::iendl;
  }
  void PrettyPrinter::operator()(const NilExp& e) { ostr_ << "nil"; }
  void PrettyPrinter::operator()(const ObjectExp& e) {} //TODO
  void PrettyPrinter::operator()(const OpExp& e)
  {
    ostr_ << e.left_get() << " ";
    switch (e.oper_get())
      {
      case OpExp::Oper::add:
        ostr_ << "+";
        break;
      case OpExp::Oper::sub:
        ostr_ << "-";
        break;
      case OpExp::Oper::mul:
        ostr_ << "*";
        break;
      case OpExp::Oper::div:
        ostr_ << "/";
        break;
      case OpExp::Oper::eq:
        ostr_ << "=";
        break;
      case OpExp::Oper::ne:
        ostr_ << "<>";
        break;
      case OpExp::Oper::lt:
        ostr_ << "<";
        break;
      case OpExp::Oper::le:
        ostr_ << "<=";
        break;
      case OpExp::Oper::gt:
        ostr_ << ">";
        break;
      case OpExp::Oper::ge:
        ostr_ << ">=";
        break;
      }
    ostr_ << " " << e.right_get();
  }

  void PrettyPrinter::operator()(const RecordExp& e)
  {
    ostr_ << e.rec_get() << "{";
    ostr_ << misc::separate(e.vec_get(), ", ");
    ostr_ << '}' << misc::iendl;
  }

  void PrettyPrinter::operator()(const SeqExp& e)
  {
    if (e.exps_get().size() == 0)
      {
        ostr_ << misc::iendl << "()";
        return;
      }

    ostr_ << misc::incendl << "(";
    ostr_ << misc::separate(e.exps_get(), "; ");
    ostr_ << ")" << misc::decendl;
  }

  void PrettyPrinter::operator()(const StringExp& e)
  {
    ostr_ << '"' << e.name_get() << '"';
  }
  void PrettyPrinter::operator()(const WhileExp& e)
  {
    ostr_ << "while ";
    if(bindings_display(ostr_))
        ostr_ << " /* " << &e << " */ ";
    ostr_ << e.test_get() << " do " << misc::incendl << e.body_get()
          << misc::decendl; //TODO: binding print
  }

  void PrettyPrinter::operator()(const ArrayTy& e)
  {
    ostr_ << "array of " << e.base_type_get();
  }
  void PrettyPrinter::operator()(const ClassTy& e) {} //TODO
  void PrettyPrinter::operator()(const NameTy& e)
  {
    //std::cout << "ouiiiiiii " << e.name_get().get() << std::endl;
    if (bindings_display(ostr_))
        ostr_ << e.name_get() << " /* " << e.def_get() << " */ ";
    else
        ostr_ << e.name_get();
  }
  void PrettyPrinter::operator()(const RecordTy& e)
  {
    ostr_ << "{";
    ostr_ << misc::separate(e.field_get(), ", ");
    ostr_ << '}';
  }
  void PrettyPrinter::operator()(const ChunkList& e)
  {
    ostr_ << misc::separate(e.chunks_get(), " ");
  }
  void PrettyPrinter::operator()(const Field& e)
  {
    ostr_ << e.type_name_get() << " : " << e.name_get();
  }
  void PrettyPrinter::operator()(const FieldInit& e)
  {
    ostr_ << e.name_get() << " = " << e.init_get();
  }

} // namespace ast
