#include "food.h"

Food::Food()
{

}

Food::Food(int X, int Y, int Rand)
{
    this -> X = X;
    this -> Y = Y;
    this -> Rand = Rand;

    NeNormEda = QImage(":/ABC/images/red.jpg");
    NormEda = QImage(":/ABC/images/green.jpg");
}

void Food::Draw(QPainter *painter)
{
  if(Rand == 0){
      painter->drawImage(QRect(X, Y, KletHeight , KletWeight), NormEda);
  }else{
      painter->drawImage(QRect(X, Y, KletHeight , KletWeight), NeNormEda);
  }
}

bool Food::FoodCheck()
{
    if(Rand == 0)
        return false;
    else
        return true;
}

int Food::getX()
{
    return X;
}

int Food::getY()
{
    return Y;
}
