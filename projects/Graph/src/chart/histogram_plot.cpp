#pragma execution_character_set("utf-8")

#include "histogram_plot.h"
#include "chart_view.h"
#include <QPainter>
#include <util.h>

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
	if (m_name2itemlist.contains(name))
		return;

	QList<QVector<double>> list = prepare_data(value_list);

	Histogram* his = new Histogram;
	his->m_index = m_name2itemlist.size() + 1;
	his->m_value = value_list;
	QScatterSeries *series = new QScatterSeries();
	series->setName(name);
	series->setColor(QColor::colorNames()[m_name2itemlist.size() + 5]);
	m_chart->addSeries(series);
	series->attachAxis(m_axisX);
	series->attachAxis(m_axisY);
	his->m_series = series;
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i][2] > m_count)
			m_count = list[i][2];
		QVector<double> ver;
		ver.append(list[i][0]); //开始
		ver.append(list[i][1]); //结束
		ver.append(list[i][2]); //总数

		HistogramItem* item = new HistogramItem();
		item->set_chart(m_chart);
		item->set_data(ver);
		item->set_index(his->m_index);
		m_chartview->add_item(item);
		his->m_list.append(item);
	}
	m_name2itemlist[name] = his;

	m_chart->setProperty("sum", m_name2itemlist.size());

	m_axisX->setTickCount(list.size()+1);
	m_max_x = m_min_x + list.size() * m_interval;
	m_axisX->setRange(m_min_x, m_max_x);
	m_axisY->setTickCount(m_count+2);
	m_axisY->setRange(0, m_count+1);
}

void HistogramPlot::delete_histogram(const QString& name)
{
	if (!m_name2itemlist.contains(name))
		return;
	m_chart->removeSeries(m_name2itemlist[name]->m_series);
	DELETE_PTR_LIST(m_name2itemlist[name]->m_list);
	DELETE_PTR(m_name2itemlist[name]);
	m_name2itemlist.remove(name);
}

void HistogramPlot::init_chart()
{
	//m_chart->legend()->hide();
	//m_chart->addSeries(m_series);
}

void HistogramPlot::init_axis()
{
	m_axisX = new QValueAxis();
	m_chart->addAxis(m_axisX, Qt::AlignBottom);
	//m_series->attachAxis(m_axisX);

	m_axisY = new QValueAxis();
	m_chart->addAxis(m_axisY, Qt::AlignLeft);
	//m_series->attachAxis(m_axisY);
}

void HistogramPlot::init_series()
{
	//m_series = new QScatterSeries();
}

QList<QVector<double>> HistogramPlot::prepare_data(QList<double>& list)
{
	if (m_name2itemlist.isEmpty())
	{
		for (auto& item : list)
		{
			if (item < m_min_x)
				m_min_x = item;
			if (item > m_max_x)
				m_max_x = item;
		}

		if ((floor((m_max_x - m_min_x) / m_interval)) * m_interval + m_min_x >= m_max_x)
			m_max_x = m_max_x + m_interval;

		QList<QVector<double>> histogram_list;
		for (double i = m_min_x; i < m_max_x; i = i + m_interval)
		{
			QVector<double> vect(3);
			vect[0] = i;
			vect[1] = i + m_interval;
			vect[2] = 0;
			histogram_list.append(vect);
		}

		for (int i = 0; i < list.size(); i++)
		{
			int index = floor((list[i] - m_min_x) / m_interval);
			if (index * m_interval + m_min_x < list[i])
				histogram_list[index--][2]++;
			else
				histogram_list[index][2]++;
		}
		return histogram_list;
	}
	else
	{
		double min = m_min_x, max = m_max_x;
		for (auto& item : list)
		{
			if (item < min)
				min = item;
			if (item > max)
				max = item;
		}
		while (  min< m_min_x)
			m_min_x -= m_interval;
		while (max>= m_max_x)
			m_max_x += m_interval;

		QList<QVector<double>> histogram_list;
		for (double i = m_min_x; i < m_max_x; i = i + m_interval)
		{
			QVector<double> vect(3);
			vect[0] = i;
			vect[1] = i + m_interval;
			vect[2] = 0;
			histogram_list.append(vect);
		}

		for (int i = 0; i < list.size(); i++)
		{
			int index = floor((list[i] - m_min_x) / m_interval);
			if (index * m_interval + m_min_x < list[i])
				histogram_list[index--][2]++;
			else
				histogram_list[index][2]++;
		}
		return histogram_list;
	}
}

//////////////////////////////////////////////////////////////////////////////
/// 直方图
HistogramItem::HistogramItem()
{
	connect(this, &HistogramItem::signal_prepare_path, this, &HistogramItem::slot_prepare_path);
}

void HistogramItem::set_chart(QChart* chart)
{
	m_chart = chart;
}

void HistogramItem::set_data(QVector<double> data)
{
	m_data = data;
}

void HistogramItem::set_index(int index)
{
	m_index = index - 1;
}

void HistogramItem::slot_prepare_path()
{
	QPainterPath path;

	int size = m_chart->property("sum").toInt();
	double width = (m_data[1] - m_data[0]) / size;
	double start = m_data[0] + width * m_index;
	double end = start + width;
	QPointF tl = m_chart->mapToPosition(QPointF(start, m_data[2]));
	QPointF br = m_chart->mapToPosition(QPointF(end, 0));
	QRectF rect(tl, br);
	path.addRect(rect);

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

	QColor color(QColor::colorNames()[m_index + 5]);

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
