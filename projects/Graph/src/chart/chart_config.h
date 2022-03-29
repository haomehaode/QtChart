#ifndef CHART_CONFIG_H
#define CHART_CONFIG_H

#include <QDialog>
#include "ui_chart_config.h"
#include "graph_global.h"

class GRAPH_EXPORT ChartConfig : public QDialog
{
	Q_OBJECT

public:
	ChartConfig(QWidget *parent = Q_NULLPTR);
	~ChartConfig();

private:
	Ui::ChartConfig ui;
};

#endif // CHART_CONFIG_H