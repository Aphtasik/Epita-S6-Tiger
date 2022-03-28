/**
 ** \file ast/object-exp.cc
 ** \brief Implementation of ast::ObjectExp.
 */

#include <ast/object-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  ObjectExp::ObjectExp(const Location& location, NameTy* name)
    : Exp(location)
    , name_(name)
  {}

  ObjectExp::~ObjectExp() { delete name_; }

  void ObjectExp::accept(ConstVisitor& v) const { v(*this); }

  void ObjectExp::accept(Visitor& v) { v(*this); }
} // namespace ast
