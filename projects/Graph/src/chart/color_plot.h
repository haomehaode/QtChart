#ifndef COLOR_PLOT_H
#define COLOR_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include "data.h"
#include <QScatterSeries>
#include <QValueAxis>

class ColorBar;

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

private:
	/** 颜色条 */
	ColorBar* m_color_item = nullptr;
	/** X 轴 */
	QValueAxis* m_axisX = nullptr;
	/** Y 轴 */
	QValueAxis* m_axisY = nullptr;
	/** Z 值和散点 */
	QMap<double, QScatterSeries*> value2series; 
};

#endif // COLOR_PLOT_H