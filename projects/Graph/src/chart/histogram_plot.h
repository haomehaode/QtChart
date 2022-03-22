#ifndef HISTOGRAM_PLOT_H
#define HISTOGRAM_PLOT_H

#include "plot.h"
#include "graph_global.h"

class GRAPH_EXPORT  HistogramPlot : public Plot
{
	Q_OBJECT

public:
	HistogramPlot(QWidget* parent = nullptr);

	~HistogramPlot();
};

#endif // HISTOGRAM_PLOT_H