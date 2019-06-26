//
//  func.cpp
//  scrabble_SFML
//
//  Created by Misha Klymchuk on 6/17/19.
//  Copyright © 2019 Misha Klymchuk, Andriy Parhomchuk. All rights reserved.
//

#include "func.h"

Color color = Color::Transparent;
Font font;
RenderWindow window(VideoMode(1900,1500), "Scrabble");
RectangleShape recBoard[BOARD_SIZE][BOARD_SIZE];
RectangleShape* rectangles1 = new RectangleShape[7];
RectangleShape* rectangles2 = new RectangleShape[7];
RectangleShape recMenu[4];
letters* lett_play1 = new letters[7];
letters* lett_play2 = new letters[7];
Text* lett1 = new Text[7];
Text* lett2 = new Text[7];
Text boardText[BOARD_SIZE][BOARD_SIZE];

char copyLetters[7];
string letter1, letter2 = "";
string Currentword;

int selectedItemIndex = 0;
int selectedMenuIndex = 0;
int score1 = 3;
int score2 = 13;
int currentScore = 0;
float x, y;

bool selectedElement[MAX_NUMBER_OF_ITEM];
bool onLetters = true;
bool onMenu = false;
bool onBoard = false;
bool secondPlayer = false;
bool firstStap = true;

void mainWindow () {
    srand(unsigned(time(NULL)));
    selectedElementInit(selectedElement);
    x = 230;
    y = 208;
    rectanglesInit(rectangles1, rectangles2, recBoard, recMenu);
    Text player1("Player 1", font, 60);
    Text player2("Player 2", font, 60);
    Text tscore1("Score: 0", font, 60);
    Text tscore2("Score: 0", font, 60);
    Text textMenu[4];
    Sprite board;
    Texture boardTex;
    boardTex.loadFromFile("board.png");
    board.setTexture(boardTex);
    board.setPosition(150, 150);
    board.setScale(4, 4);
    textInit(lett1, lett2, lett_play1, lett_play2, boardText, font, player1, player2, tscore1, tscore2, textMenu);
    
    /*TMP
    stringstream* playerScoreStr = new stringstream;
    *playerScoreStr << score1;
    string textScore1 = playerScoreStr->str();
    delete playerScoreStr;
    playerScoreStr = new stringstream;
    *playerScoreStr << score2;
    string textScore2 = playerScoreStr->str();
    TMP */
    int lastI = 0, lastJ = 0;// Save last element index
    bool gorizontal = true;
    
    while(window.isOpen()) {
        //Event processing.
        Event event;
        int i, j;
        i = lastI;
        j = lastJ;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyPressed:
                    if (event.key.code == Keyboard::Right) {
                        if (!secondPlayer) {
                            moveRight(selectedItemIndex, rectangles1);
                        } else {
                            moveRight(selectedItemIndex, rectangles2);
                        }
                    } else if (event.key.code == Keyboard::Left) {
                        if (!secondPlayer) {
                            moveLeft(selectedItemIndex, rectangles1);
                        } else {
                            moveLeft(selectedItemIndex, rectangles2);
                        }
                    } else if (event.key.code == Keyboard::Up && onMenu) {
                        moveUp(selectedMenuIndex, recMenu);
                    } else if (event.key.code == Keyboard::Down && onMenu) {
                        moveDown(selectedMenuIndex, recMenu);
                    } else if (event.key.code == Keyboard::Return) {
                        if (onLetters) {
                            onLetters = false;
                            onBoard = false;
                            onMenu = true;
                            if (secondPlayer) {
                                letter1 = lett_play2[selectedItemIndex].letter;
                                letter2 = " ";
                            }
                            recMenu[0].setOutlineColor(Color::White);
                        } else if (onMenu) {
                            onMenu = false;
                            menuFunc(boardText, gorizontal, lastI, lastJ, lett_play1, lett_play2, lett1, lett2, recBoard, rectangles1, rectangles2);
                            onBoard = true;
                        } else if (onBoard) {
                            cout << "Gor/Vert?" << endl;
                            // Set letter on position in the board
                            // Gorizontal or Vertical ?
                            // New letter selection start
                            onLetters = true;
                            onMenu = false;
                            onBoard = false;
                            recMenu[selectedMenuIndex].setOutlineColor(Color::Black);
                            selectedMenuIndex = 0;
                        }
                    } else if (event.key.code == Keyboard::S && onBoard) {// Move on the board
                        moveBDown(i, j, recBoard, boardText);
                        lastJ = j;
                        lastI = i;
                    } else if (event.key.code == Keyboard::W && onBoard) {// Move on the board
                        moveBUp(i, j, recBoard, boardText);
                        lastJ = j;
                        lastI = i;
                    } else if (event.key.code == Keyboard::D && onBoard) {// Move on the board
                        moveBRight(i, j, recBoard, boardText);
                        lastJ = j;
                        lastI = i;
                    } else if (event.key.code == Keyboard::A && onBoard) {// Move on the board
                        moveBLeft(i, j, recBoard, boardText);
                        lastJ = j;
                        lastI = i;
                    }
                    
            }
        }
        window.clear(Color(32, 178, 170));
        window.draw(board);
        for (int i = 0; i < 7; i++) {
            window.draw(rectangles1[i]);
            window.draw(rectangles2[i]);
            window.draw(lett1[i]);
            window.draw(lett2[i]);
        }
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                window.draw(recBoard[i][j]);
                window.draw(boardText[i][j]);
            }
        }
        for (int i = 0; i < 4; i++) {
            window.draw(recMenu[i]);
            window.draw(textMenu[i]);
        }
        window.draw(player1);
        window.draw(player2);
        window.draw(tscore1);
        window.draw(tscore2);
        window.display();
    }
}

void menuFunc (Text boardText[BOARD_SIZE][BOARD_SIZE], bool& gorizontal, int& lastI, int& lastJ, letters* lett_play1, letters* lett_play2, Text* lett1, Text* lett2, RectangleShape recBoard[BOARD_SIZE][BOARD_SIZE], RectangleShape* rectangles1, RectangleShape* rectangles2) {
    
    int i;
    int j;
    switch (selectedMenuIndex) {
        case 0:
            //Start with exist
            if (check_exiting_char(boardText)) {
                //Select letter to start
                firstStap = false;
                
                goto Add;// Go to add section
            }
            
            break;
        case 1:
            //Add
        Add:
            if (firstStap) {// First letter choose pozition
                onBoard = true;
                onMenu = false;
                onLetters = false;
                firstStap = false;
                gorizontal = choose_way();
                if (boardText[7][7].getString() == " ") {
                    cout << "ERROR" << endl;
                    letter1 = lett_play1[selectedItemIndex].letter;
                    lastJ = 7;
                    lastI = 7;
                    addInBoard(lett_play1, lett1, lastI, lastJ, letter1);
                    
                    break;
                }
                lastJ = 0;
                lastI = 0;
            } else {
                if (gorizontal) {
                    while (boardText[lastI][lastJ + 1].getString() != " ") {
                        lastJ++;
                    }
                    lastJ++;
                } else {
                    while (boardText[lastI + 1][lastJ].getString() != " ") {
                        lastI++;
                    }
                    lastI++;
                }
            }
            if (secondPlayer) {
                letter2 = lett_play2[selectedItemIndex].letter;
                addInBoard(lett_play2, lett2, lastI, lastJ, letter2);
            } else {
                letter1 = lett_play1[selectedItemIndex].letter;
                addInBoard(lett_play1, lett1, lastI, lastJ, letter1);
            }
            break;
        case 2:
            //helper launching
            break;
        case 3:
            //End action
            string firstLetters = Currentword; // First letters, non-full word
            Currentword = "";
            int i = lastI;
            int j = lastJ;
            if (gorizontal) {//Checking full word
                while (boardText[i][j - 1].getString() != " " && j >= 0) {
                    j--;
                }
                while (boardText[i][j].getString() != " " && j < BOARD_SIZE) {
                    Currentword += boardText[i][j].getString();
                    j++;
                }
            } else {
                while (boardText[i - 1][j].getString() != " " && i >= 0) {
                    i--;
                }
                while (boardText[i][j].getString() != " " && i < BOARD_SIZE) {
                    Currentword += boardText[i][j].getString();
                    i++;
                }
            }
            bool correct = search_words(Currentword);// Checking word
            
            if(correct){// Correct word
//                lastJ = 0;
//                lastI = 0;
                if (!secondPlayer) {
                    copy_player_letters(copyLetters, lett_play2);
                    rectangles1[selectedItemIndex].setFillColor(Color(34, 139, 34));
                    x = 515;
                    y = 35;
                    for (int i = 0; i < 7; i++) {
                        lett1[i] = Text(lett_play1[i].letter, font, 60);
                        lett1[i].setPosition(x, y);
                        lett1[i].setFillColor(Color(47, 79, 79));
                        window.draw(lett1[i]);
                        x += 70;
                    }
                    secondPlayer = true;
                } else {
                    copy_player_letters(copyLetters, lett_play1);
                    rectangles2[selectedItemIndex].setFillColor(Color(34, 139, 34));
                    secondPlayer = false;
                    x = 515;
                    for (int i = 0; i < 7; i++) {
                        lett2[i] = Text(lett_play2[i].letter, font, 60);
                        lett2[i].setPosition(x, 1355);
                        lett2[i].setFillColor(Color(47, 79, 79));
                        window.draw(lett1[i]);
                        x += 70;
                    }
                }
                selectedItemIndex = 0;
            } else {// Incorrect word
                Currentword = firstLetters;
                incorrectWord();
                cout << lastJ << ": J " << lastI << ": I" << endl;
                if (gorizontal) {
                    int i = lastJ;
                    while (boardText[lastI][i].getString() != " ") {
                        if (boardText[lastI - 1][i].getString() == " " && boardText[lastI + 1][i].getString() == " ") {
                            boardText[lastI][i].setString(" ");
                            recBoard[lastI][i].setFillColor(Color::Transparent);
                        }
                        i--;
                    }
                } else {
                    int i = lastI;
                    while (boardText[i][lastJ].getString() != " ") {
                        if (boardText[i][lastJ - 1].getString() == " " && boardText[i][lastJ + 1].getString() == " ") {
                            boardText[i][lastJ].setString(" ");
                            recBoard[i][lastJ].setFillColor(Color::Transparent);
                        }
                        i--;
                    }
                }
                if (!secondPlayer) {
                    x = 515;
                    y = 35;
                    for (int i = 0; i < 7; i++) {
                        lett_play1[i].letter = copyLetters[i];
                        lett1[i] = Text(copyLetters[i], font, 60);
                        lett1[i].setPosition(x, y);
                        lett1[i].setFillColor(Color(47, 79, 79));
                        window.draw(lett1[i]);
                        x += 70;
                    }
                }
                else {
                    x = 515;
                    for (int i = 0; i < 7; i++) {
                        lett_play2[i].letter = copyLetters[i];
                        lett2[i] = Text(copyLetters[i], font, 60);
                        lett2[i].setPosition(x, 1355);
                        lett2[i].setFillColor(Color(47, 79, 79));
                        window.draw(lett1[i]);
                        x += 70;
                    }
                }

            }
            selectedElementInit(selectedElement);
            Currentword = "";
            firstStap = true;
            letter1 = "k";
            break;
    }
}

bool search_words(string word) {
    bool result = false;
    switch (word[0])
    {
        case 'a':
            result = search_words_by_letter(word, "Dictionary/A.txt");
            break;
        case 'b':
            result = search_words_by_letter(word, "Dictionary/B.txt");
            break;
        case 'c':
            result = search_words_by_letter(word, "Dictionary/C.txt");
            break;
        case 'd':
            result = search_words_by_letter(word, "Dictionary/D.txt");
            break;
        case 'e':
            result = search_words_by_letter(word, "Dictionary/E.txt");
            break;
        case 'f':
            result = search_words_by_letter(word, "Dictionary/F.txt");
            break;
        case 'g':
            result = search_words_by_letter(word, "Dictionary/G.txt");
            break;
        case 'h':
            result = search_words_by_letter(word, "Dictionary/H.txt");
            break;
        case 'i':
            result = search_words_by_letter(word, "Dictionary/I.txt");
            break;
        case 'j':
            result = search_words_by_letter(word, "Dictionary/J.txt");
            break;
        case 'k':
            result = search_words_by_letter(word, "Dictionary/K.txt");
            break;
        case 'l':
            result = search_words_by_letter(word, "Dictionary/L.txt");
            break;
        case 'm':
            result = search_words_by_letter(word, "Dictionary/M.txt");
            break;
        case 'n':
            result = search_words_by_letter(word, "Dictionary/N.txt");
            break;
        case 'o':
            result = search_words_by_letter(word, "Dictionary/O.txt");
            break;
        case 'p':
            result = search_words_by_letter(word, "Dictionary/P.txt");
            break;
        case 'q':
            result = search_words_by_letter(word, "Dictionary/Q.txt");
            break;
        case 'r':
            result = search_words_by_letter(word, "Dictionary/R.txt");
            break;
        case 's':
            result = search_words_by_letter(word, "Dictionary/S.txt");
            break;
        case 't':
            result = search_words_by_letter(word, "Dictionary/T.txt");
            break;
        case 'u':
            result = search_words_by_letter(word, "Dictionary/U.txt");
            break;
        case 'v':
            result = search_words_by_letter(word, "Dictionary/V.txt");
            break;
        case 'w':
            result = search_words_by_letter(word, "Dictionary/W.txt");
            break;
        case 'x':
            result = search_words_by_letter(word, "Dictionary/X.txt");
            break;
        case 'y':
            result = search_words_by_letter(word, "Dictionary/Y.txt");
            break;
        case 'z':
            result = search_words_by_letter(word, "Dictionary/Z.txt");
            break;
    }
    return result;
}

bool search_words_by_letter(string word, string file_name) {
    ifstream file;
    file.open(file_name);
    bool check = false;
    string current_word;
    string temp;
    while (!file.eof() && check == false) {
        file >> current_word;
        getline(file, temp);
        if (current_word == word) {
            check = true;
        }
    }
    file.close();
    return check;
}

void letters_innit (letters* leter) {
    for (int i = 0; i < 7; i++) {
        add_letter(leter + i);
    }
}

void add_letter(letters* letter) {
    
    char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    letter->letter = alphabet[rand() % 26];
    switch (letter->letter) {
        case 'a':
            letter->points = 1;
            break;
        case 'b':
            letter->points = 3;
            break;
        case 'c':
            letter->points = 3;
            break;
        case 'd':
            letter->points = 2;
            break;
        case 'e':
            letter->points = 1;
            break;
        case 'f':
            letter->points = 4;
            break;
        case 'g':
            letter->points = 2;
            break;
        case 'h':
            letter->points = 4;
            break;
        case 'i':
            letter->points = 1;
            break;
        case 'j':
            letter->points = 8;
            break;
        case 'k':
            letter->points = 5;
            break;
        case 'l':
            letter->points = 1;
            break;
        case 'm':
            letter->points = 3;
            break;
        case 'n':
            letter->points = 1;
            break;
        case 'o':
            letter->points = 1;
            break;
        case 'p':
            letter->points = 3;
            break;
        case 'q':
            letter->points = 10;
            break;
        case 'r':
            letter->points = 1;
            break;
        case 's':
            letter->points = 1;
            break;
        case 't':
            letter->points = 1;
            break;
        case 'u':
            letter->points = 1;
            break;
        case 'v':
            letter->points = 4;
            break;
        case 'w':
            letter->points = 4;
            break;
        case 'x':
            letter->points = 8;
            break;
        case 'y':
            letter->points = 4;
            break;
        case 'z':
            letter->points = 10;
            break;
    }
}

void rectanglesInit (RectangleShape*& rectangles1, RectangleShape*& rectangles2, RectangleShape recBoard[BOARD_SIZE][BOARD_SIZE], RectangleShape recMenu[4]) {
    int x = 500;
    int y = 40;
    
    for (int i = 0; i < 7; i++) {
        rectangles1[i].setSize(Vector2f(70, 70));
        rectangles1[i].setFillColor(Color(50, 205, 50));
        rectangles1[i].setPosition(x, y);
        rectangles1[i].setOutlineThickness(3);
        rectangles1[i].setOutlineColor(Color::Black);
        x += 70;
    }
    rectangles1[0].setFillColor(Color::White);
    x = 500;
    for (int i = 0; i < 7; i++) {
        rectangles2[i].setSize(Vector2f(70, 70));
        rectangles2[i].setFillColor(Color(50, 205, 50));
        //        rectangles2[i].setPosition(x, y);
        rectangles2[i].setOutlineThickness(3);
        rectangles2[i].setOutlineColor(Color::Black);
        rectangles2[i].setPosition(x, 1360);
        x += 70;
    }
    y = 208;
    for (int i = 0; i < BOARD_SIZE; i++) {
        x = 230;
        for (int j = 0; j < BOARD_SIZE; j++) {
            recBoard[i][j].setSize(Vector2f(kub, kub));
            recBoard[i][j].setPosition(x, y);
            recBoard[i][j].setFillColor(Color::Transparent);
            recBoard[i][j].setOutlineThickness(3);
            recBoard[i][j].setOutlineColor(Color::Transparent);
            x += kub;
        }
        y += kub;
    }
    x = 1450;
    y = 240;
    for (int i = 0; i < 4; i++) {
        recMenu[i].setSize(Vector2f(350, 200));
        recMenu[i].setFillColor(Color(50, 205, 50));
        recMenu[i].setPosition(x, y);
        recMenu[i].setOutlineThickness(5);
        recMenu[i].setOutlineColor(Color::Black);
        y += 250;
    }
    
}

void textInit (Text*& lett1, Text*& lett2, letters*& lett_play1, letters*& lett_play2, Text boardText[BOARD_SIZE][BOARD_SIZE], Font& font, Text& player1, Text& player2, Text& tscore1, Text& tscore2, Text textMenu[4]) {
    font.loadFromFile("righteous.ttf");
    letters_innit(lett_play1);
    letters_innit(lett_play2);
    copy_player_letters(copyLetters, lett_play1);
    int x = 515;
    int y = 35;
    for (int i = 0; i < 7; i++) {
        lett1[i] = Text(lett_play1[i].letter, font, 60);
        lett1[i].setPosition(x, y);
        lett1[i].setFillColor(Color(47, 79, 79));
        x += 70;
    }
    x = 515;
    for (int i = 0; i < 7; i++) {
        lett2[i] = Text(lett_play2[i].letter, font, 60);
        lett2[i].setFillColor(Color(47, 79, 79));
        lett2[i].setPosition(x, 1355);
        x += 70;
    }
    x = 515;
    for (int i = 0; i < 7; i++) {
        lett2[i].setPosition(x, 1355);
        x += 70;
    }
    y = 208;
    for (int i = 0; i < BOARD_SIZE; i++) { // Boart text init
        x = 245;
        for (int j = 0; j < BOARD_SIZE; j++) {
            boardText[i][j] = Text(" ", font, 60);
            boardText[i][j].setFillColor(Color::Black);
            boardText[i][j].setPosition(x, y);
            x += kub;
        }
        y += kub;
    }
    
    player1.setPosition(100, 35);
    player1.setFillColor(Color(47, 79, 79));
    tscore1.setPosition(1200, 35);
    tscore1.setFillColor(Color(47, 79, 79));
    player2.setPosition(100, 1355);
    player2.setFillColor(Color(47, 79, 79));
    tscore2.setPosition(1200, 1355);
    tscore2.setFillColor(Color(47, 79, 79));
    
    x = 1470;
    y = 280;
    for (int i = 0; i < 4; i++) {
        textMenu[i].setFillColor(Color(47, 79, 79));
        textMenu[i].setFont(font);
        textMenu[i].setCharacterSize(60);
        textMenu[i].setPosition(x, y);
        
        y += 250;
    }
    textMenu[0].setPosition(1417, 270);
    textMenu[1].setPosition(1430, 550);
    textMenu[2].setPosition(1426, 800);
    textMenu[3].setPosition(1433, 1015);
    textMenu[0].setString("    Start with\n        exist");
    textMenu[1].setString("        Add");
    textMenu[2].setString("        Help");
    textMenu[3].setString("        End\n      action");
    
}

void addInBoard (letters* lett_play, Text* lett, int lastI, int lastJ, string letter) {
    add_letter(lett_play + selectedItemIndex);
    
    lett[selectedItemIndex] = Text("", font, 60);
    
    window.draw(lett[selectedItemIndex]);
    boardText[lastI][lastJ].setString(letter);
    recBoard[lastI][lastJ].setFillColor(Color(34, 139, 34));
    
    Currentword += letter;
    currentScore += lett_play[selectedItemIndex].points;
}


void moveRight(int& selected, RectangleShape* rec){
    if (selected + 1 < MAX_NUMBER_OF_ITEM) {
        rec[selected].setFillColor(Color(50, 205, 50));
        selected++;
        rec[selected].setFillColor(Color::White);
    }
}

void moveLeft(int& selected, RectangleShape* rec){
    if (selected - 1 >= 0) {
        rec[selected].setFillColor(Color(50, 205, 50));
        selected--;
        rec[selected].setFillColor(Color::White);
    }
}

void moveUp(int& ind, RectangleShape menu[4]){
    if (ind - 1 >= 0) {
        menu[ind].setOutlineColor(Color::Black);
        ind--;
        menu[ind].setOutlineColor(Color::White);
    }
}

void moveDown(int& ind, RectangleShape menu[4]){
    if (ind + 1 < 4) {
        menu[ind].setOutlineColor(Color::Black);
        ind++;
        menu[ind].setOutlineColor(Color::White);
    }
}

void moveBLeft (int& iInd, int& jInd, RectangleShape rec[BOARD_SIZE][BOARD_SIZE], Text boardText[BOARD_SIZE][BOARD_SIZE]) {
    if (jInd > 0) {
        rec[iInd][jInd].setFillColor(color);
        boardText[iInd][jInd].setString(letter2);
        jInd--;
        letter2 = boardText[iInd][jInd].getString();
        boardText[iInd][jInd].setString(letter1);
        color = rec[iInd][jInd].getFillColor();
        rec[iInd][jInd].setFillColor(Color(34, 139, 34));
    }
    
}

void moveBRight (int& iInd, int& jInd, RectangleShape rec[BOARD_SIZE][BOARD_SIZE], Text boardText[BOARD_SIZE][BOARD_SIZE]) {// Move on the board
    if (jInd < 14) {
        rec[iInd][jInd].setFillColor(color);
        boardText[iInd][jInd].setString(letter2);
        jInd++;
        letter2 = boardText[iInd][jInd].getString();
        boardText[iInd][jInd].setString(letter1);
        color = rec[iInd][jInd].getFillColor();
        rec[iInd][jInd].setFillColor(Color(34, 139, 34));
    }
}

void moveBUp (int& iInd, int& jInd, RectangleShape rec[BOARD_SIZE][BOARD_SIZE], Text boardText[BOARD_SIZE][BOARD_SIZE]) {// Move on the board
    if (iInd > 0) {
        rec[iInd][jInd].setFillColor(color);
        boardText[iInd][jInd].setString(letter2);
        iInd--;
        letter2 = boardText[iInd][jInd].getString();
        boardText[iInd][jInd].setString(letter1);
        color = rec[iInd][jInd].getFillColor();
        rec[iInd][jInd].setFillColor(Color(34, 139, 34));
    }
    
}

void moveBDown (int& iInd, int& jInd, RectangleShape rec[BOARD_SIZE][BOARD_SIZE], Text boardText[BOARD_SIZE][BOARD_SIZE]) {// Move on the board
    if (iInd < 14) {
        rec[iInd][jInd].setFillColor(color);
        boardText[iInd][jInd].setString(letter2);
        iInd++;
        letter2 = boardText[iInd][jInd].getString();
        boardText[iInd][jInd].setString(letter1);
        color = rec[iInd][jInd].getFillColor();
        rec[iInd][jInd].setFillColor(Color(34, 139, 34));
    }
}

void selectedElementInit (bool arr[MAX_NUMBER_OF_ITEM]) {
    for (int i = 0; i < MAX_NUMBER_OF_ITEM; i++) {
        arr[i] = false;
    }
}

void copy_player_letters(char copyLetter[7], letters* letters_arr) {
    for (int i = 0; i < 7; i++) {
        copyLetter[i] = letters_arr[i].letter;
    }
}

void way_menu_up(RectangleShape* el, int& selected) {
    if (selected - 1 >= 0) {
        el[selected].setFillColor(Color::Transparent);
        selected--;
        el[selected].setFillColor(Color::Green);
    }
}
void way_menu_down(RectangleShape* el, int& selected) {
    if (selected + 1 < MAX_WAY_NUMBER) {
        el[selected].setFillColor(Color::Transparent);
        selected++;
        el[selected].setFillColor(Color::Green);
    }
}

bool check_exiting_char(Text boardText[BOARD_SIZE][BOARD_SIZE]) {// Is letter on the board
    string temp;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            temp = boardText[i][j].getString();
            if (isalpha(temp[0])) {
                //cout << isalpha(temp[0]);
                return true;
            }
        }
    }
    RenderWindow window4(VideoMode(300, 300), "Incorrect", Style::Default);
    while (window4.isOpen()) {
        sf::Event event;
        while (window4.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window4.close();
            }
        }
        window4.clear();
    }
    return false;
}

//bool chackGorizontalFullWord () {
//        while (boardText[i][j - 1].getString() != " " && j >= 0) {
//            j--;
//        }
//        while (boardText[i][j].getString() != " " && j < BOARD_SIZE) {
//            Currentword += boardText[i][j].getString();
//            j++;
//        }
//}
