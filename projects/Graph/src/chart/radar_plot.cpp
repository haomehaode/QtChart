#include "radar_plot.h"

RadarPlot::RadarPlot(QWidget *parent)
	: Plot(true, parent)
{
	init_series();
	init_chart();
	init_axis();
}

RadarPlot::~RadarPlot()
{
}

void RadarPlot::set_radar(QStringList& lablelist)
{
	count = lablelist.size();
	const auto offset = 360  / count;
	for (int i = 0; i < count; i++)
		m_angularAxis->append(lablelist[i], offset * i);
}

void RadarPlot::add_radar(QList<double>& valuelist, const QString& name)
{
	if (valuelist.size() != count)
		return;
	if (m_name2series.contains(name))
		return;
	QLineSeries *series = new QLineSeries();
	series->setName(name);
	for (int i = 0; i < count; i++)
	{
		if (valuelist[i] < m_min_x)
			m_min_x = valuelist[i];
		if (valuelist[i] > m_max_x)
			m_max_x = valuelist[i];
		series->append(360 / count * i, valuelist[i]);
	}
	series->append(360, valuelist.first());

	m_chart->addSeries(series);
	m_name2series[name] = series;
	series->attachAxis(m_angularAxis);
	series->attachAxis(m_radialAxis);
	m_radialAxis->setRange(m_min_x*0.9, m_max_x*1.1);

}

void RadarPlot::delete_radar(const QString& name)
{
	if (!m_name2series.contains(name))
		return;
	m_chart->removeSeries(m_name2series[name]);
	m_name2series.remove(name);
}

void RadarPlot::init_chart()
{
	m_chart->legend()->setVisible(true);
	m_chart->legend()->setAlignment(Qt::AlignRight);
}

void RadarPlot::init_axis()
{
	m_angularAxis = new QCategoryAxis();
	m_angularAxis->setRange(0, 360);
	m_angularAxis->setStartValue(0);
	m_angularAxis->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
	dynamic_cast<QPolarChart*>(m_chart)->addAxis(m_angularAxis, QPolarChart::PolarOrientationAngular);

	m_radialAxis = new QValueAxis();
	m_radialAxis->setTickCount(7);
	dynamic_cast<QPolarChart*>(m_chart)->addAxis(m_radialAxis, QPolarChart::PolarOrientationRadial);
}

void RadarPlot::init_series()
{
	m_name2series.clear();
}
