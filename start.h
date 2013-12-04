#ifndef START_H
#define START_H

#include <QWidget>
#include <QtCore>
#include <QObject>

#include "ui_start.h"
#include "engine.h"
#include "editormainwindow.h"
#include "gamewindow.h"
#include "definitions.h"

namespace Ui {
class start;
}

class start : public QWidget
{
    Q_OBJECT

public:
    explicit start(QWidget *parent = 0);
    ~start();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::start *ui;
    QMediaPlayer *player;
};

#endif // START_H
