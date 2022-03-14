/**
 ** \file ast/assign-exp.hh
 ** \brief Declaration of ast::AssignExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/var.hh>

namespace ast
{
  /// AssignExp.
  class AssignExp : public Exp
  {
    // FIXME: Some code was deleted here.
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a AssignExp node.
    AssignExp(const Location& location, Var* var , Exp* exp);
    AssignExp(const AssignExp&) = delete;
    AssignExp& operator=(const AssignExp&) = delete;
    /// Destroy a AssignExp node.
    ~AssignExp() override;
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    /** \name Accessors.
     ** \{ */
    /// Return exit condition of the loop.
    const Var& var_get() const;
    /// Return exit condition of the loop.
    Var& var_get();
    /// Return instructions executed in the loop.
    const Exp& exp_get() const;
    /// Return instructions executed in the loop.
    Var& exp_get();
    /** \} */

  protected:
    /// Exit condition of the loop.
    Var* var_;
    /// Instructions executed in the loop.
    Exp* exp_;
  };
} // namespace ast
#include <ast/assign-exp.hxx>
