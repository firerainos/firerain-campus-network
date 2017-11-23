//
// Created by linux on 17-9-23.
//

#ifndef FLYOS_CAMPUS_NETWORK_H3CTHREAD_H
#define FLYOS_CAMPUS_NETWORK_H3CTHREAD_H


#include <QtCore/QThread>
#include <QtCore/QProcess>

class H3cThread : public QThread {
    Q_OBJECT
public:
    explicit H3cThread();

    void setArgv(QString username, QString passwd, QString deviceName, QString reconnect, QString version);

    QString readAllStandardOutput();
    QString readAllStandardError();

    void stop();
    bool checkC3hExist();


protected:
    virtual void run();

Q_SIGNALS:
    void readyReadStandardOutput(QPrivateSignal);
    void readyReadStandardError(QPrivateSignal);
    void finished(int exitCode);

private:
    QString username;
    QString passwd;
    QString deviceName;
    QString reconnect;
    QString version;

    QProcess *c3hProcess;
};


#endif //FLYOS_CAMPUS_NETWORK_H3CTHREAD_H
