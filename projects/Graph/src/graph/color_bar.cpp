#pragma execution_character_set("utf-8")

#include "color_bar.h"
#include <QPainter>

ColorBar::ColorBar()
	: GraphicsItem()
{
}

void ColorBar::set_orientation(Qt::Orientation orientation)
{
	m_orientation = orientation;
}

Qt::Orientation ColorBar::orientation() const
{
	return m_orientation;
}

void ColorBar::set_color_range(const QColor& light, const QColor& dark)
{
	m_light = light;
	m_dark = dark;
	update_colors();  
}

void ColorBar::set_value_range(double min, double max)
{
	m_min = min;
	m_max = max;
}

QColor ColorBar::getColor(double value)
{
	if (value >= m_max)
		return m_light;
	if (value <= m_min)
		return m_dark;
	int index = ((value - m_min) / (m_max - m_min)) * colors.size();
	return colors.at(index);
}

void ColorBar::set_chart(QChart* chart)
{
	m_chart = chart;
	QMargins margin = m_chart->margins();
	margin.setRight(100);
	m_chart->setMargins(margin);
}

QRectF ColorBar::boundingRect() const
{
	QRectF rect= m_chart->plotArea();
	return QRectF(rect.topRight(), rect.topRight() + QPointF(100, rect.height()));
}

void ColorBar::on_paint(QPainter* painter)
{
	QRectF rect = boundingRect();
	painter->save();
	painter->setPen(Qt::NoPen);
	painter->setBrush(Qt::white);
	painter->drawRect(rect);
	painter->restore();

	QRectF bar_rect = rect;
	bar_rect.setWidth(25);
	draw_color_bar(painter, bar_rect);

	QRectF title_rect = rect;
	title_rect.setWidth(50);
	title_rect.setTopLeft(QPointF(rect.topLeft().x() + 30, rect.topLeft().y()));
	draw_color_title(painter, title_rect);
}

void ColorBar::draw_color_bar(QPainter* painter,QRectF rect)
{
	int h1, s1, v1;
	int h2, s2, v2;


	m_light.getHsv(&h1, &s1, &v1);
	m_dark.getHsv(&h2, &s2, &v2);

	painter->save();
	painter->setClipRect(rect);
	painter->setClipping(true);

	painter->fillRect(rect, m_dark);

	const int sectionSize = 2;

	int numIntervalls;
	if (m_orientation == Qt::Horizontal)
		numIntervalls = rect.width() / sectionSize;
	else
		numIntervalls = rect.height() / sectionSize;
	for (int i = 0; i < numIntervalls; i++)
	{
		QRect section;
		if (m_orientation == Qt::Horizontal)
		{
			section.setRect(rect.x() + i * sectionSize, rect.y(),
				sectionSize, rect.height());
		}
		else
		{
			section.setRect(rect.x(), rect.y() + i * sectionSize,
				rect.width(), sectionSize);
		}

		const double ratio = i / (double)numIntervalls;

		QColor c;
		c.setHsv(h1 + qRound(ratio * (h2 - h1)),
			s1 + qRound(ratio * (s2 - s1)),
			v1 + qRound(ratio * (v2 - v1)));
		painter->fillRect(section, c);
	}
	painter->restore();
}

void ColorBar::draw_color_title(QPainter* painter, QRectF rect)
{
	for (int i = 0; i < 6; i++) {
		QString str = QString().sprintf("%.2f", m_min + i * (m_max - m_min) / 5);
		QFontMetrics fm = painter->fontMetrics();
		QPointF pos(rect.topLeft().x(), rect.bottomLeft().y() - (rect.height() / 5) * i + fm.ascent() / 2);
		painter->drawText(pos, str);
	}
}

void ColorBar::update_colors()
{
	colors.clear();

	int h1, s1, v1;
	int h2, s2, v2;
	m_light.getHsv(&h1, &s1, &v1);
	m_dark.getHsv(&h2, &s2, &v2);

	const int sectionSize = 2;

	int numIntervalls;
	if (m_orientation == Qt::Horizontal)
		numIntervalls = boundingRect().width() / sectionSize;
	else
		numIntervalls = boundingRect().height() / sectionSize;
	for (int i = 0; i < numIntervalls; i++)
	{
		const double ratio = i / (double)numIntervalls;
		QColor c;
		c.setHsv(h1 + qRound(ratio * (h2 - h1)), s1 + qRound(ratio * (s2 - s1)), v1 + qRound(ratio * (v2 - v1)));
		colors.push_front(c);
	}
}

