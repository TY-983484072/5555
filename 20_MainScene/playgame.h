#ifndef PLAYGAME_H
#define PLAYGAME_H

#include <QMainWindow>
#include <mycoin.h>

class PlayGame : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayGame(QWidget *parent = 0);
    PlayGame(int level);
    int m_Level;//记录关卡
    
    //重写绘图事件
    void paintEvent(QPaintEvent *);
    
    //定义二维数组记录金币银币
    int coinArray[4][4];
    
    //定义二维数组储存金币
    MyCoin * cArray[4][4];
    
    //定义是否胜利标志
    bool isWin;
signals:
    //自定义返回信号
    void SelectBack();
public slots:
};

#endif // PLAYGAME_H
