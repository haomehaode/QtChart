#pragma execution_character_set("utf-8")

#include "scatter_plot.h"

ScatterPlot::ScatterPlot(QWidget* parent)
	: Plot(parent)
{
	init_series();
	init_chart();
	init_axis();
}

ScatterPlot::~ScatterPlot()
{

}

void ScatterPlot::add_scatter(QList<QPointF>& poslist, const QString& name)
{
	if (m_name2series.contains(name))
		return;

	prepare_data(poslist);

	QScatterSeries* series = new QScatterSeries();
	series->append(poslist);
	series->setName(name);
	m_chart->addSeries(series);
	m_name2series[name] = series;
	series->attachAxis(m_axisX);
	series->attachAxis(m_axisY);
	m_axisX->setRange(m_min_x, m_max_x);
	m_axisY->setRange(m_min_y, m_max_y);

	connect(series, &QScatterSeries::hovered, this, &Plot::slot_tool_tip);
	connect_markers();
}

void ScatterPlot::delete_scatter(const QString& name)
{
	if (!m_name2series.contains(name))
		return;
	m_chart->removeSeries(m_name2series[name]);
	m_name2series.remove(name);

	m_range[0].pop();
	m_range[1].pop();
	m_range[2].pop();
	m_range[3].pop();

	m_min_x = m_range[0].top();
	m_max_x = m_range[1].top();
	m_min_y = m_range[2].top();
	m_max_y = m_range[3].top();

	m_axisX->setRange(m_min_x, m_max_x);
	m_axisY->setRange(m_min_y, m_max_y);
}

void ScatterPlot::init_chart()
{
	//m_chart->legend()->hide();
}

void ScatterPlot::init_axis()
{
	m_axisX = new QValueAxis();
	m_chart->addAxis(m_axisX, Qt::AlignBottom);

	m_axisY = new QValueAxis();
	m_chart->addAxis(m_axisY, Qt::AlignLeft);
}

void ScatterPlot::init_series()
{
	m_name2series.clear();
}

void ScatterPlot::prepare_data(QList<QPointF>& poslist)
{
	for (auto& pos : poslist)
	{
		if (pos.x() < m_min_x)
			m_min_x = pos.x();
		if (pos.x() > m_max_x)
			m_max_x = pos.x();
		if (pos.y() < m_min_y)
			m_min_y = pos.y();
		if (pos.y() > m_max_y)
			m_max_y = pos.y();
	}
	m_range[0].push(m_min_x);
	m_range[1].push(m_max_x);
	m_range[2].push(m_min_y);
	m_range[3].push(m_max_y);
}
