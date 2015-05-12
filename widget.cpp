#include "widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    tcpSocket = new QTcpSocket(this);

    fileLabel = new QLabel(this);
    progressLabel = new QLabel(this);

    fileBtn = new QPushButton(this);
    fileBtn->setText("Open");

    sendBtn = new QPushButton(this);
    sendBtn->setText("Send");

    layout = new QGridLayout;
    layout->addWidget(fileBtn, 0, 0);
    layout->addWidget(sendBtn, 0, 1);
    layout->addWidget(fileLabel, 1, 0);
    layout->addWidget(progressLabel, 2, 0);

    connect(fileBtn, &QPushButton::clicked, this, &Widget::fileOpened);
    connect(sendBtn, &QPushButton::clicked, this, &Widget::onSend);

    setLayout(layout);
}

Widget::~Widget()
{
}

void Widget::fileOpened() {
    fileName = QFileDialog::getOpenFileName(this, tr("Open file"));
    fileLabel->setText(fileName);
    qDebug() << fileName;
}

void Widget::onSend() {
    qDebug() << "trying to send a file...";

    tcpSocket->connectToHost("127.0.0.1", 33333);
    QFile file(fileName);
    QDataStream out(tcpSocket);
    int size = 0;

    if (file.open(QIODevice::ReadOnly))
        {
            QFileInfo fileInfo(file);
            QString fileName(fileInfo.fileName());

            out << fileName;
            out << QString::number(fileInfo.size());

            while (!file.atEnd())
            {
                QByteArray rawFile;
                rawFile = file.read(500);
                //false size inc
                size += 500;
                out << rawFile;
                qDebug() << QString::number(fileInfo.size());
                progressLabel->setText( QString("%1 of %2").arg(size, fileInfo.size() ) );
                qDebug() << QString("%1 of %2").arg(size, fileInfo.size());
                qDebug() << "ToSend:"<< rawFile.size();
            }
        }
}
