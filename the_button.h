//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_BUTTON_H
#define CW2_THE_BUTTON_H


#include <QPushButton>
#include <QUrl>


class TheButtonInfo {//button info class

public:
    QUrl* url; // video file to play
    QIcon* icon; // icon to display

    TheButtonInfo ( QUrl* url, QIcon* icon) : url (url), icon (icon) {}
};


class TheButton : public QPushButton {//push button class

    Q_OBJECT

public:
    TheButtonInfo* info;

     TheButton(QWidget *parent) :  QPushButton(parent) {
         setIconSize(QSize(200,110));
         connect(this, SIGNAL(released()), this, SLOT (clicked() )); // if QPushButton clicked...then run clicked() below
    }

    void init(TheButtonInfo* i);

private slots:
    void clicked();

signals:
    void jumpTo(TheButtonInfo*);

};


#endif //CW2_THE_BUTTON_H


/* widgets are objects, instances of classes
 * can be automatic allocation foo f;
 * or dynamic allocation foo* f = new foo();
 * normal to use dynamic allocation and manipulate using pointers
 *
 * containers hold pointers to widgets inside them, when parent is deleted,
 * walks through and deletes each child, when parent is enabled/disabled so are children
 *
 * parent - child relationships can be established during widget creation
 * QLabel* label = new QLabel(parentWidget);
 * or when a widget is added to a container via addWidget method
 * QLabel* label = new QLabel ();
 * label -> setParent(parentWidget);
 * -> is an operator that calls a method on a pointer to an object*/
