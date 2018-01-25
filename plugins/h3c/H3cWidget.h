//
// Created by linux on 17-9-13.
//

#ifndef FIRERAIN_CAMPUS_NETWORK_H3CWIDGET_H
#define FIRERAIN_CAMPUS_NETWORK_H3CWIDGET_H


#include <QtWidgets/QFrame>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QTextBrowser>
#include <QtCore/QProcess>
#include <QtWidgets/QCheckBox>
#include <QtCore/QSettings>
#include "H3cThread.h"

class H3cWidget : public QFrame{
    Q_OBJECT
public:
    explicit H3cWidget(QWidget *parent = nullptr);

    void startH3c();
    void stopH3c();

private:
    QLineEdit *usernameEdit;
    QLineEdit *passwdEdit;
    QLineEdit *reconnectEdit;
    QLineEdit *versionEdit;

    QComboBox *deviceBox;
    QComboBox *langBox;

    QCheckBox *remeberBox;
    QCheckBox *autoConnect;

    QTextBrowser *logDisplay;

    QPushButton *startButton;

    H3cThread *h3cThread;

    QString confPath;

    QSettings *conf;


    void initUI();

    void initConnect();

    void initAllDeviceList();

    void setEditEnable(bool enable);

    void saveConfig();

private Q_SLOT:

    void startConnect();

    void c3hProOutput();
    void c3hProError();
    void c3hFinished(int exitCode);

};


#endif //FIRERAIN_CAMPUS_NETWORK_H3CWIDGET_H
