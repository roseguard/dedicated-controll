#ifndef DEDICATEDSERVCONTROL_H
#define DEDICATEDSERVCONTROL_H

#include <QWidget>
#include <QKeyEvent>
#include <QAudioOutput>
#include <QSlider>
#include <QVBoxLayout>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextBrowser>
#include <QPushButton>
#include <QNetworkInterface>
#include <QList>
#include <QTextStream>
#include <QVector>
#include <stdlib.h>
#include <time.h>

class dedicatedServControl : public QWidget
{
    Q_OBJECT

public:
    dedicatedServControl(QWidget *parent = 0);
    ~dedicatedServControl();

private:
    QVBoxLayout     *lay;
    QTextBrowser    *text;
    QPushButton     *exit;

    QTcpServer      *server;
    QTcpSocket      *socket;

    QString         rookies;

public slots:
    void connected();
    void disconnected();
    void newMessage();
};

#endif // DEDICATEDSERVCONTROL_H
