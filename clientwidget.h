#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H
#include <QTcpSocket>
#include <QWidget>
#include <QFile>
#include <QString>
#include <QHostAddress>
namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = 0);
    ~ClientWidget();

private slots:
    void on_pushButton_clicked();

    void on_connectbutton_clicked();

private:
    Ui::ClientWidget *ui;
    QTcpSocket* st2;

    QFile file;
    QString fileName;
    qint64 fileSize;
    qint64 receivesize;//已经接受了多少文件

    bool isStart;

    qint64 port1;
    QString ip1;
};

#endif // CLIENTWIDGET_H
