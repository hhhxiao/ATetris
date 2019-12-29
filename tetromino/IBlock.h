#ifndef IBLOCK_H
#define IBLOCK_H
#include "tetromino.h"
class IBlock:public Tetromino {
public:
    IBlock(GameMap *map,QWidget *parent):Tetromino(TetrominoType::I,map,parent){
        this->blocks = new Grid<bool>(4,4,false);
        for(int i = 0;i<4;i++)
            blocks->set(i,1,true);
        this->x = 3;
        this->setFixedSize(map->getWidth()*GameMap::GRID_WIDTH,map->getHeight()*GameMap::GRID_WIDTH);
    }
};
#endif // IBLOCK_H
