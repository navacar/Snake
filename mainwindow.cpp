#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "food.h"
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QRect>
#include <QRandomGenerator>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(500); // DEFAULT 500

    setFixedSize(375, 375);

    Direction = 1;
    Number2 = 0;
    Klet = QImage(":/ABC/images/j10.gif");
    Rand = randGen.bounded(2);
    Size = 0;

    KletHeight = Klet.height();
    KletWeight = Klet.width();


    SnakeHead = QImage(":/ABC/images/glaza.jpg");
    SnakeBody = QImage(":/ABC/images/black.jpg");


    QPoint Head(SpawnX, SpawnY);
    QPoint Head1(SpawnX, SpawnY - 1);
    QPoint Head2(SpawnX, SpawnY - 2);

    SnakeList.append(Head);
    SnakeList.append(Head1);
    SnakeList.append(Head2);

    Size = SnakeList.count();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (Direction != 2){
        if (event->key() == Qt::Key_Left){
            Direction = 4;
            SnakeHead = QImage(":/ABC/images/glaza3.jpg");
        }
    }
    if (Direction != 4){
        if (event->key() == Qt::Key_Right){
            Direction = 2;
            SnakeHead = QImage(":/ABC/images/glaza1.jpg");
        }
    }
    if (Direction != 3){
        if (event->key() == Qt::Key_Down){
            Direction = 1;
            SnakeHead = QImage(":/ABC/images/glaza.jpg");
        }
    }
    if (Direction != 1){
        if (event->key() == Qt::Key_Up){
            Direction = 3;
            SnakeHead = QImage(":/ABC/images/glaza2.jpg");
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    for(i = 0; i < N; i++ ){
        for ( j = 0; j < N; j++){
            painter.drawImage(i*KletHeight, j*KletWeight, Klet);
        }
    }

    if(!Walls.isEmpty()){

        for(i = 0; i < 20; i++){
            painter.drawImage(QRect(Walls.at(i).x(), Walls.at(i).y(), KletWeight ,KletHeight),  SnakeBody);
        }
    }



    for (i = 0; i < Size; i++){
        if(i == 0)
            painter.drawImage(QRect(SnakeList.at(i).x()*KletHeight, SnakeList.at(i).y()*KletWeight, KletWeight ,KletHeight),  SnakeHead);
        else
            painter.drawImage(QRect(SnakeList.at(i).x()*KletHeight, SnakeList.at(i).y()*KletWeight, KletWeight ,KletHeight),  SnakeBody);
    }
    if (JustAFood != nullptr)
        JustAFood->Draw(&painter);
}

void MainWindow::update()
{

    int XofFood = randGen.bounded(MaxX)*KletHeight;
    int YofFood = randGen.bounded(MaxY)*KletHeight;

    if (JustAFood == nullptr){

        if(!FoodList.isEmpty()){

            for(i = 0; i < 8; i++)
            FoodList.removeLast();
        }

        JustAFood = new Food(XofFood, YofFood, Rand);
        if(JustAFood->FoodCheck()){

            Number = 0;
            SaverForX = XofFood;
            SaverForY = YofFood;

            QPoint FoodBorder1(XofFood - KletHeight, YofFood - KletWeight);
            QPoint FoodBorder2(XofFood - KletHeight, YofFood);
            QPoint FoodBorder3(XofFood, YofFood - KletWeight);
            QPoint FoodBorder4(XofFood - KletHeight, YofFood + KletWeight);
            QPoint FoodBorder5(XofFood + KletHeight, YofFood - KletWeight);
            QPoint FoodBorder6(XofFood + KletHeight, YofFood + KletWeight);
            QPoint FoodBorder7(XofFood + KletHeight, YofFood);
            QPoint FoodBorder8(XofFood, YofFood + KletWeight);

            FoodList.append(FoodBorder1);
            FoodList.append(FoodBorder2);
            FoodList.append(FoodBorder3);
            FoodList.append(FoodBorder4);
            FoodList.append(FoodBorder5);
            FoodList.append(FoodBorder6);
            FoodList.append(FoodBorder7);
            FoodList.append(FoodBorder8);
        }

    }

        QRect rect = contentsRect();
        xBorder = rect.width();
        yBorder = rect.height();

        int XofFirst, YofFirst;
        QPoint NewPoint;

     if(!SnakeList.isEmpty()){

        XofFirst = SnakeList.first().x();
        YofFirst = SnakeList.first().y();

        if(Direction == 1){
            NewPoint.setX(XofFirst);
            NewPoint.setY(YofFirst + 1);
        }
        if(Direction == 3){
            NewPoint.setX(XofFirst);
            NewPoint.setY(YofFirst - 1);
        }
        if(Direction == 2){
            NewPoint.setX(XofFirst + 1);
            NewPoint.setY(YofFirst);
        }
        if(Direction == 4){
            NewPoint.setX(XofFirst - 1);
            NewPoint.setY(YofFirst);
        }

        SnakeList.prepend(NewPoint);
        SnakeList.removeLast();
        Size = SnakeList.count();

        XofFirst = NewPoint.x();
        YofFirst = NewPoint.y();

    }

     if(XofFirst < 0 | YofFirst < 0 | XofFirst*KletWeight >= 375 | YofFirst*KletHeight >= 375 |SnakeList.isEmpty() == true){
        QMessageBox::information(this, "ABC", "Game Over!");
        QApplication::exit();
    }

    if(JustAFood->FoodCheck()){

            for(i = 0; i < 8; i++){

                if(FoodList.at(i).x() == SnakeList.first().x()*KletHeight && FoodList.at(i).y() == SnakeList.first().y()*KletWeight ){
                    Number++;
                }

            if(Number >= 8){

                Number = 0;
                Number2++;
                if (Number2 >= 3){
                    delete JustAFood;
                    JustAFood = nullptr;
                    Rand = 0;
                    JustAFood = new Food(SaverForX, SaverForY, Rand);
                    Number2 = 0;

                    if(!FoodList.isEmpty()){

                        for(i = 0; i < 8; i++)
                        FoodList.removeLast();

                    }
                }
            }
        }
    }

    for (i = 1; i < Size; i++){

        if(SnakeList.at(i).x() == XofFirst && SnakeList.at(i).y() == YofFirst){
            QMessageBox::information(this, "ABC", "Game Over!");
            QApplication::exit();
        }
    }

    if(JustAFood->getX() == XofFirst*KletHeight && JustAFood->getY() == YofFirst*KletWeight){

        if(JustAFood->FoodCheck() == false){

            if(Direction == 1){
                NewPoint.setX(XofFirst);
                NewPoint.setY(YofFirst + 1);
            }
            if(Direction == 3){
                NewPoint.setX(XofFirst);
                NewPoint.setY(YofFirst - 1);
            }
            if(Direction == 2){
                NewPoint.setX(XofFirst + 1);
                NewPoint.setY(YofFirst);
            }
            if(Direction == 4){
                NewPoint.setX(XofFirst - 1);
                NewPoint.setY(YofFirst);
            }

            SnakeList.prepend(NewPoint);
            Size = SnakeList.count();
        }else{
            SnakeList.removeFirst();
            Size = SnakeList.count();
        }
        delete JustAFood;
        JustAFood = nullptr;
        Rand = randGen.bounded(2);
    }


    for(i = 0; i < 20; i++){

        int XofWall = randGen.bounded(MaxX)*KletHeight;
        int YofWall = randGen.bounded(MaxY)*KletHeight;
        QPoint NewWall(XofWall, YofWall);
        Walls.append(NewWall);
        qDebug("%d, %d", Walls.at(i).x(), Walls.at(i).y());
    }

    for(i = 0; i < 20; i++){

        if(Walls.at(i).x() == SnakeList.first().x()*KletHeight && SnakeList.first().y()*KletWeight == Walls.at(i).y()){
            QMessageBox::information(this, "ABC", "Game Over!");
            QApplication::exit();
        }

    }
    repaint();
}
