//
// Created by linux on 17-9-13.
//

#include "LeftWidget.h"
#include <QPainter>
#include <QMouseEvent>

#include <QDebug>


LeftWidget::LeftWidget(QWidget *parent) :
    QWidget(parent){
    this->setFixedSize(160, 500);

//    item h3c;
//    h3c.name = "华三认证";
//    h3c.icon = "";
//
//    item drcom;
//    drcom.name = "Dr.com";
//    drcom.icon = "";
//
//    item fsurfing;
//    fsurfing.name = "佛大广东天翼校园";
//    fsurfing.icon = "";



}

void LeftWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(QPen(QColor(235, 235, 235)));
    painter.drawRect(this->width() - 1, 0, 1, 500);

    painter.drawPixmap(35, 10, QPixmap(":/images/logo.png").scaled(80,80,Qt::KeepAspectRatioByExpanding));

    int tabY = 140;
    for (int i = 0; i < items.length(); i++) {
        int width = 160;
        int height = 30;

        if (currentTitle == items[i].name) {
            QPainterPath path;
            path.addRect(0, tabY - 20, width, height);

            painter.setBrush(QBrush(QColor(0, 193, 127)));
            painter.setPen(QPen(QColor(0, 193, 127)));

            painter.drawPath(path);

            painter.setPen(QPen(QColor(Qt::white)));
        } else {
            painter.setPen(QPen(QColor("#32464A")));
        }

        painter.drawText(48, tabY, items[i].name);

        painter.drawPixmap(12, tabY - 18 ,items[i].icon.scaled(25,25,Qt::KeepAspectRatio));

        tabY += height;
    }
}

void LeftWidget::mouseReleaseEvent(QMouseEvent *event) {
    for (int i = items.length() -1; i >= 0; i--) {
        if (event->y() >= 140 + (i - 1) * 30) {
            currentTitle = items[i].name;
            repaint();
            emit itemChange(i);
            return;
        }

    }
}

void LeftWidget::addItem(QString name,QPixmap logo) {
    item item1;
    item1.name = name;
    item1.icon = logo;


    if (currentTitle.isEmpty())
        currentTitle = item1.name;

    items << item1;

    update();
}
