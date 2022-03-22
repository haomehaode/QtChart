#ifndef TOOL_TIP_H
#define TOOL_TIP_H

#include "graph_global.h"
#include <QtCharts/QChart>
#include <QGraphicsItem>

using namespace QtCharts;

class QGraphicsSceneMouseEvent;

class GRAPH_EXPORT ToolTip : public QGraphicsItem
{

public:

	ToolTip(QChart* chart, QWidget* parent = nullptr);

	~ToolTip();

	void setText(const QString& text);

	void setAnchor(QPointF point);

	void updateGeometry();

	QRectF boundingRect() const;

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

protected:

	void mousePressEvent(QGraphicsSceneMouseEvent* event);

	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

private:

	QString m_text;

	QRectF m_textRect;

	QRectF m_rect;

	QPointF m_anchor;

	QFont m_font;

	QChart* m_chart = nullptr;

	QWidget* m_widget = nullptr;
};

#endif // TOOL_TIP_H