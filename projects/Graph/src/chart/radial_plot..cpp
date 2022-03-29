#pragma execution_character_set("utf-8")

#include "radial_plot.h"
#include "QPieSeries"

RadialPlot::RadialPlot(QWidget* parent)
	: Plot(parent)
{
	init_series();
	init_chart();
	init_axis();
}

RadialPlot::~RadialPlot()
{
}

void RadialPlot::slot_tool_tip(QPieSlice* slice, bool state)
{
	slice->setLabelVisible(state);
	//slice->setExploded(state);
}

void RadialPlot::update_location()
{
	const QStringList colorNames = QColor::colorNames();
	double sum = 360 / m_pie_series.size();
	double start = 0;
	for (int i=0;i< m_pie_series.size();i++)
	{
		QPieSeries* series = m_pie_series[i].m_pie;

		QList<QPieSlice*> slices = series->slices();
		for (QPieSlice* slice : slices)
			slice->setColor(QColor(colorNames[(i+10)%148]));

		series->setHoleSize(m_radial_min - 0.0001);
		double length = m_radial_min + m_radial_length * m_pie_series[i].m_value / m_max_x;
		series->setPieSize(length);
		series->setPieStartAngle(start);
		start += sum;
		series->setPieEndAngle(start);
	}
}

void RadialPlot::set_data(QList<PieData>& valuelist)
{
	for (auto& item : valuelist)
		add_pie(item.m_value, item.m_name);
}

void RadialPlot::add_pie(double value, const QString& name)
{
	if (value < m_min_x)
		m_min_x = value;
	if (value > m_max_x)
		m_max_x = value;

	QPieSeries* series = new QPieSeries();
	series->append(name + " " + QString::number(value), value);
	m_chart->addSeries(series);
	connect(series, &QPieSeries::hovered, this, &RadialPlot::slot_tool_tip);

	m_pie_series.append(RadialData(name, value, series));

	update_location();
}

void RadialPlot::delete_pie(const QString& name)
{
	
}

void RadialPlot::init_chart()
{
	//m_chart->legend()->setVisible(true);
	m_chart->legend()->setAlignment(Qt::AlignRight);
}

void RadialPlot::init_axis()
{

}

void RadialPlot::init_series()
{

}
