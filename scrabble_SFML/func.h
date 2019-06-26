//
//  main.h
//  scrabble_SFML
//
//  Created by Misha Klymchuk on 6/17/19.
//  Copyright © 2019 Misha Klymchuk. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cctype>

#define MAX_NUMBER_OF_ITEM 7
#define MAX_WAY_NUMBER 2
#define BOARD_SIZE 15
#define kub 69.35
using namespace std;
using namespace sf;

struct letters {
    char letter;
    int points;
};

void mainWindow ();
void letters_innit(letters* leter);
void add_letter(letters* letter);
void moveRight(int& selected, RectangleShape* rec);
void moveLeft(int& selected, RectangleShape* rec);
void moveUp(int& ind, RectangleShape menu[4]);
void moveDown(int& ind, RectangleShape menu[4]);
void moveBLeft (int& iInd, int& jInd, RectangleShape rec[BOARD_SIZE][BOARD_SIZE], Text boardText[BOARD_SIZE][BOARD_SIZE]);
void moveBRight (int& iInd, int& jInd, RectangleShape rec[BOARD_SIZE][BOARD_SIZE], Text boardText[BOARD_SIZE][BOARD_SIZE]);
void moveBUp (int& iInd, int& jInd, RectangleShape rec[BOARD_SIZE][BOARD_SIZE], Text boardText[BOARD_SIZE][BOARD_SIZE]);
void moveBDown (int& iInd, int& jInd, RectangleShape rec[BOARD_SIZE][BOARD_SIZE], Text boardText[BOARD_SIZE][BOARD_SIZE]);
bool search_words(string word);
bool search_words_by_letter(string word, string file_name);
void incorrectWord();
void selectedElementInit (bool arr[MAX_NUMBER_OF_ITEM]);
void rectanglesInit (RectangleShape*& rectangles1, RectangleShape*& rectangles2, RectangleShape recBoard[BOARD_SIZE][BOARD_SIZE], RectangleShape recMenu[4]);
void textInit (Text*& lett1, Text*& lett2, letters*& lett_play1, letters*& lett_play2, Text boardText[BOARD_SIZE][BOARD_SIZE], Font& font, Text& player1, Text& player2, Text& tscore1, Text& tscore2, Text textMenu[4]);
void Error ();
void copy_player_letters(char copyLetter[7], letters* letters_arr);
bool choose_way();
void way_menu_up(RectangleShape* el, int& selected);
void way_menu_down(RectangleShape* el, int& selected);
bool check_exiting_char(Text boardText[BOARD_SIZE][BOARD_SIZE]);
void menuFunc (Text boardText[BOARD_SIZE][BOARD_SIZE], bool& gorizontal, int& lastI, int& lastJ, letters* lett_play1, letters* lett_play2, Text* lett1, Text* lett2, RectangleShape recBoard[BOARD_SIZE][BOARD_SIZE], RectangleShape* rectangles1, RectangleShape* rectangles2);
void addInBoard (letters* lett_play, Text* lett, int lastI, int lastJ, string letter);
int scoreForLetter (char lett);
void scoreArrInit ();
void helper ();
