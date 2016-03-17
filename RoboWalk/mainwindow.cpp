#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include "urdfparser.h"
#include <QKeyEvent>
#include "simulator/myglwidget.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

     float xrotation =  ui->robotSimulation->getXRotation();
     float yrotation =  ui->robotSimulation->getYRotation();
     float sceneDistance = ui->robotSimulation->getSceneDistance();
     switch(event->key())
     {
        case Qt::Key_S:
            xrotation -= 5.0f;
            ui->robotSimulation->setXRotation(xrotation);
            ui->robotSimulation->repaint();
            break;
        case Qt::Key_W:
            xrotation += 5.0f;
            ui->robotSimulation->setXRotation(xrotation);
            ui->robotSimulation->repaint();
            break;
        case Qt::Key_D:
            yrotation -= 5.0f;
            ui->robotSimulation->setYRotation(yrotation);
            ui->robotSimulation->repaint();
            break;
        case Qt::Key_A:
            yrotation += 5.0f;
            ui->robotSimulation->setYRotation(yrotation);
            ui->robotSimulation->repaint();
            break;
        case Qt::Key_Plus:
            sceneDistance += 10.0f;
            ui->robotSimulation->setSceneDistance(sceneDistance);
            ui->robotSimulation->repaint();
            break;
        case Qt::Key_Minus:
            sceneDistance -= 10.0f;
            ui->robotSimulation->setSceneDistance(sceneDistance);
            ui->robotSimulation->repaint();
            break;
    }
}


void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionInsert_URDF_file_triggered()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Select URDF file"),
                "",
                "URDF files (*.urdf)"
                );
    URDFparser* parser = URDFparser::getInstance();
    ui->robotSimulation->reset();
    parser->parseURDF(filename);
}
