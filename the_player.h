//
// Created by twak on 11/11/2019.
//

//Got rid of the timer

#ifndef CW2_THE_PLAYER_H
#define CW2_THE_PLAYER_H


#include <QApplication>
#include <QMediaPlayer>
#include "the_button.h"
#include <vector>
#include <QTimer>


using namespace std;

class ThePlayer : public QMediaPlayer {

    Q_OBJECT

private:
    vector<TheButtonInfo>* infos;
    vector<TheButton*>* buttons;
    long updateCount = 0;// do we need this?

public:
    ThePlayer() : QMediaPlayer(NULL) {
        setVolume(0);
        connect (this, SIGNAL (stateChanged(QMediaPlayer::State)), this, SLOT (playStateChanged(QMediaPlayer::State)) );

        mTimer = new QTimer(NULL);
        //changed the timer so that each button could have its own video
        mTimer->setInterval(50000); // 1000ms is one second between ...
        mTimer->start();
        connect( mTimer, SIGNAL (timeout()), SLOT ( shuffle() ) ); // ...running shuffle method
    }

    // all buttons have been setup, store pointers here
    void setContent(vector<TheButton*>* b, vector<TheButtonInfo>* i);

private slots:

    void playStateChanged (QMediaPlayer::State ms);

public slots:
    
    void jumpTo (TheButtonInfo* button);
};

#endif //CW2_THE_PLAYER_H

