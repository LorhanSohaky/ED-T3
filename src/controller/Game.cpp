#include "../../include/Game.hpp"
#include "../../include/FontManager.hpp"
#include "../../include/ScreenJogar.hpp"
#include "../../include/ScreenMenu.hpp"
#include "../../include/TextureManager.hpp"

Game::Game( const std::string& titulo,
            const int largura,
            const int altura,
            const int limiteDeFrames ) {
    gameRef->window =
        new sf::RenderWindow( sf::VideoMode( largura, altura ), titulo, sf::Style::Close );

    gameRef->window->setFramerateLimit( limiteDeFrames );
    gameRef->isAudioOn  = true;
    gameRef->nextScreen = MENU;

    gameRef->inputManager = new InputManager( &gameRef->event, gameRef->window );

    FontManager::add( "padrao", "bebas_neue/BebasNeue-Regular.ttf" );
}

void Game::run() {
    ScreenMenu menu( gameRef );
    ScreenJogar jogar( gameRef );

    while( gameRef->window->isOpen() ) {
        switch( gameRef->nextScreen ) {
            case MENU:
                menu.update();
                break;
            case JOGAR:
                jogar.update();
                break;
            default:
                menu.update();
                break;
        }
    }
}

Game::~Game() {
    delete gameRef->window;
    delete gameRef->inputManager;
}
