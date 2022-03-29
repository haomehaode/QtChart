#pragma execution_character_set("utf-8")

#include "probability_plot.h"
#include <QtCore/qmath.h>
#include "util.h"
#include "tool_tip.h"

ProbabilityPlot::ProbabilityPlot(QWidget *parent)
	: Plot(parent)
{
	init_series();
	init_chart();
	init_axis();
}

ProbabilityPlot::~ProbabilityPlot()
{
}

void ProbabilityPlot::slot_tool_tip(QPointF point, bool state)
{
	if (m_tooltip == nullptr)
		m_tooltip = new ToolTip(m_chart);
	if (state) {
		m_tooltip->setText(QString("X: %1 \nY: %2% ").arg(point.x()).arg(Util::normsdist(point.y())*100));
		m_tooltip->setAnchor(point);
		m_tooltip->setZValue(11);
		m_tooltip->updateGeometry();
		m_tooltip->show();
	}
	else {
		m_tooltip->hide();
	}
}

void ProbabilityPlot::add_data(QList<double>& list, const QString& name)
{
	prepare_data(list);

	QVector<QPointF> line_center_poslist;
	QVector<QPointF> scatter_poslist;

	for (Probability &item : m_probability_list)
	{
		line_center_poslist.append(QPointF(item.theory,item.theory_z));
		scatter_poslist.append(QPointF(item.reality, item.theory_z));
	}

	m_line_center->replace(line_center_poslist);
	m_scatter->replace(scatter_poslist);

	m_axisX->setRange(m_min_x - 1, m_max_x + 1);
}

void ProbabilityPlot::init_chart()
{
	//m_chart->legend()->hide();
	m_chart->addSeries(m_line_center);
	m_chart->addSeries(m_scatter);
}

void ProbabilityPlot::init_axis()
{
	m_axisX = new QValueAxis();
	m_chart->addAxis(m_axisX, Qt::AlignBottom);
	m_line_top->attachAxis(m_axisX);
	m_line_center->attachAxis(m_axisX);
	m_line_bottom->attachAxis(m_axisX);
	m_scatter->attachAxis(m_axisX);

	m_axisY = new QCategoryAxis();
	m_axisY->setTitleText("百分比");
	m_axisY->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
	m_axisY->setMin(-3.09);
	m_axisY->setMax(3.09);
	m_axisY->setStartValue(-3.71);
	m_axisY->append("0.1", -3.09);
	m_axisY->append("1", -2.33);
	m_axisY->append("5", -1.64);
	m_axisY->append("10", -1.28);
	m_axisY->append("20", -0.84);
	m_axisY->append("30", -0.52);
	m_axisY->append("40", -0.25);
	m_axisY->append("50", 0);
	m_axisY->append("60", 0.25);
	m_axisY->append("70", 0.52);
	m_axisY->append("80", 0.84);
	m_axisY->append("90", 1.28);
	m_axisY->append("95", 1.64);
	m_axisY->append("99", 2.33);
	m_axisY->append("99.9", 3.09);
	m_chart->addAxis(m_axisY, Qt::AlignLeft);
	m_line_top->attachAxis(m_axisY);
	m_line_center->attachAxis(m_axisY);
	m_line_bottom->attachAxis(m_axisY);
	m_scatter->attachAxis(m_axisY);
}

void ProbabilityPlot::init_series()
{
	m_line_center = new QLineSeries(m_chart);
	m_line_center->setName("参照线");
	m_line_center->append(QPointF(0, 0));

	m_line_top = new QLineSeries(m_chart);
	m_line_top->setName("上线百分位数");
	m_line_top->append(QPointF(0, 0));

	m_line_bottom = new QLineSeries(m_chart);
	m_line_bottom->setName("下线百分位数");
	m_line_bottom->append(QPointF(0, 0));

	m_scatter = new QScatterSeries();
	m_scatter->setName("百分数位");
	m_scatter->append(QPointF(0, 0));
	m_scatter->setMarkerSize(10);
	m_scatter->setBorderColor(Qt::transparent);
	connect(m_scatter, &QScatterSeries::hovered, this, &ProbabilityPlot::slot_tool_tip);
}

void ProbabilityPlot::prepare_data(QList<double>& list)
{
	if (list.isEmpty())
		return;

	m_n = list.count();
	m_mean = Util::average(list);
	m_variance = Util::variance(list, m_mean);
	m_sigma = Util::standard_deviation(list, m_variance);

	m_probability_list.clear();

	qSort(list);
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i] < m_min_x)
			m_min_x = list[i];
		if (list[i] > m_max_x)
			m_max_x = list[i];

		Probability pro;
		pro.index = i + 1;
		pro.theory_cdf = calculate_cdf(pro.index, list.size());
		pro.theory_z = Util::normsinv(pro.theory_cdf);
		pro.theory = m_mean + pro.theory_z * m_sigma;
		pro.reality = list.at(i);
		pro.reality_z = (pro.reality - m_mean) / m_sigma;
		//pro.reality_cdf = Util::normsdist(pro.reality_z);
		m_probability_list.append(pro);
	}
}

double ProbabilityPlot::calculate_cdf(int index, int n)
{
	double value = DBL_MIN;
	switch (m_score_type)
	{
	case Blom:
		value= (index - 0.375) / (n + 0.25);
		break;
	case Benard:
		value = (index - 0.3) / (n + 0.4);
		break;
	case Hazen:
		value = (index - 0.5) / n;
		break;
	case VanDerWaerden:
		value = index / (n + 1);
		break;
	case KaplanMeier:
		value = index / n;
		break;
	default:
		break;
	}
	return value;
}
