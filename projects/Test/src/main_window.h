#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "ui_main_window.h"

class LinePlot;
class ScatterPlot;
class PiePlot;
class ProbabilityPlot;
class QQPlot;
class ParetoPlot;
class StockPlot;
class BarPlot;
class Table;
class RadialPlot;
class BoxBarPlot;
class IntervalPlot;
class ColorPlot;
class DensityPlot;
class RadarPlot;
class HistogramPlot;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

public slots:
	void slot_add_line();
	void slot_delete_line();
	void slot_draw_line();
	void slot_draw_arrows();
	void slot_vertical_splitter();
	void slot_horizontal_splitter();
	void slot_delete_splitter();
	void slot_add_label();

private:

	void init_chart();
private:
	Ui::MainWindow ui;
	LinePlot* line = nullptr;
	ScatterPlot* scatter = nullptr;
	PiePlot* pie = nullptr;
	ProbabilityPlot* probability = nullptr;
	QQPlot* qq = nullptr;
	ParetoPlot* pareto = nullptr;
	StockPlot* stock = nullptr;
	BarPlot* bar = nullptr;
	Table* table = nullptr;
	RadialPlot* radial = nullptr;
	BoxBarPlot* boxbar = nullptr;
	IntervalPlot* interval = nullptr;
	ColorPlot* color = nullptr;
	DensityPlot* density = nullptr;
	RadarPlot* radar = nullptr;
	HistogramPlot* histogram = nullptr;
};

#endif // MAIN_WINDOW_H