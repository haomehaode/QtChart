#ifndef BAR_PLOT_H
#define BAR_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include "data.h"
#include <QLineSeries>
#include <QValueAxis>
#include <QBarCategoryAxis>
#include <QStack>
#include <QtCharts/QBarSet>
#include <QBarSeries>

class GRAPH_EXPORT BarPlot : public Plot
{
	Q_OBJECT

public:

	BarPlot(QWidget* parent = nullptr);

	~BarPlot();

public:

	void set_axis(QList<QString> list);

	void add_bar(QList<double>& value_list, const QString& name);

	void delete_bar(const QString& name);

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;


private:
	/** 数据计算 */
	void prepare_data(QList<double>& value_list);

private:
	/** 名称和系列映射 */
	QMap<QString, QBarSet*> m_name2series;

	QBarSeries* m_series = nullptr;
	/** X 轴刻度集合 */
	QStringList m_axisx_list;
	/** X 轴 */
	QBarCategoryAxis* m_axisX =nullptr;
	/** Y 轴 */
	QValueAxis* m_axisY = nullptr;
	/** 记录坐标轴范围 */
	QStack<double> m_range[2];

};

#endif // BAR_PLOT_H