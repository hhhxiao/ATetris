#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "nextwindow.h"
#include "../tetromino/tetro.h"
#include "bloodbar.h"
#include <QVector>
#include "../config/keypressmanager.h"
#include "../seq/seq.h"
/**游戏WIdget
 * 包含了游戏视图所需要的所有组件
 * - 地图
 * - next窗口*6
 * - hold
 * - 一个块
 * - 按键绑定接口
 * - 序列生成器接口
 * @brief The GameWidget class
 */
class GameWidget : public QWidget
{
    Q_OBJECT
private:
    GameMap *gameMap;
    Tetromino *mino;
    QVector<NextWindow *> nextWindows;
    BloodBar *b;
    SeqBase *seq;
    NextWindow *holdWindow;
    KeyPressManager *keyManager;
    bool keyEnable = false;
    bool hasHold = false;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private slots:
    void enableHold(){this->hasHold = false;}

public:
    explicit GameWidget(SeqBase *seqBase,QWidget *parent = nullptr);
    void SetKeyManager(KeyPressManager *m){keyManager = m;}
    void setSeq(SeqBase *seq){this->seq= seq;}
    GameMap* getGameMap(){return this->gameMap;}
    Tetromino* getMino(){return  this->mino;}
    void setKeyEnable(bool value){this->keyEnable = value;}
    void setBarValue(float rate){b->setBar(rate);}
public slots:
    void geneNewMino();
    void drop(){mino->drop();}
    void moveLeft(){mino->moveLeft();}
    void moveRight(){mino->moveRight();}
    void hardrop(){mino->hardDrop();}
    void rRotate(){mino->rigthRotate();}
    void lRotate(){mino->leftRotate();}
    void hold();
signals:

};

#endif // GAMEWIDGET_H
