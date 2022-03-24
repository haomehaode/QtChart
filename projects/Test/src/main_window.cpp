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
#include "color_plot.h"
#include "density_plot.h"

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
	interval1.m_value_list = QList<double>{ 2, 27, 7, 8, 18, 27, 23 };
	BoxData interval2;
	interval2.m_name = "Feb";
	interval2.m_value_list = QList<double>{ 1, 9, 11, 29, 20, 20, 19 };
	BoxData interval3;
	interval3.m_name = "Mar";
	interval3.m_value_list = QList<double>{ 10, 19, 19, 8, 17, 18, 8 };
	BoxData interval4;
	interval4.m_name = "Apr";
	interval4.m_value_list = QList<double>{ 32, 2, 31, 2, 31, 1, 31 };
	BoxData interval5;
	interval5.m_name = "May";
	interval5.m_value_list = QList<double>{ 17, 6, 18, 3, 20, 21, 20 };
	QList<BoxData> intervaldatalist{ interval1,interval2,interval3,interval4,interval5 };
	interval->set_data(intervaldatalist);

	color = new ColorPlot();
	QList<ThirdDData> color_list{

ThirdDData(7.1908	,1.371	,8.35),
ThirdDData(3.3199	,9.5596	,4.77),
ThirdDData(6.6349	,2.802	,9.29),
ThirdDData(7.4314	,2.7183	,4.13),
ThirdDData(6.7846	,3.6523	,6.74),
ThirdDData(5.3984	,4.6723	,3.21),
ThirdDData(8.5625	,2.1835	,6.38),
ThirdDData(1.0853	,1.2124	,3.8),
ThirdDData(9.4728	,3.9189	,3.57),
ThirdDData(5.5756	,8.3325	,5.36),
ThirdDData(4.2799	,8.475	,7.17),
ThirdDData(8.909	,8.6787	,3.68),
ThirdDData(6.5997	,5.3281	,1.91),
ThirdDData(5.2863	,5.495	,4.96),
ThirdDData(5.4844	,3.8975	,3.43),
ThirdDData(1.9507	,8.5468	,6.16),
ThirdDData(7.4732	,5.7603	,9.43),
ThirdDData(4.2143	,7.0386	,5.45),
ThirdDData(4.5841	,9.3584	,3.08),
ThirdDData(6.3912	,5.2463	,2.53),
ThirdDData(3.9729	,2.2913	,4.07),
ThirdDData(8.7678	,5.2947	,2.68),
ThirdDData(1.4079	,7.0609	,2.97),
ThirdDData(9.659	,6.9622	,6.85),
ThirdDData(4.0624	,8.2727	,6.97),
ThirdDData(5.2148	,3.892	,5.67),
ThirdDData(2.938	,3.476	,4.05),
ThirdDData(8.5964	,4.5718	,1.44),
ThirdDData(7.2144	,2.8656	,1.1),
ThirdDData(9.7124	,5.5643	,2.02),
ThirdDData(5.0421	,1.3184	,9.07),
ThirdDData(4.4336	,5.6822	,3.17),
ThirdDData(3.0745	,8.6957	,6.67),
ThirdDData(7.4707	,7.7891	,5.55),
ThirdDData(5.6016	,2.7527	,2.56),
ThirdDData(1.2459	,4.5429	,5.98),
ThirdDData(8.7453	,7.4326	,5.88),
ThirdDData(6.6394	,1.2535	,4.96),
ThirdDData(4.7364	,4.3589	,1.02),
ThirdDData(9.5998	,1.6505	,2.99),
ThirdDData(5.2584	,7.3137	,8.77),
ThirdDData(4.8707	,2.2501	,5.48),
ThirdDData(1.5872	,2.9534	,6.99),
ThirdDData(2.4531	,9.8417	,2.87),
ThirdDData(1.7778	,1.26	,2.62),
ThirdDData(9.5608	,2.5392	,4.31),
ThirdDData(4.0159	,2.4654	,2.36),
ThirdDData(3.5658	,7.8506	,3.59),
ThirdDData(3.1082	,8.0051	,7.34),
ThirdDData(8.8486	,4.9119	,2.93),
ThirdDData(3.2443	,9.6056	,4.59),
ThirdDData(6.8583	,9.4868	,4.63),
ThirdDData(4.734	,3.8559	,2.4),
ThirdDData(7.1793	,6.6535	,7.6),
ThirdDData(4.4682	,8.6705	,3.45),
ThirdDData(3.5651	,3.3115	,3.13),
ThirdDData(2.1501	,6.0707	,6.88),
ThirdDData(7.4924	,2.7056	,7.06),
ThirdDData(5.5233	,1.9889	,3.38),
ThirdDData(4.8493	,5.269	,6.55),
ThirdDData(8.7686	,8.1083	,8.9),
ThirdDData(4.9266	,6.7548	,8.15),
ThirdDData(4.7555	,3.9511	,5.01),
ThirdDData(4.4882	,8.5719	,5.84),
ThirdDData(5.7458	,9.6899	,8.71),
ThirdDData(4.7992	,2.2714	,9.53),
ThirdDData(7.5479	,4.0813	,7.4),
ThirdDData(7.5935	,1.3604	,7.13),
ThirdDData(7.1035	,3.5131	,9.36),
ThirdDData(5.7367	,5.5905	,4.5),
ThirdDData(4.5456	,5.6897	,8.24),
ThirdDData(5.0419	,1.1654	,9.96),
ThirdDData(1.5481	,4.8748	,9.95),
ThirdDData(4.6068	,9.9738	,1.99),
ThirdDData(1.4562	,5.9872	,6.26),
ThirdDData(9.2189	,3.3425	,6.13),
ThirdDData(8.8734	,9.7743	,1.34),
ThirdDData(9.7336	,1.9286	,7.65),
ThirdDData(9.5662	,7.9747	,8.76),
ThirdDData(2.2144	,7.0877	,8.11),
ThirdDData(8.9582	,8.4553	,3.15),
ThirdDData(1.1927	,2.5109	,2.95),
ThirdDData(8.0102	,5.8046	,7.3),
ThirdDData(4.2547	,8.4029	,9.66),
ThirdDData(3.8141	,8.0253	,5.94),
ThirdDData(2.2334	,6.1691	,3.73),
ThirdDData(5.1633	,3.4316	,3.98),
ThirdDData(2.9822	,5.0633	,9.15),
ThirdDData(6.8467	,6.0755	,7.37),
ThirdDData(6.4997	,2.2398	,5.49),
ThirdDData(6.569	,7.7273	,5.74),
ThirdDData(4.3138	,6.1526	,8.23),
ThirdDData(8.2114	,3.4949	,4.78),
ThirdDData(7.8527	,4.7712	,4.74),
ThirdDData(3.3897	,9.2995	,2.27),
ThirdDData(5.0169	,1.1223	,8.81),
ThirdDData(8.4492	,6.3313	,6.31),
ThirdDData(4.7655	,2.0641	,6.54),
ThirdDData(2.647	,6.5189	,8.05),
ThirdDData(3.1885, 8.0106, 9.62) 
};
	color->set_data(color_list);

	density = new DensityPlot();
	QList<QPointF> densitylist;
	for (int i = 0; i <100; i++) {
		double x = qrand() % 10;
		double y = qrand() % 10;
		QPointF p(x,y);
		densitylist.append(p);
	}
	density->set_data(densitylist);

	QWidget* w = new QWidget(this);
	QGridLayout* layout = new QGridLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);
	//layout->addWidget(line, 0, 0);
	//layout->addWidget(scatter, 0, 1);
	//layout->addWidget(probability, 0, 2);
	//layout->addWidget(pareto, 0, 3);
	//layout->addWidget(pie, 1, 0);
	//layout->addWidget(qq, 1, 1);
	//layout->addWidget(stock, 1, 2);
	//layout->addWidget(bar, 1, 3);
	//layout->addWidget(table, 2, 0);
	//layout->addWidget(radial, 2, 1);
	//layout->addWidget(boxbar, 2, 2);
	//layout->addWidget(interval, 2, 3);
	//layout->addWidget(color, 3, 0);
	layout->addWidget(density, 3, 1);
	w->setLayout(layout);
	setCentralWidget(w);
}
