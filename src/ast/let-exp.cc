/**
 ** \file ast/let-exp.cc
 ** \brief Implementation of ast::LetExp.
 */

#include <ast/let-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  LetExp::LetExp(const Location& location, ChunkList* chunklist, Exp* exp)
    : Exp(Location)
    , chunklist_(chuncklist)
    , exp_(exp)
  {}

  LetExp::~LetExp()
  {
    delete chunklist_;
    delete exp_;
  }

  void LetExp::accept(ConstVisitor& v) const { v(*this); }

  void LetExp::accept(Visitor& v) { v(*this); }
} // namespace ast
