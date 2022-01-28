#include "webclient.h"
#include <thread>

Webclient::Webclient(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    connect(u_address, &QLineEdit::returnPressed, this, &Webclient::on_goBttn_clicked);

    m_socket = new QTcpSocket(this);
    connect(m_socket, &QTcpSocket::connected, this, &Webclient::onSConnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &Webclient::onSReadyRead);
}



void Webclient::onSConnected()
{
    m_socket->write(QString("GET / HTTP/1.1\r\nHost:" + m_address + "\r\n\r\n").toLocal8Bit());
}

void Webclient::onSReadyRead()
{

    u_outputterminal->setText(m_socket->readAll());
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
            u_outputterminal->setText("connect failed!");
            m_socket->reset();
        }
    }
    else
        u_outputterminal->setText("Please enter an address");
}
