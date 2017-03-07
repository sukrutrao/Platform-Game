#include <QApplication>
#include <QTimer>
#include <QObject>
#include <QGraphicsView>
#include <QEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QStyle>
#include <QMediaPlayer>
#include <QFileInfo>
#include <QDesktopWidget>
#include "readinput.h"
#include "server.h"
#include "client.h"
#include "gamestate.h"
#include "gameobject.h"
#include "inputhandler.h"
#include "loadingtext.h"
#include "choiceserverclientstart.h"
#include "inputbox.h"
#include "exitbutton.h"

int main(int argc, char *argv[])
{
    int milliseconds_per_frame = 50;
    QApplication a(argc, argv);
    QGraphicsScene *scene = new QGraphicsScene;
    InputHandler *view = new InputHandler(NULL);

    QRect rec = QApplication::desktop()->availableGeometry();
    int screen_height = rec.height() - 2*view->frameWidth() - QApplication::style()->pixelMetric(QStyle::PM_TitleBarHeight);
    int screen_width = screen_height * 1.5;

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(screen_width, screen_height);
    view->setSceneRect(0,0,screen_width, screen_height);
    view->setScene(scene);
    view->show();
    
    Server game_server(3000 , scene , milliseconds_per_frame);
    Client game_client(milliseconds_per_frame , scene , view , screen_width , screen_height);
    ChoiceServerClientStart* startButton = new ChoiceServerClientStart(scene , view , milliseconds_per_frame , screen_width , screen_height ,  &game_client , &game_server);
    startButton->displayStartMenu();


    //qDebug () << "Setting application";
    game_client.setApp(&a);
  //  LoadingText* loading_text = new LoadingText(&game_client , scene , view , 100*(screen_initial_width/240), 60*(screen_initial_height/160));


    return a.exec();
}
