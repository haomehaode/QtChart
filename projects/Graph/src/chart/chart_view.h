#ifndef CHART_VIEW_H
#define CHART_VIEW_H

#include "graph_global.h"
#include "graphics_item.h"

#include <QtCharts/QChart>
#include <QtCharts/QChartView>


using namespace QtCharts;

class GRAPH_EXPORT ChartView : public  QGraphicsView
{
	Q_OBJECT

public:

	ChartView(QChart* chart, QWidget* parent = nullptr);

public:
	/** 重绘场景 */
	void redraw();
	/** \brief 保存图片*/
	bool save_picture(const QString& filename, const QSize& size = QSize(3050, 2050));
	/** 返回视图的widget */
	QWidget* widget();
	/** 智能设置视图的光标 */
	void set_cursor_auto();
	/** 将视图坐标转换到场景坐标 */
	QPointF map_to_scene(const QPoint& pos);
	/** 将场景坐标转换到视图坐标 */
	QPoint map_from_scene(const QPointF& pos);
	/** 将视图坐标转换到屏幕坐标 */
	QPoint map_to_global(const QPoint& pos);
	/** 添加图元 */
	void add_item(GraphicsItem* item);
	/** 删除图元 */
	void delete_item(GraphicsItem* item);
	/** 正在绘图 */
	bool is_previewing();

public slots:

	void slot_chart_config();

	void slot_series_config();

	void slot_axis_config();

protected:

	virtual void resizeEvent(QResizeEvent* event) override;

	virtual	void mousePressEvent(QMouseEvent* event) override;

	virtual void mouseMoveEvent(QMouseEvent* event) override;

	virtual void mouseReleaseEvent(QMouseEvent* event) override;

	virtual void keyPressEvent(QKeyEvent* event) override;

	virtual void wheelEvent(QWheelEvent* event) override;

	virtual void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
	/** 图表 */
	QChart* m_chart = nullptr;
	/** 框选开始点 */
	QPoint m_begin_point;
	/** 框选结束点 */
	QPoint m_end_point;
	/** 拖拽点 */
	QPoint m_old_point;
	/** 是否拖拽 */
	bool m_isTranslate = false;
	/** 拖拽记录*/
	QPointF m_translate_pos;
};

#endif // CHART_VIEW_H