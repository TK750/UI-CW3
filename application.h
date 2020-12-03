#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
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
    ThePlayer *player = new ThePlayer;
    QLabel* label = new QLabel("<h3>Description</h3>");
    QScrollArea* scrollArea = new QScrollArea;
    QComboBox* locList = new QComboBox();
    QPushButton* fullScreenButton = new QPushButton("Full Screen");
    QSlider *volumeSlider = new QSlider(Qt::Horizontal);

private slots:
    void fullScreen();

};

#endif // APPLICATION_H
