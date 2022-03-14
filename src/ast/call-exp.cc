/**
 ** \file ast/call-exp.cc
 ** \brief Implementation of ast::CallExp.
 */

#include <ast/call-exp.hh>
#include <ast/visitor.hh>
#include <misc/algorithm.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  CallExp::CallExp(const Location& location, exps_type exps)
    : Exp(location)
    , exps_(exps)
  {}

  CallExp::~CallExp() {
    delete exps_;
  }

  void CallExp::accept(ConstVisitor& v) const { v(*this); }

  void CallExp::accept(Visitor& v) { v(*this); }
} // namespace ast
