/**
 ** \file ast/assign-exp.hxx
 ** \brief Inline methods of ast::AssignExp.
 */

#pragma once

#include <ast/assign-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
    /// Return exit condition of the loop.
    inline const Var& AssignExp::var_get() const
    {
        return *this->var_;
    }
    /// Return exit condition of the loop.
    inline Var& AssignExp::var_get()
    {
        return this->var_;
    }
    /// Return instructions executed in the loop.
    inline const Exp& AssignExp::exp_get() const
    {
        return this->exp_;
    }
    /// Return instructions executed in the loop.
    inline Exp& AssignExp::exp_get()
    {
        return this->exp_;
    }
} // namespace ast
