#pragma execution_character_set("utf-8")

#include "stock_plot.h"
#include <QBarCategoryAxis>
#include "tool_tip.h"
#include "chart_view.h"

StockPlot::StockPlot(QWidget *parent)
	: Plot(parent)
{
	init_series();
	init_chart();
	init_axis();
}

StockPlot::~StockPlot()
{
	//QCandlestickSeries常用函数：
	//append(self, set)：将由set指定的单个烛台条目添加到烛台图中，并获得其所有权。如果该项为空或已在系列中，则不会附加该项。如果添加成功返回True，否则返回False。
	//clear(self) : 永久删除图中的所有条目。
	//remove(self, set)：从烛台图中删除set指定的条目。
	//take(self, set)：从图中获取由set指定的单个条目。但不删除该条目。
	//setBodyOutlineVisible(self, bodyOutlineVisible)：设置烛台轮廓是否可见。
	//setBodyWidth(self, bodyWidth)：设置烛台条目的相对宽度，范围为0.0到1.0。
	//setBrush(self, brush)：设置烛台条目的画刷。
	//setPen(self, pen)：设置烛台条目线条的画笔。
	//setCapsVisible(self, capsVisible)：设置烛台条目盖是否可见。
	//setCapsWidth(self, capsWidth)： 设置烛台条目盖的宽度。
	//setDecreasingColor(self, decreasingColor)：设置烛台条目递减颜色。
	//setIncreasingColor(self, increasingColor)：设置烛台条目递增颜色。
	//setMaximumColumnWidth(self, maximumColumnWidth)：设置烛台条目的最大宽度(以像素为单位。设置为负值表示没有最大宽度。所有负值都将转换为 - 1.0)。
	//setMinimumColumnWidth(self, minimumColumnWidth)：设置烛台条目的最小宽度(以像素为单位。设置为负值表示没有最大宽度。所有负值都将转换为 - 1.0)。

	//QCandlestickSeries常用信号：
	//bodyOutlineVisibilityChanged(self)：烛台条目主体轮廓的可见性更改时，将发出此信号。
	//bodyWidthChanged(self)：烛台条目的宽度更改时，将发出此信号。
	//brushChanged(self)：烛台条目画刷更改时，将发出此信号。
	//candlestickSetsAdded(self, sets)：当sets指定的烛台条目添加到烛台图中时，将发出此信号。
	//candlestickSetsRemoved(self, sets)：从烛台图中删除sets指定的烛台条目时，将发出此信号。
	//capsVisibilityChanged(self)：烛台条目盖的可见属性更改时，将发出此信号。
	//capsWidthChanged(self) : 烛台条目盖的宽度更改时，将发出此信号。
	//clicked(self, set) : 单击图表上由set指定的烛台条目时，将发出此信号。
	//countChanged(self)：当烛台图中中烛台条目的数量发生更改时，将发出此信号。
	//decreasingColorChanged(self) : 当烛台条目的颜色减少时，将发出此信号。
	//doubleClicked(self, set)：双击图表上由set指定的烛台条目时，将发出此信号。
	//hovered(self, status, set)：当鼠标悬停在所指定的烛台条目set时，这个信号被发射。当鼠标移至该条目上方时，state变为True，而当鼠标再次移开时，state变为False。
	//increasingColorChanged(self)：烛台条目颜色增加时，将发出此信号。
	//maximumColumnWidthChanged(self) : 烛台条目的最大列宽发生变化时，将发出此信号。
	//minimumColumnWidthChanged(self)：烛台条目的最小列宽发生变化时，将发出此信号。
	//penChanged(self)：烛台图的画笔发生更改时会发出此信号。
	//pressed(self, set)：当用户单击set指定的烛台条目并按住鼠标按钮时，将发出此信号。
	//released(self, set)：当用户释放set所指定的烛台条目上的鼠标时，将发出此信号。

	//QCandlestickSet常用函数：
	//setBrush(self, brush)：设置条目的画刷为brush。
	//setPen(self, pen)：设置条目的画笔为pen。
	//setClose(self, close)：设置条目的收盘价为close。
	//setHigh(self, high)：设置条目的上限值为high。
	//setLow(self, low)：设置条目的下限值为low。
	//setOpen(self, open)：设置条目的开盘价。
	//setTimestamp(self, timestamp)：设置条目的时间戳。

	//QCandlestickSet常用信号：
	//brushChanged(self)：更改时画刷，将发出此信号。
	//penChanged(self)：更改画笔时，将发出此信号。
	//clicked(self)：单击条目时，将发出此信号。
	//doubleClicked(self)：双击条目时，将发出此信号。
	//hovered(self, status)：当鼠标悬停在条目上时，将发出此信号。
	//pressed(self)：当用户单击条并按住鼠标按钮时，将发出此信号。
	//released(self)：当用户释放对条目的释放鼠标时，将发出此信号。
	//closeChanged(self)：条目收盘价发生改变时发出此信号。
	//highChanged(self)：条目上限值更改时，将发出此信号。
	//lowChanged(self)：条目下限值更改时，将发出此信号。
	//openChanged(self)：条目开盘价变化时发出此信号。
	//timestampChanged(self)：当条目时间戳更改时，将发出此信号。
}

void StockPlot::slot_tool_tip(bool status, QCandlestickSet* set)
{
	if (m_tooltip == nullptr)
		m_tooltip = new ToolTip(m_chart,this);
	if (status) {
		m_tooltip->setText(QString("开盘: %1 \n收盘: %2\n最高: %3\n最低: %4 ")
			.arg(set->open()).arg(set->close()).arg(set->high()).arg(set->low()));
		QPointF point = m_chartview->mapFromGlobal(QCursor::pos());
		m_tooltip->setAnchor(point);
		m_tooltip->setZValue(11);
		m_tooltip->updateGeometry();
		m_tooltip->show();
	}
	else
		m_tooltip->hide();
}

void StockPlot::add_stock(QList<CandlestickData>& data_list, const QString& name)
{
	if (m_name2series.contains(name))
		return;

	prepare_data(data_list);

	QCandlestickSeries* series = new QCandlestickSeries();
	series->setName(name);
	series->setIncreasingColor(QColor(Qt::green));
	series->setDecreasingColor(QColor(Qt::red));

	for (auto& item : data_list)
	{
		QCandlestickSet* set = new QCandlestickSet(item.m_timestamp);
		set->setProperty("parent", name);
		set->setOpen(item.m_open);
		set->setHigh(item.m_high);
		set->setLow(item.m_low);
		set->setClose(item.m_close);
		series->append(set);
		m_axisx_list << QDateTime::fromMSecsSinceEpoch(set->timestamp()).toString("dd");
	}

	m_chart->addSeries(series);
	m_name2series[name] = series;
	series->attachAxis(m_axisX);
	series->attachAxis(m_axisY);
	m_axisX->setCategories(m_axisx_list);
	m_axisY->setRange(m_min_y, m_max_y);

	connect(series, &QCandlestickSeries::hovered, this, &StockPlot::slot_tool_tip);
	//connect_markers();
}

void StockPlot::delete_stock(const QString& name)
{
	if (!m_name2series.contains(name))
		return;
	m_chart->removeSeries(m_name2series[name]);
	m_name2series.remove(name);

	m_range[0].pop();
	m_range[1].pop();
	m_range[2].pop();
	m_range[3].pop();

	m_min_x = m_range[0].top();
	m_max_x = m_range[1].top();
	m_min_y = m_range[2].top();
	m_max_y = m_range[3].top();

	m_axisX->setRange(QString::number(m_min_x), QString::number(m_max_x));
	m_axisY->setRange(m_min_y * 0.99, m_max_y * 1.01);
}

void StockPlot::init_chart()
{
	//m_chart->legend()->hide();
}

void StockPlot::init_axis()
{
	m_axisX = new QBarCategoryAxis();
	m_chart->addAxis(m_axisX, Qt::AlignBottom);

	m_axisY = new QValueAxis();
	m_chart->addAxis(m_axisY, Qt::AlignLeft);
}

void StockPlot::init_series()
{
	m_name2series.clear();
}

void StockPlot::prepare_data(QList<CandlestickData>& data_list)
{
	for (auto& data : data_list)
	{
		if (data.m_timestamp < m_min_x)
			m_min_x = data.m_timestamp;
		if (data.m_timestamp > m_max_x)
			m_max_x = data.m_timestamp;
		if (data.m_low < m_min_y)
			m_min_y = data.m_low;
		if (data.m_high > m_max_y)
			m_max_y = data.m_high;
	}
	m_range[0].push(m_min_x);
	m_range[1].push(m_max_x);
	m_range[2].push(m_min_y);
	m_range[3].push(m_max_y);
}
