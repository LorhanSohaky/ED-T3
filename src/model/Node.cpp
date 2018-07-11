#include "../../include/Node.hpp"

Node::Node( const int key, const sf::CircleShape value, Node* const left, Node* const right ) {
    this->key    = key;
    this->value  = value;
    this->left   = left;
    this->right  = right;
    this->height = 0;
}

sf::CircleShape& Node::getValue() {
    return this->value;
}

int Node::getKey() const {
    return this->key;
}