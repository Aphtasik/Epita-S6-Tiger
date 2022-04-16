/**
 ** \file bind/tasks.cc
 ** \brief Bind module tasks implementation.
 */

// FIXME: Some code was deleted here.

#include <bind/libbind.hh>
#include <ast/libast.hh>
#include <misc/contract.hh>
#define DEFINE_TASKS 1
#include <bind/tasks.hh>
#undef DEFINE_TASKS
#include <ast/tasks.hh>
#include <bind/binder.hh>

namespace bind::tasks
{
  // The abstract syntax tree.
  //std::unique_ptr<ast::ChunkList> the_program(nullptr);

  void bind_ast()
  {
    precondition(ast::tasks::the_program);
    bind::bind(*ast::tasks::the_program);
  }

  void ast_bind_display()
  {
    precondition(ast::tasks::the_program);
    ast::bindings_display(std::cout) = true;
    std::cout << "/* == Abstract Syntax Bind Tree. == */\n"
              << *ast::tasks::the_program << std::endl;
  }

} // namespace bind::tasks
