#include "../../include/Tree.hpp"
#include "../../include/Config.hpp"
#include "../../include/FontManager.hpp"
#include <cstddef>
#include <cstdlib>

#define RADIUS 20

int compare( const int left, const int right );

int heightNode( Node* node );

Node* searchSmallerNode( Node* node );

Tree::Tree() {
    this->root = nullptr;
}

Tree::~Tree() {
    destroy( &( this->root ) );
}

void Tree::destroy( Node** node ) {
    if( *node != nullptr ) {
        destroy( &( *node )->left );
        destroy( &( *node )->right );
        delete( *node );
        node = nullptr;
    }
    return;
}

void Tree::insert( const int& key ) {
    sf::Vector2f position( WINDOW_WIDTH / 2 + (RADIUS)/2, RADIUS ); // 10 = Circle width/2
    insert( &( this->root ), key, position );
}

void Tree::insert( Node** node, const int& key, sf::Vector2f& position ) {
    if( *node == nullptr ) {
        sf::CircleShape circle;
        circle.setRadius(RADIUS);
        circle.setOutlineColor( sf::Color::Black );
        circle.setOutlineThickness( 3 );
        circle.setPosition( position.x - circle.getGlobalBounds().width,
                            position.y + RADIUS + circle.getGlobalBounds().height );
        *node = new Node( key, circle, nullptr, nullptr );
        return;
    } else if( key < ( *node )->getKey() ) {
        position.x -= ( *node )->getValue().getGlobalBounds().width / 2;
        position.y = ( *node )->getValue().getPosition().y;
        insert( &( ( *node )->left ), key, position );
        /* if( factor( *node ) >= 2 ) {
            if( key < ( *node )->left->getKey() ) {
                rotateRight( node );
            } else {
                doubleRotateRight( node );
            }
        } */
    } else if( key > ( *node )->getKey() ) {
        position.x += ( *node )->getValue().getGlobalBounds().width;
        position.y = ( *node )->getValue().getPosition().y;
        insert( &( ( *node )->right ), key, position );
        /* if( factor( *node ) >= 2 ) {
            if( key > ( *node )->right->getKey() ) {
                rotateLeft( node );
            } else {
                doubleRotateLeft( node );
            }
        } */
    } else {
        throw std::runtime_error( "Duplicate key" );
    }

    ( *node )->height =
        compare( heightNode( ( *node )->left ), heightNode( ( *node )->right ) ) + 1;
}

void Tree::remove( const int& key ) {
    remove( &( this->root ), key );
}

void Tree::remove( Node** node, const int& key ) {
    if( *node == nullptr ) {
        throw std::runtime_error( "Invalid key" );
    } else if( key < ( *node )->getKey() ) {
        remove( &( ( *node )->left ), key );
        if( factor( *node ) >= 2 ) {
            if( heightNode( ( *node )->right->left ) <= heightNode( ( *node )->right->right ) ) {
                rotateLeft( node );
            } else {
                doubleRotateLeft( node );
            }
        }
    } else if( key > ( *node )->getKey() ) {
        remove( &( ( *node )->right ), key );
        if( factor( *node ) >= 2 ) {
            if( heightNode( ( *node )->left->right ) <= heightNode( ( *node )->left->left ) ) {
                rotateRight( node );
            } else {
                doubleRotateRight( node );
            }
        }
    } else {
        if( ( *node )->left == nullptr || ( *node )->right == nullptr ) {
            Node* oldNode = ( *node );

            if( ( *node )->left != nullptr ) {
                *node = ( *node )->left;
            } else {
                *node = ( *node )->right;
            }
            delete oldNode;
        } else {
            Node* tmp     = searchSmallerNode( ( *node )->right );
            Node* oldNode = *node;

            ( *node ) = new Node( tmp->getKey(), tmp->getValue(), oldNode->left, oldNode->right );
            delete oldNode;

            remove( &( *node )->right, ( *node )->getKey() );
            if( factor( ( *node ) ) >= 2 ) {
                if( heightNode( ( *node )->left->right ) <= heightNode( ( *node )->left->left ) ) {
                    rotateRight( node );
                } else {
                    doubleRotateRight( node );
                }
            }
        }
    }
}

bool Tree::searchByKey( const int& key ) const {
    Node* node = this->root;

    while( node != nullptr && key != node->getKey() ) {
        if( key < node->getKey() ) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    return node != nullptr;
}

void Tree::rotateLeft( Node** root ) {
    Node* node       = ( *root )->right;
    ( *root )->right = node->left;

    node->left = *root;

    ( *root )->height =
        compare( heightNode( ( *root )->left ), heightNode( ( *root )->right ) ) + 1;
    node->height = compare( heightNode( node->right ), ( *root )->height ) + 1;

    *root = node;
}

void Tree::rotateRight( Node** root ) {
    Node* node      = ( *root )->left;
    ( *root )->left = node->right;

    node->right = *root;

    ( *root )->height =
        compare( heightNode( ( *root )->left ), heightNode( ( *root )->right ) ) + 1;
    node->height = compare( heightNode( node->left ), ( *root )->height ) + 1;

    *root = node;
}

void Tree::doubleRotateLeft( Node** root ) {
    if( *root == nullptr ) {
        return;
    }

    rotateRight( &( *root )->right );
    rotateLeft( root );
}

void Tree::doubleRotateRight( Node** root ) {
    if( *root == nullptr ) {
        return;
    }

    rotateLeft( &( *root )->left );
    rotateRight( root );
}

int Tree::factor( Node* node ) {
    return abs( heightNode( node->left ) - heightNode( node->right ) );
}

int compare( const int left, const int right ) {
    if( left > right ) {
        return left;
    } else {
        return right;
    }
}

int heightNode( Node* node ) {
    if( node == nullptr ) {
        return -1;
    } else {
        return node->height;
    }
}

Node* searchSmallerNode( Node* node ) {
    Node* tmp = node;
    while( tmp->left != nullptr ) {
        tmp = tmp->left;
    }

    return tmp;
}

void Tree::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
    if( root == nullptr ) {
        return;
    }

    drawNode( root, target, states );
}

void Tree::drawNode( Node* node, sf::RenderTarget& target, sf::RenderStates states ) const {
    if( node->left != nullptr ) {
        sf::Vertex line[ 2 ];
        line[ 0 ].position = sf::Vector2f(
            node->getValue().getGlobalBounds().left + node->getValue().getGlobalBounds().width / 2,
            node->getValue().getGlobalBounds().top + node->getValue().getGlobalBounds().height );
        line[ 1 ].position = sf::Vector2f( node->left->getValue().getGlobalBounds().left +
                                               node->left->getValue().getGlobalBounds().width / 2,
                                           node->left->getValue().getPosition().y );
        for( int i = 0; i < 2; i++ ) {
            line[ i ].color = sf::Color::Blue;
        }
        target.draw( line, 2, sf::PrimitiveType::Lines );

        drawNode( node->left, target, states );
    }

    if( node->right != nullptr ) {
        sf::Vertex line[ 2 ];
        line[ 0 ].position = sf::Vector2f(
         node->getValue().getPosition().x + node->getValue().getGlobalBounds().width / 2,
            node->getValue().getGlobalBounds().top + node->getValue().getGlobalBounds().height );
        line[ 1 ].position = sf::Vector2f( node->right->getValue().getGlobalBounds().left +
                                               node->right->getValue().getGlobalBounds().width / 2,
                                           node->right->getValue().getPosition().y );
        for( int i = 0; i < 2; i++ ) {
            line[ i ].color = sf::Color::Blue;
        }
        target.draw( line, 2, sf::PrimitiveType::Lines );

        drawNode( node->right, target, states );
    }

    sf::Text number( std::to_string( node->getKey() ), FontManager::get( "padrao" ) );
    number.setFillColor( sf::Color::Black );
    number.setPosition( node->getValue().getGlobalBounds().left +
                            number.getGlobalBounds().width / 2,
                        node->getValue().getPosition().y );
    target.draw( node->getValue(), states );
    target.draw( number, states );
}