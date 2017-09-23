//
// Created by linux on 17-9-23.
//

#include <QtCore/QDir>
#include "H3cThread.h"

H3cThread::H3cThread() :
        QThread() {


    c3hProcess = new QProcess(this);
    connect(c3hProcess, SIGNAL(readyReadStandardOutput), SIGNAL(readyReadStandardOutput));
    connect(c3hProcess, SIGNAL(readyReadStandardError), SIGNAL(readyReadStandardError));
    connect(c3hProcess, SIGNAL(finished(int)),
            SIGNAL(finished(int)));
}

void H3cThread::run() {
    c3hProcess->execute("pkexec", QStringList() << QDir::currentPath() + "/plugins/h3c/c3hclient"
                                                << username
                                                << passwd
                                                << deviceName
                                                << reconnect
                                                << version);
}

void H3cThread::setArgv(QString username, QString passwd, QString deviceName, QString reconnect, QString version) {
    this->username = username;
    this->passwd = passwd;
    this->deviceName = deviceName;
    this->reconnect = reconnect;
    this->version = version;
}

void H3cThread::stop() {
    c3hProcess->kill();
    c3hProcess->execute("pkexec", QStringList() << "killall" << "c3hclient");
}

QString H3cThread::readAllStandardOutput() {
    return c3hProcess->readAllStandardOutput();
}

QString H3cThread::readAllStandardError() {
    return c3hProcess->readAllStandardError();
}
