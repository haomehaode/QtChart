#pragma execution_character_set("utf-8")

#include "poly_line.h"
#include "util.h"
#include <QPainter>
#include <cmath>

PolyLine::PolyLine()
	: GraphicsItem()
{
	setZValue(1);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

QList<QPointF> PolyLine::get_points() const
{
	return m_points;
}

void PolyLine::set_points(const QList<QPointF>& points)
{
	m_points = points;
}

void PolyLine::append_point(const QPointF& point)
{
	m_points.append(point);
}

QPointF PolyLine::get_last_point() const
{
	QPointF lpt;
	if (!m_points.isEmpty())
		lpt = m_points.last();
	return lpt;
}

void PolyLine::set_last_point(const QPointF& point)
{
	m_points.pop_back();
	append_point(point);
}

QRectF PolyLine::boundingRect() const
{
	auto points = get_points();
	for (auto& p : points) p.setY(-p.y());
	QRectF rect = Util::bounding_rect(points);
	return rect;
}

void PolyLine::on_paint(QPainter* painter)
{
	auto points = get_points().toVector();
	for (int i = 0; i < points.size() - 1; ++i)
	{
		auto p1 = points[i];
		auto p2 = points[i + 1];
		if ((p1 - p2).manhattanLength() > TOLERANCE)
		{
			p1.setY(-p1.y());
			p2.setY(-p2.y());
			painter->drawLine(p1, p2);
		}
	}
}

GraphicsItem* PolyLine::clone()
{
	PolyLine* line = new PolyLine();
	line->set_points(m_points);
	return line;
}

///////////////////////////////////////////////////////////////////////////////
//箭头线
Arrows::Arrows()
{

}

GraphicsItem* Arrows::clone()
{
	Arrows* arrows = new Arrows();
	arrows->set_points(m_points);
	return arrows;
}

void Arrows::on_paint(QPainter* painter)
{
	auto points = get_points().toVector();
	for (int i = 0; i < points.size() - 1; ++i)
	{
		auto p1 = points[i];
		auto p2 = points[i + 1];
		if ((p1 - p2).manhattanLength() > TOLERANCE)
		{
			p1.setY(-p1.y());
			p2.setY(-p2.y());
			painter->drawLine(p1, p2);

			if (i + 1 == points.size() - 1)
			{
				QLineF line(p1, p2);
				double angle = std::atan2(-line.dy(), line.dx());
				qreal arrowSize = 10;
				QPointF arrowP1 = line.p2() - QPointF(sin(angle + PI / 3) * arrowSize,
					cos(angle + PI / 3) * arrowSize);
				QPointF arrowP2 = line.p2() - QPointF(sin(angle + PI - PI / 3) * arrowSize,
					cos(angle + PI - PI / 3) * arrowSize);
				QPolygonF arrowHead;
				arrowHead << line.p2() << arrowP2 << arrowP1;
				painter->drawLine(p2, arrowP1);
				painter->drawLine(p2, arrowP2);
			}
		}
		else
		{
			auto p1 = points[i - 1]; p1.setY(-p1.y());
			auto p2 = points[i];	p2.setY(-p2.y());
			QLineF line(p1, p2);
			double angle = std::atan2(-line.dy(), line.dx());
			qreal arrowSize = 10;
			QPointF arrowP1 = line.p2() - QPointF(sin(angle + PI / 3) * arrowSize,
				cos(angle + PI / 3) * arrowSize);
			QPointF arrowP2 = line.p2() - QPointF(sin(angle + PI - PI / 3) * arrowSize,
				cos(angle + PI - PI / 3) * arrowSize);
			QPolygonF arrowHead;
			arrowHead << line.p2() << arrowP2 << arrowP1;
			painter->drawLine(p2, arrowP1);
			painter->drawLine(p2, arrowP2);
		}
	}
}
