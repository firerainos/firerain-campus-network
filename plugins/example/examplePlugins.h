//
// Created by linux on 17-9-23.
//

#ifndef FIRERAIN_CAMPUS_NETWORK_EXAMPLEPLUGINS_H
#define FIRERAIN_CAMPUS_NETWORK_EXAMPLEPLUGINS_H


#include "../../interfaces/pluginsInterface.h"

class ExamplePlugins : public QObject,public PluginsInterface{

    Q_OBJECT
    Q_INTERFACES(PluginsInterface)
    Q_PLUGIN_METADATA(IID "com.firerain.campus.network/1.1" FILE "example.json")

public:
    QString pluginsName() override;

    QPixmap pluginsLogo() override;

    QWidget *pluginsWidget() override;

    void pluginsClose() override;
};


#endif //FIRERAIN_CAMPUS_NETWORK_EXAMPLEPLUGINS_H
