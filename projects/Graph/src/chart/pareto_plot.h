#ifndef PARETO_PLOT_H
#define PARETO_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include <QLineSeries>
#include <QValueAxis>
#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QBarSet>
#include <QScatterSeries>

class GRAPH_EXPORT ParetoPlot : public Plot
{
	Q_OBJECT

public:

	ParetoPlot(QWidget *parent=nullptr);

	~ParetoPlot();

public:

	void set_data(QList<QPointF>& vallist, const QString& name);

	void clear_data();

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;

private:
	/** Êý¾Ý¼ÆËã */
	void prepare_data(QList<QPointF>& poslist);

private:

	QBarCategoryAxis* m_axisX = nullptr;

	QValueAxis* m_axisY_1 = nullptr;

	QValueAxis* m_axisY_2 = nullptr;

	QBarSeries* m_bar = nullptr;

	QBarSet* m_set = nullptr;

	QLineSeries* m_line = nullptr;

	QScatterSeries* m_scatter = nullptr; 

	QStringList m_axisy_list;
};

#endif // PARETO_PLOT_H