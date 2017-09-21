//
// Created by linux on 17-9-13.
//

#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include "H3cPage.h"

H3cPage::H3cPage(QWidget *parent) :
    QFrame(parent){
    QFormLayout *mainLayout = new QFormLayout(this);

    QLabel *h3cLogo = new QLabel(this);
    h3cLogo->setPixmap(QPixmap(":/images/h3c.ico"));

    usernameEdit = new QLineEdit(this);
    passwdEdit = new QLineEdit(this);

    startButton = new QPushButton("连接",this);

    mainLayout->addRow("用户名", usernameEdit);
    mainLayout->addRow("密码", passwdEdit);
    mainLayout->addRow(startButton);
}
