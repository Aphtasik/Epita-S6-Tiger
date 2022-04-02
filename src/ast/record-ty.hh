/**
 ** \file ast/record-ty.hh
 ** \brief Declaration of ast::RecordTy.
 */

#pragma once

#include <ast/field.hh>
#include <ast/ty.hh>

namespace ast
{
  /// RecordTy.
  class RecordTy : public Ty
  {
    // FIXME: Some code was deleted here.
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a RecordTy node.
    RecordTy(const Location& location, fields_type* field);
    RecordTy(const RecordTy&) = delete;
    RecordTy& operator=(const RecordTy&) = delete;
    /// Destroy a RecordTy node.
    ~RecordTy() override;
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
    const fields_type& field_get() const;
    /// Return exit condition of the loop.
    fields_type& field_get();

  protected:
    fields_type* field_;
  };
} // namespace ast
#include <ast/record-ty.hxx>
