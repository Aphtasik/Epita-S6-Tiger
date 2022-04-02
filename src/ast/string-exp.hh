/**
 ** \file ast/string-exp.hh
 ** \brief Declaration of ast::StringExp.
 */

#pragma once

#include <string>
#include <ast/exp.hh>

namespace ast
{
  /// StringExp.
  class StringExp : public Exp
  {
    // FIXME: Some code was deleted here.
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a StringExp node.
    StringExp(const Location& location, std::string name);
    StringExp(const StringExp&) = delete;
    StringExp& operator=(const StringExp&) = delete;
    /// Destroy a StringExp node.
    ~StringExp() override;
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    /** \name Accessors.
     ** \{ */
    /// Return exit condition of the loop.
    const std::string name_get() const;
    /// Return exit condition of the loop.
    std::string name_get();

  protected:
    /// Exit condition of the loop.
    std::string name_;
  };
} // namespace ast
#include <ast/string-exp.hxx>
