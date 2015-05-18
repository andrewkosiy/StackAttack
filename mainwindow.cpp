#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->action,SIGNAL(triggered()),this,SLOT(NewGame()));
    QObject::connect(ui->action_2,SIGNAL(triggered()),this,SLOT(close()));
    PoziciaIgry=2;                                                                          //PoziciaIgry=0;  заглушка1
    for(int i=0;i<12;i++)
        for(int j=0;j<6;j++)
            Pole[i][j]=0;
    background.load("../StackAttack/img/Background.png");
    R.load("../StackAttack/img/RedBlock.png");
    G.load("../StackAttack/img/GreenBlock.png");
    B.load("../StackAttack/img/BlueBlock.png");
    Y.load("../StackAttack/img/YellowBlock.png");
    Grey.load("../StackAttack/img/GreyBlock.png");
    GAMEOVER.load("../StackAttack/img/gameover.jpg");

    PosPer[0]=PosPer[1]=0; Per.load("../StackAttack/img/RedPer.png");                       //заглушка1
    isFallingBlock=false;
    isMove=false;
    isGameOver=false;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NewGame(){
//    qDebug()<<"New";
    emit NewGAME();
}

void MainWindow::keyPressEvent(QKeyEvent *keyEvent){
//    QMessageBox message;
    switch (keyEvent->key()) {
        case Qt::Key_Left: if(PoziciaIgry==1)emit LeftVybor();else if(PoziciaIgry==2) emit Left(); break;
        case Qt::Key_Right: if(PoziciaIgry==1)emit RightVybor();else if(PoziciaIgry==2) emit Right(); break;
        case Qt::Key_Up: emit Up(); break;
        case Qt::Key_Escape: emit Pause();
//            message.setText("Pause\n"+ui->label->text());
//            message.exec();
//            break;
        case Qt::Key_Space: if(PoziciaIgry==1)emit Select();else if(PoziciaIgry==2) emit Action(); break;
    }
}

void MainWindow::paintEvent(QPaintEvent *e){
    Q_UNUSED(e);
    QPainter painter(this);
    if(PoziciaIgry==0){                                                                     //заставка
        block.load("../StackAttack/img/Start.png");
//        painter.drawPixmap(10,30,510,450,block);
        painter.drawPixmap(10,30,510,450,GAMEOVER);
    }
    else if(PoziciaIgry==1){                                                                //выбор персонажа
        painter.drawPixmap(10,30,510,450,PerVybor);
    }
    else if(PoziciaIgry==2){                                                                //игра
        painter.drawPixmap(10,30,510,450,background);
        for(int i=0;i<12;i++)
            for(int j=0;j<6;j++)
            {
                if(Pole[i][j]==1) painter.drawPixmap(30+i*40,410-j*40,40,40,R);
                if(Pole[i][j]==2) painter.drawPixmap(30+i*40,410-j*40,40,40,G);
                if(Pole[i][j]==3) painter.drawPixmap(30+i*40,410-j*40,40,40,B);
                if(Pole[i][j]==4) painter.drawPixmap(30+i*40,410-j*40,40,40,Y);
                if(Pole[i][j]==5) painter.drawPixmap(30+i*40,410-j*40,40,40,Grey);
            }
        painter.drawPixmap(30+PosPer[0],370-PosPer[1],40,80,Per);
        if(isFallingBlock){
            switch(fallingblock){
                case 0: painter.drawPixmap(30+PosBl[0],370-PosBl[1],40,40,R); break;
                case 1: painter.drawPixmap(30+PosBl[0],370-PosBl[1],40,40,G); break;
                case 2: painter.drawPixmap(30+PosBl[0],370-PosBl[1],40,40,B); break;
                case 3: painter.drawPixmap(30+PosBl[0],370-PosBl[1],40,40,Y); break;
                case 4: painter.drawPixmap(30+PosBl[0],370-PosBl[1],40,40,Grey); break;
            }
        }
        if(isMove){
            switch(BlN){
            case 0: painter.drawPixmap(30+PosBlN[0],370-PosBlN[1],40,40,R); break;
            case 1: painter.drawPixmap(30+PosBlN[0],370-PosBlN[1],40,40,G); break;
            case 2: painter.drawPixmap(30+PosBlN[0],370-PosBlN[1],40,40,B); break;
            case 3: painter.drawPixmap(30+PosBlN[0],370-PosBlN[1],40,40,Y); break;
            case 4: painter.drawPixmap(30+PosBlN[0],370-PosBlN[1],40,40,Grey); break;
            }
        }
    }
}

void MainWindow::PaintVybor(int NomPer){
//    qDebug()<<NomPer;
    PoziciaIgry=1;
    switch(NomPer){
        case 0: PerVybor.load("../StackAttack/img/RedPerVyb.png"); break;
        case 1: PerVybor.load("../StackAttack/img/GreenPerVyb.png"); break;
        case 2: PerVybor.load("../StackAttack/img/BluePerVyb.png"); break;
    }
    this->update();
}

void MainWindow::EndVybor(int NomPer){
    switch(NomPer){
    case 0: Per.load("../StackAttack/img/RedPer.png"); break;
    case 1: Per.load("../StackAttack/img/GreenPer.png"); break;
    case 2: Per.load("../StackAttack/img/BluePer.png"); break;
    }
    PoziciaIgry=2;
    this->update();
}

void MainWindow::DrawPers(int Pos1,int Pos2,int Sprite,int fullpole[12][6]){
//    qDebug()<<Sprite;
    switch(5-Sprite){
        case 5:Per.load("../StackAttack/img/RedPer.png"); break;
        case 4:Per.load("../StackAttack/img/RedPer1.png"); break;
        case 3:Per.load("../StackAttack/img/RedPer2.png"); break;
        case 0: Per.load("../StackAttack/img/RedPerj.png"); break;
        case 6: Per.load("../StackAttack/img/RedPer-1.png"); break;
        case 7: Per.load("../StackAttack/img/RedPer-2.png"); break;
        case 10: Per.load("../StackAttack/img/RedPer-j.png"); break;
    }

    PosPer[0]=Pos1;
    PosPer[1]=Pos2;
//    int **P;
//    **P=&fullpole;
            //адресс на двумерный массив
   for(int i=0;i<12;i++)
       for(int j=0;j<6;j++)
           Pole[i][j]=fullpole[i][j];


    this->update();
}


void MainWindow::DrawBlock(int nom,int col,int pos1,int pos2){
    if(nom==-1){
        isMove=true;
        BlN=col;
        PosBlN[0]=pos1;
        PosBlN[1]=pos2;
    }else{
        isFallingBlock=true;
        isMove=false;
        fallingblock=col;
        PosBl[0]=pos1;
        PosBl[1]=pos2;
    }
    this->update();
}


void MainWindow::UpdateScore(int score){
    ui->label->setText(QString::number(score));
}


void MainWindow::GameOver(){
    PoziciaIgry=0;
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->setGeometry((520-ui->label->height())/2+5, 50,ui->label->height(),ui->label->width());
    this->update();
}
