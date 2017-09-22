//
// Created by linux on 17-9-22.
//

#ifndef FLYOS_CAMPUS_NETWORK_PLUGINSINTERFACE_H
#define FLYOS_CAMPUS_NETWORK_PLUGINSINTERFACE_H

#include <QtCore/QObject>

class PluginsInterface {
public:
    virtual QString pluginsName()=0;

    virtual QPixmap pluginsLogo()=0;

    virtual QWidget *pluginsWidget()=0;

};

Q_DECLARE_INTERFACE(PluginsInterface, "com.flyos.campus.network/1.0")

#endif //FLYOS_CAMPUS_NETWORK_PLUGINSINTERFACE_H
