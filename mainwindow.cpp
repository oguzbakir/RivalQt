//
// Created by oguz on 02.04.2018.
//

#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QtWidgets/QMessageBox>

#define RIVAL100SENS { "250", "500", "1000", "1250", "1500", "1750", "2000", "4000" }

#define RIVAL110SENS { "200", "300", "400", "500",\
"600", "700", "800", "900", "1000", "1100", "1200", "1300", "1400",\
"1500", "1600", "1700", "1800", "1900", "2000", "2100", "2200", "2300",\
"2400", "2500", "2600", "2700", "2800", "2900", "3000", "3100", "3200",\
"3300", "3400", "3500", "3600", "3700", "3800", "3900", "4000", "4100",\
"4200", "4300", "4400", "4500", "4600", "4700", "4800", "4900", "5000",\
"5100", "5200", "5300", "5400", "5500", "5600", "5700", "5800", "5900",\
"6000", "6100", "6200", "6300", "6400", "6500", "6600", "6700", "6800",\
"6900", "7000", "7100", "7200" }

#define RIVAL300SENS { "50", "100", "150", "200", "250", "300", "350",\
"400", "450", "500", "550", "600", "650", "700", "750", "800", "850", "900", "950",\
"1000", "1050", "1100", "1150", "1200", "1250", "1300", "1350", "1400", "1450",\
"1500", "1550", "1600", "1650", "1700", "1750", "1800", "1850", "1900", "1950",\
"2000", "2050", "2100", "2150", "2200", "2250", "2300", "2350", "2400", "2450",\
"2500", "2550", "2600", "2650", "2700", "2750", "2800", "2850", "2900", "2950",\
"3000", "3050", "3100", "3150", "3200", "3250", "3300", "3350", "3400", "3450",\
"3500", "3550", "3600", "3650", "3700", "3750", "3800", "3850", "3900", "3950",\
"4000", "4050", "4100", "4150", "4200", "4250", "4300", "4350", "4400", "4450",\
"4500", "4550", "4600", "4650", "4700", "4750", "4800", "4850", "4900", "4950",\
"5000", "5050", "5100", "5150", "5200", "5250", "5300", "5350", "5400", "5450",\
"5500", "5550", "5600", "5650", "5700", "5750", "5800", "5850", "5900", "5950",\
"6000", "6050", "6100", "6150", "6200", "6250", "6300", "6350", "6400", "6450" }

#define RIVAL310SENS { "100", "200", "300", "400", "500", "600", "700",\
"800", "900", "1000", "1100", "1200", "1300", "1400", "1500", "1600", "1700",\
"1800", "1900", "2000", "2100", "2200", "2300", "2400", "2500", "2600", "2700",\
"2800", "2900", "3000", "3100", "3200", "3300", "3400", "3500", "3600", "3700",\
"3800", "3900", "4000", "4100", "4200", "4300", "4400", "4500", "4600", "4700",\
"4800", "4900", "5000", "5100", "5200", "5300", "5400", "5500", "5600", "5700",\
"5800", "5900", "6000", "6100", "6200", "6300", "6400", "6500", "6600", "6700",\
"6800", "6900", "7000", "7100", "7200", "7300", "7400", "7500", "7600", "7700",\
"7800", "7900", "8000", "8100", "8200", "8300", "8400", "8500", "8600", "8700",\
"8800", "8900", "9000", "9100", "9200", "9300", "9400", "9500", "9600", "9700",\
"9800", "9900", "10000", "10100", "10200", "10300", "10400", "10500", "10600",\
"10700", "10800", "10900", "11000", "11100", "11200", "11300", "11400", "11500",\
"11600", "11700", "11800", "11900", "12000" }

#define POLLINGRATES { "125", "250", "500", "1000" }

#define BTN6_ACTION { "os", "default" }

#define LOGO_LIGHT_EFFECTS { "breathfast", "breathmed", "breathslow", "steady", "1", "2", "3", "4" }

#define WHEEL_LIGHT_EFFECTS { "breathfast", "breathmed", "breathslow", "steady", "1", "2", "3", "4" }




MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QStringList allDeviceIds = runCommand("xinput --list --id-only").split("\n");
    foreach( QString id, allDeviceIds)
        {
            QString result;
            QStringList resultList = runCommand("xinput --list-props " + id).split("'");
            if (resultList.size() > 2){
                result = resultList[1].toLatin1().data();
                if (result.contains("SteelSeries Rival")) {
                    ui->deviceNameLabel->setText(result);
                    device = result;
                }
            }
        }

    if (system("which rivalcfg > /dev/null 2>&1")) {
        // Command doesn't exist...
        QMessageBox::information(
                this,
                tr("RivalQt"),
                tr("Please run this command 'sudo pip install rivalcfg' ") );
        exit(1);
    }

    if (device.contains("100")) {
        ui->sens1Combo->addItems(RIVAL100SENS);
        ui->sens2Combo->addItems(RIVAL100SENS);
    } else if (device.contains("110")) {
        ui->sens1Combo->addItems(RIVAL110SENS);
        ui->sens2Combo->addItems(RIVAL110SENS);
    } else if (device.contains("300")) {
        ui->sens1Combo->addItems(RIVAL300SENS);
        ui->sens2Combo->addItems(RIVAL300SENS);
        ui->logoLightEffectCombo->addItems(LOGO_LIGHT_EFFECTS);
        ui->wheelLightEffectCombo->addItems(WHEEL_LIGHT_EFFECTS);
    } else if (device.contains("310")) {
        ui->sens1Combo->addItems(RIVAL310SENS);
        ui->sens2Combo->addItems(RIVAL310SENS);
        ui->logoLightEffectCombo->addItems(LOGO_LIGHT_EFFECTS);
        ui->wheelLightEffectCombo->addItems(WHEEL_LIGHT_EFFECTS);
    } else {
        printf("Device not found");
    }

    ui->button6Combo->addItems(BTN6_ACTION);

    ui->pollingRateCombo->addItems(POLLINGRATES);




}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_btnApply_clicked()
{


    std::string sens100[] = RIVAL100SENS;
    std::string sens110[] = RIVAL110SENS;
    std::string sens300[] = RIVAL300SENS;
    std::string sens310[] = RIVAL310SENS;
    std::string pollingRate[] = POLLINGRATES;
    std::string logoLightEffects[] = LOGO_LIGHT_EFFECTS;
    std::string wheelLightEffects[] = WHEEL_LIGHT_EFFECTS;

    std::string rivalcfg = "rivalcfg";
    std::string sens1 = "-s";
    std::string sens2 = "-S";
    std::string polling = "-p";
    std::string colorComm = "-c";
    std::string wheelColorComm = "-C";
    std::string logoLightEffectComm = "-e";
    std::string wheelLightEffectComm = "-E";

    std::string color = (ui->colorTextEdit->toPlainText().toStdString() == "") ? "red"  : ui->colorTextEdit->toPlainText().split("\n")[0].toStdString();
    std::string wheelColor = (ui->wColorTextEdit->toPlainText().toStdString() == "") ? "red"  : ui->colorTextEdit->toPlainText().split("\n")[0].toStdString();
    std::string logoLightEffect = logoLightEffects[ui->logoLightEffectCombo->currentIndex()];
    std::string wheelLightEffect = wheelLightEffects[ui->wheelLightEffectCombo->currentIndex()];
    std::string command;
    if (device.contains("100"))
        command = rivalcfg + " " + sens1 + " " + sens100[ui->sens1Combo->currentIndex()] +
                  " " + sens2 + " " + sens100[ui->sens2Combo->currentIndex()] +
                  " " + polling + " " + pollingRate[ui->pollingRateCombo->currentIndex()] +
                  " " + colorComm + " " + color;
    else if (device.contains("110"))
        command = rivalcfg + " " + sens1 + " " + sens110[ui->sens1Combo->currentIndex()] +
                  " " + sens2 + " " + sens110[ui->sens2Combo->currentIndex()] +
                  " " + polling + " " + pollingRate[ui->pollingRateCombo->currentIndex()] +
                  " " + colorComm + " " + color;
    else if (device.contains("300"))
        command = rivalcfg + " " + sens1 + " " + sens300[ui->sens1Combo->currentIndex()] + " " + sens2 + " " +
                  sens300[ui->sens2Combo->currentIndex()] + " " + polling + " " + pollingRate[ui->pollingRateCombo->currentIndex()] +
                  " " + colorComm + " " + color +
                  " " + wheelColorComm + " " + wheelColor +
                  " " + logoLightEffectComm + " " + logoLightEffect +
                  " " + wheelLightEffectComm + " " + wheelLightEffect;
    else if (device.contains("310"))
        command = rivalcfg + " " + sens1 + " " + sens310[ui->sens1Combo->currentIndex()] +
                  " " + sens2 + " " + sens310[ui->sens2Combo->currentIndex()] +
                  " " + polling + " " + pollingRate[ui->pollingRateCombo->currentIndex()];



    system(command.c_str());



    ui->statusBar->showMessage("Settings applied.", 1500);


}

void MainWindow::on_resetButton_clicked() {

    system("rivalcfg -r");

    ui->statusBar->showMessage("Settings reset.", 1500);

}

QString MainWindow::runCommand(QString cmd)
{
    QProcess process;

    process.start(cmd);
    process.waitForFinished();
    QString output(process.readAllStandardOutput());

    return output;
}



