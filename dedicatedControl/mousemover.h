#ifndef MOUSEMOVER_H
#define MOUSEMOVER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QTcpSocket>
#include <QTextStream>
#include <QTimer>

class mouseMover : public QWidget
{
    Q_OBJECT
public:
    mouseMover(QTcpSocket *sock, QString rookies, QWidget *parent = 0);

    QVBoxLayout *lay;

    int fx, fy;
    int ex, ey;
    QTcpSocket *socket;
    QString    rook;
    QTimer  *clocking;
    int tfx, tfy;
    int tex, tey;

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void sendMover();

public slots:
    void sendNewMove();
};

#endif // MOUSEMOVER_H
