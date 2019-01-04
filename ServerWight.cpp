#include "ServerWight.h"
#include "ui_serverwight.h"
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>
#include <QTimer>
ServerWight::ServerWight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWight)
{
    ui->setupUi(this);
    server=new QTcpServer(this);
    //绑定监听
    server->listen(QHostAddress::Any,8888);
    setWindowTitle("服务器端口为8888");
    ui->sendfile->setEnabled(false);
    ui->choosefile->setEnabled(false);
    //如果客户端成功和服务器连接
    connect(server,&QTcpServer::newConnection,
          [=]()
    {
        //取出建立好连接的套接字
        st1=server->nextPendingConnection();
        //获取对方ip和端口
        QString ip=st1->peerAddress().toString();
        quint16 port=st1->peerPort();
        //组一个包
        QString str=QString("[%1:%2]:成功连接").arg(ip).arg(port);
        ui->textEdit->setText(str);
        ui->sendfile->setEnabled(true);
        ui->choosefile->setEnabled(true);
    }
            );
    connect(&timer,&QTimer::timeout,
            [=]()
    {
        //g关闭定时器
        timer.stop();
        //发送文件
        sendDate();
    }

            );
}

ServerWight::~ServerWight()
{
    delete ui;
}
//选择文件按钮
void ServerWight::on_choosefile_clicked()
{
    QString filePath=QFileDialog::getOpenFileName(this,"open","../");
    if(false==filePath.isEmpty())
    {
        fileName.clear();
        fileSize=0;
        //读文件信息(只读方式打开)
        QFileInfo info(filePath);
        fileName=info.fileName();//获取文件大小和名字
        fileSize=info.size();
        sendsize=0;
        //指定文件名字
        file.setFileName(filePath);
        //打开文件
        bool isOK=file.open(QIODevice::ReadOnly);
        if(false == isOK)
        {
            qDebug()<<"以只读方式打开 77";

        }
        //提示打开文件的路径
        ui->textEdit->append(filePath);
        ui->choosefile->setEnabled(false);
        ui->sendfile->setEnabled(true);
    }
    else
    {
        qDebug()<<"选择文件目录出错！";

    }
}
//发送文件按钮
void ServerWight::on_sendfile_clicked()
{

    //先发送文件头信息 文件名##文件大小，等待一段时间
    //发送真正的文件信息
    QString head=QString("%1##%2").arg(fileName).arg(fileSize);
   qint64 len=st1->write(head.toUtf8());
   if(len>0)//头部信息发送成功
   {
       //防止tcp连包问题，需要通过定时器延时20ms
       timer.start(20);
   }
   else
   {
       qDebug()<<"头部信息发送失败 110";
       file.close();
       ui->sendfile->setEnabled(false);
       ui->choosefile->setEnabled(true);
   }

}
void ServerWight::sendDate()
{
    qint64 len=0;
    do
    {
        //每次发送数据的大小
        char buf[4*1024]={0};
        //往文件读数据
        len=file.read(buf,sizeof(buf));
        len=st1->write(buf,len);
        //发送数据累加
        sendsize+=len;
    }while(len>0);  //只要有数据就继续发
    //是否发送文件完毕
    if(sendsize==fileSize)
    {
        ui->textEdit->append("文件发送完毕！");
        file.close();\
        //断开客户端
        st1->disconnectFromHost();
        st1->close();
    }
}
