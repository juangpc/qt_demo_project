#include "renderarea.h"
#include <QPaintEvent>
#include <QPainter>
#define M_PI 3.14159265358979323846264338327950288
#include <math.h>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    mBackgroundColor(0,0,255),
    mShapeColor(255,255,255),
    mShape(Astroid)
{
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100,100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400,200);
}

QPointF RenderArea::compute_astroid(qreal t)
{
    qreal cos_t = qreal(cos(t));
    qreal sin_t = qreal(sin(t));
    qreal x = 2 * cos_t * cos_t * cos_t;
    qreal y = 2 * sin_t * sin_t * sin_t;
    return QPointF(x,y);
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    switch(mShape){
    case Astroid:
        mBackgroundColor=Qt::red;
        break;
    case Cycloid:
        mBackgroundColor=Qt::green;
        break;
    case HuygensCycloid:
        mBackgroundColor=Qt::blue;
        break;
    case HypoCycloid:
        mBackgroundColor=Qt::yellow;
        break;
    }

    painter.setBrush(mBackgroundColor);
    painter.setPen(mShapeColor);

    //this is the drawing area
    painter.drawRect(this->rect());

    //    painter.drawLine(this->rect().topLeft(),this->rect().bottomRight());
    QPoint center = this->rect().center();
    int stepCount = 256;
    qreal scale = 40;
    qreal intervalLength = 2 * qreal(M_PI);
    qreal step = intervalLength/stepCount;
    for (qreal t=0; t<intervalLength; t+=step) {
        QPointF point = compute_astroid(t);
        QPoint pixel;
        pixel.setX(center.x() + int(point.x() * scale));
        pixel.setY(center.y() + int(point.y() * scale));

        painter.drawPoint(pixel);
    }


}
