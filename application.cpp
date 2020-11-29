#include "application.h"

//first iteration:
//column of buttons has been moved to the right of the video player
//location/description of the video has been added at the bottom of the player - not functional yet
//combo box to choose the location for videos - not functional

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
    locList->addItem("Location1");
    locList->addItem("Location2");

    // a row of buttons
    QWidget *buttonWidget = new QWidget();
    // a list of the buttons
    vector<TheButton*> buttons;
    // the buttons are arranged horizontally
    QVBoxLayout *layout = new QVBoxLayout();
    buttonWidget->setLayout(layout);

    //create the 6 buttons (for 6 videos)
    for ( int i = 0; i < 6; i++ ) {
        TheButton *button = new TheButton(buttonWidget);
        button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo* ))); // when clicked, tell the player to play.
        buttons.push_back(button);
        layout->addWidget(button);
        button->init(&videos.at(i));

        //description/location of video
        QVBoxLayout* title = new QVBoxLayout();
        QLabel *description = new QLabel("Small description");
        title->addWidget(button);
        title->addWidget(description);
        layout->addLayout(title);
    }

    // tell the player what buttons and videos are available
    player->setContent(&buttons, & videos);

    scrollArea->setWidget(buttonWidget);
    scrollArea->setMinimumWidth(390);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setBackgroundRole(QPalette::Light);

    label->setAlignment(Qt::AlignLeft);

    fullScreenButton->setFixedSize(140,40);
    fullScreenButton->setBackgroundRole(QPalette::Light);
    connect(fullScreenButton, SIGNAL(clicked()), this, SLOT(fullScreen()));


}

void Application::createLayout(){

    QVBoxLayout *top = new QVBoxLayout();

    // top right centre (push buttons)
    QHBoxLayout* centreRight = new QHBoxLayout();
    centreRight->addWidget(fullScreenButton);

    // top right - layout for the combo box and scroll area
    QVBoxLayout* topRight = new QVBoxLayout();
    topRight->addWidget(locList);
    topRight->addWidget(scrollArea);

    // top left - layout containg the video player
    QVBoxLayout* topLeft = new QVBoxLayout();
    topLeft->addWidget(videoWidget);

    // top line
    QHBoxLayout* videoTopLine = new QHBoxLayout();
    videoTopLine->addLayout(topLeft);
    videoTopLine->addLayout(topRight);

    //layout for buttons
    QVBoxLayout* buttonsLayout = new QVBoxLayout();
    buttonsLayout->addWidget(fullScreenButton);
    //"Location/Description" of the video playing
    buttonsLayout->addWidget(label);

    top->addLayout(videoTopLine);
    top->addLayout(buttonsLayout);

    setLayout(top);

}

//full screen mode function
void Application::fullScreen() {
  // make videoWidget full screen
  if (isFullScreen()) {
    showNormal();
    fullScreenButton->setText("Full screen");
  }
  else {
    showFullScreen();
    fullScreenButton->setText("Back");
  }
}


