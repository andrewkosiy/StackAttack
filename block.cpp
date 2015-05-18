#include "block.h"
#include <QDebug>
Block::Block(int nom, int color, int Pole[12][6], int position[2])
{
    nomer=nom;
    for(int i=0;i<12;i++)
        for(int j=0;j<8;j++)
            _pole[i][j]=0;
    _color=color;
    Position[0]=position[0]*40;
    Position[1]=(position[1]+1)*40;
    for(int i=0;i<12;i++)
        for(int j=0;j<6;j++)
            _pole[i][j]=Pole[i][j];
    dy=-4;
    onGround=false;
}

Block::Block(){

}

bool Block::MD(){
    if(!onGround)Position[1]+=dy;
    if(_pole[Position[0]/40][(Position[1]+40)/40]){onGround=true; /*qDebug()<<Position[0]/40<<(Position[1]+40)/40;*/
    Position[1]-=dy;
    }
if((Position[1]+40)<=0) onGround=true;
return onGround;
}

bool Block::MR(){
    if(!_pole[Position[0]/40+1][(Position[1]+40)/40] && !_pole[Position[0]/40][(Position[1]+40)/40+1] &&
            (Position[0]/40+1)<12){
        return true;
    }
    else {return false;}
}

bool Block::ML(){
    qDebug()<<(Position[0]-4)/40<<(Position[1]+40)/40<<Position[0]/40<<(Position[1]+40)/40+1;
    if(!_pole[(Position[0]-4)/40][(Position[1]+40)/40] && !_pole[Position[0]/40][(Position[1]+40)/40+1] &&
            (Position[0]/40-1)>=0){
        qDebug()<<"true"; return true;
    }
    else {qDebug()<<"false"; return false;}
}

void Block::UpdatePole(int pole[12][6]){
    for(int i=0;i<12;i++)
        for(int j=0;j<6;j++)
            _pole[i][j]=pole[i][j];
}

int* Block::getPos(){
    int* a=new int[2];
    a[0]=Position[0]/40;
    a[1]=(Position[1]+40)/40;
    return a;
}

bool Block::isMD(){
    if(Position[1]>=0){
        if(_pole[Position[0]/40][(Position[1]+40)/40-1]){
            return false;
        }return true;
    }
    else return false;
}

