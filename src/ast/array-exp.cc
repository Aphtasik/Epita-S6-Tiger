/**
 ** \file ast/array-exp.cc
 ** \brief Implementation of ast::ArrayExp.
 */

#include <ast/array-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  ArrayExp::ArrayExp(const Location& location,
                     NameTy* arr_type,
                     Exp* arr_length,
                     Exp* arr_val)
    : Exp(location)
    , arr_type_(arr_type)
    , arr_length_(arr_length)
    , arr_val_(arr_val)
  {}

  ArrayExp::~ArrayExp()
  {
    delete test_;
    delete body_;
  }

  void ArrayExp::accept(ConstVisitor& v) const { v(*this); }

  void ArrayExp::accept(Visitor& v) { v(*this); }
} // namespace ast
