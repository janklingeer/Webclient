#ifndef WEBCLIENT_H
#define WEBCLIENT_H

#include "ui_webclient.h"
#include <QTcpSocket>
#include <QDebug>
#include <QAbstractSocket>


class Webclient : public QWidget, private Ui::Webclient
{
    Q_OBJECT

public:
    explicit Webclient(QWidget *parent = nullptr);

private slots:
    void on_goBttn_clicked();

private:
    void onSConnected();
    void onSReadyRead();

private:
    QTcpSocket* m_socket = nullptr;
    QString m_address;
    const char m_port = 80;

};

#endif // WEBCLIENT_H
