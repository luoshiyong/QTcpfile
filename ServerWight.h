#ifndef SERVERWIGHT_H
#define SERVERWIGHT_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QWidget>
#include <Qfile>
#include <QTimer>
namespace Ui {
class ServerWight;
}

class ServerWight : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWight(QWidget *parent = 0);
    ~ServerWight();

private slots:
    void on_choosefile_clicked();

    void on_sendfile_clicked();
    void sendDate();  //发送文件数据
private:
    Ui::ServerWight *ui;
    QTcpServer* server;
    QTcpSocket* st1;
    QFile file;
    QString fileName;
    qint64 fileSize;
    qint64 sendsize;//已经发送了多少文件
    QTimer timer;//定时器
};

#endif // SERVERWIGHT_H
