//
// Created by twak on 11/11/2019.
//

#include "the_player.h"

using namespace std;

// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i) {
    buttons = b;
    infos = i;
    jumpTo(buttons -> at(0) -> info);
}

// change the image and video for one button every one second
void ThePlayer::shuffle() {
    TheButtonInfo* i = & infos -> at (rand() % infos->size() );
//        setMedia(*i->url);
    buttons -> at( updateCount++ % buttons->size() ) -> init( i );
}

void ThePlayer::playStateChanged (QMediaPlayer::State ms) {
    switch (ms) {
        case QMediaPlayer::State::StoppedState:
            play(); // starting playing again...
            break;
    default:
        break;
    }
}

void ThePlayer::jumpTo (TheButtonInfo* button) {
    setMedia( * button -> url);
    play();
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
