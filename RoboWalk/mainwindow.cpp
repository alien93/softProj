#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include "urdfparser.h"

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
    parser->parseURDF(filename);
}
