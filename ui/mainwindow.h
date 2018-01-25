//
// Created by linux on 17-9-13.
//

#ifndef FIRERAIN_CAMPUS_NETWORK_MAINWINDOW_H
#define FIRERAIN_CAMPUS_NETWORK_MAINWINDOW_H

#include <DMainWindow>
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QSystemTrayIcon>

#include "widgets/LeftWidget.h"
#include "../interfaces/pluginsInterface.h"

DWIDGET_USE_NAMESPACE

class mainwindow : public DMainWindow{
    Q_OBJECT
public:
    explicit mainwindow(QWidget *parent = nullptr);

private:
    LeftWidget *leftWidget;
    QStackedLayout *stackedLayout;

    QSystemTrayIcon *systemTrayIcon;

    QList<PluginsInterface *> pluginsList;

    bool isExit = false;

    void itemChange(int index);

    void scanPlugins();
    void loadPlugins(QString plugPath);

    void closePlugins();

protected:
    virtual void closeEvent(QCloseEvent *event);

};


#endif //FIRERAIN_CAMPUS_NETWORK_MAINWINDOW_H
