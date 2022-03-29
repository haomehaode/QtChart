#ifndef QQ_PLOT_H
#define QQ_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include <QValueAxis>
#include <QCategoryAxis>
#include <QLineSeries>
#include <QScatterSeries>
#include "data.h"

class GRAPH_EXPORT  QQPlot : public Plot
{
	Q_OBJECT

public:

	QQPlot(QWidget* parent = nullptr);

	~QQPlot();

public slots:

	void slot_tool_tip(QPointF point, bool state) override;

public:

	void add_data(QList<double>& list, const QString& name);

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;

private:
	/** 数据计算 */
	void prepare_data(QList<double>& list);
	/** 理论CDF */
	double calculate_cdf(int index, int n);

private:
	/** 平均值 */
	double m_mean;
	/** 方差 */
	double m_variance;
	/** 标准差 */
	double m_sigma;
	/** 样本数 */
	int m_n;

private:

	QLineSeries* m_line_center = nullptr;

	QLineSeries* m_line_top = nullptr;

	QLineSeries* m_line_bottom = nullptr;

	QScatterSeries* m_scatter = nullptr;

	QValueAxis* m_axisX = nullptr;

	QValueAxis* m_axisY = nullptr;

	QList<Probability> m_probability_list;

	ScoreType m_score_type = Benard;
};

#endif // QQ_PLOT_H