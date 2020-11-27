//
// Created by twak on 11/11/2019.
//

#include "the_button.h"


void TheButton::init(TheButtonInfo* i) {//initialises itself
    setIcon( *(i->icon) );//sets icon via pointer i
    info =  i; //info - filepath?
}


void TheButton::clicked() {
    emit jumpTo(info);
}


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
