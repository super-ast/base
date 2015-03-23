#pragma once

#include <map>
#include "node.hpp"

namespace super_ast {

template <typename T>
class NodeMap {
public:
  typedef typename std::map<unsigned int, T>::iterator iterator;
  typedef typename std::map<unsigned int, T>::const_iterator const_iterator;

  T& operator[](unsigned int id) {
    return map_[id];
  }

  T& operator[](const Node* node) {
    return map_[node->id()];
  }

  bool empty() const {
    return map_.empty();
  }

  unsigned long size() const {
    return map_.size();
  }

  iterator find(const Node* node) {
    return map_.find(node->id());
  }

  const_iterator find(const Node* node) const {
    return map_.find(node->id());
  }

  iterator begin() {
    return map_.begin();
  }

  const_iterator begin() const {
    return map_.begin();
  }

  iterator end() {
    return map_.end();
  }

  const_iterator end() const {
    return map_.end();
  }

private:
  std::map<unsigned int, T> map_;
};
}
