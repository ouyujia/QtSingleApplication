# QT程序自重启与单个程序实例冲突

## 前言

在QT软件开发中很多情况下都需要保证应用程序实例只有一个（需要和硬件交互）并且需要支持程序重启操作。

可以通过QtSingleApplication和QProcess实现上述功能，但是在实际开发中发现，两者存在冲突情况，软件自重启时因为应用程序只能有一个实例导致无法自重启（通过测试发现原因为：cup及内存硬件条件差，自重启时间较长导致源程序推出后，自启程序还没起来）。下面是可行的两种解决方案。

## 解决方案

### 通过第二个程序（重启工具程序）重启目标程序（需要重启的程序）

1. 在程序需要重启的地方通过QProcess::startDetached();来启动重启工具程序;
2. 调用QApplication::exit();退出当前程序
3. 在重启工具程序中通过QProcess::startDetached();来启动目标程序
4. 调用QApplication::exit();退出重启工具程序

> 该方法需要使用第二个程序，增加了项目的复杂性，且无法确保程序稳定性，不推荐使用。

### 通过添加自定义指令达到再重启目的

程序需要自重启的地方添加下列重启代码

```c++
QString program = QApplication::applicationFilePath();
QStringList arguments = QApplication::arguments();
arguments.append("restart"); //! 命令行添加重启指令，该指令为自定义指令可为其他字符，如："reboot"
QString workingDirectory = QDir::currentPath();
QProcess::startDetached(program, arguments, workingDirectory);
QApplication::exit();
```

程序入口main中添加下列代码

```c++
QtSingleApplication a("Test.exe", argc, argv);   
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
        return EXIT_SUCCESS;
    }
}
```

> 注：需要注意QtSingleApplication是qt的库但安装qt时不会添加这个库，需要自己去qt官网下载，然后包含在项目中

## 参考资料

[qtSingleApplication使用总结](https://blog.csdn.net/iamsujin/article/details/53257038)

[QtSingleApplication 使用总结](https://blog.csdn.net/huang1600301017/article/details/121363969)

