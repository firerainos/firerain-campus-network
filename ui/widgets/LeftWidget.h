//
// Created by linux on 17-9-13.
//

#ifndef FLYOS_CAMPUS_NETWORK_LEFTWIDGET_H
#define FLYOS_CAMPUS_NETWORK_LEFTWIDGET_H


#include <QtWidgets/QWidget>

class LeftWidget : public QWidget {
Q_OBJECT

public:
    explicit LeftWidget(QWidget *parent = nullptr);

    void addItem(QString name,QPixmap logo);

Q_SIGNALS:

    void itemChange(int index);

private:
struct item {
    QPixmap icon;
    QString name;
};

QList<item> items;

QString currentTitle;

protected:

virtual void paintEvent(QPaintEvent *event);

virtual void mouseReleaseEvent(QMouseEvent *event);

};

#endif //FLYOS_CAMPUS_NETWORK_LEFTWIDGET_H
