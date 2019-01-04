#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QDebug>
#include <QMessageBox>
ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    isStart=true;
    st2=new QTcpSocket(this);
    connect(st2,&QTcpSocket::readyRead,
           [=]()
    {
        //取出接受的内容  头还是数据
        QByteArray buf=st2->readAll();

        if(true==isStart)
        {
            isStart=false;
            //解析头部信息(拆包) QString buf="hello##1024"
           // QString str="hello##1024";
            //str.section("##",0,);

            //初始化
            fileName=QString(buf).section("##",0,0);
            fileSize=QString(buf).section("##",1,1).toInt();
            qDebug()<<fileName;
            qDebug()<<"and";
            qDebug()<<fileSize;
            receivesize=0;
            //打开文件
            file.setFileName(fileName);
            bool isOK=file.open(QIODevice::WriteOnly);
            if(false==isOK)
            {
                qDebug()<<"WriteOnly error 40";

            }
        }
            else//文件信息
            {
                qDebug()<<"正在发送：";
                qDebug()<<receivesize;
               qint64 len=file.write(buf);
               receivesize+=len;
               if(receivesize==fileSize)
               {
                   file.close();
                   QMessageBox::information(this,"完成","文件接受完成");
                   st2->disconnectFromHost();
                   st2->close();
               }
            }
        }

            );
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_connectbutton_clicked()
{
  //从编辑框中获取服务器ip和端口
  port1=ui->lineEdit2->text().toInt();
  ip1=ui->lineEdit->text();
  //连接
  st2->connectToHost(QHostAddress(ip1),port1);



}
