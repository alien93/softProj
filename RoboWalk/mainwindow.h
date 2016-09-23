#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include "urdfparser.h"
#include <QKeyEvent>
#include "simulator/myglwidget.h"
#include <QtGui>
#include "simulator/anndemo.h"
#include "ann/neatann.h"
#include "model/link.h"
#include "ann/experiment.h"
#include "neat/network.h"

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
    void on_createANN_clicked();

    void on_trainANN_clicked();

    void on_pushButton_clicked();

    void on_loadANN_clicked();

    void on_hexagon_toggled(bool checked);

    void on_fixed_toggled(bool checked);

    void on_generated_toggled(bool checked);

private:
    QComboBox* cb;
    QPushButton* button;
    void keyPressEvent(QKeyEvent *event);
    void addButtons();
    Ui::MainWindow *ui;
    AnnDemo annDemo;
    NeatAnn neatAnn;
    QElapsedTimer annElapsedTimer;
    int checkedButton;
};

#endif // MAINWINDOW_H
