#pragma execution_character_set("utf-8")

#include "color_bar.h"
#include <QPainter>

ColorBar::ColorBar()
	: GraphicsItem()
{
	init_colors();
}

void ColorBar::set_dock_area(LocationType area)
{
	m_area = area;
	QMargins margin = m_chart->margins();
	switch (m_area)
	{
	case Top:
		margin.setTop(100);
		break;
	case Bottom:
		margin.setBottom(100);
		break;
	case Left:
		margin.setLeft(100);
		break;
	case Right:
		margin.setRight(100);
		break;
	default:
		break;
	}
	m_chart->setMargins(margin);
}

void ColorBar::set_value_range(double min, double max)
{
	m_min = min;
	m_max = max;
}

QColor ColorBar::getColor(double value)
{
	QVector<QColor> colors;
	switch (m_type)
	{
	case Gray:
		colors = gray_colors;
		break;
	case Jet:
		colors = jet_colors;
		break;
	case Hsv:
		colors = hsv_colors;
		break;
	case Hot:
		colors = hot_colors;
		break;
	default:
		break;
	}
	if (value >= m_max)
		return colors.last();
	if (value <= m_min)
		return colors.first();
	int index = ((value - m_min) / (m_max - m_min)) * colors.size();
	return colors.at(index);
}

void ColorBar::set_chart(QChart* chart)
{
	m_chart = chart;
	set_dock_area(m_area);
}

void ColorBar::set_type(ColorBarType type)
{
	m_type = type;
}

QRectF ColorBar::boundingRect() const
{
	QRectF rect = m_chart->plotArea();

	switch (m_area)
	{
	case Top:
		return QRectF(rect.topLeft(), rect.topRight() + QPointF(0, -100));
		break;
	case Bottom:
		return QRectF(rect.bottomLeft(), rect.bottomRight() + QPointF(0,100));
		break;
	case Left:
		return QRectF(rect.topLeft(), rect.bottomLeft() + QPointF(-100, 0));
		break;
	case Right:
		return QRectF(rect.topRight(), rect.bottomLeft() + QPointF(100, 0));
		break;
	default:
		return QRectF(0, 0, 1, 1);
		break;
	}
}

void ColorBar::on_paint(QPainter* painter)
{
	QRectF rect = boundingRect();
	//painter->save();
	//painter->setPen(Qt::NoPen);
	//painter->setBrush(Qt::white);
	//painter->drawRect(rect);
	//painter->restore();

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

	QVector<QColor> colors;
	switch (m_type)
	{
	case Gray:
		colors = gray_colors;
		break;
	case Jet:
		colors = jet_colors;
		break;
	case Hsv:
		colors = hsv_colors;
		break;
	case Hot:
		colors = hot_colors;
		break;
	default:
		break;
	}

	QColor m_light = colors.last();

	QColor m_dark = colors.first();

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
	if (m_area == Right)
		numIntervalls = rect.width() / sectionSize;
	else
		numIntervalls = rect.height() / sectionSize;
	for (int i = 0; i < numIntervalls; i++)
	{
		QRect section;
		if (m_area == Left)
			section.setRect(rect.x() + i * sectionSize, rect.y(), sectionSize, rect.height());
		else
			section.setRect(rect.x(), rect.y() + i * sectionSize, rect.width(), sectionSize);

		const double ratio = i / (double)numIntervalls;

		QColor c;
		c.setHsv(h1 + qRound(ratio * (h2 - h1)),s1 + qRound(ratio * (s2 - s1)),v1 + qRound(ratio * (v2 - v1)));
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

void ColorBar::init_colors()
{
	QColor color;
	float colorBarLength = 343.0;//设置颜色条的长度

	//------设置为gray颜色条---------//
	for (int i = 0; i <= colorBarLength; i++)// gray
	{
		color.setHsv(0, 0, (colorBarLength - i) / colorBarLength * 255);
		gray_colors.append(color);
	}

	//------设置为jet颜色条---------//
	float tempLength = colorBarLength / 4;
	for (int i = 0; i < tempLength / 2; i++)
	{
		color.setRgbF(0, 0, (tempLength / 2 + i) / tempLength);
		jet_colors.append(color);
	}
	for (int i = tempLength / 2 + 1; i < tempLength / 2 + tempLength; i++)
	{
		color.setRgbF(0, (i - tempLength / 2) / tempLength, 1);
		jet_colors.append(color);
	}
	for (int i = tempLength / 2 + tempLength + 1; i < tempLength / 2 + 2 * tempLength; i++)
	{
		color.setRgbF((i - tempLength - tempLength / 2) / tempLength, 1, (tempLength * 2 + tempLength / 2 - i) / tempLength);
		jet_colors.append(color);
	}
	for (int i = tempLength / 2 + 2 * tempLength + 1; i < tempLength / 2 + 3 * tempLength; i++)
	{
		color.setRgbF(1, (tempLength * 3 + tempLength / 2 - i) / tempLength, 0);
		jet_colors.append(color);
	}
	for (int i = tempLength / 2 + 3 * tempLength + 1; i < colorBarLength; i++)
	{
		color.setRgbF((colorBarLength - i + tempLength / 2) / (tempLength), 0, 0);
		jet_colors.append(color);
	}
	//------设置为hsv颜色条---------//
	for (int i = 0; i <= colorBarLength; i++)
	{
		color.setHsvF(i / colorBarLength, 1, 1);
		hsv_colors.append(color);
	}
	//------设置为hot颜色条---------//
	tempLength = colorBarLength / 2.5;
	for (int i = 0; i < tempLength / 2; i++)
	{
		color.setRgbF((tempLength / 2 + i) / tempLength, 0, 0);
		hot_colors.append(color);
	}
	for (int i = tempLength / 2 + 1; i < tempLength / 2 + tempLength; i++)
	{
		color.setRgbF(1, (i - tempLength / 2) / tempLength, 0);
		hot_colors.append(color);
	}
	for (int i = tempLength / 2 + tempLength + 1; i < colorBarLength; i++)
	{
		color.setRgbF(1, 1, (i - tempLength / 2 - tempLength) / (colorBarLength - tempLength / 2 - tempLength + 20));
		hot_colors.append(color);
	}
}
