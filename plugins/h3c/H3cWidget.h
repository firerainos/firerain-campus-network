//
// Created by linux on 17-9-13.
//

#ifndef FLYOS_CAMPUS_NETWORK_H3CWIDGET_H
#define FLYOS_CAMPUS_NETWORK_H3CWIDGET_H


#include <QtWidgets/QFrame>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>

class H3cWidget : public QFrame{
    Q_OBJECT
public:
    H3cWidget(QWidget *parent = nullptr);

private:
    QLineEdit *usernameEdit;
    QLineEdit *passwdEdit;
    QLineEdit *versionEdit;

    QComboBox *deviceBox;
    QComboBox *langBox;

    QPushButton *startButton;

    void initUI();

};


#endif //FLYOS_CAMPUS_NETWORK_H3CWIDGET_H
