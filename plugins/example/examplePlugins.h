//
// Created by linux on 17-9-23.
//

#ifndef FLYOS_CAMPUS_NETWORK_EXAMPLEPLUGINS_H
#define FLYOS_CAMPUS_NETWORK_EXAMPLEPLUGINS_H


#include "../../interfaces/pluginsInterface.h"

class ExamplePlugins : public QObject,public PluginsInterface{

    Q_OBJECT
    Q_INTERFACES(PluginsInterface)
    Q_PLUGIN_METADATA(IID "com.flyos.campus.network/1.0" FILE "example.json")

public:
    QString pluginsName() override;

    QPixmap pluginsLogo() override;

    QWidget *pluginsWidget() override;


};


#endif //FLYOS_CAMPUS_NETWORK_EXAMPLEPLUGINS_H
