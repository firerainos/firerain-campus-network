//
// Created by linux on 17-9-22.
//

#ifndef FIRERAIN_CAMPUS_NETWORK_H3CPLUGINS_H
#define FIRERAIN_CAMPUS_NETWORK_H3CPLUGINS_H


#include "../../interfaces/pluginsInterface.h"
#include "H3cWidget.h"

class H3cPlugins : public QObject,public PluginsInterface{

    Q_OBJECT
    Q_INTERFACES(PluginsInterface)
    Q_PLUGIN_METADATA(IID "com.firerain.campus.network/1.1" FILE "h3c.json")

public:
    QString pluginsName() override;

    QPixmap pluginsLogo() override;

    QWidget *pluginsWidget() override;

    void pluginsClose() override;

private:
    H3cWidget *h3cWidget;

};


#endif //FIRERAIN_CAMPUS_NETWORK_H3CPLUGINS_H
