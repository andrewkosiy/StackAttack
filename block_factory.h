#ifndef BLOCK_FACTORY_H
#define BLOCK_FACTORY_H

class Block
{
public:
    int color;   //r-0;g-1;b-2;y-3;grey-4
    int Position[2];
    virtual void MD();
//    virtual bool MR();
//    virtual bool ML();



    virtual ~Block(){}
};

class RBlock:public Block{
public:

};

class GBlock:public Block{
public:

};

class BBlock:public Block{
public:
};

class YBlock:public Block{
public:

};

class GreyBlock:public Block{
public:

};


class Factory{
public:
    virtual Block* GetBlock()=0;
};

class RFactory: public Factory{
public:
    virtual Block* GetBlock();
};

class GFactory: public Factory{
public:
    virtual Block* GetBlock();
};

class BFactory: public Factory{
public:
    virtual Block* GetBlock();
};

class YFactory: public Factory{
public:
    virtual Block* GetBlock();
};

class GreyFactory: public Factory{
public:
    virtual Block* GetBlock();
};



#endif // BLOCK_FACTORY_H
