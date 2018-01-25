//
// Created by linux on 17-9-23.
//

#include <QtCore/QDir>
#include <QtCore/QCoreApplication>
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
#ifdef QT_DEBUG
    QString c3hPath = QDir::currentPath()+"/plugins/h3c/c3hclient";
#else
    QString c3hPath =  qApp->applicationDirPath() + "/../share/firerain-campus-network/h3c/c3hclient";
#endif

    c3hProcess->execute("pkexec", QStringList() << c3hPath
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
    if (checkC3hExist()){
        c3hProcess->execute("pkexec", QStringList() << "killall" << "c3hclient");
    }
}

QString H3cThread::readAllStandardOutput() {
    return c3hProcess->readAllStandardOutput();
}

QString H3cThread::readAllStandardError() {
    return c3hProcess->readAllStandardError();
}

bool H3cThread::checkC3hExist() {
    c3hProcess->start("bash", QStringList() << "-c" << "ps -ef | grep [c]3hclient");
    c3hProcess->waitForFinished(-1);

    return c3hProcess->readAll() != "";
}
