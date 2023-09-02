/*
    Player ID:
        1: Player 1
        2: Player 2
        N: Unoccupied position = None won (in win check)
        D: Draw (in case of win check)

    Error Code:
        0: Success
        1: Invalid Position
        2: Invalid Occupant

    Coordinate format:

        (0,2) (1,2) (2,2)
        
        (0,1) (1,1) (2,1)

        (0,0) (1,0) (2,0)
*/

#include "point.cpp"

class Board {
    char layout[9];

public:
    Board() {
        for (int i = 0; i < 9; i++)
            layout[i] = 'N';
    }

    char getOccupant(Point pos);
    int setOccupant(Point pos, char occupant);
    char checkWin();
    bool isFull();

private:
    int isPosValid(Point pos);
    int isOccupantValid(char occupant);
};

char Board::getOccupant(Point pos) {
    if (isPosValid(pos) == 1)
        return layout[3*pos.getY() + pos.getX()];
    else
        return '\0';
}

int Board::setOccupant(Point pos, char occupant) {
    if (isPosValid(pos) == 1) {
        if (isOccupantValid(occupant) == 1) {
            layout[3*pos.getY() + pos.getX()] = occupant;
            return 0;
        } else
            return 2;
    } else {
        return 1;
    }
}

char Board::checkWin() {
    // Row wise check:
    for (int i = 0; i < 3; i++) {
        char row[3];
        for (int j = 0; j < 3; j++)
            row[j] = getOccupant(Point(j, i));
        if (row[0] == row[1] && row[1] == row[2] && row[2] != 'N')
            return row[2];
    }
    // Column wise check:
    for (int i = 0; i < 3; i++) {
        char col[3]; // short for COLumn occupants
        for (int j = 0; j < 3; j++)
            col[j] = getOccupant(Point(i, j));
        if (col[0] == col[1]  && col[1] == col[2] && col[2] != 'N')
            return col[2];
    }
    // Diagonals' check:
    char diag[3]; // short for DIAGonal occupants
    for (int i = 0; i < 3; i++) // checking bottom left to top right diagonal
        diag[i] = getOccupant(Point(i, i));
    if (diag[0] == diag[1] && diag[1] == diag[2] && diag[2] != 'N')
        return diag[2];
    for (int i = 0; i < 3; i++) // checking top left to bottom right diagonal
        diag[i] = getOccupant(Point(i, 2 - i));
    if (diag[0] == diag[1] && diag[1] == diag[2] && diag[2] != 'N')
        return diag[2];
    if (!isFull())
        return 'N';
    else
        return 'D';
}

bool Board::isFull() {
    bool is_full = true;
    for (int i = 0; i < 9; i++) {
        if (layout[i] == 'N') {
            is_full = false;
            break;
        }
    }
    return is_full;
}

int Board::isPosValid(Point pos) {
    if (pos.isValid())
        return 1;
    else
        return 0;
}

int Board::isOccupantValid(char occupant) {
    if (occupant == '1' || occupant == '2' || occupant == 'N')
        return 1;
    else
        return 0;
}