#ifndef SCREEN_JOGAR_HPP
#define SCREEN_JOGAR_HPP

#include "Screen.hpp"
#include "Tree.hpp"
#include <SFML/Graphics.hpp>

class ScreenJogar : Screen {
  public:
    explicit ScreenJogar( GameRef& gameRef );

    void loadAssets();
    void draw();
    void update();

  private:
    Tree tree;
};

#endif
