#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPaintEvent>
#include <QImage>
#include <QRandomGenerator>
#include <QList>
#include <QPoint>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Food;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

public slots:
   void update();

private:
    Ui::MainWindow *ui;
    QImage Klet, SnakeHead, SnakeBody;
    int KletWeight, KletHeight, i, j, Size, Rand, Direction, xBorder, yBorder, Number, SaverForX, SaverForY, Number2;
    const int N = 25, SpawnX = 5, SpawnY = 5, MaxX = 25, MaxY = 25;
    QList<QPoint> FoodList, Walls, SnakeList;




    Food * JustAFood;

    QRandomGenerator randGen;
};
#endif // MAINWINDOW_H
