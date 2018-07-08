#ifndef TREE_HPP
#define TREE_HPP

#include "Node.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class Tree : public sf::Drawable {
  public:
    explicit Tree();
    ~Tree();

    void insert( const int& key );
    void remove( const int& key );

    bool searchByKey( const int& key ) const;

    void draw( sf::RenderTarget& target, sf::RenderStates states ) const;

  private:
    Node* root;

    void destroy( Node** node );

    void insert( Node** node, const int& key, sf::Vector2f& position );
    void remove( Node** node, const int& key );

    int factor( Node* node );

    void rotateLeft( Node** root );
    void rotateRight( Node** root );

    void doubleRotateLeft( Node** root );
    void doubleRotateRight( Node** root );

    void drawNode( Node* node, sf::RenderTarget& target, sf::RenderStates states ) const;
};

#endif