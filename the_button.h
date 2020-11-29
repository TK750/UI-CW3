//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_BUTTON_H
#define CW2_THE_BUTTON_H


#include <QPushButton>
#include <QUrl>


class TheButtonInfo {//button info class

public:
    QUrl* url; // video file to play (pointer)
    QIcon* icon; // icon to display (pointer)

    TheButtonInfo (QUrl *url, QIcon *icon) : url (url), icon (icon) {}//constructor - takes QUrl + QIcon pointers as args
};


class TheButton : public QPushButton {//TheButton class, subclass of QPushButton

    Q_OBJECT //C Macro - used to indicate that a class will define a custom slot

public:
    TheButtonInfo *info;//pointer to button info object/class - what is this for?

     TheButton(QWidget *parent) :  QPushButton(parent) {
         setIconSize(QSize(290,110));
         connect(this, SIGNAL(released()), this, SLOT (clicked() )); // if QPushButton clicked...then run clicked() below
         //connect TheButton, send signal released () to slot in TheButton, run clicked

    }

    void init(TheButtonInfo *i);


private slots:
    void clicked();//run clicked method/function

signals:
    void jumpTo(TheButtonInfo*);//jump to sprite?

};


#endif //CW2_THE_BUTTON_H

