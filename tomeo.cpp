/*
 *
 *    ______
 *   /_  __/___  ____ ___  ___  ____
 *    / / / __ \/ __ `__ \/ _ \/ __ \
 *   / / / /_/ / / / / / /  __/ /_/ /
 *  /_/  \____/_/ /_/ /_/\___/\____/
 *              video for sports enthusiasts...
 *
 *  2811 cw3 : twak
 */

//Yeh, it's hella messy with lots of dumb comments =S

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
#include <QDesktopServices>
#include <QImageReader>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QtWidgets>
#include "the_player.h"
#include "the_button.h"


// read in videos and thumbnails to this directory - don't really wanna mess with this tbh
vector<TheButtonInfo> getInfoIn (string loc) {

    vector<TheButtonInfo> out =  vector<TheButtonInfo>();//vector of the button infos called out
    QDir dir(QString::fromStdString(loc) );//Overall iterates through directory, conversts string to unicode as intermediary process
    QDirIterator it(dir);

    while (it.hasNext()) { // for all files (while there is another file)

        QString f = it.next(); //unicode character string = next item in directory

            if (f.contains(".")) // presumably ignores files with no file extension?

#if defined(_WIN32)//something to do with determining OS and file formats - not exactly sure what
            if (f.contains(".wmv"))  { // windows - if file extension wmv (mac/linux can't play wmv natively)
#else
            if (f.contains(".mp4") || f.contains("MOV"))  { // mac/linux - if file extension mp4 or mov
#endif

            QString thumb = f.left( f .length() - 4) +".png";//potential thumbnail, takes left side of file and .png file extension
            if (QFile(thumb).exists()) { // if a png thumbnail exists
                QImageReader *imageReader = new QImageReader(thumb); // reads image from file
                    QImage sprite = imageReader->read(); // read the thumbnail - variable sprite
                    if (!sprite.isNull()) {//if not sprite is null, why not just if isnull is false? Ahh actually makes sense for else condition
                        QIcon *ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button - new scalable icon object pixelmaps as paint device from sprite to QIcon
                        QUrl *url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url - pretty much this
                        out . push_back(TheButtonInfo( url , ico  ) ); // add to the output list - passes information into vector of button infos(icon and location)
                    }
                    else
                        qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb;//self explanatory - not sprite was not null
            }
            else
                qDebug() << "warning: skipping video because I couldn't find thumbnail " << thumb;// thumbnail doesn't exist
        }
    }

    return out;
}


int main(int argc, char *argv[]) {

    qDebug() << "Qt version: " << QT_VERSION_STR;// check Qt is operational

    QApplication app(argc, argv);// create Qt Application

    vector<TheButtonInfo> videos;// vector of button info classes to store all vids in folder

    if (argc == 2)
        videos = getInfoIn( string(argv[1]) );//calls method to read all the files in specified directory and store videos in vector videos

    if (videos.size() == 0) {// if no vids - creates message box asking if you want to download them

        const int result = QMessageBox::question(
                    NULL,
                    QString("Tomeo"),
                    QString("no videos found! download, unzip, and add command line argument to \"quoted\" file location. Download videos from Tom's OneDrive?"),
                    QMessageBox::Yes |
                    QMessageBox::No );

        switch( result )
        {
        case QMessageBox::Yes://opens link to download necessary vids
          QDesktopServices::openUrl(QUrl("https://leeds365-my.sharepoint.com/:u:/g/personal/scstke_leeds_ac_uk/EcGntcL-K3JOiaZF4T_uaA4BHn6USbq2E55kF_BTfdpPag?e=n1qfuN"));
          break;
        default:
            break;
        }
        exit(-1);
    }


    // the widget that will show the video
    QVideoWidget *videoWidget = new QVideoWidget;

    // the QMediaPlayer which controls the playback
    ThePlayer *player = new ThePlayer;
    player->setVideoOutput(videoWidget);//videoWidget is media object that the player wil play

    // a row of buttons
    QWidget *buttonWidget = new QWidget();//new button widget of type QWidget
    // a list of the buttons
    vector<TheButton*> buttons;//vector of button pointers?
    // the buttons are arranged horizontally
    QHBoxLayout *layout = new QHBoxLayout();//sets the layout as horizontal box
    buttonWidget->setLayout(layout);


    /*---------------Scroll Videos--------------------
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidget(buttonWidget);
    scrollArea->setMinimumWidth(300);
    scrollArea->setBackgroundRole(QPalette::Shadow);

    doing something wrong with this
    ------------------------------------------------*/


    // create x amount of buttons for no of vids
    for ( unsigned i = 0; i < videos.size(); i++ ) {
        TheButton *button = new TheButton(buttonWidget);
        button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo* ))); // when clicked, tell the player to play.
        buttons.push_back(button);
        layout->addWidget(button);
        button->init(&videos.at(i));
    }

    // tell the player what buttons and videos are available
    player->setContent(&buttons, & videos);



    // create the main window and layout
    QWidget window;
    QVBoxLayout *top = new QVBoxLayout();
    window.setLayout(top);
    window.setWindowTitle("tomeo");
    window.setMinimumSize(800, 680);

    // add the video and the buttons to the top level widget
    top->addWidget(videoWidget);
    top->addWidget(buttonWidget);

    // showtime!
    window.show();

    return app.exec();//starts main event loop
}
