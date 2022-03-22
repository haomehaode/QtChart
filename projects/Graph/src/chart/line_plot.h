#ifndef LINE_PLOT_H
#define LINE_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include <QLineSeries>
#include <QValueAxis>
#include <QStack>

class GRAPH_EXPORT LinePlot : public Plot
{

public:

	LinePlot(QWidget *parent = Q_NULLPTR);

	~LinePlot();

public:

	void add_line(QList<QPointF>& poslist, const QString &name );

	void delete_line(const QString& name);

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;


private:
	/** 数据计算 */
	void prepare_data(QList<QPointF>& poslist);

private:
	/** 名称和系列映射 */
	QMap<QString, QLineSeries*> m_name2series;
	/** X 轴 */
	QValueAxis* m_axisX = nullptr;
	/** Y 轴 */
	QValueAxis* m_axisY = nullptr;
	/** 记录坐标轴范围 */
	QStack<double> m_range[4];
};

#endif // LINE_PLOT_H