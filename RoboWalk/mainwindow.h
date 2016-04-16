#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <ode/ode.h>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include "urdfparser.h"
#include <QKeyEvent>
#include "simulator/myglwidget.h"
#include "ui_mainwindow.h"
#include <QtGui>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionExit_triggered();
    void on_actionInsert_URDF_file_triggered();
    void testButtonClicked();

private:
    QPushButton* button;

    QComboBox* cb;
    void keyPressEvent(QKeyEvent *event);
    void addButtons();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
