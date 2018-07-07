#ifndef NODE_HPP
#define NODE_HPP

template < class T >
class Node {
  public:
    explicit Node( const int key, const T value, Node* const left, Node* const right );
    T getValue() const;
    int getKey() const;

    Node* left;
    Node* right;
    int height;

  private:
    int key;
    T value;
};

#include "../src/model/Node.cpp"

#endif