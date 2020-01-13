#include "ccbot.h"

CCBot::CCBot(GameMap*map,SeqBase *base):
    sequence(base)
    ,map(map)
{
    this->options = new CCOptions();
    this->weights = new CCWeights();
    weights->clear4 = 0;
    this->ccbot = cc_launch_async(options,weights);
    syncMap();
    cc_reset_async(ccbot,filed,true,0);
    for(int i = 0;i < 5 ; ++i){
        for(int j = 1;j<=7;j++){
            cc_add_next_piece_async(ccbot,minoAdapterList[j]);
        }
    }
    cc_request_next_move(ccbot);
}

CCMove CCBot::getNext()
{
    CCMove m;
    m.movement_count = 127;
    if(cc_poll_next_move(ccbot,&m)){
        qDebug()<<"req success";
        cc_request_next_move(ccbot);
    }
    return  m;
}



void CCBot::syncMap()
{
    map->syncMap(this->filed);
}

QMap<int,CCPiece> CCBot::minoAdapterList = {
    {C::I_BLOCK,CC_I},
    {C::T_BLOCK,CC_T},
    {C::J_BLOCK,CC_J},
    {C::L_BLOCK,CC_L},
    {C::S_BLOCK,CC_S},
    {C::Z_BLOCK,CC_Z},
    {C::O_BLOCK,CC_O},
};
