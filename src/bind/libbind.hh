/**
 ** \file bind/libbind.hh
 ** \brief Interface of the bind module.
 */

// FIXME: Some code was deleted here.

#pragma once

//#include <iosfwd>

//#include <misc/xalloc.hh>

#include <cassert>
#include <iostream>

#include <ast/chunk-list.hh>
#include <ast/libast.hh>
#include <parse/libparse.hh>

#include <ast/fwd.hh>

/// Ast management.
namespace bind
{
  //extern const misc::xalloc<bool> escapes_display;
  //extern const misc::xalloc<bool> bindings_display;

  /// Output \a a on \a ostr.
  //std::ostream& operator<<(std::ostream& ostr, const Ast& tree);

  /// Dump \a a on \a ostr.
  misc::error bind(const ast::ChunkList& tree);

} // namespace bind
