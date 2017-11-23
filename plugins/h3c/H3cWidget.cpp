//
// Created by linux on 17-9-13.
//

#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QVariant>
#include <pcap.h>
#include "H3cWidget.h"

#include <QDebug>
#include <QtCore/QDir>
#include <QtCore/QStandardPaths>
#include <QApplication>

H3cWidget::H3cWidget(QWidget *parent) :
    QFrame(parent){

    h3cThread = new H3cThread;


    confPath = (QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).first());

    confPath = confPath
               + "/" + QApplication::organizationName()
               + "/flyos-campus-network"
               + "/h3c.conf";

    conf = new QSettings(confPath, QSettings::IniFormat);

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

    usernameEdit = new QLineEdit(conf->value("h3c/username","").toString() ,this);
    passwdEdit = new QLineEdit(conf->value("h3c/passwd","").toString() ,this);
    reconnectEdit = new QLineEdit(conf->value("h3c/reconnect","0").toString() ,this);

    usernameEdit->setFixedWidth(200);
    passwdEdit->setFixedWidth(200);
    reconnectEdit->setFixedWidth(200);

    deviceBox = new QComboBox(this);
    deviceBox->setFixedWidth(200);

    versionEdit = new QLineEdit(conf->value("h3c/version","EN\x11V7.00-0102").toString(),this);
    versionEdit->setFixedWidth(200);

    startButton = new QPushButton("连接",this);
    startButton->setFixedSize(150, 35);

    logDisplay = new QTextBrowser(this);
    logDisplay->setMinimumWidth(500);
    logDisplay->setVisible(false);

    remeberBox = new QCheckBox("记住密码", this);
    autoConnect = new QCheckBox("自动登录", this);

    autoConnect->setEnabled(false);

    remeberBox->setChecked(conf->value("h3c/rember", false).toBool());
    autoConnect->setChecked(conf->value("h3c/autoConnect", false).toBool());

    auto *usernameLayout = new QHBoxLayout(this);
    auto *passwdLayout = new QHBoxLayout(this);
    auto *reconnectLayout = new QHBoxLayout(this);
    auto *deviceLayout = new QHBoxLayout(this);
    auto *versionLayout = new QHBoxLayout(this);
    auto *checkBoxLayout = new QHBoxLayout(this);

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

    checkBoxLayout->addStretch();
    checkBoxLayout->addWidget(remeberBox);
    checkBoxLayout->addSpacing(50);
    checkBoxLayout->addWidget(autoConnect);
    checkBoxLayout->addStretch();

    mainLayout->addStretch();
    mainLayout->addWidget(h3cLogo,0,Qt::AlignCenter);
    mainLayout->addSpacing(50);
    mainLayout->addLayout(usernameLayout);
    mainLayout->addLayout(passwdLayout);
    mainLayout->addLayout(reconnectLayout);
    mainLayout->addLayout(deviceLayout);
    mainLayout->addLayout(versionLayout);
    mainLayout->addLayout(checkBoxLayout);
    mainLayout->addWidget(logDisplay, 1);
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
            if (conf->value("h3c/device","").toString() == alldevs->name)
                deviceBox->setCurrentIndex(i);
#endif
            alldevs = alldevs->next;
            i++;
        }
    }
    pcap_freealldevs(alldevs);
}

void H3cWidget::initConnect() {
    connect(startButton, &QPushButton::clicked, this, &H3cWidget::startConnect);

    connect(h3cThread, &H3cThread::readyReadStandardOutput, this, &H3cWidget::c3hProOutput);
    connect(h3cThread, &H3cThread::readyReadStandardError, this, &H3cWidget::c3hProError);
    connect(h3cThread, static_cast<void (H3cThread::*)(int)>(&H3cThread::finished),
            this, static_cast<void (H3cWidget::*)(int)>(&H3cWidget::c3hFinished));
}

void H3cWidget::startConnect() {
    if (startButton->text()=="连接"){
        if (remeberBox->isChecked())
            saveConfig();

        h3cThread->setArgv(usernameEdit->text(),
                           passwdEdit->text(),
                           deviceBox->itemData(deviceBox->currentIndex()).toString(),
                           reconnectEdit->text(),
                           versionEdit->text());

        h3cThread->start();

        setEditEnable(false);
        startButton->setText("断开连接");
    }else {
        stopH3c();

        setEditEnable(true);
        startButton->setText("连接");
    }

}

void H3cWidget::c3hProOutput() {
    logDisplay->append(tr("<html><p>%1</html>").arg(h3cThread->readAllStandardOutput()));
}

void H3cWidget::c3hProError() {
    logDisplay->append(tr("<html><p style='background:red'>%1</html>").arg(h3cThread->readAllStandardError()));
}

void H3cWidget::c3hFinished(int exitCode) {
    qDebug() << exitCode;
    setEditEnable(true);
    startButton->setText("连接");
}

void H3cWidget::setEditEnable(bool enable) {
    usernameEdit->setEnabled(enable);
    passwdEdit->setEnabled(enable);
    reconnectEdit->setEnabled(enable);
    deviceBox->setEnabled(enable);
    versionEdit->setEnabled(enable);
}

void H3cWidget::saveConfig() {

    conf->setValue("h3c/username", usernameEdit->text());
    conf->setValue("h3c/passwd", passwdEdit->text());
    conf->setValue("h3c/reconnect", reconnectEdit->text());
    conf->setValue("h3c/device", deviceBox->currentData(deviceBox->currentIndex()).toString());
    conf->setValue("h3c/version", versionEdit->text());
    conf->setValue("h3c/rember", remeberBox->isChecked());
    conf->setValue("h3c/autoConnect", autoConnect->isChecked());
}

void H3cWidget::stopH3c() {
    h3cThread->stop();
}
