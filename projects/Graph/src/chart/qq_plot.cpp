#pragma execution_character_set("utf-8")

#include "qq_plot.h"
#include <QtCore/qmath.h>
#include "util.h"
#include "tool_tip.h"

QQPlot::QQPlot(QWidget *parent)
	: Plot(parent)
{
	init_series();
	init_chart();
	init_axis();
}

QQPlot::~QQPlot()
{

}

void QQPlot::slot_tool_tip(QPointF point, bool state)
{
	if (m_tooltip == nullptr)
		m_tooltip = new ToolTip(m_chart);
	if (state) {
		m_tooltip->setText(QString("X: %1 \nY: %2% ").arg(point.x()).arg(point.y()));
		m_tooltip->setAnchor(point);
		m_tooltip->setZValue(11);
		m_tooltip->updateGeometry();
		m_tooltip->show();
	}
	else {
		m_tooltip->hide();
	}
}

void QQPlot::add_data(QList<double>& list, const QString& name)
{
	prepare_data(list);

	QVector<QPointF> line_center_poslist;
	QVector<QPointF> scatter_poslist;

	for (Probability& item : m_probability_list)
	{
		line_center_poslist.append(QPointF(item.theory, item.theory));
		scatter_poslist.append(QPointF(item.reality, item.theory));
	}

	m_line_center->replace(line_center_poslist);
	m_scatter->replace(scatter_poslist);

	m_axisX->setRange(m_min_x - 1, m_max_x + 1);
	m_axisY->setRange(m_min_x - 10, m_max_x + 10);
}

void QQPlot::init_chart()
{
	m_chart->legend()->hide();
	m_chart->addSeries(m_line_center);
	m_chart->addSeries(m_scatter);
}

void QQPlot::init_axis()
{
	m_axisX = new QValueAxis();
	m_chart->addAxis(m_axisX, Qt::AlignBottom);
	m_line_top->attachAxis(m_axisX);
	m_line_center->attachAxis(m_axisX);
	m_line_bottom->attachAxis(m_axisX);
	m_scatter->attachAxis(m_axisX);

	m_axisY = new QValueAxis();
	m_axisY->setTitleText("期望正态值");
	m_chart->addAxis(m_axisY, Qt::AlignLeft);
	m_line_top->attachAxis(m_axisY);
	m_line_center->attachAxis(m_axisY);
	m_line_bottom->attachAxis(m_axisY);
	m_scatter->attachAxis(m_axisY);
}

void QQPlot::init_series()
{
	m_line_center = new QLineSeries(m_chart);
	m_line_center->append(QPointF(0, 0));

	m_line_top = new QLineSeries(m_chart);
	m_line_top->append(QPointF(0, 0));

	m_line_bottom = new QLineSeries(m_chart);
	m_line_bottom->append(QPointF(0, 0));

	m_scatter = new QScatterSeries();
	m_scatter->append(QPointF(0, 0));
	m_scatter->setMarkerSize(10);
	m_scatter->setBorderColor(Qt::transparent);
	connect(m_scatter, &QScatterSeries::hovered, this, &QQPlot::slot_tool_tip);
}

void QQPlot::prepare_data(QList<double>& list)
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
		pro.reality_cdf = Util::normsdist(pro.reality_z);
		m_probability_list.append(pro);
	}
}

double QQPlot::calculate_cdf(int index, int n)
{
	double value = DBL_MIN;
	switch (m_score_type)
	{
	case Blom:
		value = (index - 0.375) / (n + 0.25);
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
