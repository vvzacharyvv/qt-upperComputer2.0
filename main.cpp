#include "mainwindow.h"

#include <QApplication>
QString appPath()
{
    static QString path;
    if (path.isEmpty()) {
        path = qApp->applicationDirPath();
    }

    return path;
}
QString appName()
{
    //没有必要每次都获取,只有当变量为空时才去获取一次
    static QString name;
    if (name.isEmpty()) {
        name = qApp->applicationFilePath();
        //下面的方法主要为了过滤安卓的路径 lib程序名_armeabi-v7a
        QStringList list = name.split("/");
        name = list.at(list.count() - 1).split(".").at(0);
        name.replace("_armeabi-v7a", "");
    }

    return name;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //读取配置文件
    AppConfig::ConfigFile = QString("%1/%2.ini").arg(appPath()).arg(appName());
    AppConfig::readConfig();
    MainWindow w;
    w.setWindowTitle("IBSS-UperComputer");
    w.show();
    return a.exec();
}
