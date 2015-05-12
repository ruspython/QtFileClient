#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QDebug>
#include <QString>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QTcpSocket>
#include <QFile>
#include <QDataStream>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    QFileDialog *fileDialog;
    QGridLayout *layout;
    QPushButton *fileBtn;
    QPushButton *sendBtn;
    QLabel *fileLabel;
    QLabel *progressLabel;

    QString fileName;
    QTcpSocket *tcpSocket;

    ~Widget();
public slots:
    void fileOpened();
    void onSend();
};

#endif // WIDGET_H
