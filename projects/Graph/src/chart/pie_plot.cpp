#pragma execution_character_set("utf-8")

#include "pie_plot.h"

PiePlot::PiePlot(QWidget* parent)
	: Plot(parent)
{
	init_series();
	init_chart();
	init_axis();
}

PiePlot::~PiePlot()
{
}

void PiePlot::slot_tool_tip(QPieSlice* slice, bool state)
{
	slice->setLabelVisible(state);
	slice->setExploded(state);
}

void PiePlot::set_data(QList<PieData>& valuelist)
{
	for (auto& item : valuelist)
		add_pie(item.m_value, item.m_name);
}

void PiePlot::add_pie(double value, const QString& name)
{
	QPieSlice* pie = new QPieSlice(name , value);
	m_series->append(pie);
	m_name2series[name] = pie;
	update_label();
}

void PiePlot::delete_pie(const QString& name)
{
	if (!m_name2series.contains(name))
		return;
	m_series->remove(m_name2series[name]);
	m_name2series.remove(name);
}

void PiePlot::init_chart()
{
	m_chart->addSeries(m_series);
	m_chart->legend()->setVisible(true);
	m_chart->legend()->setAlignment(Qt::AlignRight);
}

void PiePlot::init_axis()
{

}

void PiePlot::init_series()
{
	m_series = new QPieSeries();
	connect(m_series, &QPieSeries::hovered, this, &PiePlot::slot_tool_tip);
}

void PiePlot::update_label()
{
	// 设置块标签
	for (int sNum = 0; sNum < m_series->slices().count(); sNum++)
	{
		QPieSlice* slice = m_series->slices().at(sNum);
		QString tagText = QString("%1 %2%")
			.arg(slice->label().split(' ')[0])
			.arg(QString::number(slice->percentage() * 100));
		slice->setLabel(tagText);
	}
}
