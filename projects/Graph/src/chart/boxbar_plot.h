#ifndef BOXBAR_PLOT_H
#define BOXBAR_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include "data.h"
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QStackedBarSeries>
#include <QBarSet>
#include "graphics_item.h"


//////////////////////////////////////////////////////////////////////////////
/// 条形图
class BoxBarItem :public GraphicsItem
{
	Q_OBJECT

public:
	BoxBarItem();
	void set_chart(QChart* chart);
	void set_data(double mean, double sum, double min, double max, int index);

signals:
	void signal_prepare_path() const;

public slots:
	void slot_prepare_path();

protected:
	QRectF boundingRect() const override;
	void on_paint(QPainter* painter) override;

private:
	QChart* m_chart = nullptr;
	QPointF	m_min;
	QPointF	m_max;
	QPointF	m_mean;
	QPointF	m_sum;
	QPainterPath m_shape;
};


class GRAPH_EXPORT BoxBarPlot : public Plot
{
	Q_OBJECT

public:

	BoxBarPlot(QWidget* parent = nullptr);

	~BoxBarPlot();

	void set_type(BoxBarType type);

public:

	void set_data(QList<BoxData> &list);

	void add_boxbar(BoxData& data, int size, int index);

	void delete_boxbar(const QString& name);

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;

private:
	/** 名称和系列映射 */
	QMap<QString, QBarSet*> m_name2series;
	/** 名称和条形图映射 */
	QMap<QString,BoxBarItem*> m_name2item;
	/** X 轴 */
	QBarCategoryAxis* m_axisX = nullptr;
	/** Y 轴 */
	QValueAxis* m_axisY = nullptr;
	/** X 轴 */
	QStringList m_axisx_list;
	/** 条形图 */
	QStackedBarSeries* m_series = nullptr;
	/** 绘画模式 */
	BoxBarType m_boxbartype = MEAN;

};

#endif // BOX_BAR_PLOT_H