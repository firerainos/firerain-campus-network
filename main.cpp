#include <DApplication>
#include <zconf.h>
#include <QtWidgets/QSystemTrayIcon>
#include "ui/mainwindow.h"


DWIDGET_USE_NAMESPACE

int main(int argc, char **argv) {
    DApplication::loadDXcbPlugin();
    DApplication app(argc, argv);
    if (app.setSingleInstance(QString("flyos-campus-network_%1").arg(getuid()))) {
        app.setTheme("light");
        app.loadTranslator();
        app.setApplicationDisplayName("校园网客户端");
        app.setApplicationName("校园网客户端");
        app.setApplicationVersion("0.0.1");
        app.setOrganizationName("flyos");
        app.setOrganizationDomain("fly-os.xyz");
        app.setApplicationDescription(DApplication::translate("MainWindow", "FlyOS校园网客户端") + "\n");
        app.setProductIcon(QPixmap(":/images/logo.png"));
        app.setWindowIcon(QIcon(":/images/logo.png"));

        mainwindow window;
        window.show();



        return app.exec();
    }

    return 0;
}