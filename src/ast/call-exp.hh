/**
 ** \file ast/call-exp.hh
 ** \brief Declaration of ast::CallExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/function-dec.hh>
#include <misc/symbol.hh>

namespace ast
{
  /// CallExp.
  class CallExp : public Exp
  {
    // FIXME: Some code was deleted here.
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a CallExp node.
    CallExp(const Location& location, misc::symbol name, exps_type* exps);
    CallExp(const CallExp&) = delete;
    CallExp& operator=(const CallExp&) = delete;
    /// Destroy a CallExp node.
    ~CallExp() override;
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}
    /// Return instructions executed in the loop.
    const exps_type& exps_get() const;
    /// Return instructions executed in the loop.
    exps_type& exps_get();
    /** \} */

    const misc::symbol name_get() const;
    /// Return instructions executed in the loop.
    misc::symbol name_get();

  protected:
    misc::symbol name_;
    exps_type *exps_;
  };
} // namespace ast
#include <ast/call-exp.hxx>
