#include "dedicatedservcontrol.h"

#include <QDir>
#include <QFile>

dedicatedServControl::dedicatedServControl(QWidget *parent)
    : QWidget(parent)
{
    lay = new QVBoxLayout(this);
    text = new QTextBrowser(this);
    exit = new QPushButton("exit" ,this);

    lay->addWidget(text);
    lay->addWidget(exit);

    qsrand(time(NULL));

    QHostAddress addr;
    QList<QHostAddress> interList = QNetworkInterface::allAddresses();
    for(int i = 0; i < interList.count(); i++)
    {
        if(interList.at(i).isLoopback())
            continue;
        else if(interList.at(i).isInSubnet(QHostAddress("0.0.0.0"), 0))
            addr = interList.at(i);
    }

    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(connected()));
    server->listen(addr, 21044);
    text->append("Started on : " + addr.toString() + ":21044");
}

void dedicatedServControl::connected()
{
    socket = server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(newMessage()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    int iters = qrand()%30;
    rookies = "";
    for(int i = 0; i < iters; i++)
        rookies.append(QString::number(qrand()%10));
    QTextStream stream(socket);
    text->append("Connected user");
    stream << "rookies " + rookies + " end \n";
    text->append("Send rookies");
}

void dedicatedServControl::newMessage()
{
    QTextStream stream(socket);
    QVector<QString> messages;
    QString mess;
    stream >> mess;
    messages.append(mess);
    text->append("=====mess recv=====");
    text->append(mess);
    while(mess!="end")
    {
        stream>>mess;
        messages.append(mess);
        text->append(mess);
        if(mess.isEmpty())
        {
            text->append("_____________________");
            text->append("||EXTREMAL END!||");
            text->append("||EMPTY     MESS!||");
            text->append("===================");
            return;
        }
    }
    text->append("===================");

    text->append("Word = " + QString::number(messages.count()));
    if(messages.at(0) == "setvolume")
    {
        if(messages.count() == 4)
        {
            QString rook = messages.at(2);
            if(rookies==rook)
            {
                system(QString("amixer set 'Master' " + messages.at(1) + "%").toStdString().c_str());
                text->append(QString("amixer set 'Master' " + messages.at(1) + "%").toStdString().c_str());
            }
        }
    }
    else if(messages.at(0) == "mousemove")
    {
        if(messages.count() == 5)
        {
            QString rook = messages.at(3);
            if(rookies==rook)
            {
                system(QString("xte 'mousermove " +
                               messages.at(1) + " " + messages.at(2) + "';")
                       .toStdString().c_str());
                text->append(QString("xte 'mousermove " +
                                     messages.at(1) + " " + messages.at(2) + "';"));
            }
        }
    }
    else if(messages.at(0) == "mousepress")
    {
        if(messages.count() == 3)
        {
            QString rook = messages.at(1);
            if(rookies == rook)
            {
                system(QString("xte 'mouseclick 1';").toStdString().c_str());
                text->append("xte 'mouseclick 1';");

            }
        }
    }
    else if(messages.at(0) == "keypress")
    {
        if(messages.count() == 4)
        {
            QString rook = messages.at(2);
            if(rookies == rook)
            {
                system(QString("xte 'key " + messages.at(1) + "';").toStdString().c_str());
                text->append("xte 'key " + messages.at(1) + "';");
            }
        }
    }
    else if(messages.at(0) == "console")
    {
        if(messages.count()>=4)
        {
            QString rook = messages.at(1);
            QString req;
            for(int i = 2; i < messages.length() && messages.at(i)!="end"; i++)
            {
                req.append(" " + messages.at(i));
            }
            req.append(" > console");
            system(req.toStdString().c_str());
            QFile *file = new QFile("./console");
            qDebug() << req;
            file->open(QIODevice::ReadOnly | QIODevice::Text);
            stream << file->readAll();
        }
    }
}

void dedicatedServControl::disconnected()
{
    socket->close();
}

dedicatedServControl::~dedicatedServControl()
{
}
