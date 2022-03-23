#pragma execution_character_set("utf-8")

#include "interval_plot.h"
#include "chart_view.h"
#include "util.h"

IntervalPlot::IntervalPlot(QWidget *parent)
	: Plot(parent)
{
	init_series();
	init_chart();
	init_axis();
}

IntervalPlot::~IntervalPlot()
{

}

void IntervalPlot::set_data(QList<BoxData>& list)
{
	for (int i = 0; i < list.size(); i++)
	{
		double min, max;
		add_interval(list[i], i, min, max);
		m_axisx_list.append(list[i].m_name);
		if (max > m_max_y)
			m_max_y = max;
		if (min < m_min_y)
			m_min_y = min;
	}
	m_axisX->setCategories(m_axisx_list);
	m_axisY->setRange(m_min_y * 0.9, m_max_y * 1.1);
}

void IntervalPlot::add_interval(BoxData& data, int index, double& y_min, double& y_max)
{
	if (m_name2item.contains(data.m_name))
		return;

	IntervalItem* item = new IntervalItem();
	item->set_data(data, index);
	item->set_chart(m_chart);
	y_min = item->get_min();
	y_max = item->get_max();
	m_chartview->add_item(item);
	m_name2item[data.m_name] = item;
}

void IntervalPlot::init_chart()
{
	m_chart->legend()->hide();
	m_chart->addSeries(m_series);
}

void IntervalPlot::init_axis()
{
	m_axisX = new QBarCategoryAxis();
	m_chart->addAxis(m_axisX, Qt::AlignBottom);
	m_series->attachAxis(m_axisX);

	m_axisY = new QValueAxis();
	m_chart->addAxis(m_axisY, Qt::AlignLeft);
	m_series->attachAxis(m_axisY);
}

void IntervalPlot::init_series()
{
	m_series = new QScatterSeries();
}

//////////////////////////////////////////////////////////////////////////////
/// ¼ä¸ôÍ¼
IntervalItem::IntervalItem()
{
	connect(this, &IntervalItem::signal_prepare_path, this, &IntervalItem::slot_prepare_path);
}

void IntervalItem::set_chart(QChart* chart)
{
	m_chart = chart;
}

void IntervalItem::set_data(BoxData& data, int index)
{
	double mean, sum, min, max;
	Util::cal_list(data.m_value_list, mean, sum, max, min);

	m_list = data.m_value_list;
	m_name = data.m_name;
	m_min = QPointF(index, min);
	m_max = QPointF(index, max);
	m_mean = QPointF(index, mean);
	m_sum = QPointF(index, sum);
}

double IntervalItem::get_max()
{
	return m_max.y();
}

double IntervalItem::get_min()
{
	return m_min.y();
}

void IntervalItem::slot_prepare_path() 
{
	QLineF line(m_chart->mapToPosition(QPointF(0, 0)), m_chart->mapToPosition(QPointF(1, 0)));
	double width = line.length();
	QPointF top = m_chart->mapToPosition(m_max);
	QPointF buttom = m_chart->mapToPosition(m_min);
	QPointF center = m_chart->mapToPosition(m_mean);
	QPointF tl = top - QPointF(width * 0.05, 0);
	QPointF tr = top + QPointF(width * 0.05, 0);
	QPointF bl = buttom - QPointF(width * 0.05, 0);
	QPointF br = buttom + QPointF(width * 0.05, 0);

	QPainterPath path;
	path.moveTo(top);
	path.lineTo(buttom);
	path.moveTo(tl);
	path.lineTo(tr);
	path.moveTo(bl);
	path.lineTo(br);
	path.addEllipse(center, width * 0.05, width * 0.05);

	m_shape = path;
}

QRectF IntervalItem::boundingRect() const
{
	emit signal_prepare_path();
	return m_chart->plotArea().intersected(m_shape.boundingRect());
}

void IntervalItem::on_paint(QPainter* painter)
{
	painter->setClipRect(boundingRect());
	painter->drawPath(m_shape);
}
