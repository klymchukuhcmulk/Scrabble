//
//  main.cpp
//  scrabble_SFML
//
//  Created by Misha Klymchuk on 6/17/19.
//  Copyright © 2019 Misha Klymchuk. All rights reserved.
//

#include "func.h"

void menu_up(Text el[2], int& selected);
void menu_down(Text el[2], int& selected);
void menuwindow ();


int main(int argc, const char * argv[]) {
    menuwindow();
    return 0;
}


void menu_up(Text el[2], int& selected) {
    if (selected - 1 >= 0) {
        el[selected].setOutlineColor(Color::Transparent);
        selected--;
        el[selected].setOutlineColor(Color::White);
    }
}
void menu_down(Text el[2], int& selected) {
    if (selected + 1 < MAX_WAY_NUMBER) {
        el[selected].setOutlineColor(Color::Transparent);
        selected++;
        el[selected].setOutlineColor(Color::White);
    }
}

void menuwindow () {
    RenderWindow window(VideoMode(1900,1500), "SCRABBLE");
    Font font;
    font.loadFromFile("righteous.ttf");
    Text game[2];
    game[0] = Text("START", font, 200);
    game[0].setPosition(630, 400);
    game[0].setStyle(Text::Bold);
    game[1] = Text("QUITE", font, 200);
    game[1].setPosition(630, 800);
    game[1].setStyle(Text::Bold);
    game[0].setOutlineThickness(4);
    game[1].setOutlineThickness(4);
    game[0].setOutlineColor(Color::White);
    game[1].setOutlineColor(Color::Transparent);
    game[0].setFillColor(Color(0, 100, 0));
    game[1].setFillColor(Color(0, 100, 0));
    
    Sprite sky;
    Texture skyTex;
    skyTex.loadFromFile("sky1.png");
    sky.setTexture(skyTex);
    sky.setPosition(0, 0);
//    sky.setScale(0.76, 0.76);
    sky.setScale(3.76, 2.76);
    
    int selectedItem = 0;
    
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyPressed:
                    switch (event.key.code) {
                        case Keyboard::Up:
                            menu_up(game, selectedItem);
                            break;
                        case Keyboard::Down:
                            menu_down(game, selectedItem);
                            break;
                        case Keyboard::Enter:
                            if (selectedItem == 0) {
                                window.close();
                                mainWindow();
                            } else if (selectedItem == 1) {
                                window.close();
                            }
                            break;
                    }
            }
        }
        window.clear(Color::Black);
        window.draw(sky);
        window.draw(game[0]);
        window.draw(game[1]);
        
        window.display();
    }
}
