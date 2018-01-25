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
#include <QCloseEvent>

#include <QDebug>
#include <QtCore/QStandardPaths>
#include <QtWidgets/QMenu>

mainwindow::mainwindow(QWidget *parent) :
        DMainWindow(parent) {
    this->setMinimumSize(800, 500);

    QFrame *mainFrame = new QFrame(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(mainFrame);

    leftWidget = new LeftWidget(this);

    stackedLayout = new QStackedLayout(this);

    mainLayout->addWidget(leftWidget);
    mainLayout->addLayout(stackedLayout);

    connect(leftWidget, &LeftWidget::itemChange, this, &mainwindow::itemChange);

    this->setCentralWidget(mainFrame);

    systemTrayIcon = new QSystemTrayIcon(QIcon(QPixmap(":/images/logo.png")), this);
    systemTrayIcon->show();

    QMenu *menu = new QMenu(this);
    QAction *openAction = new QAction("打开主窗口", this);
    QAction *exitAction = new QAction("退出", this);

    connect(openAction, &QAction::triggered, this,&mainwindow::show);
    connect(exitAction, &QAction::triggered, this, [=]{
        isExit = true;
        close();
    });

    menu->addAction(openAction);
    menu->addAction(exitAction);

    systemTrayIcon->setContextMenu(menu);

    scanPlugins();
}

void mainwindow::closeEvent(QCloseEvent *event) {
    if (!isExit){
        hide();
        systemTrayIcon->showMessage("提示", "已最小化到系统托盘");
        event->ignore();
    }

    closePlugins();
}

void mainwindow::scanPlugins() {
#ifdef QT_DEBUG
    QDir pluginsDir("plugins");
#else
    QDir pluginsDir(qApp->applicationDirPath() + "/../lib/firerain-campus-network/plugins");
#endif

    QStringList plugins = pluginsDir.entryList(QDir::Files);

    for (const QString file : plugins) {
        if (!QLibrary::isLibrary(pluginsDir.absoluteFilePath(file)))
            continue;

        loadPlugins(pluginsDir.absoluteFilePath(file));

    }

    QString confPath = (QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).first());

    confPath = confPath
               + "/" + QApplication::organizationName()
               + "/" + QApplication::applicationName()
               + "/plugins";

    pluginsDir = QDir(confPath);

    plugins = QDir(confPath).entryList(QDir::Files);

    for (const QString file : plugins) {
        if (!QLibrary::isLibrary(pluginsDir.absoluteFilePath(file)))
            continue;

        loadPlugins(pluginsDir.absoluteFilePath(file));

    }


}

void mainwindow::loadPlugins(QString plugPath) {
    qDebug() << plugPath;
    auto *loader = new QPluginLoader(plugPath, this);

    PluginsInterface *plugin = qobject_cast<PluginsInterface *>(loader->instance());

    if (!plugin){
        loader->unload();
        return;
    }

    qCritical() << "load plugins " + plugPath;

    pluginsList << plugin;

    stackedLayout->addWidget(plugin->pluginsWidget());

    leftWidget->addItem(plugin->pluginsName(), plugin->pluginsLogo());
}

void mainwindow::itemChange(int index) {
    stackedLayout->setCurrentIndex(index);
}

void mainwindow::closePlugins() {
    foreach(PluginsInterface *plug,pluginsList){
            plug->pluginsClose();
        }
}
