#ifndef BLOCK_H
#define BLOCK_H
#include <QObject>

class Block:public QObject
{
    Q_OBJECT
public:
    int Position[2];
    int _pole[12][8];
    int dy,dx;
    Block();
    Block(int,int, int[12][6],int[2]);
    bool MR();
    bool ML();
    bool MD();
    void UpdatePole(int[12][6]);
    int* getPos();
    bool onGround;
    int _color;
    int nomer;
    bool isMD();
//signals:
//    void Draw(int,int,int);

};

#endif // BLOCK_H
