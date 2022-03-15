/**
 ** \file ast/object-exp.hh
 ** \brief Declaration of ast::ObjectExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// ObjectExp.
  class ObjectExp : public Exp
  {
    // FIXME: Some code was deleted here.
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a ObjectExp node.
    ObjectExp(const Location& location, NameTy* name);
    ObjectExp(const ObjectExp&) = delete;
    ObjectExp& operator=(const ObjectExp&) = delete;
    /// Destroy a ObjectExp node.
    ~ObjectExp() override;
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    /// Return instructions executed in the loop.
    const NameTy& name_get() const;
    /// Return instructions executed in the loop.
    NameTy& name_get();
    /** \} */

  protected:
    NameTy* name_;
  };
} // namespace ast
#include <ast/object-exp.hxx>
