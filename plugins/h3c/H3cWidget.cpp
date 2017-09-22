//
// Created by linux on 17-9-13.
//

#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include "H3cWidget.h"

H3cWidget::H3cWidget(QWidget *parent) :
    QFrame(parent){

    initUI();

}

void H3cWidget::initUI() {
    auto *mainLayout = new QVBoxLayout(this);

    this->setLayout(mainLayout);

    auto *h3cLogo = new QLabel(this);
    h3cLogo->setFixedSize(100, 100);
    h3cLogo->setPixmap(QPixmap(":/resources/h3c.ico").scaled(100,100));

    auto *usernameLabel = new QLabel("用户名:", this);
    auto *passwdLabel = new QLabel("密 码:", this);
    auto *deviceLabel = new QLabel("网 卡:", this);

    usernameLabel->setFixedWidth(80);
    passwdLabel->setFixedWidth(80);
    deviceLabel->setFixedWidth(80);

    usernameEdit = new QLineEdit(this);
    passwdEdit = new QLineEdit(this);

    usernameEdit->setFixedWidth(200);
    passwdEdit->setFixedWidth(200);

    deviceBox = new QComboBox(this);
    deviceBox->setFixedWidth(200);

    startButton = new QPushButton("连接",this);
    startButton->setFixedSize(150, 35);

    auto *usernameLayout = new QHBoxLayout(this);
    auto *passwdLayout = new QHBoxLayout(this);
    auto *deviceLayout = new QHBoxLayout(this);

    usernameLayout->addStretch();
    usernameLayout->addWidget(usernameLabel);
    usernameLayout->addWidget(usernameEdit);
    usernameLayout->addStretch();

    passwdLayout->addStretch();
    passwdLayout->addWidget(passwdLabel);
    passwdLayout->addWidget(passwdEdit);
    passwdLayout->addStretch();

    deviceLayout->addStretch();
    deviceLayout->addWidget(deviceLabel);
    deviceLayout->addWidget(deviceBox);
    deviceLayout->addStretch();

    mainLayout->addStretch();
    mainLayout->addWidget(h3cLogo,0,Qt::AlignCenter);
    mainLayout->addSpacing(50);
    mainLayout->addLayout(usernameLayout);
    mainLayout->addLayout(passwdLayout);
    mainLayout->addLayout(deviceLayout);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(startButton,0,Qt::AlignCenter);
    mainLayout->addStretch();
}