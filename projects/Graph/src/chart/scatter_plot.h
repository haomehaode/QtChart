#ifndef SCATTER_PLOT_H 
#define SCATTER_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include <QScatterSeries>
#include <QValueAxis>
#include <QStack>

class GRAPH_EXPORT ScatterPlot: public Plot
{

public:

	ScatterPlot(QWidget* parent = Q_NULLPTR);

	~ScatterPlot();

public:

	void add_scatter(QList<QPointF>& poslist, const QString& name);

	void delete_scatter(const QString& name);

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;

private:
	/** 数据计算 */
	void prepare_data(QList<QPointF>& poslist);

private:
	/** 名称和系列映射 */
	QMap<QString, QScatterSeries*> m_name2series;
	/** X 轴 */
	QValueAxis* m_axisX = nullptr;
	/** Y 轴 */
	QValueAxis* m_axisY = nullptr;
	/** 记录坐标轴范围 */
	QStack<double> m_range[4];
};

#endif // SCATTER_PLOT_H