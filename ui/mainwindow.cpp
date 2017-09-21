//
// Created by linux on 17-9-13.
//

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QStackedWidget>
#include "mainwindow.h"
#include "pages/H3cPage.h"

mainwindow::mainwindow(QWidget *parent) :
        DMainWindow(parent) {
    this->setMinimumSize(800, 500);

    QFrame *mainFrame = new QFrame(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(mainFrame);

    leftWidget = new LeftWidget(this);

    QStackedLayout *stackedLayout = new QStackedLayout(this);

    H3cPage *h3cPage = new H3cPage(this);

    stackedLayout->addWidget(h3cPage);

    mainLayout->addWidget(leftWidget);
    mainLayout->addLayout(stackedLayout);

    this->setCentralWidget(mainFrame);
}

