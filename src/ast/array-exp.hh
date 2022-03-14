/**
 ** \file ast/array-exp.hh
 ** \brief Declaration of ast::ArrayExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// ArrayExp.
  class ArrayExp : public Exp
  {
    // FIXME: Some code was deleted here.
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a ArrayExp node.
    ArrayExp(const Location& location, NameTy* arr_type, Exp* arr_length, Exp* arr_val);
    ArrayExp(const ArrayExp&) = delete;
    ArrayExp& operator=(const ArrayExp&) = delete;
    /// Destroy a ArrayExp node.
    ~ArrayExp() override;
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
    const Exp& body_get() const;
    /// Return instructions executed in the loop.
    Exp& body_get();
    /** \} */

  protected:
    NameTy* arr_type_;
    Exp* arr_length_;
    Exp* arr_val_;
  };
} // namespace ast
#include <ast/array-exp.hxx>
