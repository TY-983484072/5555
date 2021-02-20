#include "mypushbutton.h"
#include <QMessageBox>
#include <QPropertyAnimation>

//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{
    
//}

MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;
    
    QPixmap pix;
    bool ret = pix.load(normalImg);
    if(!ret)
    {
        QMessageBox::warning(this,"提示","图片加载失败");
        return;
    }
    
    //设置图片固定大小
    setFixedSize(pix.width(),pix.height());
    
    //设置不规则图片样式
    setStyleSheet("QPushButton{border:0px;}");
    
    //设置图标
    setIcon(pix);
    
    //设置图标大小
    setIconSize(QSize(pix.width(),pix.height()));
}

void MyPushButton::Zoom1()
{
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置时间间隔，单位毫秒
    animation->setDuration(200);
    //创建起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置缓和曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation->start();
}
 
void MyPushButton::Zoom2()
{
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置时间间隔，单位毫秒
    animation->setDuration(200);
    //创建起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置缓和曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation->start();
}

//重写鼠标按下释放事件
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath!="")
    {
        QPixmap pix;
        bool ret = pix.load(this->pressImgPath);
        if(!ret)
        {
            QMessageBox::warning(this,"提示","图片加载失败");
            return;
        }
        
        //设置图片固定大小
        setFixedSize(pix.width(),pix.height());
        
        //设置不规则图片样式
        setStyleSheet("QPushButton{border:0px;}");
        
        //设置图标
        setIcon(pix);
        
        //设置图标大小
        setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImgPath!="")
    {
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);
        if(!ret)
        {
            QMessageBox::warning(this,"提示","图片加载失败");
            return;
        }
        
        //设置图片固定大小
        setFixedSize(pix.width(),pix.height());
        
        //设置不规则图片样式
        setStyleSheet("QPushButton{border:0px;}");
        
        //设置图标
        setIcon(pix);
        
        //设置图标大小
        setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}
