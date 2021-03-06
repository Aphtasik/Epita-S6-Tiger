/**
 ** \file ast/let-exp.hh
 ** \brief Declaration of ast::LetExp.
 */

#pragma once

#include <ast/chunk-list.hh>
#include <ast/exp.hh>
#include <misc/contract.hh>

namespace ast
{
  /// LetExp.
  class LetExp : public Exp
  {
    // FIXME: Some code was deleted here.
  public:
    LetExp(const Location& location, ChunkList* dec, Exp* exp);
    virtual ~LetExp();
    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;
    const ChunkList& chunklist_get() const;
    ChunkList& chunklist_get();
    const Exp& exp_get() const;
    Exp& exp_get();

  protected:
    ChunkList* chunklist_;
    Exp* exp_;
  };
} // namespace ast
#include <ast/let-exp.hxx>
