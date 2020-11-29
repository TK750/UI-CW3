//
// Created by twak on 11/11/2019.
//

//Got rid of the timer because it was trash

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
    vector<TheButtonInfo>* infos;
    vector<TheButton*>* buttons;
    long updateCount = 0;// do I need this?

public:
    ThePlayer() : QMediaPlayer(NULL) { //Constructor
        setVolume(0);
        connect (this, SIGNAL (stateChanged(QMediaPlayer::State)), this, SLOT (playStateChanged(QMediaPlayer::State)) );

        mTimer = new QTimer(NULL);
        //changed the timer so that each button could have its own video
        mTimer->setInterval(50000); // 1000ms is one second between ...
        mTimer->start();
        connect( mTimer, SIGNAL (timeout()), SLOT ( shuffle() ) ); // ...running shuffle method
    }

    // all buttons have been setup, store pointers here
    void setContent(vector<TheButton*>* b, vector<TheButtonInfo>* i);// links each button to the file to play?

private slots:

    void playStateChanged (QMediaPlayer::State ms);//changes player state??

public slots:

    // start playing this ButtonInfo?
    void jumpTo (TheButtonInfo* button);
};

#endif //CW2_THE_PLAYER_H

