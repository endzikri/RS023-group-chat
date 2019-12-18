#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include <string>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//testiranje povezivanja na server
    mSocket = new QTcpSocket(this);
    mSocket->connectToHost("localhost",4567);


//    klijent dobija informaciju da je neki drugi klijent povezan na server
    connect(mSocket, &QTcpSocket::readyRead, [&]() {
        QTextStream T(mSocket);
        auto text = T.readAll();
        std::string textIspis = text.toUtf8().constData();
        std::cout << textIspis << std::endl;
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::broadcastAll(){
    QTextStream T(mSocket);
    T << "cao svima!!!";
    mSocket->flush();
}

