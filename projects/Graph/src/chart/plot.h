#ifndef PLOT_H
#define PLOT_H

#include "graph_global.h"
#include <QtCharts/QChart>
#include <QtCharts/QPolarChart>
#include <QtCharts/QLegendMarker>
#include <QBoxLayout>
#include <QWidget>

using  namespace QtCharts;

class ChartView;
class ToolTip;

class GRAPH_EXPORT Plot : public QWidget
{
	Q_OBJECT

public:

	Plot(bool IsPolar=false, QWidget *parent = nullptr);

	~Plot();

public slots:
	/** 鼠标提示 */
	virtual void slot_tool_tip(QPointF point, bool state);
	/** 图例点击 */
	void slot_handle_marker_clicked();

public:
	/** 图表标题 */
	void add_title(const QString& name);
	/** 连接图例 */
	void connect_markers();
	/** 取消图例连接 */
	void disconnect_markers();
	/** 开始画线 */
	void draw_line();
	/** 开始画箭头 */
	void draw_arrows();

protected:
	/** 初始化图表 */
	virtual void init_chart() = 0;
	/** 初始化坐标轴 */
	virtual void init_axis() = 0;
	/** 初始化系列 */
	virtual void init_series() = 0;

protected:
	virtual void resizeEvent(QResizeEvent* event) override;

protected:
	/** 图表 */
	QChart* m_chart = nullptr;
	/** 视图 */
	ChartView* m_chartview = nullptr;
	/** 鼠标提示 */
	ToolTip* m_tooltip = nullptr;
	/** X 最小值 */
	double m_min_x = DBL_MAX;
	/** X 最大值 */
	double m_max_x = DBL_MIN;
	/** Y 最小值 */
	double m_min_y = DBL_MAX;
	/** Y 最大值 */
	double m_max_y = DBL_MIN;
	/** Z 最小值 */
	double m_min_z = DBL_MAX;
	/** Z 最大值 */
	double m_max_z = DBL_MIN;
};

#endif // PLOT_H