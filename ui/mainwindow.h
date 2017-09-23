//
// Created by linux on 17-9-13.
//

#ifndef FLYOS_CAMPUS_NETWORK_MAINWINDOW_H
#define FLYOS_CAMPUS_NETWORK_MAINWINDOW_H

#include <DMainWindow>
#include <QtWidgets/QStackedLayout>

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

    QList<PluginsInterface *> pluginsList;

    void itemChange(int index);

    void scanPlugins();
    void loadPlugins(QString plugPath);

};


#endif //FLYOS_CAMPUS_NETWORK_MAINWINDOW_H
