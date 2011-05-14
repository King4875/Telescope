#include "server.h"
#include <QTime>

Server::Server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Server)
{
    setupUi(this);
    socket=NULL;
    talk.clear();
    showText->setReadOnly(true);
    server.listen(QHostAddress("localhost"),12346);

    connect(&server,SIGNAL(newConnection()),this,SLOT(newSocket()));
    connect(lineEdit,SIGNAL(returnPressed()),this,SLOT(sendData()));

    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);



    QBitmap bmp(this->size());
    bmp.fill();
    QPainter pb(&bmp);
    pb.setPen(Qt::NoPen);
    pb.setBrush(Qt::black);
    pb.drawRoundedRect(bmp.rect(),10,10);
    setMask(bmp);//���ô�������


}
void Server::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.fillRect(rect(), QColor(8, 46, 84, 100));
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(7);
    pen.setColor(QColor("#DCDCDC"));
    p.setPen(pen);
    p.drawRoundedRect(rect(),10,10);
}
void Server::newSocket()
{
    socket=server.nextPendingConnection();
    connect(socket,SIGNAL(readyRead()),this,SLOT(receiveData()));
}

void Server::receiveData()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_3);
    in>>listen;

    showText->append(listen);
    if(this->isHidden()) emit showIMSignal();
}

void Server::sendData()
{
    QString str="<font size=3 color='#DEB887'>Server ";
    str.append(QTime::currentTime().toString());
    str.append("<br></font>");
    str.append("<font size=3 color='#DEB887'>");
    str.append("&nbsp;&nbsp;&nbsp;&nbsp;");
    str.append(lineEdit->text());
    str.append("<br>");
    str.append("</font>");
    if(!talk.isEmpty()) talk.append("<br>");
    talk.append(str);
    showText->append(str);
    lineEdit->clear();

    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_3);

    out<<talk;
    if(socket!=NULL)
    {
        socket->write(block);
        talk.clear();
    }
}

void Server::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {
        move(e->globalPos() - dragPoint);   //�ƶ�IM����
        this->parentWidget()->move(this->pos().x()-this->parentWidget()->width(),this->pos().y()-45);//�����ڸ���IM�ƶ�
        e->accept();
    }
}

void Server::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        dragPoint = e->globalPos() - frameGeometry().topLeft();
        e->accept();    //��ʾ���ø�����¼���Ӧ���������ˣ��൱�ڰ��¼��ػ�
    }
}

void Server::clearShowText()
{
    showText->clear();
}
