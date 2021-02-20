#include "selectlevel.h"
#include <QMenuBar>
#include <QPainter>
#include <mypushbutton.h>
#include <QMessageBox>
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include <QSound>

SelectLevel::SelectLevel(QWidget *parent) : QMainWindow(parent)
{
    //设置固定大小
    setFixedSize(320,588);
    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    setWindowTitle("选择关卡");
    
    //添加菜单栏
    QMenuBar * bar = menuBar();
    //设置到窗口上
    setMenuBar(bar);
    //添加子菜单
    QMenu * startMenu = bar->addMenu("开始(&S)");
    //添加子菜单
    QAction * exitAction = startMenu->addAction("退出");
    exitAction->setShortcut(QKeySequence(QLatin1String("Ctrl+E")));
    
    //连接
    connect(exitAction,&QAction::triggered,this,[=]()
    {
        this->close();
    });
    
    
    //创建返回按钮
    MyPushButton * btnBack = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    //设置父类
    btnBack->setParent(this);
    //移动位置
    btnBack->move(this->width()-btnBack->width(),this->height()-btnBack->height());
    
    //创建返回按钮音效
    QSound * soundBack = new QSound(":/res/BackButtonSound.wav",this);
    
    //连接返回按钮
    connect(btnBack,&QPushButton::clicked,this,[=]()
    {
        //播放音效
        soundBack->play();
        //发送返回信号给主窗口
        QTimer::singleShot(200,this,[=]()
        {  
            emit this->selectLevelBack();
        });
    });
    
    //创建音效
    QSound * sound = new QSound(":/res/TapButtonSound.wav",this);
    
    //创建选择关卡按钮
    for(int i=0;i<20;i++)
    {
        MyPushButton * btnMenu = new MyPushButton(":/res/LevelIcon.png");
        //设置父亲
        btnMenu->setParent(this);
        //移动位置
        btnMenu->move(25+i%4*75,135+i/4*75);  
        
        //连接信号槽
        connect(btnMenu,&QPushButton::clicked,this,[=]()
        {
            //播放音效
            sound->play();
            //创建玩游戏界面
            this->play = new PlayGame(i+1);
            //设置矩形框
            play->setGeometry(this->geometry());
            play->show();
            this->hide();
            
            //连接信号槽
            connect(play,&PlayGame::SelectBack,this,[=]()
            {
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play = NULL;
            });
        });
        
        //创建label显示文字
        QLabel * label = new QLabel(this);
        //设置label大小
        label->setFixedSize(btnMenu->width(),btnMenu->height());
        //设置文本
        label->setText(QString::number(i+1));
        //移动位置
        label->move(25+i%4*75,135+i/4*75);
        //设置对齐方式
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

//重写绘图事件
void SelectLevel::paintEvent(QPaintEvent *)
{
    //创建画家
    QPainter painter(this);//this 代表绘图设备
    QPixmap pix;
    //加载图像
    pix.load(":/res/OtherSceneBg.png");
    //利用画家画在窗口上
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    
    //画标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
    
}
