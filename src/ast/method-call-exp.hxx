/**
 ** \file ast/method-call-exp.hxx
 ** \brief Inline methods of ast::MethodMethodMethodCallExp.
 */

#pragma once

#include <ast/method-call-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  inline const Var& MethodMethodCallExp::var_get() const { return *var_; }
  inline Var& MethodMethodCallExp::var_get() { return *var_; }
} // namespace ast
