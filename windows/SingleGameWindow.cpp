#include "singlegamewindow.h"
#include "ui_singlegamewindow.h"

SingleGameWindow::SingleGameWindow(ModeBase *base,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SingleGameWindow),base(base)
{
    ui->setupUi(this);

    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
                     QBrush(QPixmap(":/theme/theme/gbg.png").scaled(
                                this->size(),
                                Qt::IgnoreAspectRatio,
                                Qt::SmoothTransformation)));
    this->setPalette(palette);
    overDialog = new GameOverDialog(this);
    dropTimer = new QTimer(this);
    widget = new GameWidget(base->getSeq(),this);
    widget->setKeyEnable(false);
    widget->setFocus();
    base->setStartWindow(this);
    ui->modeName->setText(base->getName());
    connect(widget->getGameMap(),SIGNAL(lineSignal(int)),this,SLOT(staticUpdate(int)));
    connect(dropTimer,SIGNAL(timeout()),widget,SLOT(drop()));
    this->stat = new GameStat();

    this->stopWatchTimer = new QTimer(this);
    connect(stopWatchTimer,SIGNAL(timeout()),SLOT(updateWatch()));
    this->stopWatch = QTime(0,0,0);
    this->showMaximized();
    base->gameinitListener();
    start();
}

SingleGameWindow::~SingleGameWindow()
{
    delete ui;
    delete base;
    delete stat;
    delete dropTimer;
    delete stopWatchTimer;
}

QLabel *SingleGameWindow::getStatLabel()
{
    return  ui->stat;
}

void SingleGameWindow::staticUpdate(int type)
{
    stat->addLineClear(type % 5);
    qDebug()<<C::LINE_CLEAR_TYPE[type];
    base->statUpdateListener();
    gameCheack();
}

void SingleGameWindow::end()
{
    this->stopWatchTimer->stop();
    overDialog->show();

}
void SingleGameWindow::start()
{
    widget->getGameMap()->setFocus();
    base->gameStartListener();
   // dropTimer->start(1000);
    stopWatchTimer->start(1000);
}

void SingleGameWindow::gameCheack()
{
    if(base->gameWinListener() || base->gameLoseListener()){
        end();
    }
}

void SingleGameWindow::updateWatch()
{
    stopWatch = stopWatch.addSecs(1);
    ui->stopWatch->setText(stopWatch.toString("mm:ss.zzz"));
}
