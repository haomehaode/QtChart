#ifndef PIE_PLOT_H
#define PIE_PLOT_H

#include "graph_global.h"
#include "plot.h"
#include "data.h"
#include <QPieSlice>
#include <QPieSeries>


class GRAPH_EXPORT PiePlot : public Plot
{
	Q_OBJECT

public:

	PiePlot(QWidget* parent = nullptr);

	~PiePlot();

public slots:
	/** 鼠标提示 */
	virtual void slot_tool_tip(QPieSlice* slice, bool state);

public:

	void set_data(QList<PieData>& valuelist);

	void add_pie(double value, const QString& name);

	void delete_pie(const QString& name);

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;

private:

	void update_label();

private:
	/** 名称和系列映射 */
	QMap<QString, QPieSlice*> m_name2series;

	QPieSeries* m_series = nullptr;

};

#endif // PIE_PLOT_H