#include "widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    progressBar = new QProgressBar(this);

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
    layout->addWidget(progressBar, 2, 0);

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

    tcpSocket->connectToHost("127.0.0.1", 33333);
    QFile file(fileName);

    QDataStream out(tcpSocket);
    int size = 0;

    if (file.open(QIODevice::ReadOnly))
        {
            QFileInfo fileInfo(file);
            QString fileName(fileInfo.fileName());

            out << fileName;
            qDebug() << fileName;
            out << QString::number(fileInfo.size());
            qDebug() << fileInfo.size();

            progressBar->setMaximum(fileInfo.size());

            while (!file.atEnd())
            {
                QByteArray rawFile;
                rawFile = file.read(50000);
                //false size inc
                QFileInfo rawFileInfo(rawFile);
                size += rawFileInfo.size();
                progressBar->setValue(size);
                out << rawFile;
                qDebug() << QString::number(fileInfo.size());
                qDebug() << QString("%1 of %2").arg(size, fileInfo.size());
                qDebug() << "ToSend:"<< rawFile.size();
            }
        }
}
