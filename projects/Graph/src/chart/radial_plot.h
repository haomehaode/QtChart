#ifndef RADIAL_PLOT_H
#define RADIAL_PLOT_H

#include "plot.h"
#include "data.h"
#include "graph_global.h"
#include <QPieSlice>
#include <QPieSeries>

class GRAPH_EXPORT RadialPlot : public Plot
{
	struct RadialData
	{
		RadialData(QString name,double value, QPieSeries* pie) 
		{
			m_name = name;
			m_value = value;
			m_pie = pie;
		};
		QString m_name;
		double m_value;
		QPieSeries* m_pie;
	};

public:

	RadialPlot(QWidget* parent = nullptr);

	~RadialPlot();

public slots:
	/** 鼠标提示 */
	virtual void slot_tool_tip(QPieSlice* slice, bool state);

private:

	void update_location();

public:

	void set_data(QList<PieData>& valuelist);

	void add_pie(double value, const QString& name);

	void delete_pie(const QString& name);

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;

private:

	QList<RadialData> m_pie_series;

	QPieSeries* m_series = nullptr;
	/** 中心圆圈大小 */
	double m_radial_min = 0.25;
	/** 外围圆圈大小 */
	double m_radial_max = 0.85;
	/** 径向长度 */
	double m_radial_length = 0.6;

};

#endif // RADIAL_PLOT_H