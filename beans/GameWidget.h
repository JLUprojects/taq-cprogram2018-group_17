#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPalette>
#include<QPainter>
#include <QIcon>
#include <QPushButton>
#include <QPainter>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <QKeyEvent>
#include <QLabel>
#include <QFont>
#include <QSound>
#include<Paceman.h>
#include<node.h>
#include<pos.h>
#include<vector>
namespace Ui
{
class GameWidget;
}

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *k);
    void movePacman(int dir);
    void smallmovePacman(int dir);
    void moveGhost();
    bool Movementcheck(int x,int y);
    bool meetGhost(int i);
    void  initialGhost(int i);
    void showlabel();
    bool judgewin();
    void hidelabel();
    void initialPacman();
    void updateMap();
    void  inMap();
    int  swp(int A,int B);
    int   qsrt(int cnt);
    int Over_map(int x,int y);
    int Bfs_dist(Paceman A);
    int Get_dist();
    int Find_aim(int ghost_num);
    int Get_value(int aim_x,int aim_y,int ghost_num);
    int Divide_role();
    int Evaluate_steps();
    int Dfs_role(int ghost_num);
    int Solve_pro();
    void getDir(char &Dir,int &tmp);
    bool Playerwin();
    int Init_parameter();
    void initialanother();
    bool judge_PacmanIsDoomed(node pacman);
    int Find_exit(int aim_x,int aim_y);
    void  game();
    QKeyEvent * ke;
    int modefy();
    int Final_check();
    int Get_degree();
    void win();
    void lose();
public slots:
    void  astartslot();
    void aexitslot();
    void acontinueslot();

private:
    Pos P[1000];
    Ui::GameWidget *ui;
    double  parameter[10];
    int Chance_of_Pacman,PlayerPoint=0,Superpower;
    const int CHANCE=10;
    int NumberofCoins=0;
    int Row=31,Column=28;// x y
    int  smallweight=25,smallheight=25;
    int  initial;
    int round=1;
    bool alreadycut;
    bool alreadywin=false;
    const static int INF=36;
    const static int COINS=244;
    int dist[INF][INF][INF][INF];
    int orien[INF][INF][INF][INF];
    int degree[INF][INF];
    Paceman safety[5];
    int pere=3;
    bool continueflag;
    bool alreadystart=false;
    int tt[5];
    int a=0;
    int vist[5];
    int min_steps;
    int Map[31][28]=
    {
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,2},
        {2,1,2,2,2,2,1,2,2,2,2,2,1,2,2,1,2,2,2,2,2,1,2,2,2,2,1,2},
        {2,4,2,2,2,2,1,2,2,2,2,2,1,2,2,1,2,2,2,2,2,1,2,2,2,2,4,2},
        {2,1,2,2,2,2,1,2,2,2,2,2,1,2,2,1,2,2,2,2,2,1,2,2,2,2,1,2},
        {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
        {2,1,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,1,2},
        {2,1,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,1,2},
        {2,1,1,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,1,1,2},
        {2,2,2,2,2,2,1,2,2,2,2,2,0,2,2,0,2,2,2,2,2,1,2,2,2,2,2,2},
        {5,5,5,5,5,2,1,2,2,2,2,2,0,2,2,0,2,2,2,2,2,1,2,5,5,5,5,5},
        {5,5,5,5,5,2,1,2,2,0,0,0,0,0,0,0,0,0,0,2,2,1,2,5,5,5,5,5},
        {5,5,5,5,5,2,1,2,2,0,2,2,2,0,0,2,2,2,0,2,2,1,2,5,5,5,5,5},
        {2,2,2,2,2,2,1,2,2,0,2,3,3,3,3,3,3,2,0,2,2,1,2,2,2,2,2,2},
        {0,0,0,0,0,0,1,0,0,0,2,3,3,3,3,3,3,2,0,0,0,1,0,0,0,0,0,0},
        {2,2,2,2,2,2,1,2,2,0,2,3,3,3,3,3,3,2,0,2,2,1,2,2,2,2,2,2},
        {5,5,5,5,5,2,1,2,2,0,2,2,2,2,2,2,2,2,0,2,2,1,2,5,5,5,5,5},
        {5,5,5,5,5,2,1,2,2,0,0,0,0,0,0,0,0,0,0,2,2,1,2,5,5,5,5,5},
        {5,5,5,5,5,2,1,2,2,0,2,2,2,2,2,2,2,2,0,2,2,1,2,5,5,5,5,5},
        {2,2,2,2,2,2,1,2,2,0,2,2,2,2,2,2,2,2,0,2,2,1,2,2,2,2,2,2},
        {2,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,2},
        {2,1,2,2,2,2,1,2,2,2,2,2,1,2,2,1,2,2,2,2,2,1,2,2,2,2,1,2},
        {2,1,2,2,2,2,1,2,2,2,2,2,1,2,2,1,2,2,2,2,2,1,2,2,2,2,1,2},
        {2,4,1,1,2,2,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,2,2,1,1,4,2},
        {2,2,2,1,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,1,2,2,2},
        {2,2,2,1,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,1,2,2,2},
        {2,1,1,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,1,1,2},
        {2,1,2,2,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,2,2,1,2},
        {2,1,2,2,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,2,2,1,2},
        {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
    };
    float dx[5]= {0,-1,1,0,0}; //up
    float dy[5]= {0,0,0,-1,1};
    float dx2[5]= {0,0,0,-0.25,0.25}; //up
    float dy2[5]= {0,-0.25,0.25,0,0};
    int Map2[31][28];

    //0 is field   1 is coin  2 is wall,5是空心的墙 3 is home 4 is big bean
    QSound *sound;
    QSound *sound1;
    int direction;

    const int  INCVTIME=100;
    QTimer *timer;
    QTimer*timercount;
    QTimer*ghosttimer;
    QTimer*viewupdate;
    bool flag=false;
    int beancount;
    const int UP=1;
    const int DOWN=2;
    const int LEFT=3;
    const int RIGHT=4;
    Paceman Thepacman;
    Paceman  Ghost[10];
    Paceman Q[10];
    int ins[4];//四个怪物的方向
    int  invtime=0;
    int inv=0;
    QPixmap wallmap;
    int openmouth;

signals:
    void UpSignal();
    void DownSignal();
    void LeftSignal();
    void RightSignal();
public slots:
    void upbtnSlot();
    void leftbtnSlot();
    void rightbtnSlot();
    void downbtnSlot();
    void timeoutSlot();//时间触发
    void timeoutSlot2();//时间触发
    //void timeoutghost();//时间触发
    void timeoutupdate();

};

#endif // GAMEWIDGET_H
