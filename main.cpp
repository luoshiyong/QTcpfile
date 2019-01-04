#include "ServerWight.h"
#include <QApplication>
#include "clientWidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerWight w;
    w.show();
    qDebug()<<"服务器没问题！";
    ClientWidget w2;
    w2.show();
    return a.exec();
}
