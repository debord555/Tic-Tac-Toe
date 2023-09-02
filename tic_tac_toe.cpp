#include "board.cpp"
#include <vector>
#include <iostream>
#include <algorithm>

class TicTacToe {
    Board board;
    char turn;
    char marks[2];

public:
    TicTacToe() {
        turn = '1';
    }

    int changeTurn();
    int executeTurn();
    Point getPositionInput();
    int runGame();
};

int TicTacToe::changeTurn() {
    if (turn == '1')
        turn = '2';
    else
        turn = '1';
    return 0;
}

int TicTacToe::executeTurn() {
    Point input = getPositionInput();
    if (input.isValid())
        board.setOccupant(input, turn);
    return 0;
}

Point TicTacToe::getPositionInput() {
    std::vector<char> tokens;
    std::vector<Point> points;
    char curr_token = 1;
    // Displaying the current condition of the board with unoccupied positions numbered.
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            char occupant = board.getOccupant(Point(i, 2 - j));
            if (occupant != 'N') {
                if (occupant == '1') {
                    std::cout << marks[0] << "   ";
                } else
                    std::cout << marks[1] << "   ";
            } else {
                tokens.push_back(curr_token);
                points.push_back(Point(i, 2 - j));
                std::cout << (int) curr_token << "   ";
                curr_token++;
            }
        }
        std::cout << std::endl;
    }
    // Asking for position number if no-one has won the game in the prev. turn
    if (board.checkWin() == 'N') {
        int choice;
        do {
            std::cout << "Please enter the number of the position you want to mark: ";
            std::cin >> choice;
            // Searching for the iterator of a token == choice in tokens vector.
            std::vector<char>::iterator iter = std::find(tokens.begin(), tokens.end(), (char) choice);
            if (iter != tokens.end())
                return points.at(iter - tokens.begin());
            else
                std::cout << "Invalid number." << std::endl;
        } while (1);
    } else {
        return Point(-1, -1); // Return an invalid position if the game was won/drawn in prev turn. This position will be ignored in executeTurn func.
        std::cout << "\n" << std::endl; // Just for formatting
    }
}

int TicTacToe::runGame() {
    std::cout << "Welcome to this 2-Player Tic Tac Toe game!" << std::endl;
    // ASking the player 1 for their preferred mark
    char mark;
    do {
        std::cout << "Player 1 may choose his mark (X or O): ";
        std::cin >> mark;
        if (mark == 'X' || mark == 'x') {
            marks[0] = 'X';
            marks[1] = 'O';
        } else if (mark == 'O' || mark == 'o') {
            marks[0] = 'O';
            marks[1] = 'X';
        } else
            std::cout << "Invalid Input" << std::endl;
    } while (mark != 'X' && mark != 'O' && mark != 'x' && mark != 'o'); // Loop if entered mark is invalid
    // Main game loop following:
    do {
        std::cout << "\n\nPlayer " << (int) turn - 48 << "\'s Turn:" << std::endl;
        executeTurn();
        changeTurn();
    } while (board.checkWin() == 'N' && !board.isFull());
    // Running executeTurn for the last time. Since the game has been won or drawn in the last turn, it will not ask for input, and just print the board.
    executeTurn();
    // Declare Results
    if (board.checkWin() == 'D') {
        std::cout << "\nThe Match is a draw!" << std::endl;
        return 0;
    } else {
        std::cout << "\nPlayer " << board.checkWin() << " has won the game!" << std::endl;
        return (int) board.checkWin();
    }
}