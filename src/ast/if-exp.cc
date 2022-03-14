/**
 ** \file ast/if-exp.cc
 ** \brief Implementation of ast::IfExp.
 */

#include <ast/if-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  IfExp::IfExp(const Location& location, Exp* test, Exp* body)
    : Exp(location)
    , test_(test)
    , body_(body)
  {}

  IfExp::~IfExp()
  {
    delete test_;
    delete body_;
  }

  void IfExp::accept(ConstVisitor& v) const { v(*this); }

  void IfExp::accept(Visitor& v) { v(*this); }
} // namespace ast
