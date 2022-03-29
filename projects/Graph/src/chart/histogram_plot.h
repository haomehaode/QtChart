#ifndef HISTOGRAM_PLOT_H
#define HISTOGRAM_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include "graphics_item.h"
#include <QValueAxis>
#include <QScatterSeries>

//////////////////////////////////////////////////////////////////////////////
/// 直方图
class HistogramItem :public GraphicsItem
{
	Q_OBJECT

public:
	HistogramItem();
	void set_chart(QChart* chart);
	void set_data(QVector<double> data);
	void set_index(int index);

signals:
	void signal_prepare_path() const;

public slots:
	void slot_prepare_path();

protected:
	QRectF boundingRect() const override;
	void on_paint(QPainter* painter) override;

private:
	QChart* m_chart = nullptr;
	QVector<double> m_data;
	int m_index = 0;
	QPainterPath m_shape;
};

struct Histogram
{
	int m_index;
	QList<HistogramItem*> m_list;
	QList<double> m_value;
	QScatterSeries* m_series = nullptr;
};

class GRAPH_EXPORT  HistogramPlot : public Plot
{
	Q_OBJECT

public:

	HistogramPlot(QWidget* parent = nullptr);

	~HistogramPlot();

	void add_histogram(QList<double>& value_list, const QString& name);

	void delete_histogram(const QString& name);

protected:

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;

	QList<QVector<double>> prepare_data(QList<double>& list);


private:
	/** 名称和系列映射 */
	QMap<QString, Histogram*> m_name2itemlist;
	/** X 轴 */
	QValueAxis* m_axisX = nullptr;
	/** Y 轴 */
	QValueAxis* m_axisY = nullptr;
	/** 间距 */
	double m_interval = 2;
	/** 总数 */
	int m_count = 0;
};

#endif // HISTOGRAM_PLOT_H