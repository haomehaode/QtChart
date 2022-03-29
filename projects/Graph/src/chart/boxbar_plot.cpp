#pragma execution_character_set("utf-8")

#include "boxbar_plot.h"
#include "util.h"
#include <QPainter>
#include "chart_view.h"
#include "plot.h"

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
	for (int i = 0; i < list.size(); i++)
	{
		if (Util::max(list[i].m_value_list) > m_max_y)
			m_max_y = Util::max(list[i].m_value_list);
		add_boxbar(list[i],list.size(),i);
	}

	m_axisX->setCategories(m_axisx_list);
	m_axisY->setRange(0, m_max_y * 1.1);
}

void BoxBarPlot::add_boxbar(BoxData& data, int size, int index)
{
	if (m_name2series.contains(data.m_name))
		return;

	double mean, sum, min, max;
	QBarSet* box = new QBarSet(data.m_name);
	Util::cal_list(data.m_value_list, mean, sum, max, min);
	box->setProperty("mean", mean);
	box->setProperty("sum", sum);
	box->setProperty("min", max);
	box->setProperty("max", min);
	box->setProperty("index", index);

	for (int i = 0; i < size; i++)
		box->append(0);	
	box->replace(index, mean);

	m_axisx_list.append(data.m_name);
	m_series->append(box);


	BoxBarItem* item = new BoxBarItem();
	item->set_chart(m_chart);
	item->set_data(mean, sum, min, max, index);
	m_chartview->add_item(item);
	m_name2item[data.m_name] = item;

	m_name2series[data.m_name] = box;
}

void BoxBarPlot::delete_boxbar(const QString& name)
{
	if (!m_name2series.contains(name))
		return;
	m_series->remove(m_name2series[name]);
	m_name2series.remove(name);

	m_chartview->delete_item(m_name2item[name]);
	m_name2item.remove(name);
}

void BoxBarPlot::init_chart()
{
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
	m_series = new QStackedBarSeries();
}

BoxBarItem::BoxBarItem()
{
	connect(this, &BoxBarItem::signal_prepare_path, this, &BoxBarItem::slot_prepare_path);
}

void BoxBarItem::set_chart(QChart* chart)
{
	m_chart = chart;
}

void BoxBarItem::set_data(double mean, double sum, double min, double max, int index)
{
	m_min = QPointF(index, min);
	m_max = QPointF(index, max);
	m_mean = QPointF(index, mean);
	m_sum = QPointF(index, sum);
}

void BoxBarItem::slot_prepare_path()
{
	QLineF line(m_chart->mapToPosition(QPointF(0, 0)), m_chart->mapToPosition(QPointF(1, 0)));
	double width = line.length();
	QPointF top = m_chart->mapToPosition(m_max);
	QPointF buttom = m_chart->mapToPosition(m_min);
	QPointF center = m_chart->mapToPosition(m_mean);
	QPointF tl = top - QPointF(width * 0.1, 0);
	QPointF tr = top + QPointF(width * 0.1, 0);
	QPointF bl = buttom - QPointF(width * 0.1, 0);
	QPointF br = buttom + QPointF(width * 0.1, 0);

	QPainterPath path;
	path.moveTo(top);
	path.lineTo(center);
	path.moveTo(tl);
	path.lineTo(tr);

	m_shape = path;
}

QRectF BoxBarItem::boundingRect() const
{
	emit signal_prepare_path();
	return m_chart->plotArea().intersected(m_shape.boundingRect());
}

void BoxBarItem::on_paint(QPainter* painter)
{
	painter->setClipRect(boundingRect());
	painter->drawPath(m_shape);
}
