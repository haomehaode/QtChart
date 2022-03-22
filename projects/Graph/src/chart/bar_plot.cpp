#pragma execution_character_set("utf-8")

#include "bar_plot.h"

BarPlot::BarPlot(QWidget *parent)
	: Plot(parent)
{
	init_series();
	init_chart();
	init_axis();
}

BarPlot::~BarPlot()
{

}

void BarPlot::set_axis(QList<QString> list)
{
	m_axisx_list = list;
	m_axisX->append(m_axisx_list);
}

void BarPlot::add_bar(QList<double>& value_list, const QString& name)
{
	if (m_name2series.contains(name))
		return;

	prepare_data(value_list);

	QBarSet* set = new QBarSet(name);
	set->append(value_list);
	m_series->append(set);

	m_name2series[name] = set;

	m_axisY->setRange(m_min_y - 1, m_max_y + 1);

	//connect(series, &QLineSeries::hovered, this, &Plot::slot_tool_tip);
	//connect_markers();
}

void BarPlot::delete_bar(const QString& name)
{
	if (!m_name2series.contains(name))
		return;
	m_series->remove(m_name2series[name]);
	m_name2series.remove(name);

	m_range[0].pop();
	m_range[1].pop();

	m_min_y = m_range[0].top();
	m_max_y = m_range[1].top();

	m_axisY->setRange(m_min_y - 1, m_max_y + 1);
}

void BarPlot::init_chart()
{
	m_chart->addSeries(m_series);
}

void BarPlot::init_axis()
{
	m_axisX = new QBarCategoryAxis();
	m_chart->addAxis(m_axisX, Qt::AlignBottom);
	m_series->attachAxis(m_axisX);

	m_axisY = new QValueAxis();
	m_chart->addAxis(m_axisY, Qt::AlignLeft);
	m_series->attachAxis(m_axisY);
}

void BarPlot::init_series()
{
	m_series = new QBarSeries();
}

void BarPlot::prepare_data(QList<double>& value_list)
{
	for (auto& value : value_list)
	{
		if (value < m_min_y)
			m_min_y = value;
		if (value > m_max_y)
			m_max_y = value;
	}
	m_range[0].push(m_min_y);
	m_range[1].push(m_max_y);
}
