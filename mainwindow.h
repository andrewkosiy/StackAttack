#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtGui>
#include "iview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public iView
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPixmap block;
    QPixmap PerVybor;
    QPixmap background;
    QPixmap Per;
    QPixmap GAMEOVER;
    int PoziciaIgry;
    int PosPer[2];
    int Pole[12][6];                                                                   //0-пусто; 1-red; 2-green; 3-blue; 4-yellow; 5-grey;
    QPixmap R,G,B,Y,Grey;
    bool isFallingBlock;
    int PosBl[2];
    int fallingblock;
    int PosBlN[2],BlN;
    bool isMove;
    bool isGameOver;

private:
    Ui::MainWindow *ui;

public:


    virtual void keyPressEvent(QKeyEvent *);
    virtual void paintEvent(QPaintEvent *e);
    virtual void DrawPers(int,int,int,int[12][6]);
    virtual void UpdateScore(int);
    virtual void GameOver();
public slots:
    void NewGame();
    void PaintVybor(int NomPer);
    void EndVybor(int NomPer);
    void DrawBlock(int,int,int,int);

signals:
    void Up();
    void Left();
    void Right();
    void Pause();
    void Action();
    void NewGAME();
    void Select();
    void RightVybor();
    void LeftVybor();
};

#endif // MAINWINDOW_H
