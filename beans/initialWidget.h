#ifndef INITIALWIDGET_H
#define INITIALWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QPixmap>
#include <QPushButton>

namespace Ui {
class initialWidget;
}

class initialWidget : public QWidget
{
    Q_OBJECT

public:
    explicit initialWidget(QWidget *parent = 0);
    ~initialWidget();
    QPoint start;
   QPoint end;

   public slots:

    void startslot();
   void exitslot();



private:
    Ui::initialWidget *ui;
};

#endif // INITIALWIDGET_H
