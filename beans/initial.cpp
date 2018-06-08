#include "InitialWidget.h"
#include "GameWidget.h"
#include "ui_initialWidget.h"

initialWidget::initialWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::initialWidget)
{

    ui->setupUi(this);
    start = QPoint(130,100);
    end = QPoint(630,600);
    this->resize(700,775);
    this->setMaximumSize(700,775);
    this->setWindowTitle("pacman");
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/images/image/background.png").scaled(this->size())));
    this->setPalette(palette);
    connect(ui->toolButtonstart,SIGNAL(clicked()),this,SLOT(startslot()));
    connect(ui->toolButtonexit,SIGNAL(clicked()),this,SLOT(exitslot()));
}
initialWidget::~initialWidget()
{
    delete ui;
}
void initialWidget::exitslot()
{
     this->close();
    exit(0);
}

void initialWidget::startslot()
{
    this->close();
    GameWidget *g=new GameWidget();
    g->show();
}



