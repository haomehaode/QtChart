#ifndef STOCK_PLOT_H
#define STOCK_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include "data.h"
#include <QBarCategoryAxis>
#include <QCandlestickSeries>
#include <QValueAxis>
#include <QCandlestickSet>
#include <QDateTime>
#include <QStack>
#include <QLabel>

class GRAPH_EXPORT StockPlot : public Plot
{

public:

	StockPlot(QWidget* parent = nullptr);

	~StockPlot();

public slots:
	/** 鼠标提示 */
	virtual void slot_tool_tip(bool status, QCandlestickSet* set);

public:

	void add_stock(QList<CandlestickData>& data_list, const QString& name);

	void delete_stock(const QString& name);

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;


private:
	/** 数据计算 */
	void prepare_data(QList<CandlestickData>& data_list);

private:
	/** 名称和系列映射 */
	QMap<QString, QCandlestickSeries*> m_name2series;
	/** X 轴 */
	QBarCategoryAxis* m_axisX = nullptr;
	/** Y 轴 */
	QValueAxis* m_axisY = nullptr;
	/** 记录坐标轴范围 */
	QStack<double> m_range[4];
	/** X 轴时间 */
	QStringList m_axisx_list;
};

#endif // STOCK_PLOT_H