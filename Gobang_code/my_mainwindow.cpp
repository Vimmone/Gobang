#include "my_mainwindow.h"
my_MainWindow::my_MainWindow(QWidget *parent) :
    QMainWindow(parent)

{
    setWindowTitle("Gobang");                           //设置标题
    setWindowFlags (Qt::FramelessWindowHint);           //隐藏界面顶部
     this->setMaximumHeight(700);
     this->setMinimumHeight(700);
     this->setMaximumSize(600,700);
     this->setMinimumSize(600,700);                     //设置界面大小
     remake();                                          //初始化
     a1=new QPushButton(this);                          //创建开始按钮
     a1->setText("开始");
     a1->setGeometry(50,600,50,50);
    connect(a1,&QPushButton::clicked,                   //监听开始事件
            [=]()
    {
        flag=0;
        remake();
    }
            );
    a2=new QPushButton(this);                           //创建悔棋按钮
    a2->setText("悔棋");
    a2->setGeometry(200,600,50,50);
    connect(a2,&QPushButton::clicked,
            [=]()
    {
         if(!a.empty()&&a.size()>1)
         {
             w.back((a[a.size()-1]).first,(a[a.size()-1]).second);
             a.pop_back();
         }
         if(!b.empty()&&b.size()>1)
         {
             w.back((b[b.size()-1]).first,(b[b.size()-1]).second);
             b.pop_back();
         }
         update();
    }
            );
    a3=new QPushButton(this);                           //创建帮助按钮
    a3->setText("帮助");
    a3->setGeometry(350,600,50,50);
    connect(a3,&QPushButton::clicked,
            [=]()
    {
         QMessageBox::about(this,"about Gobang",QString("1.本程序由QT制作\n"
                                                 "2.采用极大极小搜索算法\n"
                                                 "3.本程序设计只为方便操作，棋力一般\n"
                                                 "4.make by Vimmone"
                                                 ));
    }
            );
    a4=new QPushButton(this);                           //创建关闭按钮
    a4->setText("关闭");
    a4->setGeometry(500,600,50,50);
    connect(a4,&QPushButton::clicked,
            [=]()
    {
         close();
    }
            );
}
void my_MainWindow::remake()                            //初始化
{
    a.clear();
    b.clear();
    w.init();                                           //Gobang初始化
    if(!flag&&(!QMessageBox::information(NULL,"重来","是否先手","no","yes")))
    {
        QTime time;                                     //设置随机数
        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1000);
        int xxx=qrand()%10;
        int yyy=qrand()%10;
        w.insert(2+xxx,2+yyy);
        b<<(qMakePair((3+yyy)*30,(xxx+3)*30));
    }
    this->update();
}

my_MainWindow::~my_MainWindow()
{
    delete ui;
}
void my_MainWindow::paintEvent(QPaintEvent *)           //绘图事件
{
    QPalette palette(this->palette());                  //绘制背景颜色
    palette.setColor(QPalette::Background, qRgb(249,214,91));
    this->setPalette(palette);
    QPainter painter(this);
    QPen pen;                                            //创建画笔
    pen.setColor(Qt::red);
    painter.setPen(pen);
    for(int i=30;i<600;)                                 //绘制棋盘
    {
        QPoint pointOne(30,i);
        QPoint pointTwo(570,i);
        painter.drawLine(pointOne,pointTwo);
        i = i + 30;
    }
    for(int i=30;i<600;)
    {
        QPoint pointOne(i,30);
        QPoint pointTwo(i,570);
        painter.drawLine(pointOne,pointTwo);
        i = i + 30;
    }
    QBrush brush;                                       //绘制棋子
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);
     painter.setBrush(brush);
    for(QVector<QPair <int ,int> >::iterator iter=b.begin();iter!=b.end();iter++)
    {
        painter.drawEllipse((*iter).first-10,(*iter).second-10,20,20);
    }
    if(!b.empty())                                      //只有一颗不能悔棋
    {
        brush.setColor(Qt::blue);
        painter.setBrush(brush);
        painter.drawEllipse((b[b.size()-1]).first-10,(b[b.size()-1]).second-10,20,20);
    }
     brush.setColor(Qt::white);
     painter.setBrush(brush);
    for(QVector<QPair <int ,int> >::iterator iter=a.begin();iter!=a.end();iter++)
    {
        painter.drawEllipse((*iter).first-10,(*iter).second-10,20,20);
    }
}
void my_MainWindow::mousePressEvent(QMouseEvent *mouseEvent)    //鼠标事件
{
    if(flag) return ;                                           //判断是否第一次打开，否则不能进行鼠标事件
     x = int(float(mouseEvent->x())/30+0.5)*30;
     y = int(float(mouseEvent->y())/30+0.5)*30;
     QString infoShow;
     if(x>=30&&x<=570&&y>=30&&y<=570&&count==0)
      {
     int t=w.xy(x,y);
     if(t==-1) return ;
      a<<(qMakePair(x,y)),count=0;
    y=(t/19+1)*30;x=(t%19+1)*30;
     b<<(qMakePair(x,y));
     t=w.win();
    if(t)
    {
        if(t==1) infoShow = "电脑获胜";
        else infoShow = "恭喜获胜";
    if(QMessageBox::information(NULL,"Game Over",infoShow,"Again","Exit")==1)
    {
        close();
    }
    else remake();
    }

        this->update();
     }
}
