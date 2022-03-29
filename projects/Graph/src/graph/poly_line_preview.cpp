#pragma execution_character_set("utf-8")

#include "poly_line_preview.h"

#include "util.h"
#include "chart_view.h"
#include "poly_line.h"

PolyLinePreview::PolyLinePreview(ChartView* view)
{
	begin_preview(view);
}

void PolyLinePreview::on_finish_preview()
{
	if (m_pPolyLine != nullptr)
	{
		auto points = m_pPolyLine->get_points();
		points.pop_back();
		if (points.size() >= 2)
		{
			m_pPolyLine->set_points(points);
			m_view->add_item(m_pPolyLine->clone());
		}
		m_view->delete_item(m_pPolyLine);
		DELETE_PTR(m_pPolyLine);
	}
}

void PolyLinePreview::on_advance_preview(QPointF& point)
{
	if (step() == BEGIN_PREVIEW)
		set_step(START_POINT);
	else if (step() == START_POINT)
		set_step(NEXT_POINT);

	confirm_step(step(), point);;
}

void PolyLinePreview::on_mouse_move(QPointF& point)
{
	//将鼠标点坐标更新到直线的最后一个点
	if (step() >= START_POINT && step() <= NEXT_POINT)
	{
		if (QLineF(m_last_confirm_point, point).length() > 0.001)
		{
			if (m_pPolyLine->view() == nullptr)
			{
				m_pPolyLine->append_point(point);
				m_view->add_item(m_pPolyLine);
			}
			m_pPolyLine->set_last_point(point);
		}
	}
}

PolyLine* PolyLinePreview::new_polyline()
{
	return new PolyLine();
}

void PolyLinePreview::confirm_step(int step, QPointF& point)
{
	//确定第一个点
	if (step == START_POINT)
	{
		m_pPolyLine = new_polyline();
		m_pPolyLine->append_point(point);
		m_last_confirm_point = point;
	}
	//确定后续的点
	else if (step == NEXT_POINT)
	{
		if (QLineF(m_last_confirm_point, point).length() > 0.001)
		{
			m_pPolyLine->append_point(point);
			m_last_confirm_point = point;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
///箭头线
ArrowsPreview::ArrowsPreview(ChartView* view)
	:PolyLinePreview(view)
{

}

PolyLine* ArrowsPreview::new_polyline()
{
	return new Arrows();
}
