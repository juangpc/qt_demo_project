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
    on_shape_changed();
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100,100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400,200);
}

void RenderArea::on_shape_changed()
{
    switch(mShape){
    case Astroid:
        mScale = 40;
        mIntervalLength = 2 * qreal(M_PI);
        stepCount = 256;
        break;
    case Cycloid:
        mScale = 4;
        mIntervalLength = 6 * qreal(M_PI);
        stepCount = 128;
        break;
    case HuygensCycloid:
        mScale = 4;
        mIntervalLength = 4 * qreal(M_PI);
        stepCount = 256;
        break;
    case HypoCycloid:
        mScale = 15;
        mIntervalLength = 2 * M_PI;
        stepCount = 256;
        break;
    }
}

QPointF RenderArea::compute(qreal t)
{
    switch(mShape){
    case Astroid:
        return compute_astroid(t);
    case Cycloid:
        return compute_cycloid(t);
    case HuygensCycloid:
        return compute_hygens(t);
    case HypoCycloid:
        return compute_hypo(t);
    case FutureCurve:
        return compute_futureCurve(t);
//    default:
//        return QPointF(0,0);
    }
}

QPointF RenderArea::compute_astroid(qreal t)
{
    qreal cos_t = qreal(cos(t));
    qreal sin_t = qreal(sin(t));
    qreal x = 2 * cos_t * cos_t * cos_t;
    qreal y = 2 * sin_t * sin_t * sin_t;
    return QPointF(x,y);
}

QPointF RenderArea::compute_cycloid(qreal t)
{
    return QPointF(1.5*(1-cos(t)),
                   1.5*(t-sin(t)));
}

QPointF RenderArea::compute_hygens(qreal t)
{
    return QPointF(4*(3*cos(t) - cos(3*t)),
                   4*(3*sin(t) - sin(3*t)));
}

QPointF RenderArea::compute_hypo(qreal t)
{
    return QPointF(1.5 * (2 * cos(t) + cos(2*t)),
                   1.5 * (2 * sin(t) - sin(2*t)));
}
QPointF RenderArea::compute_futureCurve(qreal t) {return QPointF(0,0);}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);



    painter.setBrush(mBackgroundColor);
    painter.setPen(mShapeColor);

    //this is the drawing area
    painter.drawRect(this->rect());

    //    painter.drawLine(this->rect().topLeft(),this->rect().bottomRight());
    QPoint center = this->rect().center();
    qreal step = mIntervalLength/stepCount;
    for (qreal t=0; t<mIntervalLength; t+=step) {
        QPointF point = compute(t);
        QPoint pixel;
        pixel.setX(center.x() + int(point.x() * mScale));
        pixel.setY(center.y() + int(point.y() * mScale));

        painter.drawPoint(pixel);
    }


}
