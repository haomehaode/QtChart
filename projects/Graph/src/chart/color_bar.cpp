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
		margin.setTop(50);
		break;
	case Bottom:
		margin.setBottom(50);
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
	switch (m_area)
	{
	case Top: 
		{
			QRectF bar_rect = rect;
			bar_rect.setHeight(-25);
			draw_color_bar(painter, bar_rect);
			QRectF title_rect = rect;
			title_rect.setTopLeft(QPointF(rect.topLeft().x(), rect.topLeft().y() - 30));
			draw_color_title(painter, title_rect);
		}
		break;
	case Bottom:
		{
			QRectF bar_rect = rect;
			bar_rect.setHeight(25);
			draw_color_bar(painter, bar_rect);
			QRectF title_rect = rect;
			title_rect.setTopLeft(QPointF(rect.topLeft().x(), rect.topLeft().y() + 30));
			draw_color_title(painter, title_rect);
		}
		break;
	case Left:
		{
			QRectF bar_rect = rect;
			bar_rect.setBottomRight(QPointF(rect.topLeft().x() - 25, rect.bottomRight().y()));
			draw_color_bar(painter, bar_rect);
			QRectF title_rect = rect;
			title_rect.setTopLeft(QPointF(rect.topLeft().x() - 30, rect.topLeft().y()));
			draw_color_title(painter, title_rect);
		}
		break;
	case Right: 
		{
			QRectF bar_rect = rect;
			bar_rect.setWidth(25);
			draw_color_bar(painter, bar_rect);
			QRectF title_rect = rect;
			title_rect.setTopLeft(QPointF(rect.topLeft().x() + 30, rect.topLeft().y()));
			draw_color_title(painter, title_rect);
		}
		break;
	default:
		break;
	}
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

	double numIntervalls;
	if (m_area == Right|| m_area == Left)
		numIntervalls = rect.height() / colors.size();
	else
		numIntervalls = rect.width() / colors.size();

	for (int i = 0; i < colors.size(); i++) {
		QRectF section;
		if (m_area == Right || m_area == Left)
			section.setRect(rect.bottomLeft().x(), rect.bottomLeft().y() - i * numIntervalls, rect.width(), numIntervalls);
		else
			section.setRect(rect.x() + i * numIntervalls, rect.y(), numIntervalls, rect.height());

		painter->fillRect(section, colors.at(i));
	}
}

void ColorBar::draw_color_title(QPainter* painter, QRectF rect)
{
	for (int i = 0; i < 6; i++) {
		QString str = QString().sprintf("%.2f", m_min + i * (m_max - m_min) / 5);
		QFontMetrics fm = painter->fontMetrics();
		switch (m_area)
		{
		case Top:
			{
				QPointF pos(rect.topLeft().x() + (rect.width() / 5) * i - fm.width(str) / 2, rect.topLeft().y());
				painter->drawText(pos, str); 
			}
			break;
		case Bottom:
			{
				QPointF pos(rect.topLeft().x() + (rect.width() / 5) * i - fm.width(str) / 2, rect.topLeft().y()+fm.ascent());
				painter->drawText(pos, str);
			}
			break;
		case Left:
			{
				QPointF pos(rect.topLeft().x() - fm.width(str), rect.bottomLeft().y() - (rect.height() / 5) * i + fm.ascent() / 2);
				painter->drawText(pos, str);
			}
			break;
		case Right:
			{
				QPointF pos(rect.topLeft().x(), rect.bottomLeft().y() - (rect.height() / 5) * i + fm.ascent() / 2);
				painter->drawText(pos, str);
			}
			break;
		default:
			break;
		}
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
