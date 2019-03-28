#ifndef TRACKING_H
#define TRACKING_H

#include <QMainWindow>
#include "opencv.hpp"
#include "opencv2/core/ocl.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/tracking.hpp"
#include <string>

#include <QDebug>

namespace Ui {
class tracking;
}

class tracking : public QMainWindow
{
    Q_OBJECT

public:
    explicit tracking(QWidget *parent = 0);
    ~tracking();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::tracking *ui;
};

#endif // TRACKING_H
