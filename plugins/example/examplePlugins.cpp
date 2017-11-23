//
// Created by linux on 17-9-23.
//

#include <QtWidgets/QLabel>
#include "examplePlugins.h"



QString ExamplePlugins::pluginsName() {
    return "Example";
}

QPixmap ExamplePlugins::pluginsLogo() {
    return QPixmap(":/resources/logo.png");
}

QWidget *ExamplePlugins::pluginsWidget() {
    return new QLabel("Example");
}

void ExamplePlugins::pluginsClose() {

}
