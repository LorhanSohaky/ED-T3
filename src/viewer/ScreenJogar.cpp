#include "../../include/ScreenJogar.hpp"
#include "../../include/TextureManager.hpp"
#include <iostream>

ScreenJogar::ScreenJogar( GameRef& gameRef )
    : Screen( gameRef ) {
    loadAssets();
}

void ScreenJogar::loadAssets() {
}
void ScreenJogar::draw() {
    window->clear( sf::Color::White );

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
