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
#include <QProgressBar>
#include <QTcpServer>


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
    QProgressBar *progressBar;
    QTcpServer *tcpServer;
    QTcpSocket *tcpServerConnection;

    QString fileName;
    QTcpSocket *tcpSocket;

    void startServer();

    ~Widget();
public slots:
    void fileOpened();
    void onSend();
    void acceptReplyConnection();
    void slotReadClient();
};

#endif // WIDGET_H
