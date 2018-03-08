#include "Chess.h"
#include <iomanip>

unsigned short Chess::charToShort(char letter){
    switch (letter) {
        case'0':
        return 0;
        case '1':
        return 1;
        case '2':
        return 2;
        case '3':
        return 3;
        case '4':
        return 4;
        case '5':
        return 5;
        case '6':
        return 6;
        case '7':
        return 7;
        //return 20 para forzar el error de movimiento
        //si el valor introducido no corresponde al tablero
        default:
        return 20;
    }
}

void Chess::start() {
    std::cout << "Colocando las piezas..." << '\n';
    gameOver = false;
    turnNumber = 0;
}


void Chess::turn() {
    if (turnNumber % 2 == 0) {
        std::cout << "Move WHITE piece" << '\n';
        blackTurn=false;
    } else {
        std::cout << "Move BLACK piece" << '\n';
        blackTurn=true;
    }

    turnNumber++;
}
void Chess::moveAsk() {
    bool isValid=false;
    bool isBlack=false;
    std::string piecexy;
    std::string coord;
    do{
        std::cout << "Ficha que quieres mover" << '\n';
        cin>>piecexy;
        std::cout << "Donde quieres moverla" << '\n';
        cin>>coord;
        if (piecexy == "b") {
            Board::getInstance().getBoard() = record.goBack();
        } else {
            isValid=Board::getInstance().valid(charToShort(piecexy[0]),charToShort(piecexy[1]),charToShort(coord[0]),charToShort(coord[1]));
            if(isValid){
                isBlack=Board::getInstance().getCell(charToShort(piecexy[0]),charToShort(piecexy[1])).getPiece()->black;
                if (isBlack!=blackTurn){
                    std::cout <<setw(50)<<"Esta ficha no es de tu color" << '\n';
                }
            }
        }
    }while(!isValid || (isBlack!=blackTurn));
    Board::getInstance().moveOnBoard(charToShort(piecexy[0]),charToShort(piecexy[1]),charToShort(coord[0]),charToShort(coord[1])); // Pawn1
    record.saveBoard(Board::getInstance().getBoard());
    if (deadKing == true) {
        gameOver = true;
    }
}

bool Chess::end() {
    std::cout << "Comprobando jaque mate..." << '\n';
    return gameOver;
}

void Chess::finish() {
    if (turnNumber % 2 == 0) {
        std::cout << "BLACK pieces won" << '\n';
    } else {
        std::cout << "WHITE pieces won" << '\n';
    }
}