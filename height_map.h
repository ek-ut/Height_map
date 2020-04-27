#ifndef HEIGHT_MAP_H
#define HEIGHT_MAP_H

#include <QMainWindow>
#include <clickablelabel.h>

namespace Ui {
class height_map;
}

class height_map : public QMainWindow
{
    Q_OBJECT

public:
    explicit height_map(QWidget *parent = nullptr);
    ~height_map();


private:
    void Init(); //Main form initialization
    //bool eventFilter(QObject *obj, QEvent *event); // QLabel click event tracking
    QColor GetColor(QPoint pPoint);//get pixel color at cursor position
    QColor GetColor(int x, int y);//get pixel color at cursor position
    int CalculationOfHeight(QColor PixelColor); // Calculation of height from color
    void ClickCalculation();//mouse click calculation
    QPixmap CreateNewMap(QPixmap pMap, QPoint pStartPoint);// create a visibility map
    bool ChengePix(QImage* imageMap,QColor newColjr, int startHeight, int x, int y);//changing the color of the pixel if it is below the starting point
    void CheckPixels(QImage* imageMap,QColor newColjr, int startHeight,int startX, int startY); //checking the height relative to the starting point
    Ui::height_map *ui;
    QPixmap piMap; //map image uploaded to the form
    //QPixmap piGlobalScreen;//Global screen image
    QPixmap piVisibilitMmap;//
    ClickableLabel* LabelMap;

private slots:
    void on_LabelMap_clicked();//processing mouse clicks on the map
    void on_pbResetMap_clicked();//return of the map to its original state
};

#endif // HEIGHT_MAP_H
