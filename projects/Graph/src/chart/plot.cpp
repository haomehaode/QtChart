#pragma execution_character_set("utf-8")

#include "plot.h"
#include "tool_tip.h"
#include "chart_view.h"
#include "poly_line_preview.h"

Plot::Plot(QWidget *parent)
	: QWidget(parent)
{
	m_chart = new QChart();
	m_chartview = new ChartView(m_chart);

	QHBoxLayout* layout = new QHBoxLayout;
	layout->setMargin(0);
	layout->setSpacing(0);
	layout->addWidget(m_chartview);
	setLayout(layout);
}

Plot::~Plot()
{
}

void Plot::slot_tool_tip(QPointF point, bool state)
{
	if (m_tooltip == nullptr)
		m_tooltip = new ToolTip(m_chart);
	if (state) {
		m_tooltip->setText(QString("X: %1 \nY: %2 ").arg(point.x()).arg(point.y()));
		m_tooltip->setAnchor(point);
		m_tooltip->setZValue(11);
		m_tooltip->updateGeometry();
		m_tooltip->show();
	}
	else 
		m_tooltip->hide();
}

void Plot::add_title(const QString& name)
{
	m_chart->setTitle(name);
}

void Plot::connect_markers()
{
	const auto markers = m_chart-> legend()->markers();
	for (QLegendMarker* marker : markers)
	{
		disconnect(marker, &QLegendMarker::clicked, this, &Plot::slot_handle_marker_clicked);
		connect(marker, &QLegendMarker::clicked, this, &Plot::slot_handle_marker_clicked);
	}
}

void Plot::disconnect_markers()
{
	const auto markers = m_chart->legend()->markers();
	for (QLegendMarker* marker : markers)
		disconnect(marker, &QLegendMarker::clicked, this, &Plot::slot_handle_marker_clicked);
}

void Plot::draw_line()
{
	new PolyLinePreview(m_chartview);
}

void Plot::draw_arrows()
{
	new ArrowsPreview(m_chartview);
}

void Plot::slot_handle_marker_clicked()
{
	QLegendMarker* marker = qobject_cast<QLegendMarker*> (sender());
	Q_ASSERT(marker);

	switch (marker->type())
	{
	case QLegendMarker::LegendMarkerTypeXY:
	{
		marker->series()->setVisible(!marker->series()->isVisible());
		marker->setVisible(true);
		qreal alpha = 1.0;

		if (!marker->series()->isVisible())
			alpha = 0.5;

		QColor color;
		QBrush brush = marker->labelBrush();
		color = brush.color();
		color.setAlphaF(alpha);
		brush.setColor(color);
		marker->setLabelBrush(brush);

		brush = marker->brush();
		color = brush.color();
		color.setAlphaF(alpha);
		brush.setColor(color);
		marker->setBrush(brush);

		QPen pen = marker->pen();
		color = pen.color();
		color.setAlphaF(alpha);
		pen.setColor(color);
		marker->setPen(pen);
		break;
	}
	default:
		break;
	}
}
