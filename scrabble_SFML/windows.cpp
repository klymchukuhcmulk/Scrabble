//
//  windows.cpp
//  scrabble_SFML
//
//  Created by Misha Klymchuk on 6/19/19.
//  Copyright © 2019 Misha Klymchuk. All rights reserved.
//

#include "func.h"

bool choose_way() {
    Font font;
    font.loadFromFile("righteous.ttf");
    RenderWindow window2(VideoMode(600, 350), "Choose way", Style::Default);
    
    RectangleShape* rectangle = new RectangleShape[2];
    Vector2f recSize;
    recSize.x = 400;
    recSize.y = 100;
    
    int selectedItem = 0;
    
    float x, y;
    x = 100;
    y = 50;
    
    for (int i = 0; i < 2; i++) {
        rectangle[i].setSize(recSize);
        rectangle[i].setFillColor(Color::Transparent);
        rectangle[i].setOutlineThickness(3);
        rectangle[i].setPosition(x, y);
        y += 150;
    }
    
    Text way[2];
    
    x = 180;
    y = 75;
    
    way[0].setString("Gorisontal");
    way[1].setString("  Vertical");
    
    for (short i = 0; i < 2; i++)
    {
        way[i].setFont(font);
        way[i].setFillColor(Color(47, 79, 79));
        way[i].setPosition(x, y);
        way[i].setCharacterSize(50);
        y += 150;
    }
    rectangle[0].setFillColor(Color::Green);
    
    
    while (window2.isOpen()) {
        Event event;
        while (window2.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window2.close();
            }
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Up)
                {
                    way_menu_up(rectangle, selectedItem);
                    
                }
                if (event.key.code == Keyboard::Down)
                {
                    way_menu_down(rectangle, selectedItem);
                    
                }
                if (event.key.code == Keyboard::Enter)
                {
                    if (selectedItem == 0) {
                        window2.close();
                        return true;
                    }
                    else if (selectedItem == 1) {
                        window2.close();
                        return false;
                    }
                    
                }
                
            }
            
        }
        window2.clear(Color(32, 178, 170));
        for (int i = 0; i < 2; i++)
        {
            window2.draw(rectangle[i]);
            window2.draw(way[i]);
            
        }
        window2.display();
    }
    return false;
}

void Error () {
    Font font;
    font.loadFromFile("righteous.ttf");
    RenderWindow errorWindow(VideoMode(600, 150), "ERROR", Style::Default);
    Text error("Error", font, 60);
    error.setFillColor(Color(139, 0, 0));
    error.setPosition(50, 50);
    while (errorWindow.isOpen()) {
        sf::Event event;
        while (errorWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                errorWindow.close();
            }
        }
        errorWindow.clear(Color(240, 128, 128));
        errorWindow.draw(error);
        errorWindow.display();
    }
}
void incorrectWord() {
    Font font;
    RenderWindow window(VideoMode(1550, 450), "Incorrect", Style::Default);
    font.loadFromFile("righteous.ttf");
    Text error("           Non existing word\nor no letters touch each other!", font, 100);
    error.setOutlineThickness(4);
    error.setOutlineColor(Color::White);
    error.setPosition(50, 70);
    error.setFillColor(Color(255, 99, 71));
    
    Sprite sky;
    Texture skyTex;
    skyTex.loadFromFile("sky1.png");
    sky.setTexture(skyTex);
    sky.setPosition(0, 0);
    sky.setScale(3.76, 2.76);
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyPressed:
                    switch (event.key.code) {
                        case Keyboard::Enter:
                            window.close();
                            break;
                    }
            }
        }
        window.clear(Color(255, 165, 0));
        window.clear();
        window.draw(sky);
        window.draw(error);
        window.display();
    }
}
