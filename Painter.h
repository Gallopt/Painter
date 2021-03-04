#ifndef PAINTER_H
#define PAINTER_H

#include <QMainWindow>
#include <QPixmap>
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>
#include <QColor>
#include <QTimer>
#include <QXmlStreamReader>
#include <QStack>

QT_BEGIN_NAMESPACE
namespace Ui { class Painter; }
QT_END_NAMESPACE

enum PaintType{
    PEN,
    LINE,
    RECTANGLE,
    ELLIPLISE
};

//struct TypeCount{
//    int index;
//    PaintType type;
//};
class Painter : public QMainWindow
{
    Q_OBJECT

public:
    Painter(QWidget *parent = nullptr);
    ~Painter();


//    void pointFill(QImage *image, QPoint *point, QColor oldColor, QColor  newColor);
    struct point{
        QVector<QPoint> point;
        QColor color;
    };

    struct line{
        QVector<QLine> line;
        QColor color;
    };

    struct rectangle{
        QVector<QRect> rectangle;
        QColor outLinecolor;
        QColor color;

    };

    struct ellipse{
        QVector<QRect> ellipse;
        QColor outLinecolor;
        QColor color;
    };

    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);

    void saveXML();
    void loadXML();
    void fill();
    void drawPicture();

    void paintPath();

    double dis(QPoint &p1,QPoint &p2);//两点间距离
    //编辑线段
    bool isCircle(QPoint &p1,QPoint &p2,QPoint &p);//在线段的外围圆内，p指鼠标点位置
    bool isInDis(QPoint &p1,QPoint &p2,QPoint &p);//距线段一定距离内 p指鼠标点位置
    bool isInEndpointP1(QPoint &p1,QPoint &p2, QPoint &p);/*p1,p2两端点，p为鼠标位置，
    编辑矩形                                                *鼠标是否靠近线段两端，靠近p1还是p2*/
    bool isInRectPoint(QPoint &p1, QPoint &p2, QPoint &p);//检测是否靠近顶点

    bool isInEllipse(QPoint &p1, QPoint &p2, QPoint &p );
    bool isFill = false;

    enum drawType {
        UseMouse = 1,
        UseEraser,
        UseBrush,
        DrawPicture,
        FillPolygon,
        UsePattern,
        SelectColor,
        UseLine,
        UseRect,
        UseEllipse,
        Clear
    }drawType = UseMouse;

    QPainter colorPaint;

    bool findUpPoint = false;
    bool findDownPoint = false;

//    void fill4(QImage image,QPoint point, QColor oldColor);

    QString fileNName;

    void floodFill(QPainter &paint, QImage &image, QPoint &seedPoint, QColor newColor);
    void seekAndPaint(QImage &image, int &preL, int &preR, int &left, int &right, QColor &oldColor, int &moveY, QPainter &paint);

private:
    Ui::Painter *ui;
    bool perDelete = false;
    bool perDeletee = false;

    QColor multiColor;
    QPixmap pix = QPixmap(1580,882);//最终放在界面上的画布
    QPixmap tmpPixmap;//临时画布
    QPoint movePoint;//移动点

    QPoint moveStartPoint;


    QPoint startPoint;//起始点
    QPoint endPoint;//终点

    QPoint theRectPoint;//靠近的矩形顶点直接拉伸的点
    QPoint thatRectPoint;//对角线顶点

    QColor _color = QColor(Qt::black);
    QPoint staticStartPoint; //拉伸不动起点
    QPoint staticEndPoint;   //拉伸不动终点

    int penWidth = 3;

    QVector<QVector<QPoint>> perPoint;//曲线存储容器,所有点
    QVector<QPoint> points;//画的一笔点集合
    QVector<QPoint> cPoints;//涂色的点

    QVector<QLine> lines;/*(const QPoint &p1, const QPoint &p2)  每条线段生成之前存储容器，
                                                                 最后一组则为鼠标释放后最终线段*/
    QBrush brush = Qt::NoBrush;

    int perClick = 0;

    int whichLine = -1;
    bool selectWhichLine = false;//是否选中了某条线段
    QLine clearWhichLine;//需要清除的原线段
    QVector<QLine> perLine;//存储在画板上显示的所有线段

    int whichRect = -1;
    bool selectWhichRect = false;
    QRect clearWhichRect;//需要清除的原矩形
    QVector<QRect> perRect;//矩形容器

    int whichEllipse = -1;
    bool selWhichElpse = false;
    QRect clWhichElpse;//需要清除的原椭圆
    QVector<QRect> perEllipse;//椭圆

    QPainterPath myPaintPath;

    QPainterPath allPainterPath;//最后所有的路径

    int numPaintPath = -1;//路径容器的序号

    int paintnumber = 0;//遍历路径号

    QVector<QRect> rects;//QRect(int x, int y, int width, int height)矩形存储，和线段一样都是两个点，
                         //QRect(const QPoint &topLeft, const QSize &size)   考虑放在一起，还有椭圆
                         //QRect(const QPoint &topLeft, const QPoint &bottomRight)  贝塞尔曲线
    QVector<QRect> ellipses;

    bool clickLine = false;//是否点击了画直线
    bool clickRect = false;//是否点击了画矩形
    bool clickEllipse = false;//是否点击了画椭圆


    bool isDrawing = false;//允许画图标志
    bool isMoveLine = false;//允许移动线段标志
    bool isMoveRect = false;//允许移动矩形标志
    bool isInCircle = false;//是否在圆内，以线段中点为圆心

    bool isInLine = false;//是否在线段上
    bool isInP1 = false;//是否靠近p1

    bool isChangeRect = false;//允许拉伸矩形标志
    bool isChangeLine = false;//允许拉伸线段标志

    bool isInRect = false;//检测是否在矩形内
    bool isMoveEllipse = false; //检测是否可移动椭圆

    double radius;//线段的一半长度
    double distance;//鼠标点到线段中点距离

    bool releaseMouse = false; //松开鼠标标志，用来最后把存储的路径画出来标志

    QRect drawRange = QRect(QPoint(0,23),QSize(1580,882));

    QXmlStreamReader reader;

    bool isPointChanged = false;
    bool isLineChanged = false;
    bool isRectChanged = false;
    bool isEllipseChanged = false;

    int times = 0;
    QVector<QPainterPath> myPainterPaths;
    int element = 0;

    QList<int> typeCounts;//绘画步骤
};
#endif // PAINTER_H
