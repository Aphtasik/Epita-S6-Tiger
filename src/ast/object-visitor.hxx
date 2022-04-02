/**
 ** \file ast/object-visitor.hxx
 ** \brief Implementation for ast/object-visitor.hh.
 */

#pragma once

#include <ast/all.hh>
#include <ast/object-visitor.hh>
#include <misc/contract.hh>

namespace ast
{
  template <template <typename> class Const>
  GenObjectVisitor<Const>::GenObjectVisitor()
    : GenVisitor<Const>()
  {}

  template <template <typename> class Const>
  GenObjectVisitor<Const>::~GenObjectVisitor()
  {}

  /*-------------------------------.
  | Object-related visit methods.  |
  `-------------------------------*/

  template <template <typename> class Const>
  void GenObjectVisitor<Const>::operator()(const_t<ClassTy>& e)
  {
    // FIXME: Some code was deleted here. DONE
      e.chunks_get().accept(*this);
      e.super_get().accept(*this);
  }

  template <template <typename> class Const>
  void GenObjectVisitor<Const>::operator()(const_t<MethodChunk>& e)
  {
    // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void GenObjectVisitor<Const>::operator()(const_t<MethodDec>& e)
  {
    // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void GenObjectVisitor<Const>::operator()(const_t<MethodCallExp>& e)
  {
    // FIXME: Some code was deleted here. DONE
      e.object_get().accept(*this);
  }

  template <template <typename> class Const>
  void GenObjectVisitor<Const>::operator()(const_t<ObjectExp>& e)
  {
    // FIXME: Some code was deleted here. DONE
      e.name_get().accept(*this);
  }

} // namespace ast
