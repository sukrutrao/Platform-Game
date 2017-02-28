#ifndef GEM_H
#define GEM_H

#include<QGraphicsScene>
#include<QGraphicsPixmapItem>
#include<QDebug>

// A class for the graphics of the game objects
// Used as virtual functions
// And deriving QGraphicsPixmapItem for image of object

class Gem : public QGraphicsPixmapItem
{
private:
    bool isOnScreen;
    int pointValue;
public:
    virtual void drawGem(QGraphicsScene*) {}    
    int getPointValue();
    bool getIsOnScreen();
    void setIsOnScreen(bool);
    void setPointValue(int);
    void remove(QGraphicsScene*);
};

#endif // GEM_H
