#ifndef NODE_HPP
#define NODE_HPP

#include <SFML/Graphics.hpp>

class Node {
  public:
    explicit Node( const int key,
                   const sf::CircleShape value,
                   Node* const left,
                   Node* const right );
    sf::CircleShape getValue() const;
    int getKey() const;

    Node* left;
    Node* right;
    int height;

  private:
    int key;
    sf::CircleShape value;
};

#endif