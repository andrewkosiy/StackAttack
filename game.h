#ifndef GAME_H
#define GAME_H
#include <QObject>

class Game: public QObject
{
    Q_OBJECT
    int _personajVybor;
public:
    Game();
    void VyborPersonaja();
    int GetPersonaj();
public slots:
    void LeftVybor();
    void RightVybor();
    void SelectVybor();
signals:
    void PaintVybor(int NomPer);
    void EndVybor(int NomPer);
};

#endif // GAME_H
