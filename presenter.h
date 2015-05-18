#ifndef PRESENTER_H
#define PRESENTER_H
#include "iview.h"
#include <QObject>
#include <QDebug>
#include <QTime>
#include "game.h"
#include "personaj.h"
#include "block.h"
#include <QVector>

class Presenter:public QObject
{
    Q_OBJECT
public:
    Presenter(iView *view);
public slots:
    void ML();
    void MR();
    void MU();
    void Pause();
    void Action();
    void Vybor();
    void NewPer(int);
    void TimeOut();
    void NewBlock();
//    void DrawBlock(int,int,int);
private:
    void Collision(int);
    void FallingBlock();
    void FallingBlock(int);
    void Line();
    bool Naloj(int,int,int,int);
    int SearchBlock(int,int);
    bool BlockDown(int);
    bool isML(int);

    iView* view;
    QTimer *timer;
    Game *game;
    iPersonaj *pers;
    QTimer *_newBlock;
    int _pole[12];
    int _fullpole[12][6];
    QList <Block*> BL;
//    Block *BL;
    //----------
    bool isblock;
    bool isblockfall;
    int _score;
    int isFalling;
    float frame;

    //==========

};

#endif // PRESENTER_H
