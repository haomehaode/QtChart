#pragma execution_character_set("utf-8")

#include "color_plot.h"
#include "color_bar.h"

ColorPlot::ColorPlot(QWidget *parent)
	: Plot(parent)
{
	init_series();
	init_chart();
	init_axis();
}

ColorPlot::~ColorPlot()
{

}

void ColorPlot::set_data(QList<ThirdDData>& value_list)
{
	for (auto& item : value_list)
	{
		if (m_min_x > item.m_x)
			m_min_x = item.m_x;
		if (m_max_x < item.m_x)
			m_max_x = item.m_x;
		if (m_min_y > item.m_y)
			m_min_y = item.m_y;
		if (m_max_y < item.m_y)
			m_max_y = item.m_y;
		if (m_min_z > item.m_z)
			m_min_z = item.m_z;
		if (m_max_z < item.m_z)
			m_max_z = item.m_z;

		if (value2series.contains(item.m_z))
			value2series[item.m_z]->append(QPointF(item.m_x, item.m_y));
		else
		{
			QScatterSeries* scatter = new QScatterSeries;  //É¢µãÍ¼
			scatter->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
			scatter->setMarkerSize(3.0);
			scatter->setBorderColor(Qt::transparent);
			scatter->append(QPointF(item.m_x, item.m_y));
			value2series[item.m_z] = scatter;
		}
	}

	m_axisX->setRange(m_min_x, m_max_x);
	m_axisY->setRange(m_min_y, m_max_y);
	m_color_item->set_value_range(m_min_z, m_max_z);

	for (auto it = value2series.begin(); it != value2series.end(); ++it)
	{
		m_chart->addSeries(it.value());
		it.value()->attachAxis(m_axisX);
		it.value()->attachAxis(m_axisY);
		it.value()->setBrush(m_color_item->getColor(it.key()));
		it.value()->setUseOpenGL(true);
	}
}

void ColorPlot::clear_data()
{
	value2series.clear();
	m_chart->series().clear();
}

void ColorPlot::init_chart()
{
	m_chart->legend()->hide();

	m_color_item = new ColorBar();
	m_color_item->set_chart(m_chart);
	m_chartview->add_item(m_color_item);
}

void ColorPlot::init_axis()
{
	m_axisX = new QValueAxis();
	m_chart->addAxis(m_axisX, Qt::AlignBottom);
	m_axisX->setGridLineVisible(false);

	m_axisY = new QValueAxis();
	m_chart->addAxis(m_axisY, Qt::AlignLeft);
	m_axisY->setGridLineVisible(false);
}

void ColorPlot::init_series()
{
	value2series.clear();
}
