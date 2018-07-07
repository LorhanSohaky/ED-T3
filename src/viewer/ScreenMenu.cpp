#include "../../include/ScreenMenu.hpp"
#include "../../include/TextureManager.hpp"
#include <iostream>

ScreenMenu::ScreenMenu( GameRef& gameRef )
    : Screen( gameRef ) {
    loadAssets();
}

void ScreenMenu::loadAssets() {
    TextureManager::add( "menu", "menu.png" );
    background.setTexture( TextureManager::get( "menu" ) );

    TextureManager::add( "btnPlay", "btnJogar.png", true );
    TextureManager::add( "btnPlayOn", "btnJogarOn.png", true );
    btnPlay.setTexture( TextureManager::get( "btnPlay" ) );
    btnPlay.setPosition( 500, 250 );
    btnPlay.setScale( 0.5, 0.5 );

    TextureManager::add( "btnAbout", "btnSobre.png", true );
    TextureManager::add( "btnAboutOn", "btnSobreOn.png", true );
    btnAbout.setTexture( TextureManager::get( "btnAbout" ) );
    btnAbout.setPosition( 500, 350 );
    btnAbout.setScale( 0.5, 0.5 );
}
void ScreenMenu::draw() {
    window->clear();
    window->draw( background );
    window->draw( btnPlay );
    window->draw( btnAbout );
    window->display();
}
void ScreenMenu::update() {
    while( window->pollEvent( *event ) ) {
        if( event->type == sf::Event::Closed ) {
            window->close();
        }
    }

    if( inputManager->isMouseOver( btnPlay ) ) {
        btnPlay.setTexture( TextureManager::get( "btnPlayOn" ) );

        if( inputManager->isSpriteClicked( sf::Mouse::Left, btnPlay ) ) {
            *nextScreen = JOGAR;
        }

    } else if( inputManager->isMouseOver( btnAbout ) ) {
        btnAbout.setTexture( TextureManager::get( "btnAboutOn" ) );
        if( inputManager->isSpriteClicked( sf::Mouse::Left, btnAbout ) ) {
            *nextScreen = SOBRE;
        }
    } else {
        btnPlay.setTexture( TextureManager::get( "btnPlay" ) );
        btnAbout.setTexture( TextureManager::get( "btnAbout" ) );
    }

    draw();
}
