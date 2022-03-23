#pragma execution_character_set("utf-8")

#include "pareto_plot.h"

ParetoPlot::ParetoPlot(QWidget *parent)
	: Plot(parent)
{
	init_series();
	init_chart();
	init_axis();
}

ParetoPlot::~ParetoPlot()
{

}

void ParetoPlot::set_data(QList<QPointF>& list, const QString& name)
{
	QVector<QPointF> line_center_poslist;
	QVector<QPointF> scatter_poslist;

	for (int i=0;i<list.size();i++)
	{
		m_axisy_list.append(QString::number(list[i].x()));
		m_set->append(list[i].y());

		line_center_poslist.append(QPointF(i, list[i].y()));
		scatter_poslist.append(QPointF(i, list[i].y()));
	}

	m_line->replace(line_center_poslist);
	m_scatter->replace(scatter_poslist);

	m_axisY_1->setRange(1, 60);
	m_axisX->append(m_axisy_list);
	m_axisX->setRange(m_axisy_list.first(), m_axisy_list.last());

	connect(m_scatter, &QScatterSeries::hovered, this, &Plot::slot_tool_tip);
}

void ParetoPlot::clear_data()
{
	QList<QPointF> list = m_scatter->points();

	QPointF top = m_chart->mapToPosition(QPointF(5, 17));
	m_line->clear();
	m_scatter->clear();
	m_bar->clear();
}

void ParetoPlot::init_chart()
{
	m_chart->legend()->hide();
	m_chart->addSeries(m_bar);
	m_chart->addSeries(m_line);
	m_chart->addSeries(m_scatter);
}

void ParetoPlot::init_axis()
{
	m_axisX = new QBarCategoryAxis();
	m_chart->addAxis(m_axisX, Qt::AlignBottom);
	m_line->attachAxis(m_axisX);
	m_bar->attachAxis(m_axisX);
	m_scatter->attachAxis(m_axisX);
	//m_axisX->setRange(m_axisy_list.first(), m_axisy_list.last());

	m_axisY_1 = new QValueAxis();
	//m_axisY_1->setRange(1, 100);
	m_chart->addAxis(m_axisY_1, Qt::AlignLeft);
	m_bar->attachAxis(m_axisY_1);

	m_axisY_2 = new QValueAxis();
	m_axisY_2->setTickCount(12);
	m_axisY_2->setRange(0, 110);
	m_axisY_2->setLabelFormat("%.1f%");
	m_axisY_2->setGridLineVisible(false);   //Òþ²Ø±³¾°Íø¸ñYÖá¿òÏß
	m_chart->addAxis(m_axisY_2, Qt::AlignRight);
	m_line->attachAxis(m_axisY_2);
	m_scatter->attachAxis(m_axisY_2);
}

void ParetoPlot::init_series()
{
	m_set = new QBarSet("");
	m_bar = new QBarSeries();
	m_bar->append(m_set);

	m_line = new QLineSeries();
	m_line->append(QPointF(0, 0));

	m_scatter = new QScatterSeries();
	m_scatter->append(QPointF(0, 0));
	m_scatter->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
	m_scatter->setMarkerSize(10);
	m_scatter->setPointLabelsVisible();
	m_scatter->setPointLabelsFormat("@yPoint%");
	m_scatter->setPointLabelsClipping(false);
}

void ParetoPlot::prepare_data(QList<QPointF>& poslist)
{
	//qSort(poslist);
}
