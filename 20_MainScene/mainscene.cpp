#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QMessageBox>
#include <QTimer>
#include <QSound>

MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);
    
    //设置主窗口固定大小
    this->setFixedSize(320,588);
    //设置窗口图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置窗口标题
    this->setWindowTitle("翻金币主场景");
    
    //连接退出事件
    connect(ui->actionExit,&QAction::triggered,this,[=]()
    {
        this->close();
    });
    
    //添加开始按钮音效
    QSound * sound = new QSound(":/res/TapButtonSound.wav",this);
    //sound->setLoops(-1);//循环
    //添加开始按钮
    MyPushButton * btnStart = new MyPushButton(":/res/MenuSceneStartButton.png");
    //设置父类
    btnStart->setParent(this);
    //指定位置
    btnStart->move(this->width()*0.5 - btnStart->width()*0.5,this->height()*0.7);
    
    this->selectLevel = new SelectLevel();
    //监听返回信号
    connect(selectLevel,&SelectLevel::selectLevelBack,this,[=]()
    {
        //关掉选择关卡窗口
        selectLevel->hide();
        //设置矩形框
        this->setGeometry(selectLevel->geometry());
        //显示当前窗口
        this->show();
    });
    
    //添加单击事件
    connect(btnStart,&QPushButton::clicked,this,[=]()
    {
        //播放音效
        sound->play();
        btnStart->Zoom1();
        btnStart->Zoom2();
        
        QTimer::singleShot(500,this,[=]()
        {
            //创建选择界面
            selectLevel->show();
            //设置矩形框
            selectLevel->setGeometry(this->geometry());
            this->hide();
        });
    });
}

//重写绘图事件
void MainScene::paintEvent(QPaintEvent *)
{
    //声明画家
    QPainter painter(this);
    QPixmap pix;
    //加载图片
    pix.load(":/res/PlayLevelSceneBg.png");
    //画图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    
    //画标题
    pix.load(":/res/Title.png");
    //缩小比例
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    //画在窗口上
    painter.drawPixmap(10,30,pix);
}

MainScene::~MainScene()
{
    delete ui;
}
