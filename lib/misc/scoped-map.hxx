/** \file misc/scoped-map.hxx
 ** \brief Implementation of misc::scoped_map.
 */

#pragma once

#include <sstream>
#include <stdexcept>
#include <type_traits>

#include <misc/algorithm.hh>
#include <misc/contract.hh>
#include <misc/indent.hh>
#include <range/v3/view/reverse.hpp>

#include "scoped-map.hh"

namespace misc
{
  // FIXME: Some code was deleted here.

  template <typename Key, typename Data> scoped_map<Key, Data>::scoped_map(void)
  {
    std::map<Key, Data> p;
    stack_.push(p);
  }

  template <typename Key, typename Data>
  void scoped_map<Key, Data>::put(const Key& key, const Data& data)
  {
    if (stack_.top().contains(key))
        stack_.top().at(key) = data;
    else
        stack_.top().insert(std::make_pair(key, data));
  }

  template <typename Key, typename Data>
  Data scoped_map<Key, Data>::get(const Key& key)
  {
    for (auto it = stack_.top().rbegin(); it != stack_.top().rend(); ++it)
      if (it->first == key)
        return it->second;
    if constexpr (std::is_pointer<Data>::value)
      return nullptr;
    throw std::range_error("Key not found");
  }

  template <typename Key, typename Data>
  std::ostream& scoped_map<Key, Data>::dump(std::ostream& ostr) const
  {
    for (auto it = stack_.top().rbegin(); it != stack_.top().rend(); ++it)
      ostr << it->first << " -> " << it->second << "\n";
    return ostr;
  }

  template <typename Key, typename Data>
  void scoped_map<Key, Data>::scope_begin()
  {
    std::map<Key, Data> m = stack_.top();
    stack_.push(m);
  }

  template <typename Key, typename Data> void scoped_map<Key, Data>::scope_end()
  {
    stack_.pop();
  }

  template <typename Key, typename Data>
  inline std::ostream& operator<<(std::ostream& ostr,
                                  const scoped_map<Key, Data>& tbl)
  {
    return tbl.dump(ostr);
  }

} // namespace misc
