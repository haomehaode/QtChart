#ifndef AXIS_CONFIG_H
#define AXIS_CONFIG_H

#include <QDialog>
#include "ui_axis_config.h"

class AxisConfig : public QDialog
{
	Q_OBJECT

public:
	AxisConfig(QWidget *parent = Q_NULLPTR);
	~AxisConfig();

private:
	Ui::AxisConfig ui;
};

#endif // AXIS_CONFIG_H