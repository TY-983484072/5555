#include "mycoin.h"
#include <QMessageBox>

//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{
    
//}

MyCoin::MyCoin(QString normalImg)
{
    //保存路径
    this->m_NormalImg = normalImg;
    
    QPixmap pix;
    //加载图片
    bool ret = pix.load(normalImg);
    if(!ret)
    {
        QMessageBox::information(this,"提示","文件打开失败");
        return;
    }
    //设置按钮大小
    this->setFixedSize(pix.width(),pix.height());
    //设置样式风格
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
    
    //创建定时器对象
    this->timer1 = new QTimer(this);
    this->timer2 = new QTimer(this);
    
    //连接金币翻银币定时器
    connect(timer1,&QTimer::timeout,this,[=]()
    {
        QString path = QString(":/res/Coin000%1.png").arg(this->m_Min++);
        QPixmap pix;
        pix.load(path);
        
        //设置按钮固定大小
        this->setFixedSize(pix.width(),pix.height());
        //设置显示风格
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(QIcon(pix));
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
        
        if(this->m_Min > this->m_Max)
        {
            this->m_Min = 1;
            this->m_DH = false;
            timer1->stop();
        }
    });
    
    //连接银币翻金币定时器
    connect(timer2,&QTimer::timeout,this,[=]()
    {
        QString path = QString(":/res/Coin000%1.png").arg(this->m_Max--);
        QPixmap pix;
        //加载图片
        pix.load(path);
        
        //设置按钮固定大小
        this->setFixedSize(pix.width(),pix.height());
        //设置按钮风格
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(QIcon(pix));
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
        
        if(this->m_Max < this->m_Min)
        {
            this->m_Max = 8;
            this->m_DH = false;
            timer2->stop();
        }
    });
}

//改变标志
void MyCoin::changeFlag()
{
    if(this->m_Flag)//金币
    {
        //金币翻成银币
        this->m_DH = true;
        this->timer1->start(30);
        //修改标志
        this->m_Flag = false;
    }
    else
    {
        //银币翻成金币
        this->m_DH = true;
        this->timer2->start(30);
        //修改标志
        this->m_Flag = true;
    }
}

//重写鼠标按下事件
void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->m_DH || this->isWin)
    {
        return;
    }
    return QPushButton::mousePressEvent(e);
}
