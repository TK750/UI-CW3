#include "application.h"


Application::Application(vector<TheButtonInfo> videos) : videos(videos){
    //windows' properties
    setWindowTitle("Tomeo");
    setMinimumSize(800, 720);

    //functions used to create the application tomeo
    createWidgets();
    createThumbnails();
    createLayout();
    createConnections();
}

void Application::createWidgets(){
    //video description
    label->setAlignment(Qt::AlignLeft);
    label->hide();

    //full screen button
    fullScreenButton->hide();
    fullScreenButton->setBackgroundRole(QPalette::Light);

    // play/pause button
    playPauseButton->hide();
    playAndPause();

    //video timeline
    slider = new QSlider(Qt::Horizontal, this);
    slider->hide();

    //forward 10 seconds button
    forward->hide();
    forward->setIcon(QIcon(":/fast-forward.svg"));

    //go backwards 10 seconds button
    backward->hide();
    backward->setIcon(QIcon(":/rewind.svg"));

    //previous video button
    previous->hide();
    previous->setIcon(QIcon(":/back.svg"));

    //next video button
    next->hide();
    next->setIcon(QIcon(":/next.svg"));

    //search button
    search->setIcon(QIcon(":/magnifying-glass.svg"));
    search->setFixedHeight(40);
    searchField->setFixedHeight(40);
    filterBox->setFixedHeight(40);

    //volume slider
    volumeSlider->hide();
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(player->volume());
    volumeLabel->hide();
    volumeLabel->setPixmap(QPixmap(":/speaker.svg"));
    volumeLabel->setScaledContents(true);

    messageNext->setText("The 'next video' button is not currently working! The purpose of this button is to skip to the next video.");
    messageNext->hide();

    messagePrev->setText("The 'previous video' button is not currently working! The purpose of this button is to go to the previous video in the list");
    messagePrev->hide();

    messageSearch->setText("The 'search' button is not currently working! The purpose of this button is to search for videos that matched the specific filter chosen.");
    messageSearch->hide();

    //filter box elements
    elementsFilterBy<<"Filter by"<<"Country"<<"City"<<"Date";
    filterBox->setCurrentIndex(1);
    filterBox->addItems(elementsFilterBy);

    player->setVideoOutput(videoWidget);
    videoWidget->hide();

    descriptions<<"Description";
}

void Application::createThumbnails(){
    // a list of the buttons
    vector<TheButton*> buttons;
    // the buttons are arranged in a grid layout
    buttonWidget->setLayout(layout);
    int n=0, j=0, doubleDigits=1, increase=0;
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
}

//this function creates the connections between the buttons and their functionality
void Application::createConnections(){
    connect(fullScreenButton, SIGNAL(clicked()), this, SLOT(fullScreen()));
    connect(playPauseButton, SIGNAL(clicked()), this, SLOT(playAndPause()));
    connect(player, &QMediaPlayer::durationChanged, slider, &QSlider::setMaximum);
    connect(player, &QMediaPlayer::positionChanged, slider, &QSlider::setValue);
    connect(slider, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);
    connect(forward, SIGNAL(clicked()), this, SLOT(seekForward()));
    connect(backward, SIGNAL(clicked()), this, SLOT(seekBackward()));
    connect(previous, SIGNAL(clicked()), this, SLOT(vidPrevious()));
    connect(next, SIGNAL(clicked()), this, SLOT(vidNext()));
    connect(search, SIGNAL(clicked()), this, SLOT(searchVideo()));
    connect(volumeSlider, &QSlider::valueChanged, player, &QMediaPlayer::setVolume);
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

void Application::autoPlay() {
    playPauseButton->setIcon(QIcon(":/pause.svg"));
    isVideoPlaying = false;
}

// play/pause button connection
//we change the vlaue of the boolean variable isVideoPlaying
//in order to keep track of the video's status (played/paused)
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


//following 3 functions will display error messages when their corresponding button is clicked
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





