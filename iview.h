#ifndef IVIEW_H
#define IVIEW_H
#include <QtWidgets>

class iView
{
public:
    virtual void paintEvent(QPaintEvent* e)=0;
    virtual void keyPressEvent(QKeyEvent* keyEvent)=0;
    virtual void DrawPers(int,int,int,int[12][6])=0;
    virtual void DrawBlock(int,int,int,int)=0;
    virtual void UpdateScore(int)=0;
    virtual void GameOver()=0;
};

#endif // IVIEW_H
