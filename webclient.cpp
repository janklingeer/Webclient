#include "webclient.h"
#include <thread>

Webclient::Webclient(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    connect(u_address, &QLineEdit::returnPressed, this, &Webclient::on_goBttn_clicked); //Pressing enter when entering URL starts the process as well

    m_socket = new QTcpSocket(this);
    connect(m_socket, &QTcpSocket::connected, this, &Webclient::onsConnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &Webclient::onsReadyRead);
}

void Webclient::printMsg(QString message, QColor color)
{
    u_outputterminal->clear();
    u_outputterminal->setTextColor(color);
    u_outputterminal->setText(message);
}

void Webclient::onsConnected()
{
    m_socket->write(QString("GET / HTTP/1.1\r\nHost:" + m_address + "\r\n\r\n").toLocal8Bit());
}

void Webclient::onsReadyRead()
{
    printMsg(m_socket->readAll());
    m_socket->disconnectFromHost();
}

void Webclient::on_goBttn_clicked()
{
    if(!u_address->text().isEmpty())
    {
        m_address = u_address->text();

        m_socket->connectToHost(m_address, m_port);
        if(!m_socket->waitForConnected(3000))
        {
            printMsg(m_address + "Your Session has timed out, please try again!", QColor::fromRgb(255, 0, 0));
            m_socket->reset();
        }
    }
    else
        printMsg("Please enter an address", QColor::fromRgb(255, 0, 0));
}
