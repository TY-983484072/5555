#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = 0);
    
    //构造函数 参数1 正常显示的图片路劲  参数2 按下后显示的图片路径
    MyPushButton(QString normalImg,QString pressImg = "");
    
    QString normalImgPath;//存储正常显示的图片路径
    QString pressImgPath;//存储按下后显示的图片路径
    
    //添加弹跳方法
    void Zoom1();
    void Zoom2();
    
    //重写鼠标按下释放事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
signals:
    
public slots:
};

#endif // MYPUSHBUTTON_H
