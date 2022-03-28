/**
 ** \file ast/if-exp.hh
 ** \brief Declaration of ast::IfExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/seq-exp.hh>

namespace ast
{
  /// IfExp.
  class IfExp : public Exp
  {
    // FIXME: Some code was deleted here.
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a IfExp node.
    IfExp(const Location& location,
          Exp* test,
          Exp* thenclause,
          Exp* elseclause);
    IfExp(const IfExp&) = delete;
    IfExp& operator=(const IfExp&) = delete;
    /// Destroy a IfExp node.
    ~IfExp() override;
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
    const Exp& test_get() const;
    /// Return exit condition of the loop.
    Exp& test_get();
    /// Return instructions executed in the loop.
    const Exp& thenclause_get() const;
    /// Return instructions executed in the loop.
    Exp& thenclause_get();
    /// Return instructions executed in the loop.
    const Exp& elseclause_get() const;
    /// Return instructions executed in the loop.
    Exp& elseclause_get();

  protected:
    /// Exit condition of the loop.
    Exp* test_;
    /// Instructions executed in the loop.
    Exp* thenclause_;
    Exp* elseclause_;
  };
} // namespace ast
#include <ast/if-exp.hxx>
