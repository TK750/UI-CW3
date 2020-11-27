//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_PLAYER_H
#define CW2_THE_PLAYER_H


#include <QApplication>
#include <QMediaPlayer>
#include "the_button.h"
#include <vector>
#include <QTimer>


using namespace std;

class ThePlayer : public QMediaPlayer { //ThePlayer class is a subclass of QMediaPlayer (Inheritance) class definition/decleration

    Q_OBJECT //C Macro - used to indicate that a class will define a custom slot

private:
    vector<TheButtonInfo>* infos; // vector of pointers to infos?
    vector<TheButton*>* buttons; // vector of pointers to pointers to buttons??
    long updateCount = 0;// do I need this?

public:
    ThePlayer() : QMediaPlayer(NULL) { //Constructor - called whenever an object of class is created
        setVolume(0); // volume set to 0
        connect (this, SIGNAL (stateChanged(QMediaPlayer::State)), this, SLOT (playStateChanged(QMediaPlayer::State)) );
        //connect - function inherited from QWidget to connect signals to slots
        //(sender of signal, SIGNAL(stateC.. name of signal sent(paramater attached to sent signal)),
        //slot to receive signal, SLOT (parameter attached to receiveing slot
        //this pointer - this object i.e. this ThePlayer object
    }

    // all buttons have been setup, store pointers here
    void setContent(vector<TheButton*>* b, vector<TheButtonInfo>* i);// links each button to the file to play?

private slots:


    void playStateChanged (QMediaPlayer::State ms);//changes player state??

public slots:

    // start playing this ButtonInfo
    void jumpTo (TheButtonInfo* button);
};

#endif //CW2_THE_PLAYER_H


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
