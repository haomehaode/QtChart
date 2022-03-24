#pragma execution_character_set("utf-8")

#include "density_plot.h"
#include "color_bar.h"

DensityPlot::DensityPlot(QWidget *parent)
	: Plot(parent)
{
	init_series();
	init_chart();
	init_axis();
}

DensityPlot::~DensityPlot()
{
}

void DensityPlot::set_data(QList<ThirdDData>& value_list)
{

}

void DensityPlot::clear_data()
{
	value2series.clear();
	m_chart->series().clear();
}

void DensityPlot::init_chart()
{
	m_chart->legend()->hide();

	m_color_item = new ColorBar();
	m_color_item->set_chart(m_chart);
	m_chartview->add_item(m_color_item);
}

void DensityPlot::init_axis()
{
	m_axisX = new QValueAxis();
	m_chart->addAxis(m_axisX, Qt::AlignBottom);
	m_axisX->setGridLineVisible(false);

	m_axisY = new QValueAxis();
	m_chart->addAxis(m_axisY, Qt::AlignLeft);
	m_axisY->setGridLineVisible(false);
}

void DensityPlot::init_series()
{
	value2series.clear();
}
