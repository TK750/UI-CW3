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

using namespace std;

class Application: public QWidget
{
    Q_OBJECT

public:

    Application(vector<TheButtonInfo> videos);

private:
    void createWidgets();
    void createLayout();
    void autoPlay();

    vector<TheButtonInfo> videos;
    QVideoWidget *videoWidget = new QVideoWidget;
    QWidget *buttonWidget = new QWidget();
    vector<TheButton*> buttons;
    ThePlayer *player = new ThePlayer();
    QLabel* label = new QLabel("<h3>Description</h3>");
    QScrollArea* scrollArea = new QScrollArea;
    QComboBox* locList = new QComboBox();
    QComboBox* locationsList = new QComboBox();
    QPushButton* fullScreenButton = new QPushButton();
    QPushButton* playPauseButton = new QPushButton;
    QSlider *volumeSlider = new QSlider(Qt::Horizontal);
    QLabel *volumeLabel = new QLabel;
    bool isVideoPlaying; //used for the play/pause button to check the status of the video
    bool isVideoFullScreen = false;
    QStringList descriptions;
    QStringList locations;
    QSlider *slider;
    QPushButton* forward = new QPushButton;
    QPushButton* backward = new QPushButton;
    QPushButton* previous = new QPushButton;
    QPushButton* next = new QPushButton;
    QComboBox* filterBox = new QComboBox();
    QStringList elementsFilterBy;
    QLineEdit* searchField = new QLineEdit();
    QPushButton* search = new QPushButton;
    //pop up error messages for the missing functionality
    QMessageBox* messageNext = new QMessageBox();
    QMessageBox* messagePrev = new QMessageBox();
    QMessageBox* messageSearch = new QMessageBox();

    //thumbnails layout
    QGridLayout* layout = new QGridLayout(this);
    QVBoxLayout *top = new QVBoxLayout();


//definitions of the functions used for the player's buttons
//they create the connection between the button and their functionality
private slots:
    void fullScreen();
    void playAndPause();
    void seekForward();
    void seekBackward();
    void switchLocation(int index);
    void vidNext();
    void vidPrevious();
    void searchVideo();


};

#endif // APPLICATION_H
