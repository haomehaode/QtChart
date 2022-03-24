#ifndef COLOR_BAR_H
#define COLOR_BAR_H

#include "chart_view.h"
#include "graphics_item.h"
#include <QChart>

enum ColorBarType
{
	Gray,
	Jet,
	Hsv,
	Hot
};

enum LocationType
{
	Top,
	Bottom,
	Left,
	Right
};

class ColorBar : public GraphicsItem
{

public:

	ColorBar();

	void set_dock_area(LocationType area);

	void set_value_range(double min, double max);

	QColor getColor(double value);

	void set_chart(QChart* chart);

	void set_type(ColorBarType type);

protected:

	QRectF boundingRect() const override;

	void on_paint(QPainter* painter) override;

	void draw_color_bar(QPainter* painter, QRectF rect);

	void draw_color_title(QPainter* painter, QRectF rect);

	void init_colors();

private:

	LocationType m_area = Right;

	double m_min = 0;

	double m_max = 100;

	QVector<QColor> gray_colors;

	QVector<QColor> jet_colors;

	QVector<QColor> hsv_colors;

	QVector<QColor> hot_colors;

	QChart* m_chart = nullptr;

	ColorBarType m_type = Jet;
};

#endif // COLOR_BAR_H