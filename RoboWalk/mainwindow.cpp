#include "mainwindow.h"

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
    ui->robotSimulation->reset();
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
    int result = parser->parseURDF(filename);
    if(result == 0)
    {
       addButtons();
    }
}

void MainWindow::addButtons()
{
    URDFparser* parser = URDFparser::getInstance();
    RobotModel rm = parser->rm;
    map<QString, MyLink> linksMap = rm.getLinks();
    map<QString, Joint> jointsMap = rm.getJoints();
    vector<Joint> joints = rm.sortJoints(jointsMap);
    cb = new QComboBox(ui->frame);
    QStringList* sl = new QStringList();
    button = new QPushButton("Test", ui->frame);
    button->show();

    for(uint i=0; i<joints.size();i++)
    {
        if(linksMap[joints.at(i).getParent().getLink()].getVisual().size()>0)
        {
            if(!sl->contains(joints.at(i).getParent().getLink()))
                sl->append(joints.at(i).getParent().getLink());
        }
        if(linksMap[joints.at(i).getChild().getLink()].getVisual().size()>0)
        {
            if(!sl->contains(joints.at(i).getChild().getLink()))
             sl->append(joints.at(i).getChild().getLink());
        }

    }
    cb->addItems(*sl);
    cb->setFixedWidth(150);
    button->setFixedWidth(40);
    connect(button, SIGNAL(released()), this, SLOT(testButtonClicked()));
    ui->formLayout->addRow(cb, button);
}

void MainWindow::testButtonClicked()
{
    if(button->text() == "Test")
       {
           button->setText("Stop");
           MyGLWidget::jointName = cb->currentText();
           ui->robotSimulation->repaint();
           ui->robotSimulation->animation();
           ui->robotSimulation->timer.start(16);
       }
       else
       {
           button->setText("Test");
           ui->robotSimulation->timer.stop();
       }
}

void MainWindow::on_createANN_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Training data"),
                "",
                "RW files (*.rw)"
                );
    annDemo.parseTrainingData(filename);
    annDemo.createANN(ui->annSimulation);
}

void MainWindow::on_trainANN_clicked()
{
    annDemo.trainANN(ui->robotSimulation);
}

//! Load ANN
void MainWindow::on_pushButton_clicked()
{
  /*  QString filename = QFileDialog::getOpenFileName(
                this,
                tr("ANN data"),
                "",
                "RWANN files (*.rwann)"
                );
    neatAnn.parseAnnData(filename, {1, 1});
    neatAnn.run();*/

    Experiment* e = new Experiment(ui->robotSimulation);
    //e->generateTestData();
    e->roboWalk_test(100);
}
