#include "../../include/ScreenJogar.hpp"
#include "../../include/Config.hpp"
#include "../../include/TextureManager.hpp"

ScreenJogar::ScreenJogar( GameRef& gameRef )
    : Screen( gameRef ) {
    loadAssets();

    int array[] = {1024, 512, 256, 128, 64, 32, 16, 8, 4, 2};
    for( int i = 0; i < 10; i++ ) {
        tree.insert( array[ i ] );
    }
}

void ScreenJogar::loadAssets() {
}
void ScreenJogar::draw() {
    window->clear( sf::Color::White );

    window->draw( tree );

    window->display();
}
void ScreenJogar::update() {
    while( window->pollEvent( *event ) ) {
        if( event->type == sf::Event::Closed ) {
            window->close();
        }
    }

    draw();
}
