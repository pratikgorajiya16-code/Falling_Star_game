#include "Game.h"
#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>


int main(int argc, char* argv[]) {
    //std::filesystem::path Path = R"(D:\New Learning\Games\Shooter\fonts\Roboto-VariableFont_wdth,wght.ttf)";
    //std::cout << std::filesystem::exists(Path) << "\n";
    //std::cout << std::filesystem::is_regular_file(Path) << "\n";

    //try {
    //    sf::Font f1(R"(D:\New Learning\Games\Shooter\fonts\Roboto-VariableFont_wdth,wght.ttf)");
    //    std::cout << "Bingo";
    //}
    //catch(const sf::Exception &e){
    //    std::cout << e.what();
    //}

    //window_key();
    //std::srand(static_cast<unsigned>(time(NULL)));

    Game game;

    while (game.getWindowIsOpen()) {
        
        //update
        game.update();

        //render
        game.render();
    }

    return 0;
    }
