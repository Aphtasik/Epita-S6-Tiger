/**
 ** \file ast/call-exp.hxx
 ** \brief Inline methods of ast::CallExp.
 */

#pragma once

#include <ast/call-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  inline const exps_type& CallExp::exps_get() const { return *exps_; }
  inline exps_type& CallExp::exps_get() { return *exps_; }

  inline const misc::symbol CallExp::name_get() const { return name_; }
  inline misc::symbol CallExp::name_get() { return name_; }

  inline const FunctionDec* CallExp::def_get() const { return def_; }
  inline FunctionDec* CallExp::def_get() { return def_; }
  inline void CallExp::def_set(FunctionDec* def) { def_ = def; }
} // namespace ast
