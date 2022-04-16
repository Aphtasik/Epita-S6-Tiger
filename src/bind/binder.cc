/**
 ** \file bind/binder.cc
 ** \brief Implementation for bind/binder.hh.
 */

#include <ast/all.hh>
#include <bind/binder.hh>

#include <misc/contract.hh>

namespace bind
{
  /*-----------------.
  | Error handling.  |
  `-----------------*/

  /// The error handler.
  const misc::error& Binder::error_get() const { return error_; }

  // FIXME: Some code was deleted here (Error reporting).

  void Binder::error(const ast::Ast& loc, const std::string& msg)
  {
    error_ << loc.location_get() << ": " << msg << "\n";
    //error_.exit_on_error();
  }

  template <typename T>
  void Binder::undeclared(const std::string& k, const T& e)
  {
    //vars_.dump(std::cout);
    auto msg = std::string("undeclared ") + k + " " + e.name_get().get();
    error(e, msg);
  }

  template <typename T> void Binder::redefinition(const T& e1, const T& e2)
  {
    auto msg = std::string("redefinition: ") + e1.name_get().get(); //BUG: .get may give a reference to the message
    error(e2, msg);
    error(e1, "first definition");
  }

  void Binder::check_main(const ast::FunctionDec& e)
  {
    // FIXME: Some code was deleted here.
    if (e.name_get() == misc::symbol("main")
        || e.name_get() == misc::symbol("_main"))
      {
        if (funs_.get_size() != 1)
          error_ << misc::error::error_type::bind;
      }
  }

  /*----------------.
  | Symbol tables.  |
  `----------------*/

  void Binder::scope_begin()
  {
    // FIXME: Some code was deleted here.
    vars_.scope_begin();
    funs_.scope_begin();
    types_.scope_begin();
  }

  void Binder::scope_end()
  {
    // FIXME: Some code was deleted here.
    vars_.scope_end();
    funs_.scope_end();
    types_.scope_end();
  }

  /*---------.
  | Visits.  |
  `---------*/

  // FIXME: Some code was deleted here.
  // Expressions

  void Binder::operator()(ast::LetExp& e)
  {
    // FIXME: Some code was deleted here.
    scope_begin();
    loops_.push(nullptr);
    for (auto& x : e.chunklist_get())
      {
        super_type::operator()(x);
      }
    loops_.pop();
    super_type::operator()(e.exp_get());
    scope_end();
  }

  // set the declaration attribute of simple var
  void Binder::operator()(ast::SimpleVar& e)
  {
    auto x = vars_.get(e.name_get());
    if (x)
      {
        e.def_set(x);
      }
    else
      {
        error_ << misc::error::error_type::bind;
        undeclared<ast::SimpleVar>("variable", e);
      }
  }

  // set the declaration attribute of call expression
  void Binder::operator()(ast::CallExp& e)
  {
    auto x = funs_.get(e.name_get());
    if (x)
      e.def_set(x);
    else
      {
        error_ << misc::error::error_type::bind;
        undeclared<ast::CallExp>("function", e);
      }
    for (auto ntm : e.exps_get())
      super_type::operator()(ntm);
  }

  void Binder::operator()(ast::NameTy& e)
  {
    auto x = types_.get(e.name_get());
    if (x)
      e.def_set(x);
    else
      {
        error_ << misc::error::error_type::bind;
        undeclared<ast::NameTy>("type", e);
      }
  }

  void Binder::operator()(ast::WhileExp& e)
  {
    super_type::operator()(e.test_get());
    loops_.push(&e);
    super_type::operator()(e.body_get());
    loops_.pop();
  }

  void Binder::operator()(ast::ForExp& e)
  {
    e.vardec_get().accept(*this);
    e.hi_get().accept(*this);
    loops_.push(&e);
    e.body_get().accept(*this);
    loops_.pop();
  }

  void Binder::operator()(ast::VarDec& e)
  {
    visit_dec_header(e);
    visit_dec_body(e);
  }

  void Binder::operator()(ast::BreakExp& e)
  {
    if (loops_.empty() || loops_.top() == nullptr)
      {
        error_ << misc::error::error_type::bind;
        error(e, "'break' outside any loop");
      }
    else
    {
      e.def_set(loops_.top());
    }
  }

  /*-------------------.
  | Visiting VarChunk. |
  `-------------------*/

  // FIXME: Some code was deleted here.

  void Binder::operator()(ast::VarChunk& e)
  {
    chunk_visit(e);
  }

  /*------------------------.
  | Visiting FunctionChunk. |
  `------------------------*/

  // FIXME: Some code was deleted here.

  void Binder::operator()(ast::FunctionChunk& e) { chunk_visit(e); }

  /*--------------------.
  | Visiting TypeChunk. |
  `--------------------*/
  // FIXME: Some code was deleted here.

  void Binder::operator()(ast::TypeChunk& e) { chunk_visit(e); }

} // namespace bind
