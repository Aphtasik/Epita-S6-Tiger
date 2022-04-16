/**
 ** \file bind/binder.hxx
 ** \brief Inline methods of bind::Binder.
 **/

#pragma once

#include <bind/binder.hh>

namespace bind
{
  /*-----------------.
  | Error handling.  |
  `-----------------*/

  // FIXME: Some code was deleted here (Error reporting).

  /*----------------------------.
  | Visiting /ChunkInterface/.  |
  `----------------------------*/

  template <class D> void Binder::chunk_visit(ast::Chunk<D>& e)
  {
    // Shorthand.
    using chunk_type = ast::Chunk<D>;
    // FIXME: Some code was deleted here (Two passes: once on headers, then on bodies).
    for (auto& d : e.decs_get())
      {
        visit_dec_header(*d);
      }
    for (auto& d : e.decs_get())
      {
        visit_dec_body(*d);
      }
  }

  /* These specializations are in bind/binder.hxx, so that derived
     visitors can use them (otherwise, they wouldn't see them).  */

  // FIXME: Some code was deleted here.

  template <> inline void Binder::visit_dec_header(ast::FunctionDec& d)
  {
    check_main(d);
    if (auto elt = funs_.get(d.name_get()))
      {
        error_ << misc::error::error_type::bind;
        redefinition<ast::FunctionDec>(*elt, d);
        return;
      }
    funs_.put(d.name_get(), &d);
  }

  template <> inline void Binder::visit_dec_header(ast::TypeDec& d)
  {
    if (auto elt = types_.get(d.name_get()))
      {
        error_ << misc::error::error_type::bind;
        redefinition<ast::TypeDec>(*elt, d);
        return;
      }
    types_.put(d.name_get(), &d);
  }

  template <> inline void Binder::visit_dec_header(ast::VarDec& d)
  {
    if (auto elt = vars_.get(d.name_get())) //BUG: have to uncomment this and make it work
      {
        error_ << misc::error::error_type::bind;
        redefinition<ast::VarDec>(*elt, d);
        return;
      }
    vars_.put(d.name_get(), &d);
  }

  template <> inline void Binder::visit_dec_body(ast::FunctionDec& d)
  {
    if (d.body_get() == nullptr)
        return;
    scope_begin();
    for (auto& p : d.formals_get())
      {
        if (auto elt = vars_.get(p->name_get()))
          {
            error_ << misc::error::error_type::bind;
            redefinition<ast::VarDec>(*elt, *p);
            return;
          }
        vars_.put(p->name_get(), p);
      }
    super_type::operator()(d.body_get());
    scope_end();
  }

  template <> inline void Binder::visit_dec_body(ast::VarDec& d)
  {
    scope_begin();
    super_type::operator()(d.init_get()); // this is sufficient to call the visitor of VarDec
    scope_end();
  }

  template <> inline void Binder::visit_dec_body(ast::TypeDec& d)
  {
    scope_begin();
    super_type::operator()(d.ty_get());
    scope_end();
  }

} // namespace bind
