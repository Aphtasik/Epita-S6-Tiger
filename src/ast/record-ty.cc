/**
 ** \file ast/record-ty.cc
 ** \brief Implementation of ast::RecordTy.
 */

#include <ast/record-ty.hh>
#include <ast/visitor.hh>
#include <misc/algorithm.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  RecordTy::RecordTy(const Location& location, Field* field)
    : Exp(location)
    , field_(field)
  {}

  RecordTy::~RecordTy() { delete field_; }

  void RecordTy::accept(ConstVisitor& v) const { v(*this); }

  void RecordTy::accept(Visitor& v) { v(*this); }
} // namespace ast
