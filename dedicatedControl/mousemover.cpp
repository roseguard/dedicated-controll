#include "mousemover.h"

mouseMover::mouseMover(QTcpSocket *sock, QString rookies, QWidget *parent)
{
    socket = sock;
    lay = new QVBoxLayout(this);
    this->showMaximized();

    fx = 0;
    fy = 0;
    ex = 0;
    ey = 0;
    tfx = 0;
    tfy = 0;
    tex = 0;
    tey = 0;

    rook = rookies;
    clocking = new QTimer(this);
    clocking->setInterval(100);
    connect(clocking, SIGNAL(timeout()), this, SLOT(sendNewMove()));
}

void mouseMover::mousePressEvent(QMouseEvent *event)
{
    fx = event->x();
    fy = event->y();
    tfx = event->x();
    tfy = event->y();
    clocking->start();
}

void mouseMover::mouseReleaseEvent(QMouseEvent *event)
{
    ex = event->x();
    ey = event->y();
    clocking->stop();
    sendMover();
}

void mouseMover::sendMover()
{
    QTextStream stream(socket);
    QString mess;
    if  ((ey - fy > -10 && ey - fy < 10) &&
        (ex - fx > -10 && ex - fx < 10))
    {
        mess = "mousepress " + rook + " end ";
        stream << mess;
    }
}

void mouseMover::sendNewMove()
{
    tex = QCursor::pos().x();
    tey = QCursor::pos().y();
    qDebug() << tex << tey;
    qDebug() << tfx << tfy;
    QString mess;
    mess =      "mousemove " + QString::number(tex - tfx) + " " +
                 QString::number(tey - tfy) + " " + rook + " end ";
    QTextStream stream(socket);
    stream << mess;
    tfx = tex;
    tfy = tey;
}
