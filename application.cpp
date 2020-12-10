#include "application.h"

//first iteration:
//column of buttons has been moved to the right of the video player
//location/description of the video has been added at the bottom of the player - not functional yet
//combo box to choose the location for videos - not functional

//second iteration
//play/pause button and video's timeline has been added
//the description of the videos has been changed to an individual description for each video
//forward/backward 10 seconds button has been added
//the main layout has been changed to a grid layout
//the locations combo box has been fixed and it is now working, even though the videos are added at random - see switchLocation at the bottom of this file
//IMPROVEMENTS: -change the text of the buttons to icons
//              -add some styling
//              -create more functions to adhere to the 50 lines rule
//ISSUES: -videos are allocated at random when a combo box element is clicked
//        -when you click once on a video it opens the new layout and it is responsive, but if you go back and click on another video, it messes up the layout


Application::Application(vector<TheButtonInfo> videos) : videos(videos){
    //windows' properties
    setWindowTitle("Tomeo");
    setMinimumSize(800, 720);

    //functions used to create the application tomeo
    createWidgets();
    createLayout();

}

void Application::createWidgets(){
    //filter box elements
    elementsFilterBy<<"Filter by"<<"Country"<<"City"<<"Date";
    filterBox->setCurrentIndex(1);
    filterBox->addItems(elementsFilterBy);

    player->setVideoOutput(videoWidget);
    videoWidget->hide();

    descriptions<<"Description";

//    connect(locationsList, SIGNAL(activated(int)), this, SLOT(switchLocation(int)));

    // a list of the buttons
    vector<TheButton*> buttons;
    // the buttons are arranged in a grid layout
    buttonWidget->setLayout(layout);

    int n=0;
    int j=0;
    int doubleDigits=1;
    int increase=0;
    //create x buttons (for x no of videos)
    for ( unsigned i = 0; i < videos.size(); i++ ) {
        //this conditions will create the rows and columns of the grid layout
        if(i % 2 == 0){
            n++;
        }
        if(i % 2 != 0){
            j = 0;
        }
        else{
            j = 1;
        }

        //creating a container layout inside the grid layout that contains the description and the video
        QLabel *description = new QLabel();
        if(i<9){
            description->setText(descriptions[0] + ' ' + (i + '0' + 1));
        }
        else{
            //doubleDigits is set to 1 and it remains constant representing the first number
            //increase represents the second digit and it increases after each loop
            description->setText(descriptions[0] + ' ' + (doubleDigits + '0') + ('0' + increase));
            increase++;
        }
        QFrame *container = new QFrame;
        container->setLayout(new QVBoxLayout);
        //creating the thumbnails for the videos
        TheButton *button = new TheButton(buttonWidget);
        button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo* ))); // when clicked, tell the player to play.
        connect(button, SIGNAL(clicked()), this, SLOT(fullScreen()));
        button->setMaximumHeight(600);
        buttons.push_back(button);
        description->setFixedHeight(30);
        description->setStyleSheet("font-size: 20px;height: 40px;width: 120px;");
        //adding the thumnails and the buttons to the container layout
        container->layout()->addWidget(button);
        container->layout()->addWidget(description);
        layout->addWidget(container, n, j);
        button->init(&videos.at(i));

    }

    // tell the player what buttons and videos are available
    player->setContent(&buttons, & videos);

    label->setAlignment(Qt::AlignLeft);
    label->hide();

    fullScreenButton->hide();
    fullScreenButton->setBackgroundRole(QPalette::Light);
    connect(fullScreenButton, SIGNAL(clicked()), this, SLOT(fullScreen()));

    //buttons will hide as default such that they are only present when the video is played
    // play/pause button
    playPauseButton->hide();
    playAndPause();
    connect(playPauseButton, SIGNAL(clicked()), this, SLOT(playAndPause()));

    //video timeline
    //shows the progress of the video and also we can choose what minute to play
    slider = new QSlider(Qt::Horizontal, this);
    slider->hide();
    connect(player, &QMediaPlayer::durationChanged, slider, &QSlider::setMaximum);
    connect(player, &QMediaPlayer::positionChanged, slider, &QSlider::setValue);
    connect(slider, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);

    //forward 10 seconds button
    forward->hide();
    forward->setIcon(QIcon(":/fast-forward.svg"));
    connect(forward, SIGNAL(clicked()), this, SLOT(seekForward()));

    //go backwards 10 seconds button
    backward->hide();
    backward->setIcon(QIcon(":/rewind.svg"));
    connect(backward, SIGNAL(clicked()), this, SLOT(seekBackward()));

    //previous video - still working out
    previous->hide();
    previous->setIcon(QIcon(":/back.svg"));
    connect(previous, SIGNAL(clicked()), this, SLOT(vidPrevious()));

    //next video - still working out
    next->hide();
    next->setIcon(QIcon(":/next.svg"));
    connect(next, SIGNAL(clicked()), this, SLOT(vidNext()));

    //search button
    search->setIcon(QIcon(":/magnifying-glass.svg"));
    search->setFixedHeight(40);
    connect(search, SIGNAL(clicked()), this, SLOT(searchVideo()));
    //set search field height
    searchField->setFixedHeight(40);
    //set filter box height
    filterBox->setFixedHeight(40);

    //volume slider
    volumeSlider->hide();
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(player->volume());
    connect(volumeSlider, &QSlider::valueChanged, player, &QMediaPlayer::setVolume);
    volumeLabel->hide();
    volumeLabel->setPixmap(QPixmap(":/speaker.svg"));
    volumeLabel->setScaledContents(true);


    messageNext->setText("The 'next video' button is not currently working! The purpose of this button is to skip to the next video.");
    messageNext->hide();

    messagePrev->setText("The 'previous video' button is not currently working! The purpose of this button is to go to the previous video in the list");
    messagePrev->hide();

    messageSearch->setText("The 'search' button is not currently working! The purpose of this button is to search for videos that matched the specific filter chosen.");
    messageSearch->hide();

}


void Application::createLayout(){
    //layout for the player's buttons
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(fullScreenButton);
    buttonsLayout->addWidget(previous);
    buttonsLayout->addWidget(backward);
    buttonsLayout->addWidget(playPauseButton);
    buttonsLayout->addWidget(forward);
    buttonsLayout->addWidget(next);
    buttonsLayout->addWidget(volumeLabel);
    buttonsLayout->addWidget(volumeSlider);
    buttonsLayout->addStretch(); //positions the widgets on the left

    //layout for the search bar, search button and filter combo box
    QHBoxLayout* searchLayout = new QHBoxLayout();
    searchLayout->addWidget(filterBox);
    searchLayout->addWidget(searchField);
    searchLayout->addWidget(search);

    QVBoxLayout* descriptionLayout = new QVBoxLayout();
    descriptionLayout->addLayout(searchLayout);
    descriptionLayout->addWidget(buttonWidget);

    top->addWidget(videoWidget);
    //"Location/Description" of the video playing
    top->addWidget(label);
    top->addWidget(slider);
    top->addLayout(descriptionLayout);
    top->addLayout(buttonsLayout);

    setLayout(top);

}


//full screen mode function
void Application::fullScreen() {
  // make videoWidget full screen
  if (isVideoFullScreen) {
    //when the back button is pressed, the video widget is given the size of 0 such that it disappears off the screen
    videoWidget->hide();
    buttonWidget->show();
    isVideoFullScreen=false;
    filterBox->show();
    searchField->show();
    search->show();
    //player's buttons will dissapear while we are in the video grid
    playAndPause();
    playPauseButton->hide();
    forward->hide();
    backward->hide();
    slider->hide();
    fullScreenButton->hide();
    label->hide();
    volumeLabel->hide();
    volumeSlider->hide();
    previous->hide();
    next->hide();
    player->pause();
  }
  else {
    //Enables fullscreen mode with media buttons
    videoWidget->show();
    buttonWidget->hide();
    //videoWidget->setMinimumHeight(500);
    videoWidget->setMaximumHeight(2000);
    isVideoFullScreen=true;
    fullScreenButton->setIcon(QIcon(":/list.svg"));
    autoPlay();
    playPauseButton->setMaximumWidth(200);
    playPauseButton->show();
    forward->setMaximumWidth(70);
    forward->show();
    backward->setMaximumWidth(70);
    backward->show();
    slider->setMaximumWidth(2000);
    slider->show();
    fullScreenButton->setMaximumWidth(120);
    fullScreenButton->show();
    label->setMaximumWidth(200);
    label->setMaximumHeight(40);
    label->show();
    volumeLabel->setMaximumSize(20,20);
    volumeLabel->show();
    volumeSlider->setMinimumWidth(250);
    volumeSlider->show();
    previous->setMaximumWidth(70);
    previous->show();
    next->setMaximumWidth(70);
    next->show();
    filterBox->hide();
    searchField->hide();
    search->hide();

  }
}

// play/pause button connection
//we change the vlaue of the boolean variable isVideoPlaying
//in order to keep track of the video's status (played/paused)
//issue: if clicking on another video, the button has to be pressed a few times
//before it starts working properly - fixed yayyy - had to call playAndPause in fullScreen function
//also made autoplay to change icon without affecting playback status when button clicked

void Application::autoPlay() {
    playPauseButton->setIcon(QIcon(":/pause.svg"));
    isVideoPlaying = false;
}

void Application::playAndPause() {
  if (isVideoPlaying == false) {
    player->pause();
    playPauseButton->setIcon(QIcon(":/play-button.svg"));
    isVideoPlaying = true;
  }
  else {
    player->play();
    playPauseButton->setIcon(QIcon(":/pause.svg"));
    isVideoPlaying = false;
  }
}

//forward 5 seconds button connection
void Application::seekForward(){
    player->setPosition(round((double)slider->value() * 5 ));
}

//backward 5 seconds button connection
void Application::seekBackward(){
    player->setPosition(round((double)slider->value() / 5));
}


//----Prev/Next - stuck on this ----
// Tried QMediaPlaylist
void Application::vidNext(){
    messageNext->show();
}

void Application::vidPrevious(){
    messagePrev->show();
}
//shows the error message for the search button
void Application::searchVideo(){
    messageSearch->show();
}

//this function makes the connection between the elements of the combo box and the videos
//the videos are not properly distributed, hence the function does not work the proper way yet
//at least it shows that we can group the videos and that the combo box works, when an element is clicked
void Application::switchLocation(int index)//seems like something a little funky going on here
{
    label->setText(locList->itemText(index));
    for ( unsigned i = 0; i < 2; i++ ) {
        //creating the thumbnails for the videos
        TheButton *button = new TheButton(buttonWidget);
        button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo* ))); // when clicked, tell the player to play.
        connect(button, SIGNAL(clicked()), this, SLOT(fullScreen()));
        button->setMaximumHeight(500);
        buttons.push_back(button);
        layout->addWidget(button);
        button->init(&videos.at(0));
    }
}



