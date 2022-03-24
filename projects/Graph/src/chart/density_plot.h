#ifndef DENSITY_PLOT_H
#define DENSITY_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include "data.h"
#include <QScatterSeries>
#include <QValueAxis>

class ColorBar;

class GRAPH_EXPORT DensityPlot : public Plot
{
	Q_OBJECT

public:

	DensityPlot(QWidget* parent = nullptr);

	~DensityPlot();

public:

	void set_data(QList<QPointF>& pos_list);

	void clear_data();

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;

private:

	double squareDistance(DensityPoint a, DensityPoint b);

	void calculateDensity(QVector<DensityPoint>& dataset, float Eps);


private:
	/** 颜色条 */
	ColorBar* m_color_item = nullptr;
	/** X 轴 */
	QValueAxis* m_axisX = nullptr;
	/** Y 轴 */
	QValueAxis* m_axisY = nullptr;
	/** 密度值和散点 */
	QMap<int, QScatterSeries*> value2series;
	/** 密度半径 */
	double radius = 1;
};

#endif // DENSITY_PLOT_H