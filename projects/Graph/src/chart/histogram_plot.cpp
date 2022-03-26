#pragma execution_character_set("utf-8")

#include "histogram_plot.h"
#include "chart_view.h"
#include <QPainter>

HistogramPlot::HistogramPlot(QWidget *parent)
	: Plot(parent)
{
	init_series();
	init_chart();
	init_axis();
}

HistogramPlot::~HistogramPlot()
{

}

void HistogramPlot::add_histogram(QList<double>& value_list, const QString& name)
{
	QList<QVector<double>> list = prepare_data(value_list);

	QList<QVector<QPointF>> data;
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i][2] > m_count)
			m_count = list[i][2];
		QVector<QPointF> ver;
		ver.append(QPointF(list[i][0], list[i][2]));
		ver.append(QPointF(list[i][1], 0));
		data.append(ver);
	}
	HistogramItem* item = new HistogramItem();
	item->set_chart(m_chart);
	item->set_data(data);
	m_chartview->add_item(item);

	m_axisX->setTickCount(list.size()+1);
	m_max_x = m_min_x + list.size() * m_interval;
	m_axisX->setRange(m_min_x, m_max_x);
	m_axisY->setTickCount(m_count+2);
	m_axisY->setRange(0, m_count+1);

}

void HistogramPlot::delete_histogram(const QString& name)
{

}

void HistogramPlot::init_chart()
{
	//m_chart->legend()->hide();
	m_chart->addSeries(m_series);
}

void HistogramPlot::init_axis()
{
	m_axisX = new QValueAxis();
	m_chart->addAxis(m_axisX, Qt::AlignBottom);
	m_series->attachAxis(m_axisX);

	m_axisY = new QValueAxis();
	m_chart->addAxis(m_axisY, Qt::AlignLeft);
	m_series->attachAxis(m_axisY);
}

void HistogramPlot::init_series()
{
	m_series = new QScatterSeries();
}

QList<QVector<double>> HistogramPlot::prepare_data(QList<double>& list)
{
	for (auto& item : list)
	{
		if (item < m_min_x)
			m_min_x = item;
		if (item > m_max_x)
			m_max_x = item;
	}

	if ((floor((m_max_x - m_min_x) / m_interval)) * m_interval + m_min_x >=m_max_x)
		m_max_x = m_max_x + m_interval;

	QList<QVector<double>> histogram_list;
	for (double i = m_min_x; i < m_max_x; i = i + m_interval)
	{
		QVector<double> vect;
		vect.resize(3);
		vect[0] = i;
		vect[1] = i + m_interval;
		vect[2] = 0;
		histogram_list.append(vect);
	}

	for (int i = 0; i < list.size(); i++)
	{
		int index = floor((list[i] - m_min_x) / m_interval);
		if (index*m_interval+m_min_x<list[i])
			histogram_list[index--][2]++;
		else
			histogram_list[index][2]++;
	}
	return histogram_list;
}

//////////////////////////////////////////////////////////////////////////////
/// Ö±·½Í¼
HistogramItem::HistogramItem()
{
	connect(this, &HistogramItem::signal_prepare_path, this, &HistogramItem::slot_prepare_path);
}

void HistogramItem::set_chart(QChart* chart)
{
	m_chart = chart;
}

void HistogramItem::set_data(QList<QVector<QPointF>> data)
{
	m_data = data;
}

void HistogramItem::slot_prepare_path()
{
	QPainterPath path;
	for (QVector<QPointF>& item : m_data)
	{
		QPointF tl = m_chart->mapToPosition(item[0]);
		QPointF br = m_chart->mapToPosition(item[1]);
		QRectF rect(tl, br);
		path.addRect(rect);
	}
	m_shape = path;
}

QRectF HistogramItem::boundingRect() const
{
	emit signal_prepare_path();
	return m_chart->plotArea().intersected(m_shape.boundingRect());
}

void HistogramItem::on_paint(QPainter* painter)
{
	painter->setClipRect(boundingRect());

	QColor color(32, 159, 223);

	//QPen pen;
	//pen.setColor(color);
	//pen.setStyle(Qt::SolidLine);
	//painter->setPen(pen);

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(color);
	painter->setBrush(brush);

	painter->drawPath(m_shape);
}
