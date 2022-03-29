#pragma execution_character_set("utf-8")

#include "chart_config.h"

ChartConfig::ChartConfig(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

ChartConfig::~ChartConfig()
{
}
