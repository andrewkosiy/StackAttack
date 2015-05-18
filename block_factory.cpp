#include "block_factory.h"

Block* RFactory::GetBlock(){
    return new RBlock();
}

Block* GFactory::GetBlock(){
    return new GBlock();
}

Block* BFactory::GetBlock(){
    return new BBlock();
}

Block* YFactory::GetBlock(){
    return new YBlock();
}

Block* GreyFactory::GetBlock(){
    return new GreyBlock();
}

void Block::MD(){
;
}

//bool Block::ML(){
//return true;
//}

//bool Block::MR(){
//return true;
//}
