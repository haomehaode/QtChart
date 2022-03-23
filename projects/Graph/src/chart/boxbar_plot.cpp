#pragma execution_character_set("utf-8")

#include "boxbar_plot.h"
#include "util.h"

BoxBarPlot::BoxBarPlot(QWidget* parent)
	: Plot(parent)
{
	init_series();
	init_chart();
	init_axis();
}

BoxBarPlot::~BoxBarPlot()
{
}

void BoxBarPlot::set_type(BoxBarType type)
{
	switch (type)
	{
	case MEAN:
		break;
	case SUM:
		break;
	case MAX:
		break;
	case MIN:
		break;
	default:
		break;
	}
}

void BoxBarPlot::set_data(QList<BoxData>& list)
{
	for (auto& item : list)
	{
		if (Util::max(item.m_value_list) > m_max_y)
			m_max_y = Util::max(item.m_value_list);
		add_boxbar(item);
	}

	m_axisX->setCategories(m_axisx_list);
	m_axisY->setRange(0, m_max_y * 1.1);
}

void BoxBarPlot::add_boxbar(BoxData& data)
{
	if (m_name2series.contains(data.m_name))
		return;

	double mean, sum, min, max;
	QBoxSet* box = new QBoxSet(data.m_name);
	Util::cal_list(data.m_value_list, mean, sum, max, min);
	box->setProperty("mean", mean);
	box->setProperty("sum", sum);
	box->setProperty("min", max);
	box->setProperty("max", min);
	box->setValue(QBoxSet::LowerExtreme, 0);
	box->setValue(QBoxSet::UpperExtreme, max);
	box->setValue(QBoxSet::Median, 0);
	box->setValue(QBoxSet::LowerQuartile, mean);
	box->setValue(QBoxSet::UpperQuartile, 0);
	m_axisx_list.append(data.m_name);
	m_series->append(box);

	m_name2series[data.m_name] = box;
}

void BoxBarPlot::delete_boxbar(const QString& name)
{
	if (!m_name2series.contains(name))
		return;
	m_series->remove(m_name2series[name]);
	m_name2series.remove(name);
}

void BoxBarPlot::init_chart()
{
	m_chart->legend()->hide();
	m_chart->addSeries(m_series);
}

void BoxBarPlot::init_axis()
{
	m_axisX = new QBarCategoryAxis();
	m_chart->addAxis(m_axisX, Qt::AlignBottom);
	m_series->attachAxis(m_axisX);

	m_axisY = new QValueAxis();
	m_chart->addAxis(m_axisY, Qt::AlignLeft);
	m_series->attachAxis(m_axisY);
}

void BoxBarPlot::init_series()
{
	m_series = new QBoxPlotSeries();
}
