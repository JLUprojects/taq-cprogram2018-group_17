#include<queue>
#include "GameWidget.h"
#include "ui_GameWidget.h"
#include"Paceman.h"
#include"iostream"
#include<algorithm>

using namespace std;

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    this->resize(900,800);//this->resize(700,775);
    this->setMaximumSize(900,800);
    this->setWindowTitle("pacman");
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/images/image/black.png").scaled(this->size())));
    this->setPalette(palette);
    wallmap=QPixmap(700,775);
    wallmap.fill(Qt::black);
    QPainter pp(&wallmap);
    for(int i=0; i<31; i++)
    {
        for(int j=0; j<28; j++)
            Map2[i][j]=Map[i][j];
    }
    for(int i=0; i<31; i++)
    {
        for(int j=0; j<28; j++)
        {
            if(Map[i][j]==2)
                pp.drawImage(j*smallweight,i*smallheight,QImage(":/images/image/wall.png").scaled(QSize(25,25)));

        }
    }
    Chance_of_Pacman=CHANCE;
    alreadycut=false;
    initialPacman();
    for(int i=1; i<5; i++)
    {
        initialGhost(i);
        ins[i]=UP;
    }

    inv=0;
    openmouth=0;
    continueflag=false;

    direction=LEFT;


    connect(this,SIGNAL(UpSignal()),this,SLOT(upbtnSlot()));
    connect(this,SIGNAL(DownSignal()),this,SLOT(downbtnSlot()));
    connect(this,SIGNAL(LeftSignal()),this,SLOT(leftbtnSlot()));
    connect(this,SIGNAL(RightSignal()),this,SLOT(rightbtnSlot()));
    timer=new QTimer(this);
    timercount=new QTimer(this);
    viewupdate=new QTimer(this);
    timer->setInterval(200);
    viewupdate->setInterval(50);
    timercount->setInterval(1000);
    connect(timercount,SIGNAL(timeout()),this,SLOT(timeoutSlot2()));
    connect(timer,SIGNAL(timeout()),this,SLOT(timeoutSlot()));
    connect(viewupdate,SIGNAL(timeout()),this,SLOT(timeoutupdate()));
    connect(ui->toolButtonstart,SIGNAL(clicked()),this,SLOT(astartslot()));
    connect(ui->toolButtonexit,SIGNAL(clicked()),this,SLOT(aexitslot()));
    connect(ui->toolButtoncontinue,SIGNAL(clicked()),this,SLOT(acontinueslot()));
    ke=new QKeyEvent(QEvent::KeyPress,Qt::Key_Enter,Qt::NoModifier);
    ui->timedisplay->display(inv);
    ui->rounddisplay->display(Chance_of_Pacman);
    ui->scoredisplay->display(PlayerPoint);
    hidelabel();
    ui->winlabel->hide();
    ui->loselabel->hide();
    ui->begin->show();
}
void GameWidget:: initialanother()
{
    inv=0;
    openmouth=0;
    PlayerPoint=0;
    continueflag=false;
    for(int i=0; i<31; i++)
    {
        for(int j=0; j<28; j++)
            Map[i][j]=Map2[i][j];
    }
    Chance_of_Pacman=CHANCE;
    NumberofCoins=0;
    initialPacman();
    for(int i=1; i<5; i++)
    {

        initialGhost(i);
        ins[i]=UP;
    }
    ui->timedisplay->display(inv);
    ui->rounddisplay->display(Chance_of_Pacman);
    ui->scoredisplay->display(PlayerPoint);
    hidelabel();
    ui->winlabel->hide();
    ui->loselabel->hide();
    ui->begin->show();
    alreadywin=false;
}

GameWidget::~GameWidget()
{
    delete ui;
}
void GameWidget::upbtnSlot()
{

    direction=UP;

}

void GameWidget::downbtnSlot()
{


    direction=DOWN;

}

void GameWidget::leftbtnSlot()
{

    direction=LEFT;

}

void GameWidget::rightbtnSlot()
{

    direction=RIGHT;
}
void GameWidget:: timeoutSlot()
{

    movePacman(direction);
    moveGhost();
    updateMap();
    if(judgewin())
    {
        if(alreadywin==false)
            win();
    }

}
void GameWidget:: timeoutSlot2()
{
    inv--;
    ui->timedisplay->display(inv);
    if(inv==0)
    {
        timercount->stop();
    }
}

void GameWidget::astartslot()
{
    ui->begin->hide();
    if(alreadystart)
    {
        return;

    }


    QCoreApplication::postEvent(this,ke);
    alreadycut=false;
    alreadystart=true;
    initialanother();
    timer->start();
    hidelabel();
    ui->begin->hide();
    viewupdate->start();
    for(int i=1; i<5; i++)
    {
        initialGhost(i);
    }
    initialPacman();

}

void GameWidget:: aexitslot()
{
    exit(0);
}

void GameWidget::acontinueslot()
{
    if(continueflag)
    {
        alreadycut=false;
        hidelabel();
        timer->start();
        viewupdate->start();
        for(int i=1; i<5; i++)
        {
            initialGhost(i);
        }
        initialPacman();

        continueflag=false;
    }
}
void  GameWidget::timeoutupdate()
{
    this->update();
}
void GameWidget:: hidelabel()
{
    ui->text1->hide();
    ui->text2->hide();
    ui->text3->hide();
}
void GameWidget:: showlabel()
{
    ui->text1->show();
    ui->text2->show();
    ui->text3->show();
}

void GameWidget::keyPressEvent(QKeyEvent *k)
{
    this->setFocus();
    int key = k->key();
    if(key==Qt::Key_Up)
    {
        emit UpSignal();
    }
    else if(key==Qt::Key_Down)
    {
        emit DownSignal();
    }
    else if(key==Qt::Key_Left)
    {
        emit LeftSignal();
    }
    else if(key==Qt::Key_Right)
    {
        emit RightSignal();
    }
//}
}
void GameWidget::paintEvent(QPaintEvent *)
{
    //???
    QPainter painter(this);
    painter.drawPixmap(0,0,wallmap);

    //???

    for(int i=0; i<31; i++)
    {

        for(int j=0; j<28; j++)
        {
            if(Map[i][j]==1)
            {
                painter.drawImage(j*smallweight+7.5,i*smallheight+7.5,QImage(":/images/image/smallbean.png").scaled(QSize(10,10)));


            }
            if(Map[i][j]==4)
            {
                painter.drawImage(j*smallweight,i*smallheight,QImage(":/images/image/bigbean.png").scaled(QSize(25,25)));

            }
        }
    }
    //cout<<a<<endl;
    if(openmouth!=7)
    {
        switch(direction)
        {
        case 1:
            painter.drawImage(Thepacman.y*smallweight,Thepacman.x*smallheight,QImage(":/images/image/man-on-up.png").scaled(QSize(25,25)));
            break;
        case 2:
            painter.drawImage(Thepacman.y*smallweight,Thepacman.x*smallheight,QImage(":/images/image/man-on-down.png").scaled(QSize(25,25)));
            break;
        case 3:
            painter.drawImage(Thepacman.y*smallweight,Thepacman.x*smallheight,QImage(":/images/image/man-on-left.png").scaled(QSize(25,25)));
            break;
        case 4:
            painter.drawImage(Thepacman.y*smallweight,Thepacman.x*smallheight,QImage(":/images/image/man-on-right.png").scaled(QSize(25,25)));
        }
        openmouth++;
    }
    if(openmouth==7)
    {
        switch(direction)
        {
        case 1:
            painter.drawImage(Thepacman.y*smallweight,Thepacman.x*smallheight,QImage(":/images/image/man-off-up.png").scaled(QSize(25,25)));
            break;
        case 2:
            painter.drawImage(Thepacman.y*smallweight,Thepacman.x*smallheight,QImage(":/images/image/man-off-down.png").scaled(QSize(25,25)));
            break;
        case 3:
            painter.drawImage(Thepacman.y*smallweight,Thepacman.x*smallheight,QImage(":/images/image/man-off-left.png").scaled(QSize(25,25)));
            break;
        case 4:
            painter.drawImage(Thepacman.y*smallweight,Thepacman.x*smallheight,QImage(":/images/image/man-off-right.png").scaled(QSize(25,25)));
        }
        openmouth=0;
    }
    if(inv>0)
    {
        painter.drawImage(Ghost[4].y*smallweight,Ghost[4].x*smallheight,QImage(":/images/image/monsterinvTime.png").scaled(QSize(25,25)));
        painter.drawImage(Ghost[1].y*smallweight,Ghost[1].x*smallheight,QImage(":/images/image/monsterinvTime.png").scaled(QSize(25,25)));
        painter.drawImage(Ghost[2].y*smallweight,Ghost[2].x*smallheight,QImage(":/images/image/monsterinvTime.png").scaled(QSize(25,25)));
        painter.drawImage(Ghost[3].y*smallweight,Ghost[3].x*smallheight,QImage(":/images/image/monsterinvTime.png").scaled(QSize(25,25)));
    }
    else
    {
        painter.drawImage(Ghost[4].y*smallweight,Ghost[4].x*smallheight,QImage(":/images/image/monster1.png").scaled(QSize(25,25)));
        painter.drawImage(Ghost[1].y*smallweight,Ghost[1].x*smallheight,QImage(":/images/image/monster2.png").scaled(QSize(25,25)));
        painter.drawImage(Ghost[2].y*smallweight,Ghost[2].x*smallheight,QImage(":/images/image/monster3.png").scaled(QSize(25,25)));
        painter.drawImage(Ghost[3].y*smallweight,Ghost[3].x*smallheight,QImage(":/images/image/monster4.png").scaled(QSize(25,25)));
    }

    this->update();
}

void GameWidget::movePacman(int dir)
{
    int xx=Thepacman.x+dx[dir];
    int yy=Thepacman.y+dy[dir];

    if(Movementcheck(xx,yy))
    {

        Thepacman.x=xx;
        Thepacman.y=yy;
        Thepacman.face=dir;
    }

    for(int i=0; i<=3; i++)
    {
        if(meetGhost(i))
        {
            if(inv>0)//during invTime, Ghost is killed
            {
                initialGhost(i);
                PlayerPoint+=50;
            }
            else//Pacman is killed
            {
                if(!alreadycut)
                {
                    Chance_of_Pacman--;
                    ui->rounddisplay->display(Chance_of_Pacman);
                    alreadycut=true;
                    timer->stop();
                    viewupdate->stop();

                    if(Chance_of_Pacman!=0)
                    {
                        showlabel();
                        continueflag=true;
                    }
                    else if(Chance_of_Pacman==0)
                    {
                        continueflag=false;
                        if(judgewin())
                            win();
                        else
                        {
                            lose();
                        }
                    }
                }
            }
        }
    }

    //update the condition of pill and coins, player's point
    updateMap();
}

bool GameWidget::Movementcheck(int x,int y)
{
    if(x>=0&&x<Row && y>0&&y<Column)
    {
        if(Map[x][y]!=3 &&Map[x][y]!=2)
        {
            return true;
        }
    }
    return false;
}

bool GameWidget::meetGhost(int i)
{

    if(Thepacman.x==Ghost[i].x &&Thepacman.y==Ghost[i].y)
    {
        return true;
    }
    return false;

}
void GameWidget:: updateMap()
{
    int x=Thepacman.x;
    int y=Thepacman.y;
    if(Map[x][y]==0)
    {
        return;
    }
    if(Map[x][y]==1)
    {
        PlayerPoint++;
        NumberofCoins++;
        ui->scoredisplay->display(PlayerPoint);
        Map[x][y]=0;
        return;
    }
    if(Map[x][y]==4)
    {
        PlayerPoint= PlayerPoint+2;
        NumberofCoins++;//??2?
        ui->scoredisplay->display(PlayerPoint);
        Map[x][y]=0;
        inv=INCVTIME;
        ui->timedisplay->display(inv);
        timercount->start();
        //  ghosttimer->setInterval(800);
        return;
    }
}
void GameWidget:: moveGhost()
{
    Solve_pro();
    for(int i=1; i<=4; i++)
    {
        Ghost[i].face=ins[i];
        Ghost[i].x+=dx[ins[i]];
        Ghost[i].y+=dy[ins[i]];

    }
    for(int i=1; i<=4; i++)
    {
        if(meetGhost(i))
        {
            if(inv>0)//during invTime, Ghost is killed
            {
                initialGhost(i);
                PlayerPoint+=50;
            }
            else//Pacman is killed
            {
                if(!alreadycut)
                {
                    Chance_of_Pacman--;
                    ui->rounddisplay->display(Chance_of_Pacman);
                    alreadycut=true;
                    timer->stop();
                    viewupdate->stop();

                    if(Chance_of_Pacman!=0)
                    {
                        showlabel();
                        continueflag=true;
                    }
                    else if(Chance_of_Pacman==0)
                    {
                        continueflag=false;
                        if(judgewin())
                            win();
                        else
                        {
                            lose();
                        }
                    }
                }
            }
        }
    }
    updateMap();
}
bool GameWidget::judgewin()
{
    if(NumberofCoins==COINS)
        return true;
    else
        return false;
}

void GameWidget::initialGhost(int num)
{
    Ghost[num].x=14;
    Ghost[num].y=12+num;
    Ghost[num].face=UP;

}
void  GameWidget::initialPacman()
{
    Thepacman.x=23;
    Thepacman.y=14;
    Thepacman.face=LEFT;

}
void GameWidget::win()
{
    alreadywin=true;
    ui->winlabel->show();
    timer->stop();
    viewupdate->stop();
    timercount->stop();
    alreadystart=false;
    alreadywin==false;

}
void GameWidget::lose()
{
    ui->loselabel->show();
    timer->stop();
    timercount->stop();
    viewupdate->stop();
    alreadystart=false;
    alreadywin==false;
}
////////////////////////////////////////////////////////////////////////??????????????

//version1.0
int GameWidget::Over_map(int x,int y)//??????(?)
{
    if(x<0||x>=Row) return 1;
    if(y<0||y>=Column) return 1;
    if(Map[x][y]==2) return 1;
    return 0;
}
vector<Paceman> G[50][50];//@
int GameWidget::Bfs_dist(Paceman A)//bfs ??? (Get_dist)
{
    if(Map[A.x][A.y]==2)return 0;
    queue<Paceman>q;
    q.push(A);
    int dg=3;
    while(!q.empty())
    {
        Paceman u=q.front();
        if(G[u.x][u.y].size()<4&&degree[u.x][u.y]>2||A.x==u.x&&A.y==u.y)
        {
            G[u.x][u.y].push_back(Paceman(u.x,u.y));
        }
        q.pop();
        for(int i=1; i<=4; i++)
        {
            Paceman v;
            v.x= u.x+dx[i];
            v.y= u.y+dy[i];
            if(Over_map(v.x,v.y)==1) continue;

            if(dist[A.x][A.y][u.x][u.y]+1<dist[A.x][A.y][v.x][v.y])
            {
                dist[A.x][A.y][v.x][v.y]=dist[A.x][A.y][u.x][u.y]+1;
                if(dist[A.x][A.y][v.x][v.y]==1)
                {
                    orien[A.x][A.y][v.x][v.y]=i;

                }
                else orien[A.x][A.y][v.x][v.y]=orien[A.x][A.y][u.x][u.y];
                q.push(v);
            }
        }
    }
    return 0;
}
int GameWidget:: Get_dist()//??????????
{
    for(int i=1; i<=Row; i++)
        for(int j=1; j<=Column; j++)
            for(int ti=1; ti<=Row; ti++)
                for(int tj=1; tj<=Column; tj++)
                {
                    dist[i][j][ti][tj]=2147483646;
                    orien[i][j][ti][tj]=0;//no dir
                }

    for(int i=1; i<=Row; i++)
    {
        for(int j=1; j<=Column; j++)
        {
            dist[i][j][i][j]=0;
            Paceman A(i,j);
            Bfs_dist(A);
        }
    }
    return 0;
}
int p2=1.5;

int GameWidget::Evaluate_steps()//?????????????
{
    int dis_sum=0;
    for(int i=1; i<=4; i++)
    {
        dis_sum+=dist[ Ghost[i].x ][ Ghost[i].y ][ Q[i].x ][ Q[i].y ];
    }
    return dis_sum;
}
int GameWidget::Dfs_role(int ghost_num)//dfs??????????
{
    if(ghost_num==5)
    {
        for(int i=1; i<=4; i++)
        {
            // Find_aim(Ghost[i],Thepacman,i,tt[i]);

            Q[i]=G[Thepacman.x][Thepacman.y][tt[i]-1];
        }
        if(min_steps>Evaluate_steps())
        {
            min_steps=Evaluate_steps();
            for(int i=1; i<=4; i++)
            {
                ins[i]=orien[ Ghost[i].x ][ Ghost[i].y ][ Q[i].x ][ Q[i].y ];
            }
        }
        return 0;
    }
    for(int i=1; i<=4; i++)
    {
        if(vist[i]) continue;
        tt[ghost_num]=i;
        vist[i]=1;
        Dfs_role(ghost_num+1);
        vist[i]=0;
    }
    return 0;
}


int GameWidget:: Final_check()
{
    for(int i=1; i<=4; i++)
    {
        if(Over_map(Ghost[i].x+dx[ins[i]],Ghost[i].y+dy[ins[i]]))ins[i]=0;
    }

}

// version 2.0
int GameWidget:: Get_degree()
{
    for(int i=1; i<=Row; i++)
    {
        for(int j=1; j<=Column; j++)
        {
            for(int k=1; k<=4; k++)
            {
                int tx=i+dx[k];
                int ty=j+dy[k];
                if(Over_map(tx,ty)||Map[tx][ty]==2) continue;
                if(Map[tx][ty]!=2) degree[tx][ty]++;
            }
        }
    }

}
int flag1;
int GameWidget::Solve_pro()
{
    min_steps=INF*INF*INF;
    memset(vist,0,sizeof(vist));
    for(int i=0; i<=4; i++)
        Q[i].x=0,Q[i].y=0;
    if(!flag1)
    {
        Get_degree();
        Get_dist();
        flag1=1;
    }
    Init_parameter();
    Divide_role();
    return 0;
}

//version3.0

int GameWidget::Init_parameter()
{
    parameter[0]=30.0;
    parameter[1]=10.0;
    parameter[2]=8.0;
    parameter[3]=2.0;
    parameter[4]=5.0;
    parameter[5]=2.0;
    parameter[6]=4.0;
}

int runner,interceptor;
int GameWidget::Divide_role()
{
    runner=0;
    int min_dist=(int)parameter[0];
    int max_dist=0;
    for(int i=1; i<=4; i++)
    {
        if(dist[Ghost[i].x][Ghost[i].y][Thepacman.x][Thepacman.y]<min_dist)
        {
            min_dist=dist[Ghost[i].x][Ghost[i].y][Thepacman.x][Thepacman.y];
            runner=i;
        }
        if(dist[Ghost[i].x][Ghost[i].y][Thepacman.x][Thepacman.y]>max_dist)
        {
            max_dist=dist[Ghost[i].x][Ghost[i].y][Thepacman.x][Thepacman.y];
            interceptor=i;
        }
    }
    if(inv>(int)parameter[5]) runner=0;
    for(int i=1; i<=4; i++)
    {
        if(i!=runner&&i!=interceptor)Find_aim(i);
        if(i==runner) Q[i]=Thepacman;
        if(i==interceptor) Find_aim(i);
    }
    for(int i=1; i<=4; i++)
    {
        ins[i]=orien[ Ghost[i].x ][ Ghost[i].y ][ Q[i].x ][ Q[i].y ];
    }
    return 0;
}



int  GameWidget::Get_value(int aim_x,int aim_y,int ghost_num)
{
    int P_A=dist[Thepacman.x][Thepacman.y][aim_x][aim_y];
    int G_A=dist[Ghost[ghost_num].x][Ghost[ghost_num].y][aim_x][aim_y];
    int debuf=0;
    if(P_A<G_A) debuf=-(int)parameter[1];
    int debuf2=int(parameter[2]);
    int debuf3=0;
    if(P_A<=2&&P_A<=2) debuf+=parameter[3];
    if(P_A<=1&&P_A<=2) debuf=parameter[3];
    if(P_A<=2&&P_A<=1) debuf=parameter[3];
    if(P_A<=1&&P_A<=1) debuf+=parameter[3];
    if(orien[Thepacman.x][Thepacman.y][aim_x][aim_y]==Thepacman.face) debuf2+=parameter[2];
    return 50-G_A/2-P_A/2+(degree[aim_x][aim_y])*4+debuf-abs(G_A-P_A)+debuf2+debuf3+Find_exit(aim_x,aim_y);
}
int  GameWidget:: swp(int A,int B)
{
    P[0]=P[A];
    P[A]=P[B];
    P[B]=P[0];
    return 0;
}

int  GameWidget:: qsrt(int cnt)
{
    for(int i=1; i<=cnt; i++)
    {
        int k=1;
        for(int j=1; j<=cnt+1-i; j++)
        {
            if(P[k].val>P[j].val)
                k=j;
        }
        swp(k,cnt+1-i);
    }
    return 0;
}

int GameWidget::Find_aim(int ghost_num)
{
    int cnt=0;
    for(int i=1; i<=Row; i++)
        for(int j=1; j<=Column; j++)
        {
            P[++cnt]=Pos(i,j,(double)Get_value(i,j,ghost_num));
        }
    qsrt(cnt);
    int tmp_num=1;

    while(1)
    {
        int tmp_flag=0;
        for(int i=1; i<=4; i++)
        {

            if(Q[i].x==P[tmp_num].x&&Q[i].y==P[tmp_num].y)
            {
                tmp_flag=1;
                break;
            }
            if(Ghost[i].x==Ghost[ghost_num].x&&Ghost[i].y==Ghost[ghost_num].y&&
                    orien[Ghost[ghost_num].x][Ghost[ghost_num].y][P[tmp_num].x][P[tmp_num].y]==
                    orien[Ghost[i].x][Ghost[i].y][Q[i].x][Q[i].y])
            {
                tmp_flag=1;
                break;
            }//version 7.0
            if(Ghost[i].x==P[tmp_num].x&&Ghost[i].y==P[tmp_num].y)
            {
                tmp_flag=1;//???????????????
                break;
            }
            if(i==ghost_num) continue;
            int tmp_x=P[tmp_num].x,tmp_y=P[tmp_num].y;
            int tmp_cnt=0;
            while(!(tmp_x==Ghost[ghost_num].x&&tmp_y==Ghost[ghost_num].y))
            {

                if(tmp_x==Ghost[i].x&&tmp_y==Ghost[i].y) tmp_cnt++;
                int ttmp_x=tmp_x+dx[orien[tmp_x][tmp_y][Ghost[ghost_num].x][Ghost[ghost_num].y]];
                int ttmp_y=tmp_y+dy[orien[tmp_x][tmp_y][Ghost[ghost_num].x][Ghost[ghost_num].y]];
                tmp_x=ttmp_x;
                tmp_y=ttmp_y;
            }
            if(tmp_cnt>=1)tmp_flag=1;
        }
        if(inv&&orien[Ghost[ghost_num].x][Ghost[ghost_num].y][P[tmp_num].x][P[tmp_num].y]
                ==orien[Ghost[ghost_num].x][Ghost[ghost_num].y][Thepacman.x][Thepacman.y]
                &&dist[Ghost[ghost_num].x][Ghost[ghost_num].y][Thepacman.x][Thepacman.y]<(int)parameter[6])
            tmp_flag=1;
        if(!tmp_flag) break;
        tmp_num++;
        if(tmp_num>100)break;
    }
    Q[ghost_num]=Paceman(P[tmp_num].x,P[tmp_num].y);
    return 0;
}

int GameWidget::Find_exit(int aim_x,int aim_y)
{
    int tmp_x=Thepacman.x;
    int tmp_y=Thepacman.y;
    if(degree[tmp_x][tmp_y]<=2&&orien[tmp_x][tmp_y][aim_x][aim_y]==Thepacman.face) return (int)parameter;
    return 0;

}
bool GameWidget:: Playerwin()
{
    return  NumberofCoins==0;
}
