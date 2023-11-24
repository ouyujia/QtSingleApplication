#include "widget.h"
#include "qtsingleapplication.h"

#include <QApplication>
#include <QtGlobal>
#include <QRandomGenerator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QtSingleApplication a("Restart.exe", argc, argv);
    if (a.isRunning())
    {
        QStringList args{};
        for(int index = 0; index < argc; ++index)
        {
            args.append(QString::fromLocal8Bit(argv[index]));
        }
        //! 如果非软件自重启则保证只有一个程序实例
        if(args.indexOf("restart") < 0)
        {
            //! 让已存在实例激活自己的窗口并不执行任何操作（即 noop）。最后返回 EXIT_SUCCESS 表示程序正常退出。
            a.sendMessage("raise_window_noop", 1000);
            return EXIT_SUCCESS; //! 退出
        }
    }
    Widget w;
    // 生成一个范围在 [0, 99] 之间的随机整数
    int randomIntX = QRandomGenerator::global()->bounded(300);
    int randomIntY = QRandomGenerator::global()->bounded(200);
    qDebug() << "randomIntX" << randomIntX << "randomIntY" << randomIntY;
    w.move(randomIntX, randomIntY); //! 移动便于观察程序重启效果
    w.show();
    a.setActivationWindow(&w, true); //! 设置程序活动窗口
    return a.exec();
}
