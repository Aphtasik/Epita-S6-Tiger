/**
 ** \file ast/dec.hh
 ** \brief Declaration of ast::Dec.
 */

#pragma once

#include <ast/ast.hh>
#include <misc/symbol.hh>

namespace ast
{
  /// Dec.
  class Dec : public Ast
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a Dec node.
    Dec(const Location& location, misc::symbol name);
    Dec(const Dec&) = delete;
    Dec& operator=(const Dec&) = delete;
    /// Destroy a Dec node.
    /** \} */

    /** \name Accessors.
     ** \{ */
    /// Return name of the defined entity.
    misc::symbol name_get() const;
    /// Set name of the defined entity.
    void name_set(misc::symbol);
    /** \} */

  protected:
    /// Name of the defined entity.
    misc::symbol name_;
  };
} // namespace ast
#include <ast/dec.hxx>
