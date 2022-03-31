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

    /// \brief Output \a e on \a ostr.
    ///
    /// Used to factor the output of the name declared,
    /// and its possible additional attributes.
    inline std::ostream& operator<<(std::ostream& ostr, const Dec& e)
    {
      ostr << e.name_get();
      return ostr;
    }
  } // namespace

  PrettyPrinter::PrettyPrinter(std::ostream& ostr)
    : ostr_(ostr)
  {}

  void PrettyPrinter::operator()(const SimpleVar& e) { ostr_ << e.name_get(); }

  void PrettyPrinter::operator()(const FieldVar& e)
  {
    // FIXME: Some code was deleted here.
    ostr_ << e.var_get() << ": " << e.symb_get();
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
    ostr_ << "function " << e.name_get() << '(' << e.formals_get() << ")";
    if (e.result_get() != nullptr)
      ostr_ << " : " << e.result_get();
    ostr_ << " =\n(" << misc::incendl << e.body_get() << misc::decendl << ')';
  }
  void PrettyPrinter::operator()(const MethodDec& e) {} //TODO

  void PrettyPrinter::operator()(const TypeDec& e)
  {
    ostr_ << "type " << e.name_get() << "=" << e.ty_get();
  }
  void PrettyPrinter::operator()(const VarDec& e)
  {
    ostr_ << "var" << e.type_name_get() << ":= " << e.init_get();
  }
  void PrettyPrinter::operator()(const ArrayExp& e)
  {
    ostr_ << e.arr_type_get() << "[" << e.arr_length_get() << "] of "
          << e.arr_val_get();
  }
  void PrettyPrinter::operator()(const AssignExp& e)
  {
    ostr_ << e.var_get() << " := " << e.exp_get();
  }
  void PrettyPrinter::operator()(const BreakExp& e) { ostr_ << "break"; }
  void PrettyPrinter::operator()(const CallExp& e)
  {
    ostr_ << e.name_get() << "(";
    auto x = e.exps_get();
    for (auto i = 0; i < x.size() - 1; i++)
      ostr_ << x.at(i) << ",";
    ostr_ << x.at(x.size() - 1) << ")\n";
  }
  void PrettyPrinter::operator()(const MethodCallExp& e) {}
  void PrettyPrinter::operator()(const ForExp& e)
  {
    ostr_ << "for " << e.vardec_get() << " to " << e.hi_get() << " do "
          << "\n"
          << misc::incindent << e.body_get() << misc::decindent << "\n";
  }
  void PrettyPrinter::operator()(const IfExp& e) {
    ostr_ << "if (" << e.test_get() << ") then\n"
    << misc::incindent << e.thenclause_get() << misc::decindent;
    if (e.elseclause_get())
      {
        ostr_ << "\nelse\n" << misc::incindent << e.elseclause_get()
        << misc::decindent << '\n';
      }
  }
  void PrettyPrinter::operator()(const IntExp& e) {
    ostr_ << e.value_get();
  }
  void PrettyPrinter::operator()(const LetExp& e) {
    ostr_ << "let " << e.chunklist_get() << " in " << e.exp_get() << " end" << "\n";
  }
  void PrettyPrinter::operator()(const NilExp& e) {
      ostr_ << "nil";
  }
  void PrettyPrinter::operator()(const ObjectExp& e) {}
  void PrettyPrinter::operator()(const OpExp& e) {
    ostr_ << e.left_get() << " " << e.oper_get() << " " << e.right_get();
  }
  void PrettyPrinter::operator()(const RecordExp& e)
  {
    ostr_ << e.rec_get() << "= {";
    auto vec = e.vec_get();
    // printing each field one by one
    for (size_t i = 0; i < vec.size() - 1; i++)
      ostr_ << vec.at(i) << ", ";
    // putting the last item without the coma
    ostr_ << *(--vec.end()) << '}';
  }
  void PrettyPrinter::operator()(const SeqExp& e) {
    ostr_ << "(" << e.exps_get() << ")";
  }
  void PrettyPrinter::operator()(const StringExp& e) {
    ostr_ << e.name_get();
  }
  void PrettyPrinter::operator()(const WhileExp& e) {
    ostr_ << "while " << e.test_get() << " do\n" << "  " << e.body_get();
  }
  void PrettyPrinter::operator()(const ArrayTy& e) {
    ostr_ << e.arr_type_get() << "[" << e.arr_length_get() << "] of " << e.arr_val_get();
  }
  void PrettyPrinter::operator()(const ClassTy& e) {}
  void PrettyPrinter::operator()(const NameTy& e) {}
  void PrettyPrinter::operator()(const RecordTy& e) {
    ostr_ << e.field_get();
  }
  void PrettyPrinter::operator()(const ChunkList& e) {}
  void PrettyPrinter::operator()(const Field& e) {
    ostr_ << e.type_name_get() << " : " << e.name_get();
  }
  void PrettyPrinter::operator()(const FieldInit& e) {
    ostr_ << e.name_get() << " : " << e.init_get();
  }

} // namespace ast
