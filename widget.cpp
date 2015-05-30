#include "widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
//    progressBar = new QProgressBar(this);

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
//    layout->addWidget(progressBar, 2, 0);

    connect(fileBtn, &QPushButton::clicked, this, &Widget::fileOpened);
    connect(sendBtn, &QPushButton::clicked, this, &Widget::onSend);

    setLayout(layout);
}

Widget::~Widget()
{
}

void Widget::fileOpened() {
    fileName = QFileDialog::getOpenFileName(this, tr("Open file"));
    QFileInfo fileInfo(fileName);
    fileLabel->setText(fileInfo.fileName() + " : " + QString::number(fileInfo.size()));
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

//            progressBar->setMaximum(fileInfo.size());

            while (!file.atEnd())
            {
                QByteArray rawFile;
                rawFile = file.read(5000);
                //false size inc
                QFileInfo rawFileInfo(rawFile);
                size += rawFileInfo.size();
                out << rawFile;
//                progressBar->setValue(rawFile.size());
                qDebug() << "ToSend:"<< rawFile.size();
            }
            out << "#END";
            startServer();
        }
}


void Widget::startServer() {
    qDebug() << "waiting for reply...";
    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(acceptReplyConnection()));
    if (!tcpServer->listen(QHostAddress::Any, 44444)) {
        qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
    } else {
        qDebug() << QString::fromUtf8("Сервер-ожидальщик-ответа запущен!");
    }
}


void Widget::acceptReplyConnection() {
    qDebug() << QString::fromUtf8("ответное соединение");
    tcpServerConnection = tcpServer->nextPendingConnection();
    connect(tcpServerConnection,SIGNAL(readyRead()),this, SLOT(slotReadClient()));
    tcpServer->close();

}


void Widget::slotReadClient() {
    QDataStream in(tcpServerConnection);
    QByteArray tmpArr;
    QString tmpString;
    in << tmpArr;
    qDebug() << "bytesAvailable:" << tcpServerConnection->bytesAvailable();
    qDebug() << tmpArr;


    if (tmpString.toInt()==1){
        qDebug() << "successfully sent";
    }else {
        qDebug() << "fail";
    }
}
