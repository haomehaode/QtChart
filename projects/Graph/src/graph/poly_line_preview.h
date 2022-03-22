#ifndef POLYLINE_PREVIEW_H
#define POLYLINE_PREVIEW_H

#include "chart_view_preview.h"

class PolyLine;
class ChartView;

//多段线预览类
class PolyLinePreview : public ChartViewPreview
{
public:
	PolyLinePreview(ChartView* view);

protected:
	/**
	* \brief 绘制进度推进
	* @param point 鼠标在场景的坐标
	*/
	void on_advance_preview(QPointF& point) override;

	/** 完成图元绘制 */
	void on_finish_preview() override;

	/** 鼠标在图元所在的图形视图窗口中移动 */
	void on_mouse_move(QPointF& point) override;

	virtual PolyLine* new_polyline();

private:
	/**
	* \brief 完成步骤操作
	* @param step 步骤
	* @param point 鼠标在场景的位置
	*/
	void confirm_step(int step, QPointF& point);

protected:
	enum StepType
	{
		START_POINT,		//第一个点
		NEXT_POINT			//后续的点
	};

	PolyLine* m_pPolyLine = nullptr;
	QPointF m_last_confirm_point;
};

///////////////////////////////////////////////////////////////////////////////
//箭头线预览类
class ArrowsPreview : public PolyLinePreview
{

public:

	ArrowsPreview(ChartView* view);

private:

	PolyLine* new_polyline() override;
};


#endif  //!POLYLINE_PREVIEW_H


