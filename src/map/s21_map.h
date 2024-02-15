#ifndef CPP2_S21_CONTAINERS_1_SRC_MAP_MAP_H_
#define CPP2_S21_CONTAINERS_1_SRC_MAP_MAP_H_

#include <vector>

#include "../RBTree/RBTree.h"

namespace s21 {

template <typename K, typename M>
class map : public RBTree<K, M> {
 public:
  using key_type = K;
  using mapped_type = M;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = TreeIterator<K, M>;
  using const_iterator = ConstTreeIterator<K, M>;
  using size_type = size_t;

  using tree_type = RBTree<K, M>;

  map() : tree_type(){};
  map(std::initializer_list<std::pair<const key_type, mapped_type>> const
          &items) {
    for (auto iter = items.begin(); iter < items.end(); ++iter) {
      insert((*iter).first, (*iter).second);
    }
  }
  map(const map &m) : tree_type(m) { MapSize = m.size(); }
  map(map &&m) {
    tree_type::MoveTree(std::move(m));
    MapSize = 0;
    std::swap(this->MapSize, m.MapSize);
  }
  ~map() {}

  map<K, M> &operator=(const map &m) {
    tree_type::CopyTree(m);
    MapSize = m.size();
    return *this;
  }
  map<K, M> &operator=(map &&m) {
    tree_type::MoveTree(std::move(m));
    std::swap(this->MapSize, m.MapSize);
    return *this;
  }

  M &at(const K &key) { return (tree_type::find_node(key)->value); }

  M &operator[](const K &key) {
    RBTreeNode<K, M> *root_ = tree_type::find_node(key);
    if (root_ == nullptr ||
        (root_ == tree_type::getRoot() && root_->left == nullptr &&
         root_->right == nullptr)) {
      root_ = tree_type::find_insert_place(key);
      M tmp = M();
      root_ = insert(key, tmp).first.GetPtr();
    }
    return root_->value;
  }

  iterator begin() { return tree_type::begin(); }

  iterator rbegin() { return tree_type::rbegin(); }
  iterator end() { return tree_type::end(); }

  bool empty() { return !MapSize; }
  size_type size() const { return MapSize; }
  size_type max_size() {
    return (std::numeric_limits<int>::max() * sizeof(int)) /
               sizeof(RBTreeNode<K, M>) / 2 -
           1000000;
  }

  void clear() {
    tree_type::clear();
    MapSize = 0;
  }

  // RBTreeNode<K, M> *GetRoot() { return this->root; }

  std::pair<iterator, bool> insert(const value_type &value) {
    return insert(value.first, value.second);
  }

  std::pair<iterator, bool> insert(const key_type &key,
                                   const mapped_type &obj) {
    std::pair<iterator, bool> res = RBTree<K, M>::insert(key, obj);
    if (res.second) MapSize++;
    return res;
  }

  std::pair<iterator, bool> insert_or_assign(const K &key, const M &obj) {
    RBTreeNode<K, M> *node = tree_type::find_node(key);
    if (node == nullptr) {
      return insert(key, obj);
    } else {
      node->value = obj;
      return std::make_pair(node, false);
    }
  }

  void erase(iterator pos) {
    if (tree_type::Delete(pos.GetPtr())) MapSize--;
  }

  void swap(map<K, M> &other) {
    tree_type::swap(other);
    std::swap(MapSize, other.MapSize);
  }

  void merge(map<K, M> &other) {
    for (TreeIterator iter = other.begin(); iter != other.end(); ++iter) {
      insert(iter.GetPtr()->GetKey(), iter.GetPtr()->GetValue());
    }
  }

  bool contains(const K &key) { return tree_type::find_node(key); }

  template <typename... Args>
  std::vector<std::pair<TreeIterator<K, M>, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<s21::TreeIterator<K, M>, bool>> res;
    for (const auto &arg : {args...}) {
      res.push_back(insert((arg).first, (arg).second));
    }
    return res;
  }

 private:
  size_type MapSize = 0;
};

}  //  namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_MAP_MAP_H_