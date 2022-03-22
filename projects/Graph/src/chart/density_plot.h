#ifndef DENSITY_PLOT_H
#define DENSITY_PLOT_H

#include "plot.h"
#include "graph_global.h"

class GRAPH_EXPORT DensityPlot : public Plot
{
	Q_OBJECT

public:
	DensityPlot(QWidget *parent);
	~DensityPlot();
};

#endif // DENSITY_PLOT_H