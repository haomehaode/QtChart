#pragma execution_character_set("utf-8")

#include "graphics_item.h"
#include "chart_view.h"

GraphicsItem::GraphicsItem()
{

}

void GraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
	apply();
	painter->setRenderHint(QPainter::Antialiasing, true);
	on_paint(painter);
}

void GraphicsItem::apply()
{
	on_apply();
}

void GraphicsItem::set_view(ChartView* view)
{
	m_view = view;
}

ChartView* GraphicsItem::view()
{
	return m_view;
}

QRectF GraphicsItem::boundingRect() const
{
	return QRectF(0, 0, 1, 1);
}
