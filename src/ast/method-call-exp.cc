/**
 ** \file ast/method-call-exp.cc
 ** \brief Implementation of ast::MethodMethodMethodCallExp.
 */

#include <ast/method-call-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  MethodMethodCallExp::MethodMethodCallExp(const Location& location,
                                           exps_type exps,
                                           Var* var)
    : CallExp(location, exps)
    , var_(var)
  {}

  MethodMethodCallExp::~MethodMethodCallExp() { delete var_; }

  void MethodMethodCallExp::accept(ConstVisitor& v) const { v(*this); }

  void MethodMethodCallExp::accept(Visitor& v) { v(*this); }
} // namespace ast
