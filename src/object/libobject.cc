/**
 ** \file object/libobject.cc
 ** \brief Define exported object functions.
 */

// FIXME: Some code was deleted here.
#include <object/libobject.hh>
#include <bind/libbind.hh>

namespace object
{
  /*-------.
  | Bind.  |
  `-------*/

  // FIXME: Some code was deleted here.
  misc::error bind(const ast::ChunkList& tree)
  {
    return bind::bind(tree);
  }

} // namespace object
