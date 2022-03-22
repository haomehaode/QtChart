#ifndef COLOR_PLOT_H
#define COLOR_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include "data.h"

class GRAPH_EXPORT ColorPlot : public Plot
{
	Q_OBJECT

public:

	ColorPlot(QWidget* parent = nullptr);

	~ColorPlot();

public:

	void set_data(QList<ThirdDData>& value_list);

	void clear_data();

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;
};

#endif // COLOR_PLOT_H