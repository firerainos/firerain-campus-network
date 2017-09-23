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
#include <QtCore/QStandardPaths>

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

    scanPlugins();
}

void mainwindow::scanPlugins() {
#ifdef QT_DEBUG
    const QDir pluginsDir(QApplication::applicationDirPath() + "/plugins");
#else
    const QDir pluginsDir( QDir::currentPath() +"/../lib/flyos-campus-network/plugins");
#endif

    QStringList plugins = pluginsDir.entryList(QDir::Files);

    QString confPath = (QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).first());

    confPath = confPath
               + "/" + QApplication::organizationName()
               + "/" + QApplication::applicationName()
               + "/plugins";

    plugins << QDir(confPath).entryList(QDir::Files);

    for (const QString file : plugins) {
        if (!QLibrary::isLibrary(pluginsDir.absoluteFilePath(file)))
            continue;

        loadPlugins(pluginsDir.absoluteFilePath(file));

    }


}

void mainwindow::loadPlugins(QString plugPath) {

    auto *loader = new QPluginLoader(plugPath, this);

    qDebug() << loader->instance();

    PluginsInterface *plugin = qobject_cast<PluginsInterface *>(loader->instance());

    if (!plugin)
        return;

    qCritical() << "load plugins " + plugPath;

    pluginsList << plugin;

    qDebug() << plugin->pluginsName();

    stackedLayout->addWidget(plugin->pluginsWidget());

    leftWidget->addItem(plugin->pluginsName(), plugin->pluginsLogo());
}


