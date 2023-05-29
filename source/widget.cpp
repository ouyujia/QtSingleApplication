#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDir>
#include <QProcess>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("tip");
    msgBox.setInformativeText("Do you want restart ?");
    msgBox.setStandardButtons(QMessageBox::Ok |  QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    if(msgBox.exec() == QMessageBox::Ok)
    {
        QString program = QApplication::applicationFilePath();
        QStringList arguments = QApplication::arguments();
        arguments.append("restart");
        QString workingDirectory = QDir::currentPath();
        QProcess::startDetached(program, arguments, workingDirectory);
        QApplication::exit();
    }
}
