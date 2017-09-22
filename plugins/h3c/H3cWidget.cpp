//
// Created by linux on 17-9-13.
//

#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <pcap.h>
#include "H3cWidget.h"

#include <QDebug>
#include <QtCore/QDir>

H3cWidget::H3cWidget(QWidget *parent) :
    QFrame(parent){

    c3hProcess = new QProcess(this);

    initUI();

    initConnect();

    initAllDeviceList();
}

void H3cWidget::initUI() {
    auto *mainLayout = new QVBoxLayout(this);

    this->setLayout(mainLayout);

    auto *h3cLogo = new QLabel(this);
    h3cLogo->setFixedSize(100, 100);
    h3cLogo->setPixmap(QPixmap(":/resources/h3c.ico").scaled(100,100,Qt::KeepAspectRatioByExpanding));

    auto *usernameLabel = new QLabel("用户名:", this);
    auto *passwdLabel = new QLabel("密 码:", this);
    auto *deviceLabel = new QLabel("网 卡:", this);
    auto *versionLabel = new QLabel("版 本:", this);
    auto *reconnectLabel = new QLabel("重连次数:", this);

    usernameLabel->setFixedWidth(80);
    passwdLabel->setFixedWidth(80);
    deviceLabel->setFixedWidth(80);
    versionLabel->setFixedWidth(80);
    reconnectLabel->setFixedWidth(80);

    usernameEdit = new QLineEdit(this);
    passwdEdit = new QLineEdit(this);
    reconnectEdit = new QLineEdit("0",this);

    usernameEdit->setFixedWidth(200);
    passwdEdit->setFixedWidth(200);
    reconnectEdit->setFixedWidth(200);

    deviceBox = new QComboBox(this);
    deviceBox->setFixedWidth(200);

    versionEdit = new QLineEdit("EN\x11V7.00-0102",this);
    versionEdit->setFixedWidth(200);

    startButton = new QPushButton("连接",this);
    startButton->setFixedSize(150, 35);

    auto *usernameLayout = new QHBoxLayout(this);
    auto *passwdLayout = new QHBoxLayout(this);
    auto *reconnectLayout = new QHBoxLayout(this);
    auto *deviceLayout = new QHBoxLayout(this);
    auto *versionLayout = new QHBoxLayout(this);

    usernameLayout->addStretch();
    usernameLayout->addWidget(usernameLabel);
    usernameLayout->addWidget(usernameEdit);
    usernameLayout->addStretch();

    passwdLayout->addStretch();
    passwdLayout->addWidget(passwdLabel);
    passwdLayout->addWidget(passwdEdit);
    passwdLayout->addStretch();

    reconnectLayout->addStretch();
    reconnectLayout->addWidget(reconnectLabel);
    reconnectLayout->addWidget(reconnectEdit);
    reconnectLayout->addStretch();

    deviceLayout->addStretch();
    deviceLayout->addWidget(deviceLabel);
    deviceLayout->addWidget(deviceBox);
    deviceLayout->addStretch();

    versionLayout->addStretch();
    versionLayout->addWidget(versionLabel);
    versionLayout->addWidget(versionEdit);
    versionLayout->addStretch();

    mainLayout->addStretch();
    mainLayout->addWidget(h3cLogo,0,Qt::AlignCenter);
    mainLayout->addSpacing(50);
    mainLayout->addLayout(usernameLayout);
    mainLayout->addLayout(passwdLayout);
    mainLayout->addLayout(reconnectLayout);
    mainLayout->addLayout(deviceLayout);
    mainLayout->addLayout(versionLayout);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(startButton,0,Qt::AlignCenter);
    mainLayout->addStretch();
}

void H3cWidget::initAllDeviceList() {
    pcap_if_t *alldevs;

    size_t i = 0;
    char errbuf[PCAP_ERRBUF_SIZE];

    if (pcap_findalldevs(&alldevs, errbuf) == 0){
        while (!(alldevs == NULL)){
#ifdef WIN32
            deviceBox->addItem(alldevs->description, alldevs->name);
#else
            deviceBox->addItem(alldevs->name,alldevs->name);
#endif
            alldevs = alldevs->next;
            i++;
        }
    }
    pcap_freealldevs(alldevs);
}

void H3cWidget::initConnect() {
    connect(startButton, &QPushButton::clicked, this, &H3cWidget::startConnect);

    connect(c3hProcess, &QProcess::readyReadStandardOutput, this, &H3cWidget::c3hProOutput);
    connect(c3hProcess, &QProcess::readyReadStandardError, this, &H3cWidget::c3hProError);
    connect(c3hProcess, static_cast<void (QProcess::*)(int)>(&QProcess::finished),
            this, static_cast<void (H3cWidget::*)(int)>(&H3cWidget::c3hFinished));
}

void H3cWidget::startConnect() {
    if (startButton->text()=="连接"){
        c3hProcess->start("pkexec", QStringList() << QDir::currentPath() + "/plugins/h3c/c3hclient"
                                                  << usernameEdit->text()
                                                  << passwdEdit->text()
                                                  << deviceBox->currentText()
                                                  << reconnectEdit->text()
                                                  << versionEdit->text());

        setEditEnable(false);
        startButton->setText("断开连接");
    }else {
        c3hProcess->kill();
        c3hProcess->execute("pkexec", QStringList() << "killall" << "c3hclient");

        setEditEnable(true);
        startButton->setText("连接");
    }

}

void H3cWidget::c3hProOutput() {
    qDebug() << QString(c3hProcess->readAllStandardOutput());
}

void H3cWidget::c3hProError() {
    qDebug() << QString(c3hProcess->readAllStandardError());
}

void H3cWidget::c3hFinished(int exitCode) {
    setEditEnable(true);
    startButton->setText("连接");
}

void H3cWidget::setEditEnable(bool enable) {
    usernameEdit->setEnabled(enable);
    passwdEdit->setEnabled(enable);
    deviceBox->setEnabled(enable);
}
