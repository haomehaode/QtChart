#ifndef LINE_SERIES_H
#define LINE_SERIES_H

#include <QXYSeries>
#include <QtCharts>

using namespace QtCharts;

class LineSeries : public QXYSeries
{
	Q_OBJECT

public:
	explicit LineSeries(QObject* parent = nullptr);
	~LineSeries();
	void initializeGraphics(QGraphicsItem* parent);
	void initializeTheme(int index, ChartTheme* theme, bool forced = false);
};

#endif //LINE_SERIES_H