#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = 0);
    MyCoin(QString normalImg);
    //文件路径
    QString m_NormalImg;
    
    int m_X;//x轴坐标
    int m_Y;//y轴坐标
    bool m_Flag;//正反标志
    
    //改变标志
    void changeFlag();
    //金币翻银币定时器
    QTimer * timer1;
    //银币翻金币定时器
    QTimer * timer2;
    //最小值
    int m_Min=1;
    //最大值
    int m_Max=8;
    
    //动画是否完毕标志
    bool m_DH = false;
    
    //重写鼠标按下事件
    void mousePressEvent(QMouseEvent *e);
    
    //胜利标志
    bool isWin = false;
signals:
    
public slots:
};

#endif // MYCOIN_H
