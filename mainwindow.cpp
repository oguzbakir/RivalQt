//
// Created by oguz on 02.04.2018.
//

#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QtWidgets/QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList allDeviceIds = runCommand("xinput --list --id-only").split("\n");
    foreach( QString id, allDeviceIds)
        {
            QString result3;
            QStringList result2 = runCommand("xinput --list-props " + id).split("'");
            if (result2.size() > 2){
                result3 = result2[1].toLatin1().data();
            }

            std::string result = runCommand("xinput --list-props "+ id).toLatin1().data();
            std::string str2 ("SteelSeries Rival");

            // different member versions of find in the same order as above:
            std::size_t found = result.find(str2);
            if (found!=std::string::npos) {
                ui->deviceNameLabel->setText(result3);
            }
        }

    if (system("which rivalcfg > /dev/null 2>&1")) {
        // Command doesn't exist...
        QMessageBox::information(
                this,
                tr("RivalQt"),
                tr("Please run this command 'sudo pip install rivalcfg' ") );
        exit(1);
    } else {
        // Command does exist
        std::cout << "hede" << endl;
    }





}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::applySettings()
{


}

void MainWindow::on_btnApply_clicked()
{

    applySettings();

    ui->statusBar->showMessage("Settings applied.", 1500);
}

QString MainWindow::runCommand(QString cmd)
{
    QProcess process;

    process.start(cmd);
    process.waitForFinished();
    QString output(process.readAllStandardOutput());

    return output;
}



