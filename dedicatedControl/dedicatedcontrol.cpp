#include "dedicatedcontrol.h"

dedicatedControl::dedicatedControl(QWidget *parent)
    : QWidget(parent)
{
    lay =           new QVBoxLayout(this);

    addrLay =       new QHBoxLayout(this);
    addrLine =      new QLineEdit("192.168.0.105", this);
    connectButt =   new QPushButton("connect" ,this);
    tapButt     =   new QPushButton("mouse", this);
    connect(connectButt, SIGNAL(clicked(bool)), this, SLOT(connectToHost()));
    connect(tapButt,     SIGNAL(clicked(bool)), this, SLOT(showTaper()));
    addrLay->addWidget(addrLine);
    addrLay->addWidget(connectButt);
    addrLay->addWidget(tapButt);

    volume = new QSlider(Qt::Horizontal, this);
    volume->setValue(50);
    connect(volume, SIGNAL(valueChanged(int)), this ,SLOT(sendVolume()));

    lay->addLayout(addrLay);
    lay->addWidget(volume);

    socket = Q_NULLPTR;
}

void dedicatedControl::sendVolume()
{
    QTextStream stream(socket);
    QString message = "setvolume " + QString::number(volume->value()) + " ";
    message.append(   rookies + " end \n");
    stream << message;
}

void dedicatedControl::showTaper()
{
    mouseWidget = new mouseMover(socket, rookies, this);
}

void dedicatedControl::connectToHost()
{
    if(socket)
    {
        delete socket;
        socket = Q_NULLPTR;
    }

    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(messageFromHost()));
    socket->connectToHost(QHostAddress(addrLine->text()), 21044);
}

void dedicatedControl::messageFromHost()
{
    QTextStream stream(socket);
    QVector<QString> messages;
    QString mess;
    stream >> mess;
    messages.append(mess);
    qDebug() << mess;
    while(mess!="end")
    {
        stream >> mess;
        qDebug() << mess;
        if(mess.isEmpty())
            return;
        messages.append(mess);
    }
    if(messages.at(0) == "rookies")
    {
        if(messages.count() == 3)
        {
            rookies = messages.at(1);
        }
    }
}

dedicatedControl::~dedicatedControl()
{

}
