#ifndef PERSONAJ_H
#define PERSONAJ_H
#include <QObject>
#include <QTime>
#include <QDebug>

class iPersonaj:public QObject
{
    Q_OBJECT
protected:

public:
    int Position[2];

    virtual void MLeft()=0;
    virtual void MRight()=0;
    virtual void Jump()=0;

    int lives;
    bool onPosition;
    bool isPush;
    int ground;
    int levitacia;


//=======================
    QTime clock;
    float dx,dy;
    bool onGround;
signals:
    void Draw(int,int,int);
};

class PersonajR:public iPersonaj
{
public:
    PersonajR();
    virtual void MRight();
    virtual void MLeft();
    virtual void Jump();


};

class PersonajG:public iPersonaj
{
public:
    PersonajG();
    virtual void MRight();
    virtual void MLeft();
    virtual void Jump();
};

class PersonajB:public iPersonaj
{
public:
    PersonajB();
    virtual void MRight();
    virtual void MLeft();
    virtual void Jump();
};

#endif // PERSONAJ_H
