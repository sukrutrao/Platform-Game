#include "gamestate.h"
#include <QObject>
#include <thread>

GameState::GameState(std::vector<GameObject*> &game_objects, std::vector< std::vector<Tile*> > &tile_map, std::vector<Gem*> &input_gems , int screen_width , int screen_height , QGraphicsScene* scene_local, int milliseconds_per_frame, int total_time_available) :
    gameObjects(game_objects), tileMap(tile_map), gems(input_gems) ,
    screenWidth(screen_width) , screenHeight(screen_height) ,
    scene(scene_local), threadPool(4)
{
    isGameRunning = true;
    timer = new Timer(total_time_available,milliseconds_per_frame);
    timer->updateTimerOnScreen();
    timer->setFont(QFont("Helvetica" , 55));
    timer->setDefaultTextColor(QColor(51, 51, 255));
    timer->setPos(50 , 50);
    scene->addItem(timer);
}

QGraphicsScene * GameState::getScene()
{
    return scene;
}

bool GameState::isGameActive()
{
    return isGameRunning;
}

std::vector<GameObject*> GameState::getGameObjects()
{
    return gameObjects;
}

std::vector<std::vector<Tile*> > GameState::getTileMap()
{
    return tileMap;
}

std::vector<Gem*> GameState::getGems()
{
    return gems;
}

void GameState::update()
{
    bool someone_accepting_input = false;
    if(remoteIdentity == enumerator::Identity::SERVER)
    {
        threadPool.assignToThread([&]() { timer->update(); });
   //     timer->update();
    }
    else
    {
        timer->updateTimerOnScreen();
    }
    if(!timer->isTimeLeft() || timer->getTimeLeftInMilliSeconds() == 0)
    {
        return;
    }

    if(remoteIdentity == enumerator::Identity::SERVER)
    {
        someone_accepting_input = false;
        if(!isGameRunning)
        {
            return;
        }
    }
    for(unsigned int i = 0; i < gameObjects.size(); i++)
    {
        if(remoteIdentity == enumerator::Identity::SERVER)
        {
      //      qDebug() << "assigning to thread" ;
            threadPool.assignToThread([&,i]() {
        //           qDebug() << "updating server";
               if(gameObjects[i]->isAcceptingInput() && !(gameObjects[i]->getIsDead()))
               {
                   someone_accepting_input = true;
                   (gameObjects[i]->physicsComponent)->update(*gameObjects[i]);
               }
               else
               {
                   (gameObjects[i]->inputComponent)->update(*gameObjects[i]);
                   (gameObjects[i]->physicsComponent)->update(*gameObjects[i]);
               }
              });
        }
        else if(remoteIdentity == enumerator::Identity::CLIENT)
        {
            (gameObjects[i]->graphicsComponent)->update(*gameObjects[i]);
            if(gameObjects[i]->scoreComponent)
            {
                    (gameObjects[i]->scoreComponent)->update(gameObjects[i]->getScore());
            }
        }
    }
    if(remoteIdentity == enumerator::Identity::SERVER)
    {
        threadPool.waitTillAllComplete();
        for(unsigned int i = 0; i < gameObjects.size(); i++)
        {
            gameObjects[i]->updatePos();
        }
    }

    if(remoteIdentity == enumerator::Identity::CLIENT)
    {
        for(unsigned int i = 0; i < gems.size(); i++)
        {
            if( (!((gems[i])->getIsOnScreen())) && (!(gems[i])->getRemovedFromScreen()))
            {
                qDebug() << "Deleting Gem";
                (gems[i])->setRemovedFromScreen(true);
                scene->removeItem(gems[i]);
            }
        }
    }
    if(remoteIdentity == enumerator::Identity::SERVER)
    {
        if(!someone_accepting_input)
            isGameRunning = false;
    }
}




