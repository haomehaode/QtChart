#ifndef BOXBAR_PLOT_H
#define BOXBAR_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include "data.h"
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QBoxPlotSeries>
#include <QBoxSet>

class GRAPH_EXPORT BoxBarPlot : public Plot
{
	Q_OBJECT

public:

	BoxBarPlot(QWidget* parent = nullptr);

	~BoxBarPlot();

	void set_type(BoxBarType type);

public:

	void set_data(QList<BoxData> &list);

	void add_boxbar(BoxData& data);

	void delete_boxbar(const QString& name);

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;

private:
	/** 名称和系列映射 */
	QMap<QString, QBoxSet*> m_name2series;
	/** X 轴 */
	QBarCategoryAxis* m_axisX = nullptr;
	/** Y 轴 */
	QValueAxis* m_axisY = nullptr;
	/** X 轴 */
	QStringList m_axisx_list;
	/** 条形图 */
	QBoxPlotSeries* m_series = nullptr;
	/** 绘画模式 */
	BoxBarType m_boxbartype = MEAN;

};

#endif // BOX_BAR_PLOT_H