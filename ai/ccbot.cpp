#include "ccbot.h"


CCBot::CCBot(GameMap *map,SeqBase *base)
   :map(map),seq(base)
{
    cc_default_options(&options);
    cc_default_weights(&weights);
    map->syncMap(this->filed);
    this->bot = cc_launch_async(&options,&weights);
    cc_reset_async(bot,filed,false,0);
    for(int i = 0;i<7;i++){
        cc_add_next_piece_async(this->bot,minoAdapterList[seq->getNext()]);
    }

}

CCMove CCBot::getNextMove()
{
    CCMove move;
    cc_request_next_move(bot);
    while(!cc_poll_next_move(bot,&move)){
         qDebug()<<"try Next Move";
    }
        cc_add_next_piece_async(this->bot,minoAdapterList[seq->getNext()]);
        qDebug()<<"can not get Next Move";
       return  move;

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
