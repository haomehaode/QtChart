#ifndef WATERFALL_PLOT_H
#define WATERFALL_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include "data.h"
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QBarSeries>
#include <QBarSet>
#include "graphics_item.h"

//////////////////////////////////////////////////////////////////////////////
/// 瀑布图
class WaterfallItem :public GraphicsItem
{
	Q_OBJECT

public:
	WaterfallItem();
	void set_chart(QChart* chart);
	void set_data(QList<QPointF> data);
	void set_series(QBarSet* series);

signals:
	void signal_prepare_path() const;

public slots:
	void slot_prepare_path();

protected:
	QRectF boundingRect() const override;
	void on_paint(QPainter* painter) override;

private:
	QChart* m_chart = nullptr;
	QList<QPointF> m_data;
	QBarSet* m_series = nullptr;
	QPainterPath m_shape;
};

class GRAPH_EXPORT WaterfallPlot : public Plot
{
	Q_OBJECT

public:

	WaterfallPlot(QWidget *parent = nullptr);

	~WaterfallPlot();

public:

	void set_data(QList<PieData>& value_list);

	void clear_data();

protected:

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;

	void init_item();

private:
	/** 名称和系列映射 */
	//QMap<QString, Histogram*> m_name2itemlist;
	/** X 轴 */
	QBarCategoryAxis* m_axisX = nullptr;
	/** Y 轴 */
	QValueAxis* m_axisY = nullptr;
	/** Y 轴刻度 */
	QStringList m_axis_list;

	QBarSeries* m_bar = nullptr;

	QBarSet* m_bar_start = nullptr;

	QBarSet* m_bar_end = nullptr;

	QBarSet* m_bar_add = nullptr;

	QBarSet* m_bar_low = nullptr;

	WaterfallItem* m_item_start = nullptr;

	WaterfallItem* m_item_end = nullptr;

	WaterfallItem* m_item_add = nullptr;

	WaterfallItem* m_item_low = nullptr;

	/** 起始值 */
	double start_value = 0;
};

#endif // WATERFALL_PLOT_H