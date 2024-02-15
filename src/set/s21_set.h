#ifndef CPP2_S21_CONTAINERS_1_SRC_SET_SET_H_
#define CPP2_S21_CONTAINERS_1_SRC_SET_SET_H_

#include <vector>

#include "../RBTree/RBTree.h"

namespace s21 {

template <typename K>
class set : public RBTree<K, K> {
 public:
  using key_type = K;
  using value_type = K;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = TreeIterator<K, K>;
  using const_iterator = ConstTreeIterator<K, K>;
  using size_type = size_t;

  using tree_type = RBTree<K, K>;

  set() : tree_type(){};
  set(std::initializer_list<value_type> const &items) {
    for (auto iter = items.begin(); iter < items.end(); ++iter) {
      insert((*iter));
    }
  }
  set(const set &s) : tree_type(s) { setSize = s.size(); }
  set(set &&s) {
    tree_type::MoveTree(std::move(s));
    setSize = 0;
    std::swap(this->setSize, s.setSize);
  }
  ~set(){};

  set<K> &operator=(const set &s) {
    tree_type::CopyTree(s);
    setSize = s.size();
    return *this;
  }
  set<K> &operator=(set &&s) {
    tree_type::MoveTree(std::move(s));
    std::swap(this->setSize, s.setSize);
    return *this;
  }

  iterator begin() { return tree_type::begin(); }
  iterator end() { return tree_type::end(); }

  bool empty() { return !setSize; }
  size_type size() const { return setSize; }
  size_type max_size() {
    return (std::numeric_limits<int>::max() * sizeof(int)) /
               sizeof(RBTreeNode<K, K>) / 2 -
           1000000;
  }

  void clear() {
    tree_type::clear();
    setSize = 0;
  }

  std::pair<iterator, bool> insert(const key_type &key) {
    std::pair<iterator, bool> res = RBTree<K, K>::insert(key, key);
    if (res.second) setSize++;
    return res;
  }

  void erase(iterator pos) {
    tree_type::Delete(pos.GetPtr());
    setSize--;
  }

  void swap(set<K> &other) {
    tree_type::swap(other);
    std::swap(setSize, other.setSize);
  }

  void merge(set<K> &other) {
    for (TreeIterator iter = other.begin(); iter != other.end(); ++iter) {
      insert(iter.GetPtr()->GetKey());
    }
  }

  iterator find(const K &key) { return tree_type::find_node(key); }

  bool contains(const K &key) { return tree_type::find_node(key); }

  template <typename... Args>
  std::vector<std::pair<TreeIterator<K, K>, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<s21::TreeIterator<K, K>, bool>> res;
    for (const auto &arg : {args...}) {
      res.push_back(insert(arg));
    }
    return res;
  }

 private:
  size_t setSize = 0;
};

}  //  namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_MULTIset_MULTISET_H_