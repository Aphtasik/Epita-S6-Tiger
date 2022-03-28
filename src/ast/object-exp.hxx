/**
 ** \file ast/object-exp.hxx
 ** \brief Inline methods of ast::ObjectExp.
 */

#pragma once

#include <ast/object-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  inline const NameTy& ObjectExp::name_get() const { return *name_; }
  inline NameTy& ObjectExp::name_get() { return *name_; }
} // namespace ast
