#include "gamewidget.h"

GameWidget::GameWidget(SeqBase *seqBase,QWidget *parent) : QWidget(parent)
{
    //    this->setAutoFillBackground(true);
    //    QPalette palette = this->palette();
    //    palette.setBrush(QPalette::Window,
    //                     QBrush(QPixmap(":/theme/theme/gameBg.png").scaled(
    //                                this->size(),
    //                                Qt::IgnoreAspectRatio,
    //                                Qt::SmoothTransformation)));
    bg = new QPixmap();
    bg->load(":/theme/theme/gameBg.png");

    this->seq = seqBase;
    this->setGeometry(2*C::WIDTH,2*C::WIDTH,C::WIDTH*22,C::WIDTH*22);
    gameMap = new GameMap(this);
    mino = new Tetromino(1,gameMap,gameMap);
    for (int i = 0;i<6;i++) {
        NextWindow* next = new NextWindow(this,seq->getNext());
        next->setGeometry(C::WIDTH*17,(3*i+1)*C::WIDTH,C::WIDTH*4,C::WIDTH*3);
        this->nextWindows.push_back(next);
    }
    this->holdWindow = new NextWindow(this,7);
    holdWindow->setGeometry(C::WIDTH,C::WIDTH,C::WIDTH*4,C::WIDTH*4);
    b = new BloodBar(this);
    b->setGeometry(C::WIDTH*5.5,C::WIDTH,C::WIDTH/2,C::WIDTH*C::MAP_HEIGHT);
    keyManager = new KeyPressManager();
    keyManager->setGameWidget(this);
    geneNewMino();

    connect(mino,SIGNAL(death(int)),this,SLOT(geneNewMino()));
    connect(mino,SIGNAL(death(int)),gameMap,SLOT(clearLine(int)));
    connect(mino,SIGNAL(death(int)),this,SLOT(enableHold()));
    connect(gameMap,SIGNAL(lineSignal(int)),this,SLOT(statUpdate(int)));
}

void GameWidget::hold()
{
    if(!hasHold){
        if(holdWindow->getType() == C::EMPTY){
            holdWindow->setType(mino->getType());
            geneNewMino();
        }
        int type = mino->getType();
        mino->reset(holdWindow->getType());
        mino->update();
        holdWindow->setType(type);
        hasHold = true;
    }
}

void GameWidget::keyPressEvent(QKeyEvent *event){if(keyManager)keyManager->keyPressHandler(event);}

void GameWidget::keyReleaseEvent(QKeyEvent *event){if(keyManager)keyManager->keyReleaseHanler(event);}

void GameWidget::wheelEvent(QWheelEvent *event){if(keyManager)keyManager->wheelEventHandler(event);}

void GameWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QFont font = p.font();
    font.setBold(true);//加粗
    font.setPixelSize(20);//改变字体大小
    p.setFont(font);
    p.drawPixmap(0,0,C::WIDTH*22,C::WIDTH*22,*bg);
    QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
       option.setWrapMode(QTextOption::WordWrap);
    p.drawText(QRect(C::WIDTH,C::WIDTH*6,C::WIDTH*4,C::WIDTH*16),
               QString("LINE:%1\n TSM:%2\n TSS:%3\n TSD:%4\n TST:%5\n 1:%6\n 2:%7\n 3:%8\n 4:%9")
               .arg(stat.lineClear)
               .arg(stat.tsm)
               .arg(stat.tss)
               .arg(stat.tsd)
               .arg(stat.tst)
               .arg(stat.singe)
               .arg(stat.doub)
               .arg(stat.trigle)
               .arg(stat.tetris)
               ,option);
}

void GameWidget::statUpdate(int lineClerSinnal)
{
    /**
const QMap<int,QString> C::LINE_CLEAR_TYPE = {
    {1,"single"},
    {2,"double"},
    {3,"trigle"},
    {4,"tetris"},
    {6,"tss"},
    {7,"tsd"},
    {8,"tst"},
    {11,"t mini"}
};

      */
    stat.addLineClear(lineClerSinnal % 5);
    switch (lineClerSinnal) {
    case 1:
        stat.addSingle();break;
    case 2:
        stat.addDouble();break;
    case 3:
        stat.addTrigle();break;
    case 4:
        stat.addTertis();break;
    case 6:
        stat.addTss();break;
    case 7:
        stat.addTsd();break;
    case 8:
        stat.addTst();break;
    case 11:
        stat.addTsm();break;
    }
    update();
}

void GameWidget::geneNewMino()
{
    mino->reset(nextWindows[0]->getType());
    int size = nextWindows.size();
    for(int i = 0;i<size-1;i++)
        nextWindows[i]->setType(nextWindows[i+1]->getType());
    nextWindows[size-1]->setType(seq->getNext());
}
