/**
 ** \file ast/method-call-exp.hxx
 ** \brief Inline methods of ast::MethodMethodMethodCallExp.
 */

#pragma once

#include <ast/method-call-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.

  inline const Var& MethodCallExp::object_get() const { return *object_; }
  /// Return instructions executed in the loop.
  inline Var& MethodCallExp::object_get() { return *object_; }
  /** \} */
  /*inline const exps_type& MethodCallExp::args_get() const { return *args_; }
  /// Return instructions executed in the loop.
  inline exps_type& MethodCallExp::args_get() { return *args_; }

  inline const misc::symbol MethodCallExp::name_get() const { return *name_; }
  /// Return instructions executed in the loop.
  inline misc::symbol MethodCallExp::name_get() { return *name_; }*/
} // namespace ast
