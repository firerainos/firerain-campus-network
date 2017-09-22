//
// Created by linux on 17-9-22.
//

#ifndef FLYOS_CAMPUS_NETWORK_H3CPLUGINS_H
#define FLYOS_CAMPUS_NETWORK_H3CPLUGINS_H


#include "../../interfaces/pluginsInterface.h"
#include "H3cWidget.h"

class H3cPlugins : public QObject,public PluginsInterface{

    Q_OBJECT
    Q_INTERFACES(PluginsInterface)
    Q_PLUGIN_METADATA(IID "com.flyos.campus.network/1.0" FILE "h3c.json")

public:
    QString pluginsName() override;

    QPixmap pluginsLogo() override;

    QWidget *pluginsWidget() override;

private:
    H3cWidget *h3cWidget;

};


#endif //FLYOS_CAMPUS_NETWORK_H3CPLUGINS_H
