#include "game.h"

Game::Game()
{
    _personajVybor=2;                                               //_personajVybor=0;  заглушка1
}
//------------------------------------------------------
//выбор персонажа
void Game::VyborPersonaja(){
    _personajVybor=0;
    emit PaintVybor(_personajVybor);
}

void Game::LeftVybor(){
    if(!_personajVybor)
        _personajVybor=2;
    else _personajVybor--;
    emit PaintVybor(_personajVybor);
}

void Game::RightVybor(){
    _personajVybor=(++_personajVybor)%3;
    emit PaintVybor(_personajVybor);
}

void Game::SelectVybor(){
    emit EndVybor(_personajVybor);
}

int Game::GetPersonaj(){
    return _personajVybor;
}

//======================================================

