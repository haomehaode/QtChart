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

void DensityPlot::set_data(QList<QPointF>& pos_list)
{
	QVector<DensityPoint> dataset;

	for (auto& item : pos_list)
	{
		if (m_min_x > item.x())
			m_min_x = item.x();
		if (m_max_x < item.x())
			m_max_x = item.x();
		if (m_min_y > item.y())
			m_min_y = item.y();
		if (m_max_y < item.y())
			m_max_y = item.y();

		dataset.push_back(DensityPoint(item.x(), item.y()));
	}

	calculateDensity(dataset, radius);

	for (int i = 0; i < dataset.size(); i++)
	{
		auto pos = dataset.at(i);
		int zi = pos.pts;
		qreal x = pos.x;
		qreal y = pos.y;
		if (value2series.contains(zi))
			value2series[zi]->append(x, y);
		else
		{
			QScatterSeries* scatter = new QScatterSeries;  //散点图
			//scatter->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
			scatter->setMarkerSize(3.0);
			scatter->setBorderColor(Qt::transparent);
			scatter->append(x, y);
			value2series[zi] = scatter;
		}
	}

	m_axisX->setRange(m_min_x, m_max_x);
	m_axisY->setRange(m_min_y, m_max_y);
	m_color_item->set_value_range(1.0, value2series.size());

	for (auto it = value2series.begin(); it != value2series.end(); ++it)
	{
		m_chart->addSeries(it.value());
		it.value()->attachAxis(m_axisX);
		it.value()->attachAxis(m_axisY);
		it.value()->setBrush(m_color_item->getColor(it.key()));
		it.value()->setUseOpenGL(true);
	}
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

double DensityPlot::squareDistance(DensityPoint a, DensityPoint b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void DensityPlot::calculateDensity(QVector<DensityPoint>& dataset, float Eps)
{
	int len = dataset.size();

	for (int i = 0; i < len; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			if (squareDistance(dataset[i], dataset[j]) <= Eps)
			{
				dataset[i].pts++;
				dataset[j].pts++;
			}
		}
	}
}
