//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_BUTTON_H
#define CW2_THE_BUTTON_H


#include <QPushButton>
#include <QUrl>


class TheButtonInfo {

public:
    QUrl* url;
    QIcon* icon;

    TheButtonInfo (QUrl *url, QIcon *icon) : url (url), icon (icon) {}
};


class TheButton : public QPushButton {

    Q_OBJECT

public:
    TheButtonInfo *info;

     TheButton(QWidget *parent) :  QPushButton(parent) {
         setIconSize(QSize(290,110));
         connect(this, SIGNAL(released()), this, SLOT (clicked() ));
    }

    void init(TheButtonInfo *i);


private slots:
    void clicked();
    
signals:
    void jumpTo(TheButtonInfo*);

};


#endif //CW2_THE_BUTTON_H

