/**
 ** \file misc/scoped-map.hh
 ** \brief Declaration of misc::scoped_map.
 **
 ** This implements a stack of dictionnaries.  Each time a scope is
 ** opened, a new dictionnary is added on the top of the stack; the
 ** dictionary is removed when the scope is closed.  Lookup of keys
 ** is done in the last added dictionnary first (LIFO).
 **
 ** In particular this class is used to implement symbol tables.
 **/

#pragma once

#include <map>
#include <ostream>
#include <stack>

namespace misc
{
  template <typename Key, typename Data> class scoped_map
  {
    // FIXME: Some code was deleted here.
  public:
    scoped_map(void);

    void put(const Key& key, const Data& data);

    Data get(const Key& key);

    std::ostream& dump(std::ostream& ostr) const;

    void scope_begin();

    void scope_end();

    size_t get_size() { return stack_.size(); }

  private:
    std::stack<std::map<Key, Data>> stack_;
  };

  template <typename Key, typename Data>
  std::ostream& operator<<(std::ostream& ostr,
                           const scoped_map<Key, Data>& tbl);

  // FIXME: Some code was deleted here.

} // namespace misc

#include <misc/scoped-map.hxx>
