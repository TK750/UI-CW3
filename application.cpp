#include "application.h"

//first iteration:
//column of buttons has been moved to the right of the video player
//location/description of the video has been added at the bottom of the player - not functional yet
//combo box to choose the location for videos - not functional

//second iteration
//play/pause button and video's timeline has been added
//the description of the videos has been changed to an individual description for each video
//forward/backward 10 seconds button has been added
//IMPROVEMENTS: -change the text of the buttons to icons
//              -create more functions to adhere to the 50 lines rule

Application::Application(vector<TheButtonInfo> videos) : videos(videos){
    //windows' properties
    setWindowTitle("tomeo");
    setMinimumSize(800, 680);
    setMaximumWidth(2000);
    setMaximumHeight(2000);

    //functions used to create the application tomeo
    createWidgets();
    createLayout();

}

void Application::createWidgets(){

    player->setVideoOutput(videoWidget);

    //list of possible locations of where the videos where taken
    //this helps organinzing the videos making them more accessbile
    locList->addItem("Location1");
    locList->addItem("Location2");

    //more descriptions will be added to the list after getting the locations' combo boc working
    descriptionList<<"Description"<<"Description2";

    // a row of buttons
    QWidget *buttonWidget = new QWidget();
    // a list of the buttons
    vector<TheButton*> buttons;
    // the buttons are arranged vertically
    QVBoxLayout *layout = new QVBoxLayout();
    buttonWidget->setLayout(layout);

    //create x buttons (for x no of videos)
    for ( unsigned i = 0; i < videos.size(); i++ ) {
        TheButton *button = new TheButton(buttonWidget);
        button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo* ))); // when clicked, tell the player to play.
        buttons.push_back(button);
        layout->addWidget(button);
        button->init(&videos.at(i));

        //description/location of video
        QVBoxLayout* title = new QVBoxLayout();
        QLabel *description = new QLabel();
        //picks the first location and numbers the videos from 1 to x (x being the no of videos available),
        //in order to give each video an individual description
        description->setText(descriptionList[0] + ' ' + (i + '0' + 1));
        title->addWidget(button);
        title->addWidget(description);
        layout->addLayout(title);

    }

    // tell the player what buttons and videos are available
    player->setContent(&buttons, &videos);

    scrollArea->setWidget(buttonWidget);
    scrollArea->setMinimumWidth(390);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setBackgroundRole(QPalette::Light);

    label->setAlignment(Qt::AlignLeft);

    fullScreenButton->setFixedSize(140,30);
    fullScreenButton->setBackgroundRole(QPalette::Light);
    connect(fullScreenButton, SIGNAL(clicked()), this, SLOT(fullScreen()));

    // play/pause button
    playPauseButton->setFixedSize(100, 30);
    playPauseButton->setText("Pause");
    connect(playPauseButton, SIGNAL(clicked()), this, SLOT(playAndPause()));

    //video timeline
    //shows the progress of the video and also we can choose what minute to play
    slider = new QSlider(Qt::Horizontal, this);
    connect(player, &QMediaPlayer::durationChanged, slider, &QSlider::setMaximum);
    connect(player, &QMediaPlayer::positionChanged, slider, &QSlider::setValue);
    connect(slider, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);

    //forward 10 seconds button
    forward->setFixedSize(70,30);
    forward->setText("+10s");
    connect(forward, SIGNAL(clicked()), this, SLOT(seekForward()));

    //go backwards 10 seconds button
    backward->setFixedSize(70,30);
    backward->setText("-10s");
    connect(backward, SIGNAL(clicked()), this, SLOT(seekBackward()));

    previous->setFixedSize(70,30);
    previous->setText("Prev");
    connect(previous, SIGNAL(clicked()), this, SLOT(vidPrevious()));

    next->setFixedSize(70,30);
    next->setText("Next");
    connect(next, SIGNAL(clicked()), this, SLOT(vidNext()));

    //volume slider
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(player->volume());
    connect(volumeSlider, &QSlider::valueChanged, player, &QMediaPlayer::setVolume);

}

void Application::createLayout(){

    QVBoxLayout *top = new QVBoxLayout();

    // top right - layout for the combo box and scroll area
    QVBoxLayout* topRight = new QVBoxLayout();
    topRight->addWidget(locList);
    topRight->addWidget(scrollArea);

    // first line of the layout, containg the video player
    QHBoxLayout* videoTopLine = new QHBoxLayout();
    videoTopLine->addWidget(videoWidget);
    videoTopLine->addLayout(topRight);

    //layout for the player's buttons
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(fullScreenButton);
    buttonsLayout->addWidget(playPauseButton);
    buttonsLayout->addWidget(previous);
    buttonsLayout->addWidget(backward);
    buttonsLayout->addWidget(forward);
    buttonsLayout->addWidget(next);
    buttonsLayout->addWidget(volumeSlider);
    buttonsLayout->addStretch(); //positions the widgets on the left

    QVBoxLayout* descriptionLayout = new QVBoxLayout();
    //"Location/Description" of the video playing
    descriptionLayout->addWidget(label);
    descriptionLayout->addWidget(slider);

    top->addLayout(videoTopLine);
    top->addLayout(descriptionLayout);
    top->addLayout(buttonsLayout);

    setLayout(top);

}

//full screen mode function - still can't get it to return from fullscreen
void Application::fullScreen() {
  // make videoWidget full screen
  if (isFullScreen()) {
    videoWidget->QVideoWidget::setFullScreen(0);
    fullScreenButton->setText("Full screen");
  }
  //or if the widget is already in full screen mode, it makes it go back to normal
  else {
    videoWidget->QVideoWidget::setFullScreen(1);
    fullScreenButton->setText("Back");
  }
}

// play/pause button connection
//we change the vlaue of the boolean variable isVideoPlaying
//in order to keep track of the video's status (played/paused)
//issue: if clicking on another video, the button has to be pressed a few times
//before it starts working properly
void Application::playAndPause() {
  if (isVideoPlaying == false) {
    player->pause();
    playPauseButton->setText("Play");
    isVideoPlaying = true;
  }
  else {
    player->play();
    playPauseButton->setText("Pause");
    isVideoPlaying = false;
  }
}

//forward 10 seconds button connection
void Application::seekForward(){
    player->setPosition(round((double)slider->value() * 10 ));
}

//backward 10 seconds button connection
void Application::seekBackward(){
    player->setPosition(round((double)slider->value() / 10));
}

//----Prev/Next - stuck on this ----
// Tried QMediaPlaylist

/*
void Application::vidNext(){

    player->
}

void Application::vidPrevious(){
    player->setContent(b, i))
}
*/
