#include "color_map.h"

ColorMap::ColorMap(Qt::Orientation orientation)
	: GraphicsItem(), 
	d_orientation(orientation),
	d_light(Qt::white), 
	d_dark(Qt::black)
{
	setZValue(0);
}

void ColorMap::setOrientation(Qt::Orientation orientation)
{

}

Qt::Orientation ColorMap::orientation() const
{

}

void ColorMap::setRange(const QColor& light, const QColor& dark)
{

}

void ColorMap::setLight(const QColor& light)
{

}

void ColorMap::setDark(const QColor& dark)
{

}

QColor ColorMap::light() const
{

}

QColor ColorMap::dark() const
{

}

QRectF ColorMap::boundingRect() const
{

}

void ColorMap::on_paint(QPainter* painter)
{

}
