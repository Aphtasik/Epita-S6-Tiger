/**
 ** \file bind/libbind.cc
 ** \brief Define exported bind functions.
 */

// FIXME: Some code was deleted here.

//#include <fstream>

//#include <ast/dumper-dot.hh>
#include <ast/libast.hh>
#include <bind/binder.hh>
//#include <ast/pretty-printer.hh>

// Define exported ast functions.
namespace bind
{
  // Making the following variables const is more than merely
  // stylistic.  If they were not, Swig will create set/get for them,
  // and there is no set (operator=), since it has a const member.

  /// xalloc slot to enable escapes display in Ast display.
  //const misc::xalloc<bool> escapes_display;
  /// xalloc slot to enable bindings display in Ast display.
  //const misc::xalloc<bool> bindings_display;

  /*// Print the TREE on OSTR.
  std::ostream& operator<<(std::ostream& ostr, const Ast& tree)
  {
    PrettyPrinter print(ostr);
    print(tree);
    return ostr;
  }*/

  /// Dump \a a on \a ostr.
  misc::error bind(const ast::ChunkList& tree)
  {
    Binder bindeu = Binder();
    for (auto chunk : tree)
      {
        bindeu(chunk);
      }
    if (bindeu.error_get())
      bindeu.error_get().exit_on_error();
    return bindeu.error_get();
  }

} // namespace bind