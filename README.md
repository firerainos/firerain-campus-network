# flyos-campus-network

校园网客户端

集结各种第三方校园网客户端为不同的插件(c3hclient等)

## Build Dependencies (编译依赖)

* gcc >= 7
* cmake
* qt5-tools

## Dependencies (依赖)

* qt5-base
* qt5-svg
* dtkwidget
* dtkcore

## Installation (安装)

* mkdir build
* cd build
* cmake ..
* make
* sudo make install

## Usage (使用)

* flyos-campus-network 或者 点击启动器上的校园网客户端

## 插件开发

* plugins/example 为示例插件
* interfaces/pluginsInterface.h 为插件接口
* plugins/CMakeLists.txt中添加add_subdirectory(example)即可编译示例插件

## 插件加载目录

* 系统 ${CMAKE_INSTALL_PREFIX}/lib/flyos-campus-network/plugins
* 用户主目录 ~/.conf/flyos/flyos-campus-network/plugins (用于加载第三方插件)

## License

FlyOS campus network is licensed under [GPLv3](LICENSE).
