/**
 ** \file ast/record-exp.cc
 ** \brief Implementation of ast::RecordExp.
 */

#include <ast/record-exp.hh>
#include <ast/visitor.hh>
#include <misc/algorithm.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  RecordExp::RecordExp(const Location& location, NameTy* rec, fieldinits_type vec)
    : Exp(location)
    , rec_(rec)
    , vec_(vec)
  {}

  RecordExp::~RecordExp() {
    delete rec_;
    delete vec_;
  }

  void RecordExp::accept(ConstVisitor& v) const { v(*this); }

  void RecordExp::accept(Visitor& v) { v(*this); }
} // namespace ast
