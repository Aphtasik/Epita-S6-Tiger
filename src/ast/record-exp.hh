/**
 ** \file ast/record-exp.hh
 ** \brief Declaration of ast::RecordExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/field-init.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// RecordExp.
  class RecordExp : public Exp
  {
    // FIXME: Some code was deleted here.
  public:
    /** \name Ctor & dtor.
 ** \{ */
    /// Construct a RecordExp node.
    RecordExp(const Location& location, NameTy* rec, fieldinits_type *vec);
    RecordExp(const RecordExp&) = delete;
    RecordExp& operator=(const RecordExp&) = delete;
    /// Destroy a RecordExp node.
    ~RecordExp() override;
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    /// Return instructions executed in the loop.
    const NameTy& rec_get() const;
    /// Return instructions executed in the loop.
    NameTy& rec_get();
    /** \} */

    const fieldinits_type vec_get() const;
    /// Return instructions executed in the loop.
    fieldinits_type vec_get();


  protected:
    NameTy* rec_;
    fieldinits_type *vec_;
  };
} // namespace ast
#include <ast/record-exp.hxx>
