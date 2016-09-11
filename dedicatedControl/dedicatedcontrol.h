#ifndef DEDICATEDCONTROL_H
#define DEDICATEDCONTROL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QPushButton>
#include <QLineEdit>


#include <QTcpSocket>
#include <QHostAddress>
#include <QTextStream>
#include <QVector>

#include "mousemover.h"

class dedicatedControl : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout *lay;

    QHBoxLayout *addrLay;
    QLineEdit   *addrLine;
    QPushButton *connectButt;
    QPushButton *tapButt;

    QSlider     *volume;

    QTcpSocket  *socket;
    QString     rookies;

    mouseMover  *mouseWidget;

public slots:
    void sendVolume();

    void connectToHost();
    void messageFromHost();
    void showTaper();
public:
    dedicatedControl(QWidget *parent = 0);
    ~dedicatedControl();
};

#endif // DEDICATEDCONTROL_H
