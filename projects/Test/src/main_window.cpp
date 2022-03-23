#pragma execution_character_set("utf-8")

#include "main_window.h"
#include "line_plot.h"
#include "qmath.h"
#include "qrandom.h"
#include "scatter_plot.h"
#include "pie_plot.h"
#include "probability_plot.h"
#include "qq_plot.h"
#include "pareto_plot.h"
#include "stock_plot.h"
#include "bar_plot.h"
#include "Table.h"
#include "radial_plot.h"
#include "boxbar_plot.h"
#include "interval_plot.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	init_chart();
}

MainWindow::~MainWindow()
{
}

void MainWindow::slot_add_line()
{
	QList<QPointF> list;
	for (int i = 0; i < 500; i++) {
		QPointF p((qreal)i, qCos(M_PI / 50 * i) * 100);
		p.ry() += QRandomGenerator::global()->bounded(20);
		list.append(p);
	}
	line->add_line(list, "2");
	scatter->add_scatter(list, "2");
	pie->add_pie(45, "2");

	QList<CandlestickData> data_list
	{
		CandlestickData(1435708800000, 26.90, 26.94, 25.99, 26.60),
		CandlestickData(1435795200000, 26.69, 26.69, 26.69, 26.69),
		CandlestickData(1436140800000, 24.85, 26.23, 24.85, 26.00),
		CandlestickData(1436227200000, 25.89, 26.15, 23.77, 25.69),
		CandlestickData(1436313600000, 24.64, 24.64, 22.54, 22.54),
		CandlestickData(1436400000000, 23.85, 24.06, 19.22, 20.07),
		CandlestickData(1436486400000, 21.94, 23.85, 21.21, 23.28),
		CandlestickData(1436745600000, 25.03, 25.76, 24.32, 25.66),
		CandlestickData(1436832000000, 26.04, 26.37, 25.04, 25.61),
		CandlestickData(1436918400000, 25.72, 27.15, 25.58, 26.82),
		CandlestickData(1437004800000, 27.74, 28.57, 27.35, 28.51),
		CandlestickData(1437091200000, 29.08, 29.62, 28.31, 29.62),
		CandlestickData(1437436800000, 32.85, 32.92, 30.32, 30.75),
		CandlestickData(1437523200000, 21.99, 25.50, 21.99, 25.22),
		CandlestickData(1437609600000, 26.20, 27.09, 25.06, 25.16),
		CandlestickData(1437696000000, 25.32, 25.74, 23.90, 24.50),
		CandlestickData(1437955200000, 23.09, 23.61, 22.12, 22.77),
		CandlestickData(1438041600000, 23.38, 23.91, 22.55, 23.38),
		CandlestickData(1438128000000, 23.15, 23.50, 22.27, 22.99),
		CandlestickData(1438214400000, 22.32, 22.57, 21.71, 22.37),
		CandlestickData(1438300800000, 22.60, 22.64, 20.91, 21.30)
	};
	stock->add_stock(data_list, "2");

	QList<double> bar_list{ 11,4,35,8,49,15 };
	bar->add_bar(bar_list, "2");

	table->add_data(bar_list, "2");
}

void MainWindow::slot_delete_line()
{
	//line->delete_line("1");
	//bar->delete_bar("1");

	//table->delete_data("2");
	//interval->delete_scatter("1");
	pareto->clear_data();
}

void MainWindow::slot_draw_line()
{
	line->draw_line();
}

void MainWindow::slot_draw_arrows()
{
	line->draw_arrows();
}

void MainWindow::init_chart()
{
	line = new LinePlot();
	QList<QPointF> linelist;
	for (int i = 0; i < 500; i++) {
		QPointF p((qreal)i, qSin(M_PI / 50 * i) * 10);
		p.ry() += QRandomGenerator::global()->bounded(20);
		linelist.append(p);
	}
	line->add_line(linelist, "1");

	scatter = new ScatterPlot();
	QList<QPointF> scatterlist;
	for (int i = 0; i < 500; i++) {
		QPointF p((qreal)i, qSin(M_PI / 50 * i) * 100);
		p.ry() += QRandomGenerator::global()->bounded(20);
		scatterlist.append(p);
	}
	scatter->add_scatter(scatterlist, "1");

	pie = new PiePlot();
	QList<PieData> pie_list
	{
		PieData("一月",4),
		PieData("二月",6),
		PieData("三月",0.5),
		PieData("四月",2.6),
		PieData("五月",8)
	};
	pie->set_data(pie_list);

	probability = new ProbabilityPlot();
	QList<double> probabilitylist{ 11,15,27,55,46,29,35,18,42 };
	probability->add_data(probabilitylist, "1");

	qq = new QQPlot();
	QList<double> qqlist{ 11,15,27,55,46,29,35,18,42 };
	qq->add_data(qqlist, "1");

	pareto = new ParetoPlot();
	QList<QPointF> paretolist{ QPointF(1,35),QPointF(2,5) ,QPointF(3,21) ,QPointF(4,9) ,QPointF(5,10) ,QPointF(6,17),QPointF(7,3) };
	pareto->set_data(paretolist, "1");

	stock = new StockPlot();
	QList<CandlestickData> data_list
	{
		CandlestickData(1435708800000, 126.90, 126.94, 125.99, 126.60),
		CandlestickData(1435795200000, 126.69, 126.69, 126.69, 126.69),
		CandlestickData(1436140800000, 124.85, 126.23, 124.85, 126.00),
		CandlestickData(1436227200000, 125.89, 126.15, 123.77, 125.69),
		CandlestickData(1436313600000, 124.64, 124.64, 122.54, 122.54),
		CandlestickData(1436400000000, 123.85, 124.06, 119.22, 120.07),
		CandlestickData(1436486400000, 121.94, 123.85, 121.21, 123.28),
		CandlestickData(1436745600000, 125.03, 125.76, 124.32, 125.66),
		CandlestickData(1436832000000, 126.04, 126.37, 125.04, 125.61),
		CandlestickData(1436918400000, 125.72, 127.15, 125.58, 126.82),
		CandlestickData(1437004800000, 127.74, 128.57, 127.35, 128.51),
		CandlestickData(1437091200000, 129.08, 129.62, 128.31, 129.62),
		CandlestickData(1437436800000, 132.85, 132.92, 130.32, 130.75),
		CandlestickData(1437523200000, 121.99, 125.50, 121.99, 125.22),
		CandlestickData(1437609600000, 126.20, 127.09, 125.06, 125.16),
		CandlestickData(1437696000000, 125.32, 125.74, 123.90, 124.50),
		CandlestickData(1437955200000, 123.09, 123.61, 122.12, 122.77),
		CandlestickData(1438041600000, 123.38, 123.91, 122.55, 123.38),
		CandlestickData(1438128000000, 123.15, 123.50, 122.27, 122.99),
		CandlestickData(1438214400000, 122.32, 122.57, 121.71, 122.37),
		CandlestickData(1438300800000, 122.60, 122.64, 120.91, 121.30)
	};
	stock->add_stock(data_list, "1");

	bar = new BarPlot();
	QList<QString> axis_list{ "一月","二月","三月","四月","五月","六月" };
	bar->set_axis(axis_list);
	QList<double> bar_list{ 1,24,5,7,9,10 };
	bar->add_bar(bar_list, "1");

	table = new Table();
	table->add_data(qqlist, "1");

	radial = new RadialPlot();
	QList<PieData> radial_list
	{
		PieData("一月",4),
		PieData("二月",6),
		PieData("三月",0.5),
		PieData("四月",2.6),
		PieData("五月",8),
		PieData("六月",18),
		//PieData("七月",38),
		//PieData("八月",48),
		//PieData("九月",58),
		//PieData("十月",68),
		//PieData("十一月",78),
		//PieData("十二月",88)

	};
	radial->set_data(radial_list);

	boxbar = new BoxBarPlot();
	BoxData box1;
	box1.m_name = "Jan";
	box1.m_value_list = QList<double>{ 27.74, 27.28, 27.86, 28.05, 28.64, 27.47, 43.67 };
	BoxData box2;
	box2.m_name = "Feb";
	box2.m_value_list = QList<double>{ 19.48, 19.70, 19.94, 19.82, 20.25, 20.21, 19.63 };
	BoxData box3;
	box3.m_name = "Mar";
	box3.m_value_list = QList<double>{ 20.13, 19.74, 19.27, 18.25, 17.72, 18.02, 18.20 };
	BoxData box4;
	box4.m_name = "Apr";
	box4.m_value_list = QList<double>{ 32.51, 32.69, 31.83, 32.47, 31.41, 31.39, 31.78 };
	BoxData box5;
	box5.m_name = "May";
	box5.m_value_list = QList<double>{ 17.17, 16.95, 18.25, 20.52, 20.61, 21.40, 20.45 };
	QList<BoxData> boxdatalist{ box1,box2,box3,box4,box5 };
	boxbar->set_data(boxdatalist);

	interval = new IntervalPlot();
	BoxData interval1;
	interval1.m_name = "Jan";
	interval1.m_value_list = QList<double>{ 2, 27, 7, 8, 18, 27, 23};
	BoxData interval2;
	interval2.m_name = "Feb";
	interval2.m_value_list = QList<double>{ 1, 9, 11, 29, 20, 20, 19};
	BoxData interval3;
	interval3.m_name = "Mar";
	interval3.m_value_list = QList<double>{ 10, 19, 19, 8, 17, 18, 8};
	BoxData interval4;
	interval4.m_name = "Apr";
	interval4.m_value_list = QList<double>{ 32, 2, 31, 2, 31, 1, 31};
	BoxData interval5;
	interval5.m_name = "May";
	interval5.m_value_list = QList<double>{ 17, 6, 18, 3, 20, 21, 20};
	QList<BoxData> intervaldatalist{ interval1,interval2,interval3,interval4,interval5 };
	interval->set_data(intervaldatalist);

	QWidget* w = new QWidget(this);
	QGridLayout* layout = new QGridLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);
	layout->addWidget(line, 0, 0);
	layout->addWidget(scatter, 0, 1);
	layout->addWidget(probability, 0, 2);
	layout->addWidget(pareto, 0, 3);
	layout->addWidget(pie, 1, 0);
	layout->addWidget(qq, 1, 1);
	layout->addWidget(stock, 1, 2);
	layout->addWidget(bar, 1, 3);
	layout->addWidget(table, 2, 0);
	layout->addWidget(radial, 2, 1);
	layout->addWidget(boxbar, 2, 2);
	layout->addWidget(interval, 2, 3);
	w->setLayout(layout);
	setCentralWidget(w);
}
