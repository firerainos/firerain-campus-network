//
// Created by linux on 17-9-13.
//

#ifndef FLYOS_CAMPUS_NETWORK_H3CWIDGET_H
#define FLYOS_CAMPUS_NETWORK_H3CWIDGET_H


#include <QtWidgets/QFrame>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QTextBrowser>
#include <QtCore/QProcess>
#include "H3cThread.h"

class H3cWidget : public QFrame{
    Q_OBJECT
public:
    explicit H3cWidget(QWidget *parent = nullptr);

private:
    QLineEdit *usernameEdit;
    QLineEdit *passwdEdit;
    QLineEdit *reconnectEdit;
    QLineEdit *versionEdit;

    QComboBox *deviceBox;
    QComboBox *langBox;

    QTextBrowser *logDisplay;

    QPushButton *startButton;

    H3cThread *h3cThread;

    void initUI();

    void initConnect();

    void initAllDeviceList();

    void setEditEnable(bool enable);

private Q_SLOT:

    void startConnect();

    void c3hProOutput();
    void c3hProError();
    void c3hFinished(int exitCode);

};


#endif //FLYOS_CAMPUS_NETWORK_H3CWIDGET_H
