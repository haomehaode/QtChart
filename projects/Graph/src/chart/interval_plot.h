#ifndef INTERVAL_PLOT_H
#define INTERVAL_PLOT_H

#include "plot.h"
#include "data.h"
#include "graph_global.h"
#include "graphics_item.h"
#include <QScatterSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QStack>

//////////////////////////////////////////////////////////////////////////////
/// 间隔图
class IntervalItem :public GraphicsItem 
{
	Q_OBJECT

public:
	IntervalItem();
	void set_chart(QChart* chart);
	void set_data(BoxData& data, int index);
	double get_max();
	double get_min();

signals:
	void signal_prepare_path() const;

public slots:
	void slot_prepare_path();

protected:
	QRectF boundingRect() const override;
	void on_paint(QPainter* painter) override;

private:
	QChart* m_chart = nullptr;
	QList<double> m_list;
	QString	m_name;
	QPointF	m_min ;
	QPointF	m_max ;
	QPointF	m_mean;
	QPointF	m_sum ;
	QPainterPath m_shape;
};

class GRAPH_EXPORT IntervalPlot : public Plot
{
	Q_OBJECT

public:

	IntervalPlot(QWidget* parent = nullptr);

	~IntervalPlot();

public:

	void set_data(QList<BoxData>& list);

	void add_interval(BoxData& data, int index, double& y_min, double& y_max);

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;

private:
	/** 名称和系列映射 */
	QMap<QString, GraphicsItem*> m_name2item;
	/** X 轴 */
	QBarCategoryAxis* m_axisX = nullptr;
	/** X 轴刻度 */
	QStringList m_axisx_list;
	/** Y 轴 */
	QValueAxis* m_axisY = nullptr;
	/** 记录坐标轴范围 */
	QStack<double> m_range[4];
	/** 参考点 */
	QScatterSeries* m_series = nullptr;
};

#endif // INTERVAL_PLOT_H