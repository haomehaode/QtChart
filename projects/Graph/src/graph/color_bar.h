#ifndef COLOR_BAR_H
#define COLOR_BAR_H

#include "chart_view.h"
#include "graphics_item.h"
#include <QChart>

class ColorBar : public GraphicsItem
{

public:

	ColorBar();

	void set_orientation(Qt::Orientation orientation);

	void set_value_range(double min, double max);

	QColor getColor(double value);

	void set_chart(QChart* chart);

protected:

	QRectF boundingRect() const override;

	void on_paint(QPainter* painter) override;

	void draw_color_bar(QPainter* painter, QRectF rect);

	void draw_color_title(QPainter* painter, QRectF rect);

	void init_colors();

private:

	Qt::Orientation m_orientation = Qt::Vertical;

	QColor m_light = Qt::red;

	QColor m_dark = Qt::darkBlue;

	double m_min = 0;

	double m_max = 100;

	QVector<QColor> colors;

	QChart* m_chart = nullptr;
};

#endif // COLOR_BAR_H