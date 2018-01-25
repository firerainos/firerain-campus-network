#include <DApplication>
#include <zconf.h>
#include <QtWidgets/QSystemTrayIcon>
#include "ui/mainwindow.h"


DWIDGET_USE_NAMESPACE

int main(int argc, char **argv) {
    DApplication::loadDXcbPlugin();
    DApplication app(argc, argv);
    if (app.setSingleInstance(QString("firerain-campus-network_%1").arg(getuid()))) {
        app.setTheme("light");
        app.loadTranslator();
        app.setApplicationDisplayName("校园网客户端");
        app.setApplicationName(DApplication::translate("firerain-campus-network","校园网客户端"));
        app.setApplicationVersion("1.0.0");
        app.setOrganizationName("firerain");
        app.setOrganizationDomain("firerain.xyz");
        app.setApplicationDescription(DApplication::translate("MainWindow", "校园网客户端") + "\n");
        app.setProductIcon(QIcon(":/images/logo.png"));

        mainwindow window;
        window.show();

        return app.exec();
    }

    return 0;
}