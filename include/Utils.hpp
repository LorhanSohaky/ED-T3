#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>
#include <memory>

enum WINDOW_STATES { MENU = 1, JOGAR, CREDITOS, GANHOU, PERDEU, FECHAR };

struct GameData {
    sf::RenderWindow* window;
    sf::Event event;
    bool isAudioOn;
    WINDOW_STATES estadoJanela;
};

typedef std::shared_ptr< GameData > GameRef;

#endif
