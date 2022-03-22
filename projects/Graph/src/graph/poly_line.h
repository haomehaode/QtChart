#ifndef POLY_LINE_H
#define POLY_LINE_H

#include "chart_view.h"
#include "graphics_item.h"

///////////////////////////////////////////////////////////////////////////////
//多段线
class PolyLine : public GraphicsItem
{
public:

	PolyLine();

public:

	QList<QPointF> get_points() const;

	void set_points(const QList<QPointF>& points);

	void append_point(const QPointF& point);

	QPointF get_last_point() const;

	void set_last_point(const QPointF& point);

	virtual GraphicsItem* clone() override;

protected:

	QRectF boundingRect() const override;

	void on_paint(QPainter* painter) override;

protected:

	QList<QPointF> m_points;

};

///////////////////////////////////////////////////////////////////////////////
//箭头线
class Arrows : public PolyLine
{
public:

	Arrows();

	virtual GraphicsItem* clone() override;

protected:

	void on_paint(QPainter* painter) override;
};


#endif  // POLY_LINE_H
