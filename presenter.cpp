#include "presenter.h"


Presenter::Presenter(iView *view)
{
    game=new Game();
    timer=new QTimer(this);
    _newBlock= new QTimer(this);
    isFalling=-1;
    _score=0;
    this->view=view;
    QObject *view_obj = dynamic_cast<QObject*>(view);
    Q_UNUSED(view_obj);
    QObject::connect(view_obj,SIGNAL(Left()),this,SLOT(ML()));
    QObject::connect(view_obj,SIGNAL(Right()),this,SLOT(MR()));
    QObject::connect(view_obj,SIGNAL(Up()),this,SLOT(MU()));
    QObject::connect(view_obj,SIGNAL(Pause()),this,SLOT(Pause()));
    QObject::connect(view_obj,SIGNAL(Action()),this,SLOT(Action()));
    QObject::connect(view_obj,SIGNAL(NewGAME()),this,SLOT(Vybor()));
    QObject::connect(game,SIGNAL(PaintVybor(int)),view_obj,SLOT(PaintVybor(int)));
    QObject::connect(view_obj,SIGNAL(LeftVybor()),game,SLOT(LeftVybor()));
    QObject::connect(view_obj,SIGNAL(RightVybor()),game,SLOT(RightVybor()));
    QObject::connect(view_obj,SIGNAL(Select()),game,SLOT(SelectVybor()));
    QObject::connect(game,SIGNAL(EndVybor(int)),view_obj,SLOT(EndVybor(int)));
    QObject::connect(game,SIGNAL(EndVybor(int)),this,SLOT(NewPer(int)));
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(TimeOut()));
    QObject::connect(_newBlock,SIGNAL(timeout()),this,SLOT(NewBlock()));
    QObject::connect(view_obj,SIGNAL(Pause()),this,SLOT(Vybor()));

    for(int i=0;i<12;i++)
        for(int j=0;j<6;j++)
            _fullpole[i][j]=0;

    timer->start(50);//50
    //заглушка1
    pers=new PersonajR();
    NewBlock();
    frame=0;
}

void Presenter::ML(){
    pers->MLeft();
}

void Presenter::MR(){
    pers->MRight();
}

void Presenter::MU(){
    pers->Jump();
}

void Presenter::Action(){
}

void Presenter::Pause(){
}


void Presenter::Vybor(){
    if(timer->isActive()){timer->stop();
    for(int i=0;i<BL.length();i++){
                    qDebug()<<BL[i]->nomer<<BL[i]->Position[0]<<BL[i]->Position[1]<<BL[i]->_color;
    }
    }
    else timer->start(50);

//    view->GameOver();
}

void Presenter::NewPer(int NomPer){
    switch (NomPer){
        case 0: pers=new PersonajR(); break;
        case 1: pers=new PersonajG(); break;
        case 2: pers=new PersonajB(); break;
    }
    view->DrawPers(pers->Position[0],pers->Position[1],0,_fullpole);
}




void Presenter::TimeOut(){
    FallingBlock();
    FallingBlock(isFalling);
//разбиение блока
    if(Naloj(pers->Position[0],pers->Position[1],BL[BL.length()-1]->Position[0],BL[BL.length()-1]->Position[1])
           && pers->dy>0 /*&& pers->dx==0*/){
        BL.removeLast();
        _score++;
        view->UpdateScore(_score);
        NewBlock();
    }
//удар по голове
    if(Naloj(pers->Position[0],pers->Position[1],BL[BL.length()-1]->Position[0],BL[BL.length()-1]->Position[1])
           && pers->dy==0){
        timer->stop();
        _newBlock->stop();
        view->GameOver();
    }

    if(!pers->onPosition){pers->Position[0]+=pers->dx; if(pers->dx>0){frame+=0.5; if(frame>2) frame-=2;}
                                                       if(pers->dx<0){frame-=0.5; if(frame<-3)frame+=2;}}
//падающие блоки
    if(Naloj(pers->Position[0],pers->Position[1],BL[BL.length()-1]->Position[0],BL[BL.length()-1]->Position[1])
           && pers->dx!=0){
        if(pers->dx>0){
            if(BL.last()->Position[0]>=440){
            pers->Position[0]=(pers->Position[0]/40)*40; pers->dx=0;}
            BL.last()->Position[0]=pers->Position[0]+40;
        }else{
            BL.last()->Position[0]=pers->Position[0]-40;
        }
    }

//наземные блоки
    if(pers->dx>0){
        int iter=SearchBlock(pers->Position[0]/40+1,pers->Position[1]/40);
        if(iter!=-1){
            BL[iter]->UpdatePole(_fullpole);
            if(!BL[iter]->MR()) {Collision(0);}
            else{
                if(Naloj(pers->Position[0],pers->Position[1],BL[iter]->Position[0],BL[iter]->Position[1])){
                    BL[iter]->Position[0]=pers->Position[0]+40;
                    pers->isPush=true;
                    view->DrawBlock(-1,BL[iter]->_color,BL[iter]->Position[0],BL[iter]->Position[1]);
                    _fullpole[pers->Position[0]/40+1][pers->Position[1]/40]=0;
                    if((BL[iter]->Position[0]+4)%40==0){
                        BL[iter]->Position[0]+=4;
                        if(BL[iter]->isMD()) {int *tempo=BL[iter]->getPos(); /*qDebug()<<"pada"<<tempo[0]<<tempo[1];*/
                            _fullpole[tempo[0]][tempo[1]]=0; BlockDown(iter);}
//                        if(BL[iter]->isMD()) BlockDown(iter);
                        int* temp=BL[iter]->getPos();
                        _fullpole[temp[0]][temp[1]]=BL[iter]->_color+1;
                        view->DrawBlock(-1,BL[iter]->_color,BL[iter]->Position[0],BL[iter]->Position[1]);
                        pers->isPush=false;
                    }
                }
            }
        }
    }else{
        if(pers->dx<0){
//влево
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            if(SearchBlock(pers->Position[0]/40-1,pers->Position[1]/40)!=-1 /*&& !pers->onGround*/)Collision(0);
//            pers->Position[0]-=pers->dx;
            int iter=-1;
                if(pers->Position[0]%40>=36)iter=SearchBlock(pers->Position[0]/40,pers->Position[1]/40);
                else                        iter=SearchBlock(pers->Position[0]/40-1,pers->Position[1]/40);
            if(iter!=-1){
qDebug()<<"est block";
                BL[iter]->UpdatePole(_fullpole);
                if(/*!BL[iter]->ML()*/!isML(iter)){
                    Collision(0);
                    qDebug()<<"stoyat";
                }
                else{
                    if(Naloj(pers->Position[0],pers->Position[1],BL[iter]->Position[0],BL[iter]->Position[1])){
                        BL[iter]->Position[0]=pers->Position[0]-40;/*qDebug()<<"POSLE"<<BL[iter]->Position[0];*/
                        pers->isPush=true;
                        view->DrawBlock(-1,BL[iter]->_color,BL[iter]->Position[0],BL[iter]->Position[1]);
                        _fullpole[pers->Position[0]/40][pers->Position[1]/40]=0;
//                        qDebug()<<"Obnul"<<pers->Position[0]/40<<pers->Position[1]/40;
                        if((BL[iter]->Position[0]-4)%40==0){
                            BL[iter]->Position[0]-=4;
                            if(BL[iter]->isMD()) {int *tempo=BL[iter]->getPos(); _fullpole[tempo[0]][tempo[1]]=0; BlockDown(iter);}
//                            if(BL[iter]->isMD()) BlockDown(iter);
                            int* temp=BL[iter]->getPos();
                            _fullpole[temp[0]][temp[1]]=BL[iter]->_color+1;
                            view->DrawBlock(-1,BL[iter]->_color,BL[iter]->Position[0],BL[iter]->Position[1]);
                            pers->isPush=false;
                        }
                    }
                }
            }
        }
    }


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






    if(pers->onGround) pers->ground=pers->Position[1];
    if(pers->Position[1]>=pers->ground+60)
    {
        if (pers->levitacia==3){
            pers->dy=-4; pers->levitacia=0;}
        else {pers->levitacia++; pers->dy=0;}
    }
    if(!pers->onGround){
        pers->Position[1]+=pers->dy;
    }
    Collision(1);

    //
    pers->onPosition=false;
    //
    if(!(pers->Position[0]%40)){pers->dx=0; pers->onPosition=true; if(pers->onGround)frame=0;}
    if(!pers->onGround){ if(pers->dx<0)frame=-5; if(pers->dx>0) frame=5;}
    view->DrawPers(pers->Position[0],pers->Position[1],frame,_fullpole);//рисование персонажа
    if(pers->Position[1]==pers->ground) pers->onGround=true;
//========================================================================================






}

void Presenter::Collision(int dir){
    if(dir==0){
        if(pers->Position[0]<0){ pers->Position[0]=0; pers->dx=0;}else
        if(pers->Position[0]>11*40){ pers->Position[0]=11*40; pers->dx=0;}else
        if(pers->dx>0 && pers->Position[0]%40){
            if(_fullpole[(pers->Position[0]+40)/40][pers->Position[1]/40]) {
                pers->Position[0]=(pers->Position[0]/40)*40; pers->dx=0;
            }
        }else
        if(pers->dx<0 && pers->Position[0]%40 && pers->Position[0]/40>=0){
            if(_fullpole[(pers->Position[0]/40)][pers->Position[1]/40]){
                pers->Position[0]=(pers->Position[0]/40+1)*40; pers->dx=0;
            }
        }
    }else{
        if(pers->Position[1]<=0){pers->Position[1]=0; pers->dy=0; pers->onGround=true; pers->ground=0;}else
        if(pers->dy<0 && !pers->onGround){
            if(_fullpole[pers->Position[0]/40][(pers->Position[1]/40)]
                    || _fullpole[(pers->Position[0]+39)/40][(pers->Position[1]/40)]){
                pers->Position[1]=(pers->Position[1]/40+1)*40;
                pers->dy=0; pers->onGround=true; pers->ground=(pers->Position[1]/40+1)*40;
            }
        }
        if(pers->onGround && pers->Position[1]>1){
                if(!_fullpole[pers->Position[0]/40][(pers->Position[1]/40)-1])
                    {
                    if(pers->onPosition)
                    if(pers->onGround){
                            pers->dy=-4; pers->onGround=false; pers->ground=(pers->Position[1]/40-1)*40;
                        }
                    }
        }
    }
}

void Presenter::NewBlock(){
    QTime _time(0,0,0);
    qsrand(_time.secsTo(QTime::currentTime()));
    int _colorBlock=qrand()%5;
    int _positionBlock=qrand()%12;
    int temp[2]={_positionBlock,6};
    BL.push_back(new Block(BL.length(),_colorBlock,_fullpole,temp));
    view->DrawBlock(BL[BL.length()-1]->nomer,BL[BL.length()-1]->_color,BL[BL.length()-1]->Position[0],BL[BL.length()-1]->Position[1]);
}

void Presenter::FallingBlock(){
        BL[BL.length()-1]->UpdatePole(_fullpole);
        bool b=BL[BL.length()-1]->MD();
        view->DrawBlock(BL[BL.length()-1]->nomer,BL[BL.length()-1]->_color,BL[BL.length()-1]->Position[0],BL[BL.length()-1]->Position[1]);
        if(b) {
            int* temp=BL[BL.length()-1]->getPos();
            _fullpole[temp[0]][temp[1]]=BL[BL.length()-1]->_color+1;
            NewBlock();
            Line();
        }
}

void Presenter::FallingBlock(int iter){
    if(isFalling!=-1){
        BL[iter]->UpdatePole(_fullpole);
        bool b=BL[iter]->MD(); BL[iter]->Position[1]+BL[iter]->dy;
        view->DrawBlock(-1,BL[iter]->_color,BL[iter]->Position[0],BL[iter]->Position[1]);
        _fullpole[*(BL[iter]->getPos())][*(BL[iter]->getPos()+1)+1]=0;
        if(b) {
            int* temp=BL[iter]->getPos();
            _fullpole[temp[0]][temp[1]]=BL[iter]->_color+1;
            isFalling=-1;
            Line();
        }
    }
}

void Presenter::Line(){
    if(_fullpole[0][0]&&
       _fullpole[1][0]&&
       _fullpole[2][0]&&
       _fullpole[3][0]&&
       _fullpole[4][0]&&
       _fullpole[5][0]&&
       _fullpole[6][0]&&
       _fullpole[7][0]&&
       _fullpole[8][0]&&
       _fullpole[9][0]&&
       _fullpole[10][0]&&
       _fullpole[11][0]){
        _score+=12;
        view->UpdateScore(_score);
        for(int k=0;k<5;k++){
            for(int j=0;j<12;j++){
                _fullpole[j][k]=_fullpole[j][k+1];
        }}
        for(int j=0;j<11;j++){
            _fullpole[j][5]=0;
        }
        Block *temp; temp=BL.last(); BL.removeLast();
        for(int i=0;i<12;i++){
            int iter=SearchBlock(i,0);
            if(iter!=-1){
                BL.swap(BL.length()-1,iter);
                BL.removeLast();
            }
        }
        BL.push_back(temp);
        for(int i=0;i<BL.length();i++){
            BL[i]->Position[1]-=40;
        }
//        for(int i=0;i<BL.length();i++){
////            qDebug()<<BL[i]->nomer<<BL[i]->Position[0]<<BL[i]->Position[1];
//        }
        BL[BL.length()-1]->UpdatePole(_fullpole);
        view->DrawBlock(BL[BL.length()-1]->nomer,BL[BL.length()-1]->_color,BL[BL.length()-1]->Position[0],BL[BL.length()-1]->Position[1]);
    }
}

bool Presenter::Naloj(int x1,int y1,int x2,int y2){
    y2+=40;
    if(x1 >= (x2+40) || x2 >= (x1+40) || y1 > (y2+40) || y2 > (y1+80))return false;
    else return true; //пересекаются
}

int Presenter::SearchBlock(int x, int y){
    //qDebug()<<"Nujno"<<x<<y;
    int kkk=-1;
    int *temp;
    for(int i=0; i<BL.length();i++){
        temp=BL[i]->getPos();   //qDebug()<<"est"<<temp[0]<<temp[1]<<"Nom"<<BL[i]->nomer;
        if(temp[0]==x && temp[1]==y){
            kkk=i; break;
        }
    }
    return kkk;
}

bool Presenter::BlockDown(int i){
    BL[i]->UpdatePole(_fullpole);
    BL[i]->onGround=false;
    BL[i]->dy=-4;
    isFalling=i;
}


bool Presenter::isML(int it){
//    qDebug()<<"Pers"<<pers->Position[0]<<pers->Position[1]<<(pers->Position[0])/40-1<<(pers->Position[1]+40)/40;
    if(!_fullpole[(pers->Position[0])/40-1][(pers->Position[1]+40)/40]){



//    qDebug()<<(Position[0]-4)/40<<(Position[1]+40)/40<<Position[0]/40<<(Position[1]+40)/40+1;
//    if(!_pole[(Position[0]-4)/40][(Position[1]+40)/40] && !_pole[Position[0]/40][(Position[1]+40)/40+1] &&
//            (Position[0]/40-1)>=0){
        qDebug()<<"true"; return true;
    }
    else {qDebug()<<"false"; return false;}
}
