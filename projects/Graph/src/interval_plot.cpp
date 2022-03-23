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

	for (int i=0;i<list.size();i++)
	{
		add_interval(list[i], i);
		m_axisx_list.append(list[i].m_name);
	}
	m_axisX->setRange(0, 100);
	//m_axisX->setCategories(m_axisx_list);
	m_axisY->setRange(0, 100);
}

void IntervalPlot::add_interval(BoxData& data, int index)
{
	if (m_name2item.contains(data.m_name))
		return;

	IntervalItem* item = new IntervalItem();
	item->set_data(data,index);
	item->set_chart(m_chart);
	m_chartview->add_item(item);
	m_name2item[data.m_name] = item;

}

void IntervalPlot::clear_data()
{

}


void IntervalPlot::init_chart()
{
	//m_chart->legend()->hide();
}

void IntervalPlot::init_axis()
{
	m_axisX = new QValueAxis();
	m_chart->addAxis(m_axisX, Qt::AlignBottom);

	m_axisY = new QValueAxis();
	m_chart->addAxis(m_axisY, Qt::AlignLeft);
}

void IntervalPlot::init_series()
{
	//m_name2series.clear();
}

void IntervalPlot::resizeEvent(QResizeEvent* event)
{
	QPointF pos(0, 0);
	QPointF scene_pos = m_chart->mapToPosition(pos);

	QGraphicsEllipseItem* item = new QGraphicsEllipseItem(0, 0, 100, 100);//x,y Ϊ���Ͻǵ�ͼԪ�ֲ����꣬ͼԪ���ĵ�Ϊ0,0
	item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
	item->setZValue(1);
	item->setPos(scene_pos);
	item->setSelected(true);
	m_chartview->scene()->addItem(item);
}

void IntervalPlot::prepare_data(QList<QPointF>& poslist)
{
	//for (auto& pos : poslist)
	//{
	//	if (pos.x() < m_min_x)
	//		m_min_x = pos.x();
	//	if (pos.x() > m_max_x)
	//		m_max_x = pos.x();
	//	if (pos.y() < m_min_y)
	//		m_min_y = pos.y();
	//	if (pos.y() > m_max_y)
	//		m_max_y = pos.y();
	//}
	//m_range[0].push(m_min_x);
	//m_range[1].push(m_max_x);
	//m_range[2].push(m_min_y);
	//m_range[3].push(m_max_y);
}

void IntervalPlot::draw_limt()
{
	QPointF pos(0, 0);

	//QPointF anchor = m_chart->mapToPosition(pos, );

	QPointF scene_pos2 = m_chart->mapFromParent( pos);
	QPointF scene_pos3 = m_chart->mapFromParent(pos);
	QPointF scene_pos4 = m_chart->mapToScene(pos);
	QPointF scene_pos5 = m_chart->mapToScene(pos);
	QPointF scene_pos6 = m_chart->mapToScene(pos);
	QPointF scene_pos = m_chart->mapToScene(pos);

	QGraphicsEllipseItem* item = new QGraphicsEllipseItem(0, 0, 100, 100);//x,y Ϊ���Ͻǵ�ͼԪ�ֲ����꣬ͼԪ���ĵ�Ϊ0,0
	item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
	item->setZValue(1);
	item->setPos(scene_pos);
	item->setSelected(true);
	m_chartview->scene()->addItem(item);
}

//////////////////////////////////////////////////////////////////////////
///	���ͼ
IntervalItem::IntervalItem()
{

}

void IntervalItem::set_data(BoxData& data, int index)
{
	double mean, sum, min, max;
	Util::cal_list(data.m_value_list, mean, sum, max, min);

	m_list = data.m_value_list;
	m_name = data.m_name;
	m_min = QPointF(index*10, min);
	m_max = QPointF(index*10, max);
	m_mean = QPointF(index*10, mean);
	m_sum = QPointF(index*10, sum);
}

void IntervalItem::set_chart(QChart* chart)
{
	m_chart = chart;
}

QRectF IntervalItem::boundingRect() const
{
	return m_chart->plotArea();
}

void IntervalItem::on_paint(QPainter* painter)
{
	QPointF top = m_chart->mapToPosition(m_max);
	top.setY(-top.y());
	QPointF buttom= m_chart->mapToPosition(m_min);
	buttom.setY(-buttom.y());
	painter->drawLine(top, buttom);
}
