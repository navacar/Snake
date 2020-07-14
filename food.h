#ifndef FOOD_H
#define FOOD_H
#include <QPainter>
#include <QImage>
#include <QRandomGenerator>

class Food
{
public:
    Food();
    Food(int X, int Y, int Rand);
    void Draw(QPainter *painter);
    bool FoodCheck();
    int getX();
    int getY();

private:
    int X, Y, Rand;
    QImage NormEda, NeNormEda;
    const int KletHeight = 15, KletWeight = 15;
    QRandomGenerator randGen;
};

#endif // FOOD_H
