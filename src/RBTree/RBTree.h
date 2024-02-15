
#ifndef CPP2_S21_CONTAINERS_1_SRC_RBTREE_RBTREE_H_
#define CPP2_S21_CONTAINERS_1_SRC_RBTREE_RBTREE_H_

#include <iostream>
#include <limits>

#include "RBTreeNode.h"

namespace s21{



template <typename K, typename T>
class ConstTreeIterator;

template <typename K, typename T>
class TreeIterator;

template <typename K, typename T>
class RBTree
{

public:
    RBTree();
    RBTree(const K &key, const T &value = T());
    RBTree(const K &key, const T &value, const Color &color);
    RBTree(const RBTree<K, T> &other);
    RBTree(RBTree<K, T> &&other);
    ~RBTree();

    RBTreeNode<K, T> *begin() const;
    RBTreeNode<K, T> *rbegin() const;
    RBTreeNode<K, T> *end() const;

    void swap(RBTree<K, T> &other);

    void CopyTree(const RBTree<K, T> &other);
    void MoveTree(RBTree<K, T> &&other);

    RBTreeNode<K, T> *InsertCheckBalance(RBTreeNode<K, T> *root_);
    RBTreeNode<K, T> *InsertBalancer1(RBTreeNode<K, T> *root_);
    RBTreeNode<K, T> *InsertBalancer2(RBTreeNode<K, T> *root_);

    std::pair<RBTreeNode<K, T> *, bool> insert(K key, T value, bool isMultiSet = false);

    void DeleteCheckBalance(RBTreeNode<K, T> *root_);
    void DeleteCheckBalanceLeft(RBTreeNode<K, T> *root_);
    void DeleteCheckBalanceRight(RBTreeNode<K, T> *root_);
    bool Delete(TreeIterator<K, T> iter);

    RBTreeNode<K, T> *GetFather(const RBTreeNode<K, T> *root_);
    RBTreeNode<K, T> *GetGrandFather(const RBTreeNode<K, T> *root_);
    RBTreeNode<K, T> *GetUncle(const RBTreeNode<K, T> *root_);
    RBTreeNode<K, T> *GetBrother(const RBTreeNode<K, T> *root_);

    RBTreeNode<K, T> *find_node(const K key);
    RBTreeNode<K, T> *find_insert_place(const K key, bool isMultiSet = false);

    void ReplaceFatherSun(RBTreeNode<K, T> *A, RBTreeNode<K, T> *B);

    bool IsValid(const RBTreeNode<K, T> *root_);
    void clear();
    void clean_tree(RBTreeNode<K, T> **root_);

    void Print();
    RBTreeNode<K, T> *getRoot() { return root; }

private:
    RBTreeNode<K, T> *root = nullptr;
    RBTreeNode<K, T> *NIL = nullptr;
};

template <typename K, typename T>
RBTree<K, T>::RBTree()
{
    root = new RBTreeNode<K, T>();
    NIL = new RBTreeNode<K, T>(BLACK);
}

template <typename K, typename T>
RBTree<K, T>::RBTree(const K &key, const T &value)
{
    root = new RBTreeNode<K, T>(key, value, BLACK);
    if (!NIL)
        NIL = new RBTreeNode<K, T>(BLACK);
    root->left = NIL;
    root->right = NIL;
}

template <typename K, typename T>
RBTree<K, T>::RBTree(const K &key, const T &value, const Color &color)
{
    root = new RBTreeNode<K, T>(key, value, color);
    NIL = new RBTreeNode<K, T>(BLACK);
    root->left = NIL;
    root->right = NIL;
}

template <typename K, typename T>
RBTree<K, T>::RBTree(const RBTree<K, T> &other)
{
    CopyTree(other);
}

template <typename K, typename T>
RBTree<K, T>::RBTree(RBTree<K, T> &&other)
{
    MoveTree(other);
}

template <typename K, typename T>
RBTree<K, T>::~RBTree()
{
    clean_tree(&root);
    if (NIL)
        delete NIL;
    NIL = nullptr;
}

template <typename K, typename T>
RBTreeNode<K, T> *RBTree<K, T>::begin() const
{
    return GetMin(root);
}

template <typename K, typename T>
RBTreeNode<K, T> *RBTree<K, T>::rbegin() const
{
    return GetMax(root);
}

template <typename K, typename T>
RBTreeNode<K, T> *RBTree<K, T>::end() const
{
    return nullptr;
}

template <typename K, typename T>
void RBTree<K, T>::swap(RBTree<K, T> &other)
{
    std::swap(root, other.root);
    std::swap(NIL, other.NIL);
}

template <typename K, typename T>
void RBTree<K, T>::CopyTree(const RBTree<K, T> &other)
{
    clean_tree(&(this->root));
    root = new RBTreeNode<K, T>(other.root->key, other.root->value, other.root->color);
    NIL = new RBTreeNode<K, T>(BLACK);
    root->left = NIL;
    root->right = NIL;
    for (TreeIterator iter = other.begin(); iter != other.end(); ++iter)
    {
        insert(iter.GetPtr()->GetKey(), *iter);
    }
}

template <typename K, typename T>
void RBTree<K, T>::MoveTree(RBTree<K, T> &&other)
{
    clean_tree(&root);
    clean_tree(&NIL);
    std::swap(root, other.root);
    std::swap(NIL, other.NIL);
}

//  ищет минимальный элемент ниже по дереву
template <typename K, typename T>
RBTreeNode<K, T> *GetMin(RBTreeNode<K, T> *root_)
{
    if (root_ == nullptr)
    {
        return nullptr;
    }
    while (root_ && !IsNil(root_->left))
        root_ = root_->left;
    return root_;
}

//  ищет максимальный элемент ниже по дереву
template <typename K, typename T>
RBTreeNode<K, T> *GetMax(RBTreeNode<K, T> *root_)
{
    if (root_ == nullptr)
    {
        return nullptr;
    }
    while (root_ && !IsNil(root_->right))
        root_ = root_->right;
    return root_;
}

template <typename K, typename T>
RBTreeNode<K, T> *RBTree<K, T>::GetFather(const RBTreeNode<K, T> *root_)
{
    return root_->father;
}

template <typename K, typename T>
RBTreeNode<K, T> *RBTree<K, T>::GetGrandFather(const RBTreeNode<K, T> *root_)
{
    if (GetFather(root_) == nullptr)
        return nullptr;
    return GetFather(GetFather(root_));
}

template <typename K, typename T>
RBTreeNode<K, T> *RBTree<K, T>::GetUncle(const RBTreeNode<K, T> *root_)
{
    if (GetGrandFather(root_) == nullptr)
        return nullptr;
    return (GetGrandFather(root_)->right) == (root_->father) ? (GetGrandFather(root_)->left) : (GetGrandFather(root_)->right);
}

template <typename K, typename T>
RBTreeNode<K, T> *RBTree<K, T>::GetBrother(const RBTreeNode<K, T> *root_)
{
    if (root_->father->left == NIL || root_->father->left == NIL)
    {
        return nullptr;
    }
    return (root_->father->left == root_) ? (root_->father->left) : (root_->father->right);
    // return root_;
}

template <typename K, typename T>
RBTreeNode<K, T> *RBTree<K, T>::InsertCheckBalance(RBTreeNode<K, T> *root_)
{

    if (root_->color == RED && GetFather(root_) != nullptr && GetFather(root_)->color == RED)
    {

        if (GetUncle(root_) != nullptr && GetUncle(root_)->color == RED)
        {
            root_ = InsertBalancer1(root_);
        }
        else if (GetUncle(root_) != nullptr && GetUncle(root_)->color == BLACK)
        {
            root_ = InsertBalancer2(root_);
        }
        if (root_ == root)
        {
            root_->color = BLACK;
        }
    }
    return root_;
}

template <typename K, typename T>
RBTreeNode<K, T> *RBTree<K, T>::InsertBalancer1(RBTreeNode<K, T> *root_)
{
    if (root_ == root)
    {
        root_->color = BLACK;
    }
    else
    {
        GetFather(root_)->color = BLACK;
        GetUncle(root_)->color = BLACK;
        GetGrandFather(root_)->color = RED;
        root_ = InsertCheckBalance(GetGrandFather(root_));
    }
    return root_;
}

template <typename K, typename T>
RBTreeNode<K, T> *RBTree<K, T>::InsertBalancer2(RBTreeNode<K, T> *root_)
{
    if (GetGrandFather(root_)->left == GetFather(root_))
    {
        if (GetFather(root_)->left == root_)
        {
            GetGrandFather(root_)->color = RED;
            GetFather(root_)->color = BLACK;
            ReplaceFatherSun(GetGrandFather(root_), GetFather(root_));
            root_ = GetFather(root_);
        }
        else
        {
            ReplaceFatherSun(GetFather(root_), root_);
            root_ = root_->left;
            root_ = InsertCheckBalance(root_);
        }
    }
    else if (GetGrandFather(root_)->right == GetFather(root_))
    {
        if (GetFather(root_)->right == root_)
        {
            GetGrandFather(root_)->color = RED;
            GetFather(root_)->color = BLACK;
            ReplaceFatherSun(GetGrandFather(root_), GetFather(root_));
            root_ = GetFather(root_);
        }
        else
        {
            ReplaceFatherSun(GetFather(root_), root_);
            root_ = root_->right;
            root_ = InsertCheckBalance(root_);
        }
    }
    return root_;
}

template <typename K, typename T>
std::pair<RBTreeNode<K, T> *, bool> RBTree<K, T>::insert(K key, T value, bool isMultiSet)
{
    RBTreeNode<K, T> *root_ = root;
    bool insertStatus = false;
    if (root_->father == nullptr && root_->left == nullptr && root_->right == nullptr)
    {
        root_->key = key;
        root_->value = value;
        root->left = NIL;
        root->right = NIL;
        insertStatus = true;
    }
    else
    {
        if ((root_ = find_insert_place(key, isMultiSet)) != NIL)
        {
            if (key < root_->GetKey())
            {
                            insertStatus = true;

                root_->left = new RBTreeNode<K, T>(key, value);
                root_->left->father = root_;
                root_->left->left = NIL;
                root_->left->right = NIL;
                root_ = root_->left;
            }
            else if (key > root_->GetKey() || (key == root_->GetKey() && isMultiSet))
            {
                            insertStatus = true;

                root_->right = new RBTreeNode<K, T>(key, value);
                root_->right->father = root_;
                root_->right->left = NIL;
                root_->right->right = NIL;
                root_ = root_->right;
            }
            InsertCheckBalance(root_);
            if (root->father != nullptr)
            {
                while (GetFather(root) != nullptr)
                {
                    root = GetFather(root);
                }
            }
        }
    }

    return std::make_pair(root_, insertStatus);
}

template <typename K, typename T>
void RBTree<K, T>::DeleteCheckBalance(RBTreeNode<K, T> *root_)
{
    if (IsValid(root_) && IsValid(root_->father))
    {
        if (root_->father->left == root_)
        {
            DeleteCheckBalanceLeft(root_);
        }
        else
        {
            DeleteCheckBalanceRight(root_);
        }
    }
}

// производит балансировку дерева если удаляемый элемент слева от родителя
template <typename K, typename T>
void RBTree<K, T>::DeleteCheckBalanceLeft(RBTreeNode<K, T> *root_)
{
    if (root_->color == BLACK)
    {
        if (IsValid(GetBrother(root_)) && GetBrother(root_)->color == RED)
        {
            root_->father->color = RED;
            GetBrother(root_)->color = BLACK;
            ReplaceFatherSun(root_->father, GetBrother(root_));
            DeleteCheckBalanceLeft(root_);
        }
        else if (IsValid(GetBrother(root_)) && GetBrother(root_)->color == BLACK)
        {
            if (IsValid(GetBrother(root_)->left) && GetBrother(root_)->left->color == BLACK && IsValid(GetBrother(root_)->right) && GetBrother(root_)->right->color == BLACK)
            {
                GetBrother(root_)->color = RED;
                root_->father->color = BLACK;
                DeleteCheckBalance(root_->father);
            }
            else if (IsValid(GetBrother(root_)->left) && GetBrother(root_)->left->color == RED && IsValid(GetBrother(root_)->right) && GetBrother(root_)->right->color == BLACK)
            {
                GetBrother(root_)->left->color = BLACK;
                GetBrother(root_)->color = RED;
                ReplaceFatherSun(GetBrother(root_), GetBrother(root_)->left);
                DeleteCheckBalanceLeft(root_);
            }
            else if (IsValid(GetBrother(root_)->right) && GetBrother(root_)->right->color == RED)
            {
                GetBrother(root_)->right->color = BLACK;
                GetBrother(root_)->color = root_->father->color;
                root_->father->color = BLACK;
                ReplaceFatherSun(root_->father, GetBrother(root_));
                DeleteCheckBalance(GetGrandFather(root_));
            }
        }
    }
}

// производит балансировку дерева если удаляемый элемент справа от родителя
template <typename K, typename T>
void RBTree<K, T>::DeleteCheckBalanceRight(RBTreeNode<K, T> *root_)
{
    if (root_->color == BLACK)
    {
        if (IsValid(GetBrother(root_)) && GetBrother(root_)->color == RED)
        {
            root_->father->color = RED;
            GetBrother(root_)->color = BLACK;
            ReplaceFatherSun(root_->father, GetBrother(root_));
            DeleteCheckBalanceRight(root_);
        }
        else if (IsValid(GetBrother(root_)) && GetBrother(root_)->color == BLACK)
        {
            if (IsValid(GetBrother(root_)->right) && GetBrother(root_)->right->color == BLACK && IsValid(GetBrother(root_)->left) && GetBrother(root_)->left->color == BLACK)
            {
                GetBrother(root_)->color = RED;
                root_->father->color = BLACK;
                DeleteCheckBalance(root_->father);
            }
            else if (IsValid(GetBrother(root_)->right) && GetBrother(root_)->right->color == RED && IsValid(GetBrother(root_)->left) && GetBrother(root_)->left->color == BLACK)
            {
                GetBrother(root_)->right->color = BLACK;
                GetBrother(root_)->color = RED;
                ReplaceFatherSun(GetBrother(root_), GetBrother(root_)->right);
                DeleteCheckBalanceRight(root_);
            }
            else if (IsValid(GetBrother(root_)->left) && GetBrother(root_)->left->color == RED)
            {
                GetBrother(root_)->left->color = BLACK;
                GetBrother(root_)->color = root_->father->color;
                root_->father->color = BLACK;
                ReplaceFatherSun(root_->father, GetBrother(root_));
                DeleteCheckBalance(GetGrandFather(root_));
            }
        }
    }
}

template <typename K, typename T>
bool RBTree<K, T>::Delete(TreeIterator<K, T> iter)
{
    bool res = false;
    RBTreeNode<K, T> *root_ = iter.GetPtr();
    if (root_ != nullptr)
    {
        if (root_->left == NIL && root_->right == NIL)
        {
            DeleteCheckBalance(root_);
            GetFather(root_)->left == root_ ? GetFather(root_)->left = NIL : GetFather(root_)->right = NIL;
            delete root_;
            res =true;
        }
        else if ((root_->left != NIL) ^ (root_->right != NIL))
        {
            DeleteCheckBalance(root_);
            if (root_->left != NIL)
            {
                root_->left->color = BLACK;
                GetFather(root_)->left == root_ ? GetFather(root_)->left = root_->left : GetFather(root_)->right = root_->left;
            }
            else
            {
                root_->right->color = BLACK;
                GetFather(root_)->left == root_ ? GetFather(root_)->left = root_->right : GetFather(root_)->right = root_->right;
            }
            delete root_;
            res = true;
        }
        else if (root_->left != NIL && root_->right != NIL)
        {
            RBTreeNode<K, T> *replace = root_->right;
            while (replace->left != NIL)
            {
                replace = replace->left;
            }
            K tmp_key = replace->key;
            T tmp_value = replace->value;
            res = Delete(replace);
            root_->key = tmp_key;
            root_->value = tmp_value;
        }
    }
    return res;
}

template <typename K, typename T>
RBTreeNode<K, T> *RBTree<K, T>::find_node(const K key)
{
    RBTreeNode<K, T> *root_ = find_insert_place(key);
    if (key != root_->GetKey())
    {
        root_ = nullptr;
    }
    return root_;
}

template <typename K, typename T>
RBTreeNode<K, T> *RBTree<K, T>::find_insert_place(const K key, bool isMultiSet)
{
    RBTreeNode<K, T> *root_ = root;
    while ((key < root_->GetKey() && root_->left != NIL) || (key > root_->GetKey() && root_->right != NIL) || ((key == root_->GetKey() && root_->right != NIL && isMultiSet)))
    {
        if (key < root_->GetKey())
        {
            root_ = root_->left;
        }
        else if (key > root_->GetKey() || ((key == root_->GetKey() && isMultiSet)))
        {
            root_ = root_->right;
        }
    }
    return root_;
}

//  меняет вершины местами, ставя на место отца его сына, отец становится сыном, изначально A это отец для B
template <typename K, typename T>
void RBTree<K, T>::ReplaceFatherSun(RBTreeNode<K, T> *A, RBTreeNode<K, T> *B)
{
    if (A->right == B)
    {
        A->right = B->left;
        if (B->left != NIL)
            B->left->father = A;
        B->father = A->father;
        if (B->father != nullptr)
            B->father->right == A ? B->father->right = B : B->father->left = B;
        A->father = B;
        B->left = A;
    }
    else if (A->left == B)
    {
        A->left = B->right;
        if (B->right != NIL)
            B->right->father = A;
        B->father = A->father;
        if (B->father != nullptr)
            B->father->right == A ? B->father->right = B : B->father->left = B;
        A->father = B;
        B->right = A;
    }
}

template <typename K, typename T>
bool RBTree<K, T>::IsValid(const RBTreeNode<K, T> *root_)
{
    if (root_ == nullptr || root_ == NIL)
    {
        return false;
    }
    return true;
}

template <typename K, typename T>
bool IsNil(RBTreeNode<K, T> *node)
{
    return node && !node->father && !node->right && !node->left && node->color == BLACK;
}

template <typename K, typename T>
void RBTree<K, T>::clear()
{
    clean_tree(&root);
}

template <typename K, typename T>
void RBTree<K, T>::clean_tree(RBTreeNode<K, T> **root_)
{
    if ((*root_) != nullptr)
    {
        if (IsValid((*root_)->left))
        {
            clean_tree(&((*root_)->left));
        }
        if (IsValid((*root_)->right))
        {
            clean_tree(&((*root_)->right));
        }
        delete *root_;
    }
    *root_ = nullptr;
}

template <typename K, typename T>
void RBTree<K, T>::Print()
{
    if (root)
    {
        root->Print(0, NIL);
    }
    else
    {
        std::cout << ANSI_BLACK << "nullptr" << ANSI_RESET;
    }
    std::cout << '\n';
}

template <typename K, typename T>
class ConstTreeIterator
{
public:
    ConstTreeIterator(RBTreeNode<K, T> *node) : ptr(node) {}

    friend class RBTree<K, T>;

    ConstTreeIterator<K, T> &operator++()
    {
        if (ptr != nullptr)
        {
            if (IsNil(ptr->right))
            {
                while (ptr->father != nullptr && ptr->father->right == ptr)
                    ptr = ptr->father;
                ptr = ptr->father;
            }
            else
            {
                ptr = GetMin(ptr->right);
            }
        }
        return *this;
    }

    ConstTreeIterator<K, T> &operator--()
    {
        if (ptr != nullptr)
        {
            if (IsNil(ptr->left))
            {
                while (ptr->father != nullptr && ptr->father->left == ptr)
                    ptr = ptr->father;
                ptr = ptr->father;
            }
            else
            {
                ptr = GetMax(ptr->left);
            }
        }
        return *this;
    }

    ConstTreeIterator<K, T> operator++(int)
    {
        ConstTreeIterator<K, T> copy = *this;
        ++(*this);
        return copy;
    }

    ConstTreeIterator<K, T> operator--(int)
    {
        ConstTreeIterator<K, T> copy = *this;
        --(*this);
        return copy;
    }

    RBTreeNode<K, T> *GetPtr()
    {
        return ptr;
    }

    bool operator==(const ConstTreeIterator<K, T> &other)
    {
        return ptr == other.ptr ? true : false;
    }

    bool operator!=(const ConstTreeIterator<K, T> &other)
    {
        return ptr == other.ptr ? false : true;
    }

    const T &operator*() const
    {
        if (ptr == nullptr)
        {
            static T zero = T();
            return zero;
        }
        else
        {
            return ptr->value;
        }
    }

protected:
    RBTreeNode<K, T> *ptr;
};

template <typename K, typename T>
class TreeIterator : public ConstTreeIterator<K, T>
{
public:
    TreeIterator(RBTreeNode<K, T> *node) : ConstTreeIterator<K, T>(node){};
    friend class RBTree<K, T>;

    T &operator*() const
    {
        return const_cast<T &>(ConstTreeIterator<K, T>::operator*());
    }

    TreeIterator &operator++()
    {
        ConstTreeIterator<K, T>::operator++();
        return *this;
    }

    TreeIterator &operator--()
    {
        ConstTreeIterator<K, T>::operator--();
        return *this;
    }

    TreeIterator operator++(int)
    {
        ConstTreeIterator<K, T>::operator++();
        return *this;
    }

    TreeIterator operator--(int)
    {
        ConstTreeIterator<K, T>::operator--();
        return *this;
    }
};

}  //  namespace s21

#endif // CPP2_S21_CONTAINERS_1_SRC_RBTREE_RBTREE_H_