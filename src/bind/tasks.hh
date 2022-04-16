/**
 ** \file bind/tasks.hh
 ** \brief Bind module related tasks.
 */

// FIXME: Some code was deleted here.

#pragma once

#include <ast/chunk-list.hh>
#include <task/libtask.hh>
#include <bind/libbind.hh>

namespace bind::tasks
{
  /// Global root node of abstract syntax tree.
  //extern std::unique_ptr<ast::ChunkList> the_program;

  void bind_ast();
  void ast_bind_display();

  TASK_GROUP("3. Binding");

  /// Display the abstract syntax tree.
  TASK_DECLARE("b|bindings-compute", "bind the AST", bind_ast, "parse");

  /// Display the abstract syntax tree using a dumper.
  TASK_DECLARE("B|bindings-display",
               "print the bind AST",
               ast_bind_display,
               "bindings-compute");

} // namespace bind::tasks
