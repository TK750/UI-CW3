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
