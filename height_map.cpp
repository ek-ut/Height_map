#include "height_map.h"
#include "ui_height_map.h"

height_map::height_map(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::height_map)
{
    ui->setupUi(this);
    Init();
}

height_map::~height_map()
{
    delete ui;
}
void  height_map::Init()
{
    LabelMap = new ClickableLabel("",this);
    ui->horizontalLayout_6->addWidget(LabelMap,1);
    piMap = QPixmap(":/images/Iraq_mountains.png");//loading map from resource file
    LabelMap->setPixmap(piMap);
    connect(LabelMap, SIGNAL(clicked()), this, SLOT(on_LabelMap_clicked()));
}
void height_map::on_LabelMap_clicked()
{
    ClickCalculation();
}


void height_map::ClickCalculation()
{

    piVisibilitMmap = piMap;
    QPoint p;// = QCursor::pos(); //gets the global cursor position
    p = LabelMap->GetMousePoint();
    QColor pixelColor = GetColor(p);
    ui->lEX->setText(QString("%1").arg(p.x()*5)+ "m");
    ui->lEY->setText(QString("%1").arg(p.y()*5)+ "m");
    ui->lER->setText(QString("%1").arg(pixelColor.red()));

    ui->lEB->setText(QString("%1").arg(pixelColor.blue()));

    ui->lEG->setText(QString("%1").arg(pixelColor.green()));
    ui->lEHeight->setText( QString("%1").arg(CalculationOfHeight(pixelColor))+ "m");

    LabelMap->setPixmap(CreateNewMap(piMap, p));

}



QColor height_map::GetColor(QPoint pPoint)
{
    QImage ImageMap = piMap.toImage();

    return ImageMap.pixelColor(pPoint);
}

QColor height_map::GetColor(int x, int y)
{
    QImage ImageMap = piMap.toImage();

    return ImageMap.pixelColor(x, y);
}

int height_map::CalculationOfHeight(QColor PixelColor)
{
    int NumberColor = qMin(PixelColor.red(), PixelColor.blue());
    NumberColor = qMin(NumberColor, PixelColor.green());
    return NumberColor*2;
}

QPixmap height_map::CreateNewMap(QPixmap pMap, QPoint pStartPoint)
{
    QPixmap newMap = pMap;
    QImage imageMap = newMap.toImage();
    QColor newColjr = QColor(255,0,0,255);
    int height = CalculationOfHeight(GetColor(pStartPoint)) + 2;

    CheckPixels(&imageMap,newColjr,height,pStartPoint.x(), pStartPoint.y());



    newMap = QPixmap::fromImage(imageMap);

    return newMap;
}

bool height_map::ChengePix(QImage* imageMap,QColor newColjr, int startHeight, int x, int y)
{
    int countHeight = CalculationOfHeight(GetColor(x, y));
    if(startHeight >= countHeight)
    {
        imageMap->setPixelColor(x, y, newColjr);
        return  true;
    }
    return false;
}

void height_map::CheckPixels(QImage* imageMap,QColor newColjr, int startHeight, int startX, int startY)
{
    /*
     * checks visibility depending on height. quarterly on the map
     */
    int stopX = 0;
    int stopY = 0;
    for(int x = startX; x >= stopX; x--)
    {
        for(int y = startY; y >= stopY; y--)
        {
            if(!ChengePix(imageMap, newColjr, startHeight, x, y))//if at a given point the height exceeds the height observed, then visibility stops at a given point
            {
                stopY = y;
            }
        }
    }

    stopX = 0;
    stopY = 1024;
    for(int x = startX; x >= stopX; x--)
    {
        for(int y = startY; y <= stopY; y++)
        {
            if(!ChengePix(imageMap, newColjr, startHeight, x, y))//if at a given point the height exceeds the height observed, then visibility stops at a given point
            {
                stopY = y;
            }
        }
    }

    stopX = 1024;
    stopY = 0;
    for(int x = startX; x <= stopX; x++)
    {
        for(int y = startY; y >= stopY; y--)
        {
            if(!ChengePix(imageMap, newColjr, startHeight, x, y))//if at a given point the height exceeds the height observed, then visibility stops at a given point
            {
                stopY = y;
            }
        }
    }
    stopX = 1024;
    stopY = 1024;
    for(int x = startX; x <= stopX; x++)
    {
        for(int y = startY; y <= stopY; y++)
        {
            if(!ChengePix(imageMap, newColjr, startHeight, x, y))//if at a given point the height exceeds the height observed, then visibility stops at a given point
            {
                stopY = y;
            }
        }
    }


}

void height_map::on_pbResetMap_clicked()
{
    LabelMap->setPixmap(piMap);
}
