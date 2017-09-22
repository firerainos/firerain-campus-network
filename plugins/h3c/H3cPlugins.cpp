//
// Created by linux on 17-9-22.
//

#include "H3cPlugins.h"



QString H3cPlugins::pluginsName() {
    return "华三认证";
}

QPixmap H3cPlugins::pluginsLogo() {
    return QPixmap(":/resources/h3c.ico");
}

QWidget *H3cPlugins::pluginsWidget() {
    if (h3cWidget == nullptr)
        h3cWidget = new H3cWidget;

    return h3cWidget;
}
