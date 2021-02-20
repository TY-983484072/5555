#ifndef SELECTLEVEL_H
#define SELECTLEVEL_H

#include <QMainWindow>
#include "playgame.h"

class SelectLevel : public QMainWindow
{
    Q_OBJECT
public:
    explicit SelectLevel(QWidget *parent = 0);
    //重写绘图事件
    void paintEvent(QPaintEvent *);
    
    //开始游戏对象
    PlayGame * play;
signals:
    void selectLevelBack();
public slots:
};

#endif // SELECTLEVEL_H
