#include "playgame.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include "dataconfig.h"
#include <QPropertyAnimation>
#include <QSound>

//PlayGame::PlayGame(QWidget *parent) : QMainWindow(parent)
//{
    
//}

PlayGame::PlayGame(int level)
{
    //保存关卡
    this->m_Level = level;
    
    //设置窗口大小
    this->setFixedSize(320,588);
    //设置窗口图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置窗口标题
    this->setWindowTitle("开始游戏");
    
    //创建菜单栏
    QMenuBar * bar = menuBar();
    //设置到窗口上
    setMenuBar(bar);
    //添加菜单
    QMenu * startMenu = bar->addMenu("开始(&S)");
    //添加子菜单
    QAction * exitAction = startMenu->addAction("退出");
    //设置快捷键
    exitAction->setShortcut(QKeySequence(QLatin1String("Ctrl+E")));
    
    //连接信号槽
    connect(exitAction,&QAction::triggered,this,[=]()
    {
        this->close();
    });
    
    //创建返回按钮音效
    QSound * soundBack = new QSound(":/res/BackButtonSound.wav",this);
    //创建翻金币音效
    QSound *soundCoin = new QSound(":/res/ConFlipSound.wav",this);
    //创建胜利音效
    QSound * soundWin = new QSound(":/res/LevelWinSound.wav",this);
    
    //创建返回按钮
    MyPushButton * btnBack = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    //设置父亲
    btnBack->setParent(this);
    //移动位置
    btnBack->move(this->width()-btnBack->width(),this->height()-btnBack->height());
    //连接信号槽
    connect(btnBack,&QPushButton::clicked,this,[=]()
    {
        soundBack->play();
        QTimer::singleShot(200,this,[=]()
        {
            emit this->SelectBack();
        });
    });
    
    //创建显示关卡标签
    QLabel * label = new QLabel(this);
    //设置字体
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    //设置到label上
    label->setFont(font);
    //设置label文本
    QString str1 = QString("Level: %1").arg(this->m_Level);
    label->setText(str1);
    //设置label位置
    label->setGeometry(30,this->height()-50,120,50);
    
    //创建胜利图片
    QLabel * lblWin = new QLabel(this);
    QPixmap pix1;
    //加载图片
    pix1.load(":/res/LevelCompletedDialogBg.png");
    //设置显示位置
    lblWin->setGeometry(0,0,pix1.width(),pix1.height());
    //设置到label上
    lblWin->setPixmap(pix1);
    //移动位置
    lblWin->move((this->width()-pix1.width()) *0.5,-pix1.height());
    
    //初始化数组
    dataConfig data;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->coinArray[i][j] = data.mData[this->m_Level][i][j];
        }
    }
    
    //创建金币
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            //创建图片
            QPixmap pix;
            pix.load(":/res/BoardNode(1).png");
            //创建背景
            QLabel * label = new QLabel(this);
            //设置大小
            label->setGeometry(0,0,pix.width(),pix.height());
            //设置图片
            label->setPixmap(pix);
            //移动
            label->move(57+50*i,200+50*j);
            
            QString path;
            if(this->coinArray[i][j] == 1)
            {
                path = ":/res/Coin0001.png";
            }
            else
            {
                path = ":/res/Coin0008.png";
            }
            //创建按钮
            MyCoin * coin = new MyCoin(path);
            //设置父亲
            coin->setParent(this);
            //移动位置
            coin->move(59+50*i,204+50*j);
            
            //记录金币的位置
            coin->m_X = i;
            coin->m_Y = j;
            coin->m_Flag = this->coinArray[i][j];
            
            //添加到金币数组中
            this->cArray[i][j] = coin;
            
            //连接信号槽
            connect(coin,&QPushButton::clicked,this,[=]()
            {
                //播放翻金币音效
                soundCoin->play();
                
                coin->changeFlag();
                //修改数组里的记录
                this->coinArray[i][j] = this->coinArray[i][j]==0?1:0;
                
                for(int i=0;i<4;i++)
                {
                    for(int j=0;j<4;j++)
                    {
                        this->cArray[i][j]->isWin = true;
                    }
                }
                
                //设置延时
                QTimer::singleShot(300,this,[=]()
                {
                    //翻右边的金币
                    if(coin->m_X+1<=3)
                    {
                        this->cArray[coin->m_X+1][coin->m_Y]->changeFlag();
                        //修改数组里的记录
                        this->coinArray[coin->m_X+1][coin->m_Y] = this->coinArray[coin->m_X+1][coin->m_Y]==0?1:0;
                    }
                    
                    //翻左边的金币
                    if(coin->m_X-1>=0)
                    {
                        this->cArray[coin->m_X-1][coin->m_Y]->changeFlag();
                        //修改数组里的记录
                        this->coinArray[coin->m_X-1][coin->m_Y] = this->coinArray[coin->m_X-1][coin->m_Y]==0?1:0;
                    }
                    
                    //翻上边的金币
                    if(coin->m_Y-1>=0)
                    {
                        this->cArray[coin->m_X][coin->m_Y-1]->changeFlag();
                        //修改数组里的记录
                        this->coinArray[coin->m_X][coin->m_Y-1] = this->coinArray[coin->m_X][coin->m_Y-1]==0?1:0;
                    }
                    
                    //翻下边的金币
                    if(coin->m_Y+1<=3)
                    {
                        this->cArray[coin->m_X][coin->m_Y+1]->changeFlag();
                        //修改数组里的记录
                        this->coinArray[coin->m_X][coin->m_Y+1] = this->coinArray[coin->m_X][coin->m_Y+1]==0?1:0;
                    }
                    
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            this->cArray[i][j]->isWin = false;
                        }
                    }
                    
                    //判断金币标志是否都是1;
                    this->isWin = true;
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(this->cArray[i][j]->m_Flag == false)
                            {
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    
                    if(this->isWin)
                    {
                        //播放胜利音效
                        soundWin->play();
                        //将所有按钮的胜利标志改成true
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                this->cArray[i][j]->isWin = true;
                            }
                        }
                        
                        //显示胜利图片
                        QPropertyAnimation * animation1 = new QPropertyAnimation(lblWin,"geometry");
                        //设置延时
                        animation1->setDuration(1000);
                        //设置开始位置
                        animation1->setStartValue(QRect(lblWin->x(),lblWin->y(),lblWin->width(),lblWin->height()));
                        //设置结束位置
                        animation1->setEndValue(QRect(lblWin->x(),lblWin->y()+174,lblWin->width(),lblWin->height()));
                        //设置缓和曲线
                        animation1->setEasingCurve(QEasingCurve::OutBounce);
                        //开始
                        animation1->start();
                    }
                }); 
            });
        }
    }
}

//重写绘图事件
void PlayGame::paintEvent(QPaintEvent *)
{
    //声明画家
    QPainter painter(this);//this代表绘图设备
    QPixmap pix;
    //加载图片
    pix.load(":/res/PlayLevelSceneBg.png");
    //画在窗口上
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
   
    //画标题
    pix.load(":/res/Title.png");
    //缩小比例
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    //画在窗口上
    painter.drawPixmap(10,30,pix);
}
