//
// Created by oguz on 02.04.2018.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    

    QObject::connect(ui->sliderValue, SIGNAL(valueChanged(int)),
            ui->lblValue, SLOT(setNum(int)) );

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::runCommand(QString cmd)
{
    QProcess process;

    process.start(cmd);
    process.waitForFinished();
    QString output(process.readAllStandardOutput());

    return output;
}



