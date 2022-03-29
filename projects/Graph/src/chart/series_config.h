#ifndef SERIES_CONFIG_H
#define SERIES_CONFIG_H

#include <QDialog>
#include "ui_series_config.h"

class SeriesConfig : public QDialog
{
	Q_OBJECT

public:
	SeriesConfig(QWidget *parent = Q_NULLPTR);
	~SeriesConfig();

private:
	Ui::SeriesConfig ui;
};

#endif // SERIES_CONFIG_H