/**
 ** \file ast/field-var.cc
 ** \brief Implementation of ast::FieldVar.
 */

#include <ast/field-var.hh>
#include <ast/visitor.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  FieldVar::FieldVar(const Location& location, Var* var, misc::symbol symb)
    : Var(location)
    , var_(var)
    , symb_(symb)
  {}

  FieldVar::~FieldVar() { delete var_; }

  void FieldVar::accept(ConstVisitor& v) const { v(*this); }

  void FieldVar::accept(Visitor& v) { v(*this); }
} // namespace ast
