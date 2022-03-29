#ifndef CHART_VIEW_PREVIEW_H
#define CHART_VIEW_PREVIEW_H

#include <QHash>
#include <QPointF>
#include <QLabel>

class ChartView;
class QMouseEvent;

/** 开始预览 */
#define BEGIN_PREVIEW -1

class ChartViewPreview 
{

public:

	virtual ~ChartViewPreview();
	/** 是否正在预览 */
	static bool is_previewing(ChartView* view);
	/** 完成并退出所有的绘制 */
	static void finish_all(ChartView* view);

	static void on_mouse_move(ChartView* view, QMouseEvent* event);

	static void on_mouse_release(ChartView* view, QMouseEvent* event);

public:
	/**
	* \brief 子类实现，绘制进度推进
	* @param point 鼠标在场景的坐标
	*/
	virtual void on_advance_preview(QPointF& point) {}
	/** 子类实现，完成图元绘制 */
	virtual void on_finish_preview() {}

protected:
	/** 设置数据,开始预览 */
	void begin_preview(ChartView* view);
	/**
	* \brief 子类实现，鼠标在所属的图形视图窗口移动
	* @param point 鼠标在场景的坐标
	*/
	virtual void on_mouse_move(QPointF& point) {}
	/** 获取预览步骤 */
	int step() const { return m_step; }
	/** 设置预览步骤 */
	void set_step(int step);

private:
	/** 完成绘制操作 */
	void finish_preview();
	/** 推进绘制进度 */
	void advance_preview(const QPoint& point);
	/** 鼠标在视图中移动 */
	void on_mouse_move(QMouseEvent* event);

protected:

	ChartView* m_view = nullptr;

private:
	//正在绘制的图元，key 视图， value 预览图元
	static QMap<ChartView*, ChartViewPreview*> s_view2preview;
	//已完成的步骤
	int m_step;
};

#endif // CHART_VIEW_PREVIEW_H