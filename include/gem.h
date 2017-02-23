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
    int pointValue;
    QGraphicsScene* scene;

public:
    virtual void draw() {}

    int getPointValue();
    void setPointValue(int pointValue);

    QGraphicsScene* getQGraphicsScene();
    void setQGraphicsScene(QGraphicsScene* scene);
    void remove();
};

#endif // GEM_H