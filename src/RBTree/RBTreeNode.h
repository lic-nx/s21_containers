#ifndef CPP2_S21_CONTAINERS_1_SRC_RBTREENODE_
#define CPP2_S21_CONTAINERS_1_SRC_RBTREENODE_

namespace s21{

enum Color
{
    RED,
    BLACK
};

const std::string ANSI_RED("\033[1;31m");
const std::string ANSI_BLACK("\033[1;34m");
const std::string ANSI_RESET("\033[0m");

template<typename K, typename T>
struct RBTreeNode
{
    K key;
    T value;
    Color color;
    RBTreeNode *father;
    RBTreeNode *left;
    RBTreeNode *right;

    K GetKey(){return key;}
    T GetValue() { return value; }

    RBTreeNode() : key(), value(), color(BLACK), father(nullptr), left(nullptr), right(nullptr) {};
    RBTreeNode(K key, T value, Color color = RED, RBTreeNode *father = nullptr, RBTreeNode *left = nullptr, RBTreeNode *right = nullptr) :
        key(key), value(value), color(color), father(father), left(left), right(right){};
    RBTreeNode(Color color) : key(), value(), color(color),  father(nullptr), left(nullptr), right(nullptr) {};
};

}  //  namespace s21

#endif // CPP2_S21_CONTAINERS_1_SRC_RBTREENODE_