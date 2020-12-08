#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <string>
#include <vector>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QImageReader>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QtWidgets>
#include <QKeyEvent>
#include <QMouseEvent>
#include "the_button.h"
#include "the_player.h"


class Application: public QWidget
{
    Q_OBJECT

public:

    Application(vector<TheButtonInfo> videos);

private:
    void createWidgets();
    void createLayout();

    vector<TheButtonInfo> videos;
    QVideoWidget *videoWidget = new QVideoWidget;
    QWidget *buttonWidget = new QWidget();
    vector<TheButton*> buttons;
    ThePlayer *player = new ThePlayer();
    QLabel* label = new QLabel("<h3>Description</h3>");
    QScrollArea* scrollArea = new QScrollArea;
    QComboBox* locList = new QComboBox();
    QPushButton* fullScreenButton = new QPushButton("Full Screen");
    QSlider *volumeSlider = new QSlider(Qt::Horizontal);
    QPushButton* playPauseButton = new QPushButton;
    bool isVideoPlaying = false; //used for the play/pause button to check the status of the video
    QStringList descriptionList;
    QSlider *slider;
    QPushButton* forward = new QPushButton;
    QPushButton* backward = new QPushButton;
    QPushButton* previous = new QPushButton;
    QPushButton* next = new QPushButton;
    QMediaPlaylist *playlist = new QMediaPlaylist;


//definitions of the functions used for the player's buttons
//they create the connection between the button and their functionality
private slots:
    void fullScreen();
    void playAndPause();
    void seekForward();
    void seekBackward();
    // void vidNext();
    // void vidPrevious();

};

#endif // APPLICATION_H
