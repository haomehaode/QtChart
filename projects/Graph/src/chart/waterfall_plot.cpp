#pragma execution_character_set("utf-8")

#include "waterfall_plot.h"
#include "chart_view.h"
#include "plot.h"
#include <QPainter>

WaterfallPlot::WaterfallPlot(QWidget *parent)
	: Plot(parent)
{
	init_series();
	init_chart();
	init_axis();
	init_item();
}

WaterfallPlot::~WaterfallPlot()
{

}

void WaterfallPlot::set_data(QList<PieData>& value_list)
{
	QList<QPointF> start_pos, end_pos, add_pos, low_pos;

	double sum = start_value;
	m_axis_list.append(tr("起始值"));
	start_pos.append(QPointF(0, 0));
	start_pos.append(QPointF(0, sum));

	m_max_y = m_min_y = start_value;
	for (int i = 0; i < value_list.size(); i++)
	{
		if (value_list[i].m_value >= 0)
		{
			add_pos.append(QPointF(i + 1, sum + value_list[i].m_value));
			add_pos.append(QPointF(i + 1, sum));
		}
		else
		{
			low_pos.append(QPointF(i + 1, sum));
			low_pos.append(QPointF(i + 1, sum - value_list[i].m_value));
		}
		sum += value_list[i].m_value;

		if (sum > m_max_y)
			m_max_y = sum;
		if (sum < m_min_y)
			m_min_y = sum;

		m_axis_list.append(value_list[i].m_name);
	}

	m_axis_list.append(tr("累计值"));
	end_pos.append(QPointF(value_list.size() + 1, 0));
	end_pos.append(QPointF(value_list.size() + 1, sum));

	m_item_start->set_data(start_pos);
	m_item_end->set_data(end_pos);
	m_item_add->set_data(add_pos);
	m_item_low->set_data(low_pos);

	m_axisX->append(m_axis_list);
	m_axisX->setRange(m_axis_list.first(), m_axis_list.last());
	m_axisY->setRange(m_min_y * 0.9, m_max_y * 1.1);
}

void WaterfallPlot::clear_data()
{

}

void WaterfallPlot::init_chart()
{
	m_chart->addSeries(m_bar);
}

void WaterfallPlot::init_axis()
{
	m_axisX = new QBarCategoryAxis();
	m_chart->addAxis(m_axisX, Qt::AlignBottom);
	m_bar->attachAxis(m_axisX);

	m_axisY = new QValueAxis();
	m_chart->addAxis(m_axisY, Qt::AlignLeft);
	m_bar->attachAxis(m_axisY);
}

void WaterfallPlot::init_series()
{
	m_bar = new QBarSeries();
	m_bar_start = new QBarSet(tr("起始"));
	m_bar_add = new QBarSet(tr("增加"));
	m_bar_low = new QBarSet(tr("降低"));
	m_bar_end = new QBarSet(tr("累计"));
	m_bar->append(m_bar_start);
	m_bar->append(m_bar_add);
	m_bar->append(m_bar_low);
	m_bar->append(m_bar_end);
}

void WaterfallPlot::init_item()
{
	m_item_start = new WaterfallItem();
	m_item_start->set_chart(m_chart);
	m_item_start->set_series(m_bar_start);
	m_chartview->add_item(m_item_start);

	m_item_end = new WaterfallItem();
	m_item_end->set_chart(m_chart);
	m_item_end->set_series(m_bar_end);
	m_chartview->add_item(m_item_end);

	m_item_add = new WaterfallItem();
	m_item_add->set_chart(m_chart);
	m_item_add->set_series(m_bar_add);
	m_chartview->add_item(m_item_add);

	m_item_low = new WaterfallItem();
	m_item_low->set_chart(m_chart);
	m_item_low->set_series(m_bar_low);
	m_chartview->add_item(m_item_low);
}

//////////////////////////////////////////////////////////////////////////////
/// 瀑布图
WaterfallItem::WaterfallItem()
{
	connect(this, &WaterfallItem::signal_prepare_path, this, &WaterfallItem::slot_prepare_path);
}

void WaterfallItem::set_chart(QChart* chart)
{
	m_chart = chart;
}

void WaterfallItem::set_data(QList<QPointF> data)
{
	m_data = data;
}

void WaterfallItem::set_series(QBarSet* series)
{
	m_series = series;
}

void WaterfallItem::slot_prepare_path()
{
	QPainterPath path;

	QLineF line(m_chart->mapToPosition(QPointF(0, 0)), m_chart->mapToPosition(QPointF(1, 0)));
	double width = line.length();
	for (int i = 0; i < m_data.size(); i=i+2)
	{
		QPointF top = m_data[i].y()>= m_data[i + 1].y() ? m_chart->mapToPosition(m_data[i]) : m_chart->mapToPosition(m_data[i + 1]);
		QPointF buttom = m_data[i].y() < m_data[i + 1].y() ? m_chart->mapToPosition(m_data[i]) : m_chart->mapToPosition(m_data[i + 1]);
		QPointF tl = top - QPointF(width * 0.05, 0);
		QPointF tr = top + QPointF(width * 0.05, 0);
		QPointF bl = buttom - QPointF(width * 0.05, 0);
		QPointF br = buttom + QPointF(width * 0.05, 0);
		QRectF rect(tl, br);
		path.addRect(rect);
	}

	m_shape = path;
}

QRectF WaterfallItem::boundingRect() const
{
	emit signal_prepare_path();
	return m_chart->plotArea().intersected(m_shape.boundingRect());
}

void WaterfallItem::on_paint(QPainter* painter)
{
	painter->setClipRect(boundingRect());

	QColor color = m_series->color();

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
