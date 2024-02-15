#ifndef CPP2_S21_CONTAINERS_1_SRC_MULTISET_MULTISET_H_
#define CPP2_S21_CONTAINERS_1_SRC_MULTISET_MULTISET_H_

#include <vector>

#include "../RBTree/RBTree.h"

namespace s21 {

template <typename K>
class multiset : public RBTree<K, K> {
 public:
  using key_type = K;
  using value_type = K;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = TreeIterator<K, K>;
  using const_iterator = ConstTreeIterator<K, K>;
  using size_type = size_t;

  using tree_type = RBTree<K, K>;

  multiset() : tree_type(){};

  multiset(std::initializer_list<value_type> const &items) {
    for (auto iter = items.begin(); iter < items.end(); ++iter) {
      insert((*iter));
    }
  }
  multiset(const multiset &s) : tree_type(s) { MultiSetSize = s.size(); }
  multiset(multiset &&s) {
    tree_type::MoveTree(std::move(s));
    MultiSetSize = 0;
    std::swap(this->MultiSetSize, s.MultiSetSize);
  }
  ~multiset(){};

  multiset<K> &operator=(const multiset &s) {
    tree_type::CopyTree(s);
    MultiSetSize = s.size();
    return *this;
  }
  multiset<K> &operator=(multiset &&s) {
    tree_type::MoveTree(std::move(s));
    std::swap(this->MultiSetSize, s.MultiSetSize);
    return *this;
  }

  iterator begin() { return tree_type::begin(); }
  iterator end() { return tree_type::end(); }

  bool empty() { return !MultiSetSize; }
  size_type size() const { return MultiSetSize; }
  size_type max_size() {
    return (std::numeric_limits<int>::max() * sizeof(int)) /
               sizeof(RBTreeNode<K, K>) / 2 -
           1000000;
  }

  void clear() {
    tree_type::clear();
    MultiSetSize = 0;
  }

  std::pair<iterator, bool> insert(const key_type &key) {
    std::pair<iterator, bool> res = RBTree<K, K>::insert(key, key, true);
    if (res.second) MultiSetSize++;
    return res;
  }

  void erase(iterator pos) { tree_type::Delete(pos); }

  void swap(multiset<K> &other) {
    tree_type::swap(other);
    std::swap(MultiSetSize, other.MultiSetSize);
  }

  void merge(multiset<K> &other) {
    for (TreeIterator iter = other.begin(); iter != other.end(); ++iter) {
      insert(iter.GetPtr()->GetKey());
    }
  }

  size_type count(const K &key) {
    size_type count_node = 0;
    for (TreeIterator iter = begin(); iter != end(); ++iter) {
      if (*iter == key) count_node++;
    }
    return count_node;
  }

  iterator find(const K &key) { return tree_type::find_node(key); }

  bool contains(const K &key) { return tree_type::find_node(key); }

  std::pair<iterator, iterator> equal_range(const key_type &key) {
    RBTreeNode<K, K> *nowElement = tree_type::getRoot();
    RBTreeNode<K, K> *startIterator = nullptr;
    RBTreeNode<K, K> *endIterator = nullptr;

    while (nowElement != nullptr) {
      const K &nodeKey = nowElement->GetKey();
      if (key > nodeKey) {
        nowElement = nowElement->right;
      } else {
        if (endIterator == nullptr && key < nodeKey) {
          endIterator = nowElement;
        }
        startIterator = nowElement;
        nowElement = nowElement->left;
      }
    }
    if (endIterator == nullptr)
      nowElement = tree_type::getRoot();
    else
      nowElement = endIterator->left;
    while (nowElement != nullptr) {
      if (key < nowElement->GetKey()) {
        endIterator = nowElement;
        nowElement = nowElement->left;
      } else {
        nowElement = nowElement->right;
      }
    }

    return std::pair<iterator, iterator>(iterator(startIterator),
                                         iterator(endIterator));
  }

  iterator lower_bound(const key_type &key) { return equal_range(key).first; }

  iterator upper_bound(const key_type &key) { return equal_range(key).second; }

  template <typename... Args>
  std::vector<std::pair<TreeIterator<K, K>, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<s21::TreeIterator<K, K>, bool>> res;
    for (const auto &arg : {args...}) {
      res.push_back(insert(arg));
    }
    return res;
  }

 private:
  size_t MultiSetSize = 0;
};

}  //  namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_MULTISET_MULTISET_H_
