//
// Created by linux on 17-9-22.
//

#ifndef FIRERAIN_CAMPUS_NETWORK_PLUGINSINTERFACE_H
#define FIRERAIN_CAMPUS_NETWORK_PLUGINSINTERFACE_H

#include <QtCore/QObject>

class PluginsInterface {
public:
//    插件名字，用于显示在主程序侧边栏的名字
    virtual QString pluginsName()=0;
//    插件logo，用于显示在主程序侧边栏的logo
    virtual QPixmap pluginsLogo()=0;
//    插件主widget。用于显示在主程序上插件对应的GUI
    virtual QWidget *pluginsWidget()=0;
//    程序退出时调用
    virtual void pluginsClose()=0;

};

Q_DECLARE_INTERFACE(PluginsInterface, "com.firerain.campus.network/1.1")

#endif //FIRERAIN_CAMPUS_NETWORK_PLUGINSINTERFACE_H
