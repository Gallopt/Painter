#include "Painter.h"
#include "ui_Painter.h"

#include "Shape.h"
#include "Outline.h"
#include "Beeline.h"
#include "Rectangle.h"
#include "Ellipse.h"

#include <QDebug>
#include <QFileDialog>
#include <QToolBar>
#include <QPen>
#include <QDebug>
#include <math.h>
#include <stdlib.h>
#include <QColorDialog>
#include <QPainterPath>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QByteArray>
#include <QBuffer>
#include <QXmlStreamWriter>
#include <QLabel>
#include <QToolButton>
#include <QRandomGenerator>
#include <QMovie>


Painter::Painter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Painter)
{
    ui->setupUi(this);
    setFixedSize(1000,800);

    //    setMouseTracking(true);

    pix.fill(QColor(Qt::white));
    //    pix.transformed();


    //工具栏
    QToolBar *toolBar =addToolBar("toolBar");
    toolBar->setMovable(false);
    toolBar->setIconSize(QSize(16,16));

    //保存为图片
    QAction *saveBtn = new QAction(this);
    saveBtn->setText("Save");
    toolBar->addAction(saveBtn);
    //保存为xml文件
    QAction *saveXml = new QAction(this);
    saveXml->setText("SaveXml");
    toolBar->addAction(saveXml);
    //打开xml文件
    QAction *loadXmlBtn = new QAction(this);
    loadXmlBtn->setText("OpenXml");
    toolBar->addAction(loadXmlBtn);
    //放大画笔
    QAction *maxPenBtn = new QAction(this);
    maxPenBtn->setText("+");
    toolBar->addAction(maxPenBtn);
    //缩小画笔
    QAction *miniPenBtn = new QAction(this);
    miniPenBtn->setText("-");
    toolBar->addAction(miniPenBtn);
    //鼠标
    QAction *mouseBtn = new QAction(this);
    mouseBtn->setText("Mouse");
    toolBar->addAction(mouseBtn);
    //橡皮擦
    QAction *eraserBtn = new QAction(this);
    eraserBtn->setText("Eraser");
    toolBar->addAction(eraserBtn);
    //颜色按钮
    QAction *colorBtn = new QAction(this);
    colorBtn->setText("Color");
    toolBar->addAction(colorBtn);
    //油漆桶
    QAction *brushBtn = new QAction(this);
    brushBtn->setText("Brush");
    toolBar->addAction(brushBtn);
    //    QAction *fillBtn = new QAction(this);
    //    fillBtn->setText("Fill");
    //    toolBar->addAction(fillBtn);
    QAction *fill4Btn = new QAction(this);
    fill4Btn->setText("Fill4");
    toolBar->addAction(fill4Btn);
    //Pattern
    QAction *patternBtn = new QAction(this);
    patternBtn->setText("Pattern");
    toolBar->addAction(patternBtn);
    //贴图
    QAction *pictureBtn = new QAction(this);
    pictureBtn->setText("DrawPicture");
    toolBar->addAction(pictureBtn);
    //直线
    QAction *lineBtn = new QAction(this);
    lineBtn->setText("Line");
    toolBar->addAction(lineBtn);
    //矩形
    QAction *rectBtn = new QAction(this);
    rectBtn->setText("Rectangle");
    toolBar->addAction(rectBtn);
    //椭圆
    QAction *ellipseBtn = new QAction(this);
    ellipseBtn->setText("Ellipse");
    toolBar->addAction(ellipseBtn);
    //删除形状
    QAction *deleteBtn = new QAction(this);
    deleteBtn->setText("Delete");
    toolBar->addAction(deleteBtn);//选中当前形状，删除存储的点，最后更新画布
    //清空
    QAction *clearBtn = new QAction(this);
    clearBtn->setText("Clear");
    toolBar->addAction(clearBtn);

    QToolButton *white = new QToolButton(this);
    white->setGeometry(10,770,40,30);
    //    white->setText("White");
    white->setAutoRaise(true);
    white->setStyleSheet("background:white");
    QAction *whiteBtn = new QAction(this);
    whiteBtn->setText("White");
    white->setDefaultAction(whiteBtn);


    QToolButton *black = new QToolButton(this);
    black->setGeometry(70,770,40,30);
    //    black->setText("Black");
    black->setAutoRaise(true);
    black->setStyleSheet("background:black;color:white");
    QAction *blackBtn = new QAction(this);
    blackBtn->setText("Black");
    black->setDefaultAction(blackBtn);

    QToolButton *red = new QToolButton(this);
    red->setGeometry(130,770,40,30);
    //    red->setText("Red");
    red->setAutoRaise(true);
    red->setStyleSheet("background:red;color:white");
    QAction *redBtn = new QAction(this);
    redBtn->setText("Red");
    red->setDefaultAction(redBtn);

    QToolButton *blue = new QToolButton(this);
    blue->setGeometry(190,770,40,30);
    //    blue->setText("Blue");
    blue->setAutoRaise(true);
    blue->setStyleSheet("background:blue;color:white");
    QAction *blueBtn = new QAction(this);
    blueBtn->setText("Blue");
    blue->setDefaultAction(blueBtn);

    QToolButton *magenta = new QToolButton(this);
    magenta->setGeometry(250,770,40,30);
    //    purple->setText("Magenta");
    magenta->setAutoRaise(true);
    magenta->setStyleSheet("background:magenta;color:white");
    QAction *magentaBtn = new QAction(this);
    magentaBtn->setText("Magenta");
    magenta->setDefaultAction(magentaBtn);

    QToolButton *green = new QToolButton(this);
    green->setGeometry(310,770,40,30);
    //    green->setText("Green");
    green->setAutoRaise(true);
    green->setStyleSheet("background:green;color:white");
    QAction *greenBtn = new QAction(this);
    greenBtn->setText("Green");
    green->setDefaultAction(greenBtn);

    QToolButton *cyan = new QToolButton(this);
    cyan->setGeometry(370,770,40,30);
    //    cyan->setText("Cyan");
    cyan->setAutoRaise(true);
    cyan->setStyleSheet("background:cyan");
    QAction *cyanBtn = new QAction(this);
    cyanBtn->setText("Cyan");
    cyan->setDefaultAction(cyanBtn);

    QToolButton *yellow = new QToolButton(this);
    yellow->setGeometry(430,770,40,30);
    //    yellow->setText("Yellow");
    yellow->setAutoRaise(true);
    yellow->setStyleSheet("background:yellow");
    QAction *yellowBtn = new QAction(this);
    yellowBtn->setText("Yellow");
    yellow->setDefaultAction(yellowBtn);

    QToolButton *randomColor = new QToolButton(this);
    randomColor->setGeometry(490,770,40,30);
    //    randomColor->setText("RColor");(10,770,40,30);
    randomColor->setAutoRaise(true);
    QAction *randomColorBtn = new QAction(this);
    randomColorBtn->setText("Radom");
    randomColor->setDefaultAction(randomColorBtn);

    QToolButton *presentColor = new QToolButton(this);
    presentColor->setGeometry(960,770,40,30);
    //    randomColor->setText("RColor");(10,770,40,30);
    randomColor->setAutoRaise(true);
    QAction *presentColorBtn = new QAction(this);
    presentColor->setDefaultAction(presentColorBtn);

    //点击事件
    connect(saveBtn , &QAction::triggered,[=](){
        clickRect = false;
        clickLine = false;
        clickEllipse = false;
        lines.clear();
        rects.clear();
        QString picture = QString("PNG (*.PNG);;BMP (*.bmp);;JPEG (*.jpg *.jpeg);;Text files (*.txt);;XML files (*.xml)");
        QString fileName = QFileDialog::getSaveFileName(this,"Save Picture","",picture);//QFileDialog::getSaveFileName(this, "Save_Picture",path,picture);
        if(!fileName.isNull())
            pix.save(fileName);//保存模板图片，部分》》pix
    });
    connect(saveXml , &QAction::triggered,[=](){//保存为Xml文件
        saveXML();
    });
    connect(loadXmlBtn , &QAction::triggered,[=](){//打开Xml文件
        loadXML();
    });
    connect(maxPenBtn , &QAction::triggered,[=](){
        clickRect = false;
        clickLine = false;
        clickEllipse = false;
        drawType = UseMouse;
        lines.clear();
        rects.clear();
        penWidth++;
        //        update();
    });
    connect(miniPenBtn , &QAction::triggered,[=](){
        clickRect = false;
        clickLine = false;
        clickEllipse = false;
        drawType = UseMouse;
        lines.clear();
        rects.clear();
        penWidth--;
        //        update();

    });
    connect(mouseBtn , &QAction::triggered,[=](){
        clickRect = false;
        clickLine = false;
        clickEllipse = false;
        ellipses.clear();
        lines.clear();
        rects.clear();
        update();
        drawType = UseMouse;


    });
    connect(eraserBtn , &QAction::triggered,[=](){
        clickRect = false;
        clickLine = false;
        clickEllipse = false;
        //        drawType = UseEraser;
        ellipses.clear();
        lines.clear();
        rects.clear();
        drawType = UseEraser;
        update();
    });
    connect(colorBtn , &QAction::triggered,[=](){
        clickRect = false;
        clickLine = false;
        clickEllipse = false;
        _color = QColorDialog::getColor(Qt::red, this,"Select Color",QColorDialog::ShowAlphaChannel);
        drawType = SelectColor;
        //        update();
    });
    connect(pictureBtn, &QAction::triggered,[=](){
        drawPicture();
    });

    connect(fill4Btn, &QAction::triggered,[=](){
        clickRect = false;
        clickLine = false;
        clickEllipse = false;
        drawType = FillPolygon;
        _color = QColorDialog::getColor(Qt::red, this,"Select Color",QColorDialog::ShowAlphaChannel);
        fill();
    });
    connect(randomColorBtn, &QAction::triggered,[=](){
        clickRect = false;
        clickLine = false;
        clickEllipse = false;//red blue cyan magenta yellow green  QColor( 4 - 18);
        int i = QRandomGenerator::global()->bounded(4,18);//随机
        _color=QColor(Qt::GlobalColor(i));
        qDebug() << "RandomColor:" <<_color;
        qDebug() << "QRandomGenerator::global()->bounded(4,18):" <<i;
        drawType = SelectColor;
        //update();
    });
    connect(blackBtn , &QAction::triggered,[=](){
        clickRect = false;
        clickLine = false;
        clickEllipse = false;
        _color = QColor(Qt::black);
        qDebug() << "Color:" <<_color;
        drawType = SelectColor;
        //        update();
    });
    connect(redBtn , &QAction::triggered,[=](){
        clickRect = false;
        clickLine = false;
        clickEllipse = false;
        _color = QColor(Qt::red);
        qDebug() << "Color:" <<_color;
        drawType = SelectColor;
        update();
    });
    connect(blueBtn , &QAction::triggered,[=](){
        clickRect = false;
        clickLine = false;
        clickEllipse = false;
        _color = QColor(Qt::blue);
        qDebug() << "Color:" <<_color;
        drawType = SelectColor;
        //        update();
    });
    connect(magentaBtn , &QAction::triggered,[=](){
        clickRect = false;
        clickLine = false;
        clickEllipse = false;
        _color = QColor(Qt::magenta);
        qDebug() << "Color:" <<_color;
        drawType = SelectColor;
        //        update();
    });
    connect(cyanBtn , &QAction::triggered,[=](){
        clickRect = false;
        clickLine = false;
        clickEllipse = false;
        _color = QColor(Qt::cyan);
        qDebug() << "Color:" <<_color;
        drawType = SelectColor;
        //        update();
    });
    connect(yellowBtn , &QAction::triggered,[=](){
        clickRect = false;
        clickLine = false;
        clickEllipse = false;
        _color = QColor(Qt::yellow);
        qDebug() <<"Color" << _color;
        qDebug() <<"SelectColor" << drawType;
        drawType = SelectColor;
        //        update();
    });
    connect(whiteBtn , &QAction::triggered,[=](){
        clickRect = false;
        clickLine = false;
        clickEllipse = false;
        _color = QColor(Qt::white);
        drawType = SelectColor;
        //        update();
    });
    connect(greenBtn , &QAction::triggered,[=](){
        clickRect = false;
        clickLine = false;
        clickEllipse = false;
        _color = QColor(Qt::green);
        drawType = SelectColor;
        //        update();
    });
    connect(brushBtn , &QAction::triggered,[=](){
        clickRect = false;
        clickLine = false;
        clickEllipse = false;
        drawType =  UseBrush;
        update();
    });
    connect(patternBtn , &QAction::triggered,[=](){
        clickRect = false;
        clickLine = false;
        clickEllipse = false;
        drawType = UsePattern;
        update();
    });

    connect(lineBtn , &QAction::triggered,[=](){
        clickRect = false;
        clickEllipse = false;
        lines.clear();
        rects.clear();
        clickLine = true;
        drawType = UseLine;
        update();
    });
    connect(rectBtn , &QAction::triggered,[=](){
        clickLine = false;
        clickEllipse = false;
        ellipses.clear();
        lines.clear();
        rects.clear();
        clickRect = true;
        drawType = UseRect;
        update();
    });
    connect(ellipseBtn , &QAction::triggered,[=](){
        clickRect = false;
        clickLine = false;
        ellipses.clear();
        lines.clear();
        rects.clear();
        clickEllipse = true;
        drawType = UseEllipse;
        update();
    });
    connect(deleteBtn , &QAction::triggered,[=](){
        perDeletee = true;
        ellipses.clear();
        lines.clear();
        rects.clear();
    });
    connect(clearBtn , &QAction::triggered,[=](){
        //        startPoint = QPoint(-1,-1);
        //        movePoint = QPoint(-1,-1);
        cPoints.clear();
        clickRect = false;
        clickLine = false;
        clickEllipse = false;
        perPoint.clear();
        perLine.clear();
        perRect.clear();
        perEllipse.clear();
        ellipses.clear();
        lines.clear();
        rects.clear();
        myPaintPath = myPainterPaths.first();
        myPainterPaths.clear();
        myPainterPaths.append(myPaintPath);
        myPaintPath.clear();
        qDebug() <<"isDrawing:"<<isDrawing;
        drawType = Clear;
        update();//点击Clear立即更新画布，实时清空画布
        qDebug() <<"isdrawType:"<<drawType;
    });

    QPen bGroundPen;
    bGroundPen.setColor(Qt::white);
    myPaintPath.addRect(QRect(QPoint(0,22),QPoint(1000,749)));//两张布，底布为白色，顶布为透明色
    //    p.setPen(bGroundPen);
    //        p.drawPath(myPaintPath);
    myPainterPaths.append(myPaintPath);
    allPainterPath.addPath(myPaintPath);
    myPaintPath.clear();/**/

}

//void Painter::ColorChanged()
//{
//    emit
//}
Painter::~Painter()
{
    delete ui;
}

void Painter::paintPath(){
    switch (drawType) {
    case UseMouse:
        if(perPoint.size())
        {

            //        for (int i = 0; i<perPoint.size(); i++) {
            QPoint sPoint;
            sPoint = QPoint(perPoint.last().first());
            myPaintPath.moveTo(sPoint);
            for (int i = 0; i < perPoint.last().size(); i++) {
                myPaintPath.lineTo(perPoint.last()[i]);
            }
            myPainterPaths.append(myPaintPath);
            allPainterPath.addPath(myPaintPath);//->
            myPaintPath.clear();
            //        }
        }
        break;
    case UseLine:
        if(perLine.size())
        {
            //        for (int i = 0; i < perLine.size(); i++) {
            QPoint lSPoint = perLine.last().p1();
            QPoint lEPoint = perLine.last().p1();
            myPaintPath.moveTo(lSPoint);
            myPaintPath.lineTo(lEPoint);
            myPainterPaths.append(myPaintPath);
            allPainterPath.addPath(myPaintPath);
            myPaintPath.clear();
            //        }
        }
        break;
    case UseRect:
        if(perRect.size())
        {
            //        for (int i = 0; i < perRect.size(); i++) {
            myPaintPath.addRect(perRect.last());
            myPainterPaths.append(myPaintPath);
            allPainterPath.addPath(myPaintPath);
            myPaintPath.clear();
            //        }
        }
        break;
    case UseEllipse:
        if(perEllipse.size())
        {
            //        for (int i = 0; i < perEllipse.size(); i++) {
            myPaintPath.addEllipse(perEllipse.last());
            myPainterPaths.append(myPaintPath);
            allPainterPath.addPath(myPaintPath);
            myPaintPath.clear();
            //        }
        }
        break;

    }

}

void Painter::paintEvent(QPaintEvent *)
{
    tmpPixmap = QPixmap (pix );

    QPainter paint (&pix );
    QPainter p (this );
    QPainter tmpPaint (&tmpPixmap );//临时画布

//    paint.setRenderHints(QPainter::Antialiasing, true);//消锯齿
//    tmpPaint.setRenderHints(QPainter::Antialiasing, true);//消锯齿
//    p.setRenderHints(QPainter::Antialiasing, true);//消锯齿

    p.drawPixmap(0,0,pix );

    QPen pen;                                      //Qt::BrushStyle
    pen.setWidth(penWidth);
    pen.setColor(_color);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    tmpPaint.setPen(pen);

    if(isDrawing)//先画到临时画布上，鼠标动一次画一次，释放鼠标时再画到最终界面上
        switch (drawType) {
        case UseMouse://曲线直接画到最终界面
        {//movePoint 不会重置，会记录上一次的位置
            paint.setPen(pen);
            paint.drawLine(moveStartPoint,movePoint);
            moveStartPoint = movePoint;
            QImage image;
            image = pix.toImage();
            QPoint point = (moveStartPoint);
            QColor rgb = image.pixel(QPoint(point));

            qDebug()<<"PixPointColor:"<<rgb;
        }
            break;
        case UseEraser:
            myPainterPaths.clear();
            myPaintPath.clear();
            pen.setWidth(30);
            pen.setColor(QColor(Qt::white));
            paint.setPen(pen);
            p.setPen(pen);
            paint.drawLine(moveStartPoint,movePoint);

            moveStartPoint = movePoint;
            break;
        case DrawPicture:
        {
            QPixmap pixmap;
            pixmap.load(":/tree.png");

            QPixmap gif;
            gif.load(":/sun.gif");

            gif.scaled(0.5*gif.size());//放在QLabel动，使用Qmovie
            //            QLabel
            //            QMovie *movie = new QMovie("animations/fire.gif");
            //            movie->start();
            int x,y;
            QPoint point;
            point = startPoint;
            x=point.x()-30;
            y=point.y()-48;
            if(dis(movePoint,point)>10)
            {
                point = movePoint;
                x=point.x()-30;
                y=point.y()-48;
            }
            QRect rect(x,y,pixmap.width(),pixmap.height());
            paint.drawPixmap(rect,pixmap);
            //            QRect rect(x,y,gif.width(),gif.height());
            //            paint.drawPixmap(rect,gif);
        }
            break;
        case UseBrush:
        {
            QPoint p1,p2;//正向的p1在左下
            int xdis = movePoint.x() - moveStartPoint.x();
            p1 = QPoint(movePoint.x()-xdis,movePoint.y());
            p2 = QPoint(moveStartPoint.x()+xdis,moveStartPoint.y());

            QPoint p3,p4;
            p3 = moveStartPoint;
            p4 = movePoint;
            if(dis(p3,p4) >= 100)
            {
                p3 = p4;
            }

            QPoint point1,point2;

            point1 = QPoint((moveStartPoint.x()+movePoint.x()+movePoint.y()-movePoint.y())/2,
                            (moveStartPoint.y()+movePoint.y()+ moveStartPoint.x()-movePoint.x())/2);

            point2 = QPoint((moveStartPoint.x()+movePoint.x()+moveStartPoint.y()-movePoint.y())/2,
                            (moveStartPoint.x()+movePoint.y()+movePoint.x()-moveStartPoint.x())/2);

            QLinearGradient linearGradient;//垂直点
            linearGradient.setColorAt(0.2,Qt::green);
            linearGradient.setColorAt(0.4,Qt::cyan);
            linearGradient.setColorAt(0.6,Qt::blue);
            linearGradient.setColorAt(0.8,Qt::red);
            linearGradient.setColorAt(1.0,Qt::yellow);

            linearGradient.setStart(point1);//横向渐变
            linearGradient.setFinalStop(point2);
            qDebug()<<"moveStartPoint"<<moveStartPoint;
            qDebug()<<"movePoint"<<movePoint;
            qDebug()<<"point1"<<point1;
            qDebug()<<"point2"<<point2;

            //
            QRadialGradient radialGradient;
            radialGradient.setColorAt(0.2,Qt::green);
            radialGradient.setColorAt(0.4,Qt::cyan);
            radialGradient.setColorAt(0.6,Qt::blue);
            radialGradient.setColorAt(0.8,Qt::red);
            radialGradient.setColorAt(1.0,Qt::yellow);
            radialGradient.setCenter(moveStartPoint);
            radialGradient.setRadius(100);
            radialGradient.setFocalPoint(movePoint);
            //
            QConicalGradient conicalGradient;
            conicalGradient.setColorAt(0.2,Qt::green);
            conicalGradient.setColorAt(0.4,Qt::cyan);
            conicalGradient.setColorAt(0.6,Qt::blue);
            conicalGradient.setColorAt(0.8,Qt::red);
            conicalGradient.setColorAt(1.0,Qt::yellow);
            conicalGradient.setCenter(moveStartPoint);
            conicalGradient.setAngle(90);

            //pen.setColor(QColor(hsla(0.5,0.5,1,1)));
            //int i = movePoint.x();
            //if(!movePoint.isNull())
            //{
            //    int i = 0;
            //    i+=20;
            //    multiColor = QColor((i+50)%256,(i+150)%256,(i+225)%256);
            //}
            //int i = QRandomGenerator::global()->bounded(4,18);//随机
            //multiColor=QColor(Qt::GlobalColor(i));

            //pen.setColor(multiColor);
//            pen.setWidth(20);
            //pen.setCapStyle(Qt::FlatCap);
            pen.setCapStyle(Qt::RoundCap);
            pen.setJoinStyle(Qt::BevelJoin);

            pen.setBrush(QBrush(linearGradient));
            //pen.setBrush(QBrush(radialGradient));
            //pen.setBrush(QBrush(conicalGradient));
            //pen.setBrush(QColor(multiColor));
            //pen.setBrush(QColor(Qt::blue));
            paint.setPen(pen);

            paint.drawLine(moveStartPoint,movePoint);
            moveStartPoint = movePoint;
            //QPen peen;
            //peen.setColor(QColor(Qt::red));
            //peen.setWidth(10);
            //paint.setPen(peen);
            //paint.drawLine(QPoint(moveStartPoint.x()-9,moveStartPoint.y()-9),QPoint(movePoint.x()-9,movePoint.y()-9));
            //moveStartPoint = movePoint;
        }
            break;
        case FillPolygon:
        {
            QImage image;
            image = pix.toImage();
            //            allPainterPath.setFillRule(Qt::WindingFill);
            allPainterPath.setFillRule(Qt::OddEvenFill);

            qDebug()<<"_color:"<<_color;
            QPainterPathStroker stroker;
            stroker.setCapStyle(Qt::RoundCap);
            stroker.setWidth(penWidth);     // 生成一个新路径（可填充区域），表示原始路径 path 的轮廓
            QPainterPath outlinePath = stroker.createStroke(myPainterPaths[element]);
            //                }
            qDebug()<<"Element"<<element;
            QPen pen;
//            pen.setWidthF(0.5);
            pen.setColor(_color);
//            pen.setCapStyle(Qt::RoundCap);
            paint.setPen(pen);
            QColor oldColor = image.pixelColor(startPoint);
            //QPoint seedPoint = startPoint;
            QPoint ppoint = startPoint;
            uchar *line;
            line = image.scanLine(ppoint.x());
            if(drawRange.contains(ppoint) && oldColor != _color)//画上点的颜色与要填充的颜色不同
            {
                //                paint.drawPoint(point);
                if(image.pixelColor(startPoint) == _color)
                    return;

                QStack<QPoint> *stack = new QStack<QPoint>;
                stack->push(ppoint);//种子点
                while (!stack->isEmpty())
                {//第一次循环，种子点出栈，该行涂色
                    QPoint point = stack->pop();
                    qDebug()<<"oldColor"<<QColor(oldColor);
                    qDebug()<<"PopPoint"<<point;
                    qDebug()<<"PopPointColor:"<<image.pixelColor(point);
                    int R, L, UpL, DownL,UpR, DownR;
                    L = R =point.x();
                    qDebug()<<"L"<<L;
                    qDebug()<<"R"<<R;
                    while( R < 1000 && image.pixelColor(QPoint(R,point.y())) == oldColor)
                    {
                        R++;
                    }
                    while( L > 0 && image.pixelColor(QPoint(L-1,point.y())) == oldColor)
                    {
                        L--;
                    }
//                    for (int i = L; i < R; i++) {//抗锯齿,画点
//                        paint.drawPoint(QPoint(i,point.y()));
//                    }
                    paint.drawLine(QPoint(L,point.y()),QPoint(R,point.y()));//填充当前扫描线
                    paint.drawLine(QPoint(L,point.y()),QPoint(R,point.y()));

                    image = pix.toImage();

                    UpL = DownL = L;
                    UpR = DownR = R;
                    qDebug()<<"L"<<L;
                    qDebug()<<"R"<<R;

                    //upL->R
                    while((image.pixelColor(QPoint(UpL,point.y()-1)) != oldColor) && (UpL < R))
                    {
                        ++UpL;
                    }
                    qDebug()<<"UpL"<<UpL;
                    QColor color;
                    color = QColor(image.pixelColor(QPoint(UpL,point.y()-1)));
                    qDebug()<<"imageColor"<<color;
                    qDebug()<<"oldColor"<<QColor(oldColor);
                    qDebug()<<"isimageColor"<<(image.pixelColor(QPoint(UpL,point.y()-1)) == oldColor);
                    if(image.pixelColor(QPoint(UpL,point.y()-1)) == oldColor
                            && drawRange.contains(QPoint(UpL,point.y()-1)))
                    {
                            stack->push(QPoint(UpL,point.y()-1));
                    }

                    //upR->L
                    while((image.pixelColor(QPoint(UpR,point.y()-1)) != oldColor) && (UpR > L))
                    {
                        --UpR;
                    }
                    qDebug()<<"UpR"<<UpR;
                    qDebug()<<"imageColor"<<QColor(image.pixelColor(QPoint(UpR,point.y()-1)));
                    qDebug()<<"oldColor"<<QColor(oldColor);
                    qDebug()<<"isimageColor"<<(image.pixelColor(QPoint(UpR,point.y()-1)) == oldColor);

                    if(image.pixelColor(QPoint(UpR,point.y()-1)) == oldColor
                            && drawRange.contains(QPoint(UpR,point.y()-1)))
                    {

                        stack->push(QPoint(UpR,point.y()-1));
                    }

                    //downL->R
                    while ((image.pixelColor(QPoint(DownL,point.y()+1)) != oldColor) && (DownL != R ))
                    {
                        DownL++;
                    }

                    qDebug()<<"DownL"<<DownL;
                    qDebug()<<"imageColor"<<image.pixelColor(QPoint(DownL,point.y()+1));
                    if(image.pixelColor(QPoint(DownL,point.y()+1)) == oldColor
                            && drawRange.contains(QPoint(DownL,point.y()-1)))
                    {
                        stack->push(QPoint(DownL,point.y()+1));
                    }
                    //downR->L
                    while ((image.pixelColor(QPoint(DownR,point.y()+1)) != oldColor) && (DownR != L ))
                    {
                        DownR--;
                    }
                    qDebug()<<"DownR"<<DownR;
                    if(image.pixelColor(QPoint(DownR,point.y()+1)) == oldColor
                            && drawRange.contains(QPoint(DownR,point.y()-1)))
                    {
                        stack->push(QPoint(DownR,point.y()+1));
                    }
                }
                delete stack;
                qDebug()<<"cPoints.size："<<cPoints.size();
            }

        }
            break;

        case UsePattern:
        {
            QPixmap pixmap;
            pixmap.load(":/tree.png");
            QBrush brushh;
            brushh.setTexture(QPixmap(pixmap));
            pen.setWidth(pixmap.width());
            pen.setBrush(brushh);
            paint.setPen(pen);
            paint.drawLine(moveStartPoint,movePoint);
            moveStartPoint = movePoint;
        }
            break;
        case SelectColor:
            qDebug() <<"SelectColor:"<<SelectColor;
            qDebug() <<"Color:"<<_color;
            pen.setColor(_color);
            paint.setPen(pen);
            p.setPen(pen);
            paint.drawLine(moveStartPoint,movePoint);
            moveStartPoint = movePoint;
            break;
        case UseLine:
        {
            if(lines.isEmpty())
                return;
            if(clickLine)
            {
                if(selectWhichLine)//编辑选中的线段,选中了可以删除它，涂白然后重新刷新画布
                {
                    if(isMoveLine)
                    {
                        QPen pen;
                        pen.setWidth (penWidth+1);
                        pen.setColor(QColor(Qt::white));
                        paint.setPen(pen);
                        paint.drawLine(clearWhichLine);
                        tmpPaint.drawLine(lines.last());
                        qDebug () << "clearWhichLine:" <<clearWhichLine;
                    }
                    if(isChangeLine)
                    {
                        qDebug () << "重新画直线段"<< perLine[whichLine];
                        QPen pen;
                        pen.setWidth (penWidth+1);
                        pen.setColor(QColor(Qt::white));
                        paint.setPen(pen);
                        paint.drawLine(clearWhichLine);
                        tmpPaint.drawLine(lines.last());
                        qDebug () << "clearWhichLine:" <<clearWhichLine;
                    }
                }
                else
                    tmpPaint.drawLine(lines.last());
                p.drawPixmap(0,0,tmpPixmap);

            }
        }
            break;
        case UseRect:
            if(rects.isEmpty())
                return;
            if(clickRect)
            {
                if(selectWhichRect)
                {
                    if(isChangeRect)
                    {
                        qDebug() <<"重新画矩形:" <<perRect[whichRect];
                        pen.setWidth (penWidth+1);
                        pen.setColor(QColor(Qt::white));
                        paint.setPen(pen);
                        paint.drawRect(clearWhichRect);
                        tmpPaint.drawRect(rects.last());
                        qDebug () << "clearWhichRect:" <<clearWhichRect;
                    }
                    else if(isMoveRect)
                    {
                        qDebug() <<"移动矩形:" <<perRect[whichRect];
                        QPen pen;
                        pen.setWidth(penWidth+1);
                        pen.setColor(QColor(Qt::white));
                        paint.setPen(pen);
                        paint.drawRect(clearWhichRect);
                        tmpPaint.drawRect(rects.last());
                        qDebug () << "clearWhichRect:" <<clearWhichRect;
                    }
                }
                else
                    tmpPaint.drawRect(rects.last());
                p.drawPixmap(0,0,tmpPixmap);
            }
            //            tmpPaint.drawRoundedRect(rects.last(),25,25);
            //            tmpPaint.drawQuadBezier;
            //            tmpPaint.drawPie(rects.last(),10,20);
            break;
        case UseEllipse:
            if(ellipses.isEmpty())
                return;
            if(clickEllipse)
            {
                if(selWhichElpse)
                {
                    if(isMoveEllipse)
                    {
                        qDebug() <<"移动椭圆" <<perEllipse[whichEllipse];
                        QPen pen;
                        pen.setWidth(penWidth + 1);
                        pen.setColor(QColor(Qt::white));
                        paint.setPen(pen);
                        paint.drawEllipse(clWhichElpse);
                        tmpPaint.drawEllipse(ellipses.last());
                        qDebug () << "ClearWhichEllipse:" <<clWhichElpse;
                    }
                }
                else
                    tmpPaint.drawEllipse(ellipses.last());
                p.drawPixmap(0,0,tmpPixmap);
            }
            break;
        case Clear:
            break;
        }
    /*case UseArc://画弧形
         * tmpPaint.drawArc(rect,startAngle,spanAngle);  //后面两个参数分别为 起始角与跨度角
         * p.drawPixmap(0,0,tmpPixmap);
            break;*/
    else
    {
        switch (drawType) {
        case DrawPicture:
            break;
        case FillPolygon:
            break;
        case UseMouse:
        {
            //qDebug() <<"movePoint:" <<movePoint; //这个会经常显示
            paint.setPen(pen);
            paint.drawLine(moveStartPoint,movePoint);
            moveStartPoint = movePoint;
        }
            break;
        case UseEraser:
            pen.setWidth(20);
            pen.setColor(QColor(Qt::white));
            paint.setPen(pen);
            p.setPen(pen);
            paint.drawLine(moveStartPoint,movePoint);
            moveStartPoint = movePoint;
            break;
        case UseBrush:
            break;
        case UsePattern:
        {
            QPixmap pixmap;
            pixmap.load(":/tree.png");
            QBrush brushh;
            brushh.setTexture(QPixmap(pixmap));
            pen.setWidth(pixmap.width());
            pen.setBrush(brushh);
            paint.setPen(pen);
            paint.drawLine(moveStartPoint,movePoint);
            moveStartPoint = movePoint;
        }
            break;
        case SelectColor:
            qDebug() <<"SelectColor:"<<SelectColor;
            qDebug() <<"Color:"<<_color;
            pen.setColor(_color);
            p.setPen(pen);
            paint.setPen(pen);
            paint.drawLine(moveStartPoint,movePoint);
            moveStartPoint = movePoint;
            break;
        case UseLine:
        {
            qDebug() <<"点击直线"<<clickLine;
            if(clickLine)
            {
                qDebug () << "selectWhichLine:" <<selectWhichLine;
                if(selectWhichLine)//编辑选中的那条线段
                {
                    qDebug () << "MoveLine:StartclearWhichLine:" <<clearWhichLine;
                    qDebug () << "MoveLine:perLine[whichLine]:" <<whichLine;
                    qDebug () << "MoveLine:isMoveLine:" <<isMoveLine;
                    qDebug () << "MoveLine:isChangeLine:" <<isChangeLine;
                    if(isMoveLine)
                    {
                        QPen pen;//最终用白色笔画的那条选中的线段
                        pen.setWidth (penWidth+1);
                        pen.setColor(QColor(Qt::white));
                        paint.setPen(pen);
                        paint.drawLine(clearWhichLine);//选中的那条线,画白线
                        //                        clearWhichLine = lines.last();//将要移动的线段
                        qDebug () << "MoveLine:clearWhichLine:" <<clearWhichLine;
                        isMoveLine = false;
                    }
                    if(isChangeLine)
                    {
                        QPen pen;
                        pen.setWidth (penWidth+1);
                        pen.setColor(QColor(Qt::white));
                        paint.setPen(pen);
                        paint.drawLine(clearWhichLine);
                        qDebug () << "ChangeLine:clearWhichLine:" <<clearWhichLine;
                        //                        perLine.remove(whichLine);//把画白色的线段删掉，不存储白色线
                        isChangeLine = false;
                    }

                    pen.setCapStyle(Qt::RoundCap);
                    paint.setPen(pen);
                    qDebug() << "Paint.drawLine(lines.last()):" <<lines.last();
                    paint.drawLine(lines.last());
                    p.drawPixmap(0,0,pix);

                    //myPaintPath
                    selectWhichLine = false;
                    whichLine = -1;
                }
                else
                {
                    if(lines.isEmpty())
                        return;
                    //                    perLine.append(lines.last());//把最终画好的线段存储到容器中
                    if(lines.size())
                    {
                        QPen pen;
                        pen.setWidth(penWidth);
                        pen.setColor(_color);
                        pen.setCapStyle(Qt::RoundCap);
                        paint.setPen(pen);
                        paint.drawLine(lines.last());
                        p.drawPixmap(0,0,pix);
                        qDebug () << "最终画的线perlines.lastPoints:" <<perLine.last();
                        qDebug() << "PerLine.size:"<<perLine.size();
                    }
                }
                selectWhichLine = false;

                QImage image = pix.toImage();
                QPoint point = QPoint((perLine.last().p1().x()+perLine.last().p2().x())/2,((perLine.last().p1().y()+perLine.last().p2().y())/2));
                qDebug()<<"point"<<point;
                QPen pen;
                pen.setColor(Qt::red);
                pen.setWidth(3);
                p.setPen(pen);
                p.drawPoint(point);
                qDebug()<<"UpPoint"<<image.pixelColor(QPoint(point.x(),point.y()-1));
                qDebug()<<"DownPoint"<<image.pixelColor(QPoint(point.x(),point.y()+1));
                qDebug()<<"RightPoint"<<image.pixelColor(QPoint(point.x()+1,point.y()));
                qDebug()<<"LeftPoint"<<image.pixelColor(QPoint(point.x()-1,point.y()));

            }
        }
            break;
        case UseRect://最后画在画布上的坐标一定得是左上点和右下点，不然只能移动，不能拉伸，修改起始点和终点
        {
            if(rects.isEmpty())
                return;
            //            QPainterPath paintPath;//把矩形放进路径中
            //            clearRect = rects.last();
            qDebug () <<"clearWhichRect" <<clearWhichRect;
            if(clickRect)
            {
                qDebug () << "selectWhichRect:" <<selectWhichRect;
                if(selectWhichRect)
                {
                    if(isChangeRect)
                    {
                        qDebug () <<"isChangeRect:" <<isChangeRect;
                        QPen pen;
                        pen.setWidth (penWidth+1);
                        pen.setColor(QColor(Qt::white));
                        paint.setPen(pen);
                        paint.drawRect(clearWhichRect);
                        qDebug () << "ChangeRect:clearWhichRect:" <<clearWhichRect;
                        //                    paintPath.clear();
                        isChangeRect = false;
                    }
                    else if(isMoveRect)
                    {
                        qDebug () <<"isMoveRect:" <<isMoveRect;
                        QPen pen;
                        pen.setWidth (penWidth+1);
                        pen.setColor(QColor(Qt::white));
                        paint.setPen(pen);
                        paint.drawRect(clearWhichRect);
                        qDebug () << "MoveRect:clearWhichRect:" <<clearWhichRect;
                        isMoveRect = false;
                    }

                    //                    paint.eraseRect(clearWhichRect);//清除原先的路径

                }
                qDebug () << "最终画的矩形rects.lastPoints:" <<rects.last();
                QPen pen;
                pen.setWidth(penWidth);
                pen.setColor(_color);
                pen.setCapStyle(Qt::RoundCap);
                paint.setPen(pen);
                paint.drawRect(rects.last());
                //            paint.drawRoundedRect(rects.last(),25,25);
                p.drawPixmap(0,0,pix);
                //                paintPath.addRect(rects.last());
                qDebug () << "最终perRect.size:" <<perRect.size();
                //                myPaintPath.append(paintPath);
                selectWhichRect = false;
                isInRect = false;//可能需要在paintEvent里使用
                whichRect = -1;
            }
        }
            break;
        case UseEllipse:
        {
            if(ellipses.isEmpty())
                return;
            qDebug () <<"ClearWhichEllipse:" <<clWhichElpse;
            if(clickEllipse)
            {
                qDebug() <<"selectWhichEllipse:" <<selWhichElpse;
                if(selWhichElpse)
                {
                    if(isMoveEllipse)
                    {
                        qDebug() << "isMoveEllipse:" <<isMoveEllipse;

                        QPen pen;
                        pen.setWidth (penWidth+1);
                        pen.setColor(QColor(Qt::white));
                        paint.setPen(pen);
                        paint.drawEllipse(clWhichElpse);
                        qDebug () << "MoveEllipse:ClearWhichEllipse:" <<clWhichElpse;
                        isMoveEllipse = false;
                    }

                    qDebug() << "WhichEllipse:" <<whichEllipse;
                    qDebug() << "Ellipses.last:" <<ellipses.last();

                    //                    paint.eraseRect(clWhichElpse);//清除原先的路径
                    selWhichElpse = false;
                }
                QPen pen;
                pen.setWidth(penWidth);
                pen.setColor(_color);
                pen.setCapStyle(Qt::RoundCap);
                paint.setPen(pen);
                qDebug () << "最终画的椭圆Ellipse.lastPoints:" <<ellipses.last();
                paint.drawEllipse(ellipses.last());
                p.drawPixmap(0,0,pix);
                qDebug() << "ClearEllipse" <<clWhichElpse;
                selWhichElpse = false;
                whichEllipse = -1;
            }
        }
            break;
        case Clear:
            pix.fill(QColor(Qt::white));    //  没有立刻响应清屏？？？在点击事件上加update();
            p.drawPixmap(0,0,pix);
            myPaintPath.clear();
            paintnumber = 0;
            drawType=UseMouse;
            break;
        }
    }

    if(!myPaintPath.isEmpty())
    {
        p.setPen(Qt::NoPen);
        p.drawPath(myPaintPath);
    }

    if(perDelete)//删除形状,添加路径
    {
        pen.setColor(Qt::white);
        paint.setPen(pen);
        p.setPen(pen);
        if(clickLine)
        {
            if(selectWhichLine)
            {
                isMoveLine = false;
                isChangeLine = false;
                paint.drawLine(clearWhichLine);
                p.drawPixmap(0,0,pix);
                perLine.remove(whichLine);
            }
            selectWhichLine = false;
        }
        else if(clickRect)
        {
            if(selectWhichRect)
            {
                isMoveRect = false;
                isChangeRect = false;
                paint.drawRect(clearWhichRect);
                p.drawPixmap(0,0,pix);
                perRect.remove(whichRect);
            }
            selectWhichRect = false;

        }
        else if(clickEllipse)
        {
            if(selWhichElpse)
            {
                paint.drawEllipse(clWhichElpse);
                p.drawPixmap(0,0,pix);
                perEllipse.remove(whichEllipse);
            }
            isMoveEllipse = false;
            selWhichElpse = false;
        }
        perDelete = false;
    }
}


void Painter::mousePressEvent(QMouseEvent * e)//点击鼠标左键
{
    if(drawRange.contains(e->pos()))
    {
        if(e->button() == Qt::LeftButton)                                //在点击事件里判断选中了第几号路径（矩形，椭圆等）
        {

            /*判断是否选中线段，
             * 如果选中则不画图：
             * P点到线段中点的距离不大于半径的9/8;
             * 选择到底是选择两端（哪两端）还是整条线段?点到两端点距离？？？
             */
            //usemouse:drawline(moveStartPoint,movePoint);
            //moveStartPoint = movePoint;
            isDrawing = true;
            startPoint = e->pos();
            movePoint = e->pos();
            moveStartPoint = e->pos();


            if(perDeletee)
            {
                perDelete = true;
                perDeletee = false;
            }
            if(clickLine)
            {
                qDebug () <<"clickLine:"<<clickLine;
                QPoint point = e->pos();
                //判断靠近哪个线段的点组合
                //                int i = 0;
                qDebug() <<"PerLine.size:" <<perLine.size();

                if(lines.isEmpty())
                    return;
                if(perLine.size())//
                {
                    int i = perLine.size() -1;
                    do {
                        QPoint p1 = perLine[i].p1();
                        QPoint p2 = perLine[i].p2();
                        whichLine = i;
                        if(isCircle(p1,p2,point)  && isInDis(p1,p2,point))//判断是否靠近线段，如果靠近线段，则编辑该线段，否则继续画图
                        {
                            //                    qDebug () <<"distance:"<< distance;
                            //                    qDebug () <<"radius *3/4:"<< radius*3/4;
                            qDebug () <<"(distance <= radius*3/4):"<< (distance <= radius*3/4);
                            if(distance <= radius*3/4)//如果距离中点近，移动该线段
                            {
                                isMoveLine = true;
                                clearWhichLine = perLine[whichLine];
                                qDebug () <<"isMoveLine:"<< isMoveLine;
                            }
                            else//距离两端点近，拉伸近的一端
                            {
                                isChangeLine = true;
                                clearWhichLine = perLine[whichLine];
                                qDebug () <<"isChangeLine:"<<isChangeLine;
                            }

                            selectWhichLine = true;
                            break;
                        }
                        i--;
                    } while (i >= 0);
                    staticStartPoint = perLine[whichLine].p1();  //点击到更改区域时，锁定该条线段的两端点
                    staticEndPoint = perLine[whichLine].p2();

                }
            }

            if(clickRect)
            {
                qDebug () <<"clickRect:"<<clickRect;
                QPoint point = e->pos();
                qDebug() <<"perRect.size()" <<perRect.size();
                //                qDebug() <<"rects.isEmpty()" <<rects.isEmpty();
                //                if(rects.isEmpty())
                //                    return;
                //                qDebug() <<"rects.isEmpty()" <<rects.isEmpty();
                if(perRect.size())
                {
                    int i = perRect.size() - 1;
                    while(i >= 0)
                    {
                        QPoint p1 = perRect[i].topLeft();
                        QPoint p2 = perRect[i].bottomRight();
                        if(isInRectPoint(p1,p2,point))//判断是否可编辑矩形
                        {//拉伸矩形
                            whichRect = i;
                            selectWhichRect = true;
                            isChangeRect = true;
                            qDebug () <<"theRectPoint:" <<theRectPoint;
                            qDebug () <<"thatRectPoint:" <<thatRectPoint;
                            break;
                        }
                        else if(isInRect)//“移动”矩形
                        {
                            whichRect = i;
                            //                            clearWhichRect = perRect[whichRect];
                            selectWhichRect = true;
                            isMoveRect = true;
                            qDebug() <<"isInRectangle:"<<isMoveRect;
                            break;
                        }
                        i--;
                    }
                    qDebug() <<"whichRect:" << whichRect;
                    //clearWhichRect = perRect[whichRect];
                }
            }
            if(clickEllipse)
            {
                qDebug () <<"clickEllipse:"<<clickEllipse;
                QPoint point = e->pos();

                if(perEllipse.size())
                {
                    int i = perEllipse.size() - 1;
                    while(i >= 0)
                    {
                        QPoint p1 = perEllipse[i].topLeft();
                        QPoint p2 = perEllipse[i].bottomRight();
                        if(isInEllipse(p1,p2,point))
                        {
                            whichEllipse = i;
                            selWhichElpse = true;
                            isMoveEllipse = true;
                            break;
                        }
                        i--;
                    }
                    qDebug() <<"whichEllipse:" << whichEllipse;
                }
            }
            qDebug () <<"isDrawing:"<<isDrawing;

            if(isDrawing)
            {
                qDebug () <<"drawType:"<<drawType;
                switch (drawType) {
                case UseBrush:
                    break;
                case DrawPicture:
                    break;
                case UsePattern:
                    break;
                case UseMouse:
                {
                    startPoint = e->pos();
                    moveStartPoint = e->pos();
                    movePoint = e->pos();

                    qDebug () <<"UseMousePressPoint:"<<movePoint;
                    qDebug () <<"perPoint.size():"<<perPoint.size();
                    points.append(movePoint);
                    qDebug () <<"points.size():"<<points.size();


                }
                    break;
                case UseEraser:
                {
                    startPoint = e->pos();
                    movePoint = e->pos();
                    qDebug () <<"EraserPressPoint:"<<movePoint;
                }
                case SelectColor:
                {
                    startPoint = e->pos();
                    movePoint = e->pos();
                    QPoint point = e->pos();
                    qDebug () <<"EraserPressPoint:"<<point;
                }
                    break;
                case FillPolygon:
                {
                    QPoint point = e->pos();

                    if(myPainterPaths.size())
                    {
                        for (int i = 0 ; i < myPainterPaths.size(); i++) {
                            //for (int i = myPainterPaths.size()-1 ; i == 0; i--) {
                            if(myPainterPaths[i].contains(point))
                            {
                                element = i;
                            }
                        }
                    }

                }
                    break;
                case UseLine://点击画直线，做是否选择线段操作
                {
                    startPoint = e->pos();
                    movePoint = e->pos();
                    QPoint point = e->pos();
                    qDebug () <<"LinePressPoint:"<<startPoint<<"------------------------------------------------";


                    if(!isMoveLine & !isChangeLine)
                    {
                        lines.append(QLine(startPoint,point));//如果画直线，记录所有点
                    }
                    if(isChangeLine)
                    {
                        QPoint p1 = perLine[whichLine].p1();
                        QPoint p2 = perLine[whichLine].p2();
                        qDebug () <<"whichLine:"<< whichLine;
                        qDebug () <<"clearWhichLine::"<< perLine[whichLine];

                        qDebug () <<"isInp1靠近p1:"<< isInEndpointP1(p1,p2,point);
                        isInP1 = isInEndpointP1(p1,p2,point);
                        if(isInP1)//靠近p1起始点,更改起始点
                        {
                            QPoint point = e->pos();
                            lines.append(QLine(point,staticEndPoint));
                            qDebug () << " Press更改起点" <<lines.last();
                        }
                        else//靠近p2终点，更改终点
                        {
                            QPoint point = e->pos();
                            lines.append(QLine(staticStartPoint,point));
                            qDebug () << " Press更改终点" <<lines.last();
                        }
                    }
                }
                    break;
                case UseRect:
                {
                    startPoint = e->pos();
                    movePoint = e->pos();
                    QPoint point = e->pos();
                    qDebug () <<"RectPressPoint:"<<startPoint<<"--------------------------------------------";

                    if(!isChangeRect & !isMoveRect)
                        rects.append(QRect(startPoint,point));
                    else if(isChangeRect)
                    {
                        qDebug() <<"perRect[whichRect]:" <<perRect[whichRect];
                        clearWhichRect = perRect[whichRect];
                        rects.append(QRect(thatRectPoint,point));
                    }
                    else if(isMoveRect)
                    {
                        clearWhichRect = perRect[whichRect];
                        qDebug() <<"perRect[whichRect]:" <<perRect[whichRect];
                    }
                }
                    break;
                case UseEllipse:
                {
                    startPoint = e->pos();
                    movePoint = e->pos();
                    QPoint point = e->pos();
                    qDebug () <<"RectPressPoint:"<<startPoint<<"--------------------------------------------";
                    if(selWhichElpse)
                    {
                        if(isMoveEllipse)
                            clWhichElpse = perEllipse[whichEllipse];
                        qDebug() <<"perEllipse[whichEllipse]:" <<perEllipse[whichEllipse];
                    }
                    else
                        ellipses.append(QRect(startPoint,point));
                }
                    break;
                case Clear:
                    break;
                }
                update();
            }
        }
    }
}

void Painter::mouseMoveEvent(QMouseEvent * e)//移动鼠标左键
{
    if(drawRange.contains(e->pos()))
    {
        if(e->buttons() & Qt::LeftButton)
        {
            //            lines. = nullptr;
            movePoint = e->pos();
            switch (drawType) {
            case UseBrush:
                break;
            case FillPolygon:
                break;
            case DrawPicture:
                break;
            case UsePattern:
                break;
            case UseMouse:
            {
                movePoint = e->pos();

                points.append(movePoint);
                qDebug () <<"points.size():"<<points.size();
                qDebug () <<"MovestartPoint:"<<moveStartPoint;
                qDebug () <<"MovePoint:"<<movePoint;

            }
                break;
            case UseLine:
            {
                movePoint = e->pos();
                QPoint point = e->pos();
                if(selectWhichLine)//选中那条线段对其进行编辑操作
                {
                    qDebug () <<"isMoveLine:"<<isMoveLine;
                    if(isMoveLine)//移动线段
                    {
                        if(perLine.isEmpty())
                            return;
                        if(lines.isEmpty())
                            return;
                        QPoint p1 = perLine[whichLine].p1();
                        QPoint p2 = perLine[whichLine].p2();
                        QPoint point = e->pos();//startPoint
                        int disX = point.x() - startPoint.x();
                        int disY = point.y() - startPoint.y();
                        //                        startPoint = point;
                        lines.append(QLine(QPoint(p1.x()+disX,p1.y()+disY),QPoint(p2.x()+disX,p2.y()+disY)));
                        staticStartPoint = perLine[whichLine].p1();  //移动后也要更改不动点，以作选择拉伸使用
                        staticEndPoint = perLine[whichLine].p2();
                    }
                    else if(isChangeLine)
                    {
                        if(isInP1)//靠近p1,p1是起始点,更改起始点
                        {
                            if(lines.isEmpty())
                                return;
                            QPoint point = e->pos();
                            lines.append(QLine(point,staticEndPoint));
                            qDebug () <<"终点p2不变lines.lastPoint:"<<lines.last();
                        }
                        else//靠近p2，终点，更改终点
                        {
                            QPoint point = e->pos();
                            lines.append(QLine(staticStartPoint,point));
                            qDebug () <<"起始点p1不变lines.lastPoint:"<<lines.last();
                        }
                    }
                }
                else
                {
                    lines.append(QLine(startPoint,point));
                }

                qDebug () <<"MovePoint:"<<point;
            }
                break;
            case UseEraser:
            {
                movePoint = e->pos();
                qDebug () <<"EraserMovePoint:"<<movePoint;
            }
                break;
            case SelectColor:
            {
                movePoint = e->pos();
                QPoint point = e->pos();
                qDebug () <<"ColorMovePoint:"<<point;
            }
                break;
            case UseRect:
            {
                movePoint = e->pos();
                QPoint point = e->pos();
                qDebug () <<"RectMovePoint:"<<point;
                if(selectWhichRect)
                {
                    if(isChangeRect)
                    {
                        if(rects.isEmpty())
                            return;
                        QPoint point = e->pos();
                        rects.append(QRect(thatRectPoint,point));
                    }
                    else if(isMoveRect)
                    {
                        if(rects.isEmpty())
                            return;
                        QPoint p1 = perRect[whichRect].topLeft();
                        QPoint p2 = perRect[whichRect].bottomRight();
                        QPoint point = e->pos();
                        int disX = point.x() - startPoint.x();
                        int disY = point.y() - startPoint.y();
                        //                    startPoint = point;
                        rects.append(QRect(QPoint(p1.x()+disX,p1.y()+disY),QPoint(p2.x()+disX,p2.y()+disY)));
                        staticStartPoint = perRect[whichRect].topLeft();//这两个“不动点”在线段里使用过
                        staticEndPoint = perRect[whichRect].bottomRight();
                    }

                }
                else
                    rects.append(QRect(startPoint,point));
            }
                break;
            case UseEllipse:
            {
                movePoint = e->pos();
                QPoint point = e->pos();
                if(selWhichElpse)
                {
                    if(isMoveEllipse)
                    {
                        if(ellipses.isEmpty())
                            return;
                        QPoint point = e->pos();
                        QPoint p1 = perEllipse[whichEllipse].topLeft();
                        QPoint p2 = perEllipse[whichEllipse].bottomRight();
                        int disX = point.x() - startPoint.x();
                        int disY = point.y() - startPoint.y();
                        //                        startPoint = point;
                        ellipses.append(QRect(QPoint(p1.x()+disX,p1.y()+disY),QPoint(p2.x()+disX,p2.y()+disY)));
                        staticStartPoint = perEllipse[whichEllipse].topLeft();
                        staticEndPoint = perEllipse[whichEllipse].bottomRight();
                    }
                }

                else
                {
                    ellipses.append(QRect(startPoint,point));
                }
                qDebug () <<"EllipseMovePoint:"<<point;
            }
                break;
            case Clear:
                break;
            }
            update();
        }
    }
}

void Painter::mouseReleaseEvent(QMouseEvent * e)//释放鼠标左键
{
    if(drawRange.contains(e->pos()))
    {
        if(e->buttons() != Qt::LeftButton)
        {
            movePoint = e->pos();
            isDrawing = false;

            qDebug () <<"MouseReleasedrawType:"<<drawType;
            switch (drawType) {
            case UseMouse:
            {
                movePoint = e->pos();

                qDebug () <<"ReleaseStartPoint:"<<moveStartPoint;
                qDebug () <<"ReleasePoint:"<<movePoint;

                points.append(movePoint);
                qDebug() <<"points.size()" << points.size();
                perPoint.append(points);
                qDebug() <<"perPoint.size()" << perPoint.size();
                points.clear();
                qDebug() <<"points.size()" << points.size();
                myPaintPath.clear();
                paintPath();

            }
            case UseEraser:
            {
                movePoint = e->pos();
                qDebug () <<"EraserReleasePoint:"<<movePoint;
                myPaintPath.clear();
                paintPath();
            }
                break;
            case SelectColor:
            {
                movePoint = e->pos();
                QPoint point = e->pos();
                qDebug () <<"ColorReleasePoint:"<<point;
                myPaintPath.clear();
                paintPath();
            }
                break;
            case FillPolygon:

                break;
            case UseLine:
            {
                movePoint = e->pos();
                endPoint = e->pos();
                if(!isMoveLine & !isChangeLine)
                {
                    lines.append(QLine(startPoint,movePoint));//如果画直线，记录所有点
                    staticStartPoint = startPoint;
                    staticEndPoint = movePoint;
                    perLine.append(lines.last());//把最终画好的线段存储到容器中         只有鼠标松开会记录存储线段
                    //                    QPainterPath painterPath;
                    //                    painterPath.
                    qDebug() << "staticStartPoint" << staticStartPoint;
                    qDebug() << "staticEndPoint" << staticEndPoint;
                }
                if(selectWhichLine)//选中那条线段对其进行编辑操作
                {
                    if(isMoveLine)//移动线段
                    {
                        if(lines.isEmpty())
                            return;
                        QPoint p1 = perLine[whichLine].p1();
                        QPoint p2 = perLine[whichLine].p2();
                        QPoint point = e->pos();//startPoint
                        qDebug () <<"Releaselines.startPoint:"<<startPoint;
                        int disX = point.x() - startPoint.x();
                        int disY = point.y() - startPoint.y();
                        //                startPoint = point;
                        lines.append(QLine(QPoint(p1.x()+disX,p1.y()+disY),QPoint(p2.x()+disX,p2.y()+disY)));
                        staticStartPoint = perLine[whichLine].p1(); //移动后也要更改不动点，更新线段位置
                        staticEndPoint = perLine[whichLine].p2();


                        qDebug () <<"Releaselines.lastPoint:"<<lines.last();
                    }
                    else if(isChangeLine)
                    {
                        if(isInP1)//靠近p1,p1是起始点,更改起始点
                        {
                            QPoint point = e->pos();
                            lines.append(QLine(point,staticEndPoint));
                            qDebug () <<"终点p2不变lines.lastPoint:"<<lines.last();
                        }
                        else//靠近p2，终点，更改终点
                        {
                            QPoint point = e->pos();
                            lines.append(QLine(staticStartPoint,point));
                            qDebug () <<"起始点p1不变lines.lastPoint:"<<lines.last();
                        }
                    }
                    perLine.replace(whichLine,lines.last());//把最终画好的线段替换到容器中

                }

                //                qDebug () <<"ReleaseStartPoint:"<<startPoint;
                qDebug () <<"ReleaseEndPoint:"<<movePoint;
                qDebug ()<<"lines.lastpoint:"<<lines.last();
                myPaintPath.clear();
                paintPath();
            }
                break;
            case UseRect:
            {
                movePoint = e->pos();
                QPoint point = e->pos();

                qDebug () <<"ReleaseRectStartPoint:"<<startPoint;
                qDebug () <<"ReleaseRectEndPoint:"<<point;

                if(selectWhichRect)
                {
                    if(isChangeRect)
                    {
                        if(rects.isEmpty())
                            return;
                        QPoint point = e->pos();
                        rects.append(QRect(thatRectPoint,point));
                    }
                    else if(isMoveRect)
                    {
                        if(rects.isEmpty())
                            return;
                        QPoint p1 = perRect[whichRect].topLeft();
                        QPoint p2 = perRect[whichRect].bottomRight();
                        QPoint point = e->pos();
                        int disX = point.x() - startPoint.x();
                        int disY = point.y() - startPoint.y();
                        //                        startPoint = point;
                        rects.append(QRect(QPoint(p1.x()+disX,p1.y()+disY),QPoint(p2.x()+disX,p2.y()+disY)));
                        staticStartPoint = perRect[whichRect].topLeft();//这两个“不动点”在线段里使用过
                        staticEndPoint = perRect[whichRect].bottomRight();
                        //                        isInRect = false;//可能需要在paintEvent里使用
                    }
                    perRect.replace(whichRect,rects.last());//选中线段，把画好的线段替换到容器中
                }
                else
                {
                    rects.append(QRect(startPoint,point));
                    perRect.append(rects.last());
                }
                myPaintPath.clear();
                paintPath();
            }
                break;
            case UseEllipse:
            {
                movePoint = e->pos();
                QPoint point = e->pos();
                qDebug () <<"ReleaseEllipseStartPoint:"<<startPoint;
                qDebug () <<"ReleaseEllipseEndPoint:"<<point;
                if(selWhichElpse)
                {
                    if(isMoveEllipse)
                    {
                        if(ellipses.isEmpty())
                            return;
                        QPoint point = e->pos();
                        QPoint p1 = perEllipse[whichEllipse].topLeft();
                        QPoint p2 = perEllipse[whichEllipse].bottomRight();
                        int disX = point.x() - startPoint.x();
                        int disY = point.y() - startPoint.y();
                        //                    startPoint = point;
                        rects.append(QRect(QPoint(p1.x()+disX,p1.y()+disY),QPoint(p2.x()+disX,p2.y()+disY)));
                        staticStartPoint = perEllipse[whichEllipse].topLeft();
                        staticEndPoint = perEllipse[whichEllipse].bottomRight();
                        perEllipse.replace(whichEllipse,ellipses.last());

                    }
                }
                else
                {
                    ellipses.append(QRect(startPoint,point));
                    perEllipse.append(ellipses.last());
                }
                myPaintPath.clear();
                paintPath();
            }
                break;
            case Clear:
                break;
            }

            qDebug () <<"ReleaseMovePoint:"<<movePoint<<"---------------------------------------------";
            qDebug () <<"isDrawing:"<<isDrawing;

            int mPainterPaths = myPainterPaths.size();
            qDebug()<<"mPainterPaths.size:"<<mPainterPaths;
            update();
        }

    }
}

double Painter::dis(QPoint &p1,QPoint &p2)
{
    int disX = p1.x()-p2.x();
    int disY = p1.y()-p2.y();
    return sqrt(pow(disX,2)+pow(disY,2));
}

bool Painter::isCircle (QPoint &p1, QPoint &p2, QPoint &p)
{
    double centerX = (p1.x() + p2.x())/2;//中点
    double centerY = (p1.y() + p2.y())/2;
    QPoint center =QPoint(centerX,centerY);
    qDebug ()<<"centerX:"<<centerX;//线段中点X坐标
    qDebug ()<<"centerY"<<centerY;//线段中点Y坐标

    radius = dis(p1,p2)/2;//线段一半长度
    distance = dis(center,p);//当前鼠标点击位置与线段中点的距离dis
    return (distance <= radius + radius/20) ? true :false;
}

bool Painter::isInDis (QPoint &p1, QPoint &p2, QPoint &p)
{
    int x1 = p1.x(),
            y1 = p1.y(),
            x2 = p2.x(),
            y2 = p2.y(),
            x3 = p.x(),//Point
            y3 = p.y();

    double disP12 = dis(p1,p2);//两端点距离
    //Sabc=fabs(x1*y2+y1*x3+x2*y3-y2*x3-y3*x1-y1*x2)/2;
    /*     |  x1 y1 1  |
     *     |  x2 y2 1  |
     *     |  x3 y3 1  |
     */
    double squareABC =fabs(x1*y2+y1*x3+x2*y3-y2*x3-y3*x1-y1*x2);//square：dis*h* 1/2= 1/2(fabs())
    double h = squareABC / disP12;

    qDebug () <<"h = "<<h<<endl;
    return (h<15) ? true : false;
}

bool Painter::isInEndpointP1 (QPoint &p1,QPoint &p2, QPoint &p)
{
    double inP1 = dis(p1,p);
    double inP2 = dis(p2,p);
    return (inP1<inP2) ? true :false;
}


bool Painter::isInRectPoint(QPoint &p1, QPoint &p2, QPoint &p )
{
    /*求另外两个顶点，以每一顶点为中心，定长为半径的范围做标准*/            /*      o-------o
                                                                 *      |       |
                                                                 *      |       |
                                                                 *      |       |
                                                                 *      o-------o
                                                                 */
    QPoint p3,p4;//正向的p3在左下
    int xdis = p2.x() - p1.x();
    p3 = QPoint(p2.x()-xdis,p2.y());
    p4 = QPoint(p1.x()+xdis,p1.y());

    double pP1= dis(p,p1);
    double pP2=dis(p,p2);
    double pP3=dis(p,p3);
    double pP4=dis(p,p4);
    double radius = abs(xdis/8);         //radius可能为负数
    //    QRect rectRange;
    //    判断画矩形的起始点，小点在左上，大点在右下
    //    if((p1.x()>p2.x()) & (p1.y()>p2.y()))
    //        rectRange = QRect(p2,p1);
    //    else if((p1.x()<p2.x()) & (p1.y()>p2.y()))
    //        rectRange = QRect(p3,p4);
    //    else if((p1.x()<p2.x()) & (p1.y()<p2.y()))
    //        rectRange = QRect(p1,p2);
    //    else
    //        rectRange = QRect(p4,p3);
    QRect rectRange = QRect(p1,p2);
    if(pP1 <= radius)//检测靠近哪一点，记录靠近的点和对角顶点，再判断是否在矩形内
    {
        theRectPoint = p1;
        thatRectPoint = p2;
        qDebug () <<"theRectPoint:" <<theRectPoint;
        qDebug () <<"thatRectPoint:" <<thatRectPoint;
        return true;
    }
    else if(pP2 <= radius)
    {
        theRectPoint = p2;
        thatRectPoint = p1;
        return true;
    }
    else if(pP3 <= radius)
    {
        theRectPoint = p3;
        thatRectPoint = p4;
        return true;
    }
    else if(pP4 <= radius)
    {
        theRectPoint = p4;
        thatRectPoint = p3;
        return true;
    }
    else if(rectRange.contains(p))//判断是否在矩形内
    {
        isInRect = true;
        return false;
    }
    else
        return false;
}

bool Painter::isInEllipse(QPoint &p1, QPoint &p2, QPoint &p )
{
    QRect rectRange = QRect(p1,p2);
    return rectRange.contains(p) ? true :false;
}

void Painter::loadXML()
{
    clickRect = false;
    clickLine = false;
    clickEllipse = false;
    lines.clear();
    rects.clear();
    QString fileName = QFileDialog::getOpenFileName(this,"Open Xml","","XML(*.XML)");
    QFile file(fileName);
    if(fileName.isEmpty())
        return;
    if(!file.open(QFile::ReadOnly | QFile::Text))
        return;

    reader.setDevice(&file);
    while(!reader.atEnd())
    {
        QXmlStreamReader::TokenType type = reader.readNext();

        int pointX,pointY;
        int lStartPointX,lStartPointY,lEndpointX,lEndpointY;
        int rStartPointX,rStartPointY,rEndPointX,rEndPointY;
        int eStartPointX,eStartPointY,eEndPointX,eEndPointY;

        if(type == QXmlStreamReader::StartElement /*&& !reader.isWhitespace()*/)
        {
            //                qDebug()<<"Type:"<<type;
            QString nameStr = reader.name().toString();
            qDebug()<<"nameStr:"<<nameStr;//查看每个StartElement

            if(nameStr == "image")
            {
                QString image_str = reader.readElementText();
                qDebug()<<"content:"<<image_str;
                qDebug()<<"Pix" <<(type == QXmlStreamReader::Characters && !reader.isWhitespace());
                if(type == QXmlStreamReader::Characters && !reader.isWhitespace())
                {
                    bool isloadPixmap = false;//是否加载成功
                    QPixmap pixmap;
                    isloadPixmap = pixmap.loadFromData(QByteArray::fromHex(reader.text().toLatin1()));
                    qDebug()<<"LoadFromData:"<<isloadPixmap;
                    pix = pixmap;
                    qDebug()<<"loadPixmap~";
                }
                //                    qDebug()<<"content:"<<reader.readElementText();
                QPixmap pixmap;
                bool isloadPixmap = false;//是否加载成功
                QByteArray arr = image_str.toLatin1();
                isloadPixmap = pixmap.loadFromData(QByteArray::fromHex(arr));
                qDebug()<<"LoadFromData:"<<isloadPixmap;
                pix = pixmap;
            }
            //点集合，每一个reader.readNext()进入下一层
            if(nameStr == "POINTS")
            {
                reader.readNext();
                qDebug()<<"reader.text():"<<reader.text();
            }
            if(nameStr == "Points")
            {
                reader.readNext();
                qDebug()<<"reader.text():"<<reader.text();
            }
            if(nameStr == "Point")
            {
                reader.readNext();
                qDebug()<<"reader.text():"<<reader.text();
            }

            //点
            if(nameStr == "PointX")
            {

                pointX = reader.readElementText().toInt();
                qDebug()<<"PointX:"<<pointX;
            }
            if(nameStr == "PointY")
            {
                pointY = reader.readElementText().toInt();
                qDebug()<<"PointY:"<<pointY;
                isPointChanged = true;
            }

            //线段
            if(nameStr == "LINES")
            {
                reader.readNext();
                qDebug()<<"reader.text():"<<reader.text();
            }
            if(nameStr == "LStartPointX")
            {
                qDebug()<<"reader.text():"<<reader.text();
                lStartPointX = reader.readElementText().toInt();
                qDebug()<<"lStartPointX:"<<lStartPointX;
            }
            if(nameStr == "LStartPointY")
            {
                qDebug()<<"reader.text():"<<reader.text();
                lStartPointY = reader.readElementText().toInt();
                qDebug()<<"LStartPointY:"<<lStartPointY;
            }
            if(nameStr == "LEndpointX")
            {
                qDebug()<<"reader.text():"<<reader.text();
                lEndpointX = reader.readElementText().toInt();
                qDebug()<<"lEndpointX:"<<lEndpointX;
            }
            if(nameStr == "LEndpointY")
            {
                qDebug()<<"reader.text():"<<reader.text();//换了个debug位置就赋值进去了？？？？
                lEndpointY = reader.readElementText().toInt();//before:qDebug()<<"lEndpointY:"<<readElementText();
                qDebug()<<"lEndpointY:"<<lEndpointY;
                isLineChanged = true;
            }
            //矩形
            if(nameStr == "RStartPointX")
            {
                qDebug()<<"reader.text():"<<reader.text();
                rStartPointX = reader.readElementText().toInt();
            }
            if(nameStr == "RStartPointY")
            {
                qDebug()<<"reader.text():"<<reader.text();
                rStartPointY = reader.readElementText().toInt();
            }
            if(nameStr == "REndpointX")
            {
                qDebug()<<"reader.text():"<<reader.text();
                rEndPointX = reader.readElementText().toInt();
            }
            if(nameStr == "REndpointY")
            {
                qDebug()<<"reader.text():"<<reader.text();
                rEndPointY = reader.readElementText().toInt();
                isRectChanged = true;
            }
            //椭圆
            if(nameStr == "EStartPointX")
            {
                qDebug()<<"reader.text():"<<reader.text();
                eStartPointX = reader.readElementText().toInt();
            }
            if(nameStr == "EStartPointY")
            {
                qDebug()<<"reader.text():"<<reader.text();
                eStartPointY = reader.readElementText().toInt();
            }
            if(nameStr == "EEndpointX")
            {
                qDebug()<<"reader.text():"<<reader.text();
                eEndPointX = reader.readElementText().toInt();
            }
            if(nameStr == "EEndpointY")
            {
                qDebug()<<"reader.text():"<<reader.text();
                eEndPointY = reader.readElementText().toInt();
                isEllipseChanged = true;
            }
        }
        if(isPointChanged)
        {
            qDebug()<<"pointX:"<<pointX;
            points.append(QPoint(pointX,pointY));
            isPointChanged = false;
            qDebug()<<"points.size():"<<points.size();
            for (int i = 0;i<points.size(); i++) {
                qDebug()<<"points:"<<points[i];
            }
        }
        if(isLineChanged)
        {
            perLine.append(QLine(lStartPointX,lStartPointY,lEndpointX,lEndpointY));
            isLineChanged = false;
            qDebug()<<"lines.size():"<<perLine.size();
            for (int i = 0;i<perLine.size(); i++) {
                qDebug()<<"lines:"<<perLine[i];
            }
        }
        if(isRectChanged)
        {
            perRect.append(QRect(QPoint(rStartPointX,rStartPointY),QPoint(rEndPointX,rEndPointY)));
            isRectChanged = false;
            qDebug()<<"rects.size():"<<perRect.size();
            for (int i = 0;i<perRect.size(); i++) {
                qDebug()<<"rects:"<<perRect[i];
            }
        }
        if(isEllipseChanged)
        {
            perEllipse.append(QRect(QPoint(eStartPointX,eStartPointY),QPoint(eEndPointX,eEndPointY)));
            isEllipseChanged = false;
            qDebug()<<"ellipses.size():"<<perEllipse.size();
            for (int i = 0;i<perEllipse.size(); i++) {
                qDebug()<<"ellipses:"<<perEllipse[i];
            }
        }
        if(type == QXmlStreamReader::EndElement)
        {
            QString nameStr = reader.name().toString();
            qDebug()<<"nameStr:"<<nameStr;
            if(nameStr == "Points")//每个点集合的结束位置
            {
                perPoint.append(points);
                qDebug()<<"perPoint.size():"<<perPoint.size();
                for (int i = 0;i<perPoint.size(); i++) {
                    qDebug()<<"perPoint:"<<perPoint[i];
                }
            }
        }
    }
    file.close();
}

void Painter::saveXML()
{
    clickRect = false;
    clickLine = false;
    clickEllipse = false;
    lines.clear();
    rects.clear();
    QPixmap pixmap = pix;
    QImage image = pixmap.toImage();//要保存的图片
    QVector<QLine> line = perLine;//保存的线段数据
    QVector<QRect> rect = perRect;//要保存的矩形数据
    QVector<QRect> ellipse = perEllipse;//要保存的椭圆数据
    QVector<QVector<QPoint>> points = perPoint;//点集合
    QRgb rgb = (_color.red(),_color.green(),_color.blue());//每画一笔，记下颜色
    qDebug()<<"RGB"<<rgb;

    QByteArray ba;
    QBuffer buffer(&ba);
    if(!buffer.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this,"Save Xml","Saving Xml Failed");
    }
    image.save(&buffer,"PNG");//保存到
    buffer.close();
    QByteArray array = ba.toHex();
    QString tmp = array;

    QString fileName = QFileDialog::getSaveFileName(this,"Save XML","",QString("XML (*.xml)"));
    QFile file;
    file.setFileName(fileName);

    if(!file.open(QFile::WriteOnly | QFile::Text))
        return;
    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("file");

    stream.writeTextElement("image",tmp);

    stream.writeStartElement("VECTOR");

    if(points.size())
    {
        stream.writeStartElement("POINTS");
        for (int i = 0;i<points.size();i++)
        {
            stream.writeStartElement("Points");
            if(points[i].size())
            {
                stream.writeTextElement("PNumber",QString::number(i));
                for (int j = 0; j < points[i].size(); j++) {

                    stream.writeStartElement("Point");

                    stream.writeTextElement("PRGB",QString::number(rgb));
                    stream.writeTextElement("PointX",QString::number(points[i][j].x()));
                    stream.writeTextElement("PointY",QString::number(points[i][j].y()));
                    stream.writeEndElement();
                }
            }
            stream.writeEndElement();
        }
        stream.writeEndElement();
    }

    if(line.size())
    {
        stream.writeStartElement("LINES");
        for (int i = 0;i<line.size();i++)
        {
            stream.writeStartElement("Line");

            stream.writeTextElement("LNumber",QString::number(i));
            stream.writeTextElement("LRGB",QString::number(rgb));
            stream.writeTextElement("LStartPointX",QString::number(line[i].p1().x()));
            stream.writeTextElement("LStartPointY",QString::number(line[i].p1().y()));
            stream.writeTextElement("LEndpointX",QString::number(line[i].p2().x()));
            stream.writeTextElement("LEndpointY",QString::number(line[i].p2().y()));
            stream.writeEndElement();
        }
        stream.writeEndElement();
    }

    if(rect.size())
    {
        stream.writeStartElement("RECTANGLES");
        for (int i = 0;i<rect.size();i++)
        {
            stream.writeStartElement("Rectangle");

            stream.writeTextElement("RNumber",QString::number(i));
            stream.writeTextElement("RRGB",QString::number(rgb));
            stream.writeTextElement("RStartPointX",QString::number(rect[i].topLeft().x()));
            stream.writeTextElement("RStartPointY",QString::number(rect[i].topLeft().y()));
            stream.writeTextElement("REndpointX",QString::number(rect[i].bottomRight().x()));
            stream.writeTextElement("REndpointY",QString::number(rect[i].bottomRight().y()));
            stream.writeEndElement();
        }
        stream.writeEndElement();
    }

    if(ellipse.size())
    {
        stream.writeStartElement("ELLIPSES");
        for (int i = 0;i<ellipse.size();i++)
        {
            stream.writeStartElement("Ellipse");

            stream.writeTextElement("ENumber",QString::number(i));
            stream.writeTextElement("ERGB",QString::number(rgb));
            stream.writeTextElement("EStartPointX",QString::number(ellipse[i].topLeft().x()));
            stream.writeTextElement("EStartPointY",QString::number(ellipse[i].topLeft().y()));
            stream.writeTextElement("EEndpointX",QString::number(ellipse[i].bottomRight().x()));
            stream.writeTextElement("EEndpointY",QString::number(ellipse[i].bottomRight().y()));
            stream.writeEndElement();
        }
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    file.close();
}

void Painter::fill()
{
    clickRect = false;
    clickLine = false;
    clickEllipse = false;
    drawType = FillPolygon;
}

void Painter::drawPicture()
{
    drawType = DrawPicture;
}



//void Painter::pointFill(QImage *image, QPoint *point, QColor oldColor, QColor newColor)
//{
//    int fillL, fillR, i, in_line;

//}















