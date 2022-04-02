/**
 ** \file ast/array-exp.hxx
 ** \brief Inline methods of ast::ArrayExp.
 */

#pragma once

#include <ast/array-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  inline const NameTy& ArrayExp::arr_type_get() const { return *arr_type_; }
  inline NameTy& ArrayExp::arr_type_get() { return *arr_type_; }

  inline const Exp& ArrayExp::arr_length_get() const { return *arr_length_; }
  inline Exp& ArrayExp::arr_length_get() { return *arr_length_; }

  inline const Exp& ArrayExp::arr_val_get() const { return *arr_val_; }
  inline Exp& ArrayExp::arr_val_get() { return *arr_val_; }
} // namespace ast
