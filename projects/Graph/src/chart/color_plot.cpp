#pragma execution_character_set("utf-8")

#include "color_plot.h"
#include "color_bar.h"

ColorPlot::ColorPlot(QWidget *parent)
	: Plot(parent)
{
	init_series();
	init_chart();
	init_axis();
}

ColorPlot::~ColorPlot()
{

	//if (d_yColNameList.size() < 2)
	//	return;

	//widget = new QWidget;
	//colorMap = new QtColorMap(Qt::Vertical, widget);
	//colorMap->setRange(Qt::red, Qt::darkBlue);
	//colorMap->setFocusPolicy(Qt::TabFocus);

	//int xcol = d_table->colIndex(d_xColName);
	//Column* x_col_ptr = d_table->column(xcol);

	//int ycol = d_table->colIndex(d_yColNameList.at(0));
	//Column* y_col_ptr = d_table->column(ycol);

	//int zcol = d_table->colIndex(d_yColNameList.at(1));
	//Column* z_col_ptr = d_table->column(zcol);

	//QMap<double, QScatterSeries*> value2pos;    //点和值


	//double x_min = x_col_ptr->valueAt(d_start_row);
	//double x_max = x_col_ptr->valueAt(d_start_row);
	//double y_min = y_col_ptr->valueAt(d_start_row);
	//double y_max = y_col_ptr->valueAt(d_start_row);
	//double z_min = z_col_ptr->valueAt(d_start_row);
	//double z_max = z_col_ptr->valueAt(d_start_row);

	//for (int row = d_start_row; row <= d_end_row && row < x_col_ptr->rowCount(); row++)
	//{
	//	const double xi = x_col_ptr->valueAt(row);
	//	const double yi = y_col_ptr->valueAt(row);
	//	const double zi = z_col_ptr->valueAt(row);

	//	if (x_min > xi)
	//		x_min = xi;
	//	if (x_max < xi)
	//		x_max = xi;
	//	if (y_min > yi)
	//		y_min = yi;
	//	if (y_max < yi)
	//		y_max = yi;
	//	if (z_min > zi)
	//		z_min = zi;
	//	if (z_max < zi)
	//		z_max = zi;

	//	if (value2pos.contains(zi))
	//		value2pos[zi]->append(QPointF(xi, yi));
	//	else
	//	{
	//		QScatterSeries* scatter = new QScatterSeries;  //散点图
	//		scatter->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
	//		scatter->setMarkerSize(3.0);
	//		scatter->setBorderColor(Qt::transparent);
	//		scatter->append(QPointF(xi, yi));
	//		value2pos[zi] = scatter;
	//	}
	//}

	//colorMap->setMinMax(z_min, z_max);

	//QChart* chart = new QChart();
	//QValueAxis* axisX = new QValueAxis();
	//axisX->setRange(x_min, x_max);
	//// axisX->setTitleText(d_xColName);
	//chart->addAxis(axisX, Qt::AlignBottom);
	//QValueAxis* axisY = new QValueAxis();
	//axisY->setRange(y_min, y_max);
	////axisY->setTitleText(d_yColNameList[0]);
	//chart->addAxis(axisY, Qt::AlignLeft);

	//for (auto it = value2pos.begin(); it != value2pos.end(); ++it)
	//{
	//	chart->addSeries(it.value());
	//	it.value()->attachAxis(axisX);
	//	it.value()->attachAxis(axisY);
	//	it.value()->setBrush(colorMap->getColor(it.key()));
	//	it.value()->setUseOpenGL(true);
	//}

	//axisX->setGridLineVisible(false);   //隐藏背景网格X轴框线
	//axisY->setGridLineVisible(false);   //隐藏背景网格Y轴框线

	//chart->legend()->setVisible(false);

	//chart->layout()->setContentsMargins(0, 0, 0, 0);//设置外边界全部为0
	//chart->setMargins(QMargins(0, 0, 0, 0));//设置内边界全部为0
	//chart->setBackgroundRoundness(0);//设置背景区域无圆角
	//chartView = new QChartView(chart);

	//chartView->setRenderHint(QPainter::Antialiasing);
}

void ColorPlot::set_data(QList<ThirdDData>& value_list)
{
	for (auto& item : value_list)
	{
		if (m_min_x > item.m_x)
			m_min_x = item.m_x;
		if (m_max_x < item.m_x)
			m_max_x = item.m_x;
		if (m_min_y > item.m_y)
			m_min_y = item.m_y;
		if (m_max_y < item.m_y)
			m_max_y = item.m_y;
		if (m_min_z > item.m_z)
			m_min_z = item.m_z;
		if (m_max_z < item.m_z)
			m_max_z = item.m_z;

		if (value2series.contains(item.m_z))
			value2series[item.m_z]->append(QPointF(item.m_x, item.m_y));
		else
		{
			QScatterSeries* scatter = new QScatterSeries;  //散点图
			scatter->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
			scatter->setMarkerSize(3.0);
			scatter->setBorderColor(Qt::transparent);
			scatter->append(QPointF(item.m_x, item.m_y));
			value2series[item.m_z] = scatter;
		}
	}

	m_color_item->set_value_range(m_min_z, m_max_z);

	for (auto it = value2series.begin(); it != value2series.end(); ++it)
	{
		m_chart->addSeries(it.value());
		it.value()->attachAxis(m_axisX);
		it.value()->attachAxis(m_axisY);
		it.value()->setBrush(m_color_item->getColor(it.key()));
		it.value()->setUseOpenGL(true);
	}
}

void ColorPlot::clear_data()
{
	value2series.clear();
	m_chart->series().clear();
}

void ColorPlot::init_chart()
{
	m_chart->legend()->hide();

	m_color_item = new ColorBar();
	m_color_item->set_chart(m_chart);
	m_chartview->add_item(m_color_item);
}

void ColorPlot::init_axis()
{
	m_axisX = new QValueAxis();
	m_chart->addAxis(m_axisX, Qt::AlignBottom);
	m_axisX->setGridLineVisible(false);

	m_axisY = new QValueAxis();
	m_chart->addAxis(m_axisY, Qt::AlignLeft);
	m_axisY->setGridLineVisible(false);
}

void ColorPlot::init_series()
{
	value2series.clear();
}
