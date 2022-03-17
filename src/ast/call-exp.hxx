/**
 ** \file ast/call-exp.hxx
 ** \brief Inline methods of ast::CallExp.
 */

#pragma once

#include <ast/call-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  inline const exps_type CallExp::exps_get() const { return *exps_; }
  inline exps_type CallExp::exps_get() { return *exps_; }

  inline const misc::symbol MethodCallExp::name_get() const { return *name_; }
  inline misc::symbol MethodCallExp::name_get() { return *name_; }*/
} // namespace ast
