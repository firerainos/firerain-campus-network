//
// Created by linux on 17-9-13.
//

#include <QtWidgets/QHBoxLayout>
#include <QtCore/QDir>
#include "mainwindow.h"
#include <QApplication>
#include <QtCore/QLibrary>
#include <QPluginLoader>
#include <QtWidgets/QFrame>

#include <QDebug>

mainwindow::mainwindow(QWidget *parent) :
        DMainWindow(parent) {
    this->setMinimumSize(800, 500);

    QFrame *mainFrame = new QFrame(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(mainFrame);

    leftWidget = new LeftWidget(this);

    stackedLayout = new QStackedLayout(this);

    mainLayout->addWidget(leftWidget);
    mainLayout->addLayout(stackedLayout);

    this->setCentralWidget(mainFrame);

    loadPlugins();
}

void mainwindow::loadPlugins() {
#ifdef QT_DEBUG
    const QDir pluginsDir(QApplication::applicationDirPath() + "/plugins");
#else
    const QDir pluginsDir( "/usr/lib/flyos-campus-network/plugins");
#endif
    const QStringList plugins = pluginsDir.entryList(QDir::Files);
    for (const QString file : plugins) {
        if (!QLibrary::isLibrary(pluginsDir.absoluteFilePath(file)))
            continue;

        auto *loader = new QPluginLoader(pluginsDir.absoluteFilePath(file), this);

        qDebug() << loader->instance();

        PluginsInterface *plugin = qobject_cast<PluginsInterface *>(loader->instance());

        if (!plugin)
            continue;

        qCritical() << "load plugins " + file;

        pluginsList << plugin;

        qDebug() << plugin->pluginsName();

        stackedLayout->addWidget(plugin->pluginsWidget());

        leftWidget->addItem(plugin->pluginsName(), plugin->pluginsLogo());


    }

}

