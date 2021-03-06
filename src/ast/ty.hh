/**
 ** \file ast/ty.hh
 ** \brief Declaration of ast::Ty.
 */

#pragma once

#include <ast/ast.hh>

namespace ast
{
  /// Ty.
  class Ty : public Ast
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a Ty node.
    explicit Ty(const Location& location);
    Ty(const Ty&) = delete;
    Ty& operator=(const Ty&) = delete;
    /// Destroy a Ty node.
    /** \} */
  };
} // namespace ast
#include <ast/ty.hxx>
