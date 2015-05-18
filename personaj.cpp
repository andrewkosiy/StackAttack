#include "personaj.h"


PersonajR::PersonajR()
{
    clock.start();


    lives=2;
    Position[0]=0;
    Position[1]=0;
    onPosition=true;
    onGround=true;
    isPush=false;
    dx=dy=0;
    ground=0;
    levitacia=0;
}

PersonajG::PersonajG()
{
    lives=2;
    Position[0]=0;
    Position[1]=0;
    onPosition=true;
}

PersonajB::PersonajB()
{
    lives=2;
    Position[0]=0;
    Position[1]=0;
    onPosition=true;
}
//==========================================
void PersonajR::MRight(){
    if(onPosition && Position[0]<440){
            this->dx=4; onPosition=false;
    }
}

void PersonajR::MLeft(){
    if(onPosition && Position[0]>0){
            this->dx=-4; onPosition=false;
    }
}

void PersonajR::Jump(){
//    qDebug()<<onGround;
    if(Position[1]<5*40)
    if(onGround && onPosition/* && !isPush*/){
            this->dy=4; onGround=false;}
}



//===============================================
void PersonajG::MRight(){
    return;
}

void PersonajG::MLeft(){
    return;
}

void PersonajG::Jump(){
    return;
}


void PersonajB::MRight(){
        Position[0]++;
}

void PersonajB::MLeft(){
    return;
}

void PersonajB::Jump(){
    return;
}


