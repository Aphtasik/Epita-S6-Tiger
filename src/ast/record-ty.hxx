/**
 ** \file ast/record-ty.hxx
 ** \brief Inline methods of ast::RecordTy.
 */

#pragma once

#include <ast/record-ty.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  inline const Field& WhileExp::field_get() const { return *field_; }
  inline Field& WhileExp::field_get() { return *field_; }
} // namespace ast
