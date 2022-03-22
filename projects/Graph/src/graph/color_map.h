#ifndef COLOR_MAP_H
#define COLOR_MAP_H

#include "chart_view.h"
#include "graphics_item.h"

class ColorMap : public GraphicsItem
{

public:

	ColorMap(Qt::Orientation orientation);

	void setOrientation(Qt::Orientation orientation);

	Qt::Orientation orientation() const;

	void setRange(const QColor& light, const QColor& dark);

	void setLight(const QColor& light);

	void setDark(const QColor& dark);

	QColor light() const;

	QColor dark() const;

protected:

	QRectF boundingRect() const override;

	void on_paint(QPainter* painter) override;

private:

	Qt::Orientation d_orientation;

	QColor d_light;

	QColor d_dark;

	double m_min = 0;

	double m_max = 100;

	QVector<QColor> colors;
};

#endif // COLOR_MAP_H