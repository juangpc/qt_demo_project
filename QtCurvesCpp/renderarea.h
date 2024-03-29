#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    enum ShapeType {Astroid,Cycloid,HuygensCycloid,HypoCycloid,FutureCurve};

    void setBackgroundColor(QColor color) {mBackgroundColor=color;} //setter
    QColor backgroundColor() const {return mBackgroundColor;} // getter

    void setShape(ShapeType shape) {mShape = shape; on_shape_changed();}
    ShapeType shape () const {return mShape;}

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:

private:
    void on_shape_changed();
    QPointF compute(qreal t);
    QPointF compute_astroid (qreal t);
    QPointF compute_cycloid (qreal t);
    QPointF compute_hygens (qreal t);
    QPointF compute_hypo (qreal t);
    QPointF compute_futureCurve(qreal t);
private:
    QColor mBackgroundColor;
    QColor mShapeColor;
    ShapeType mShape;

    qreal mIntervalLength;
    qreal mScale;
    int stepCount;

};

#endif // RENDERAREA_H
