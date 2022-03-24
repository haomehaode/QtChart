#ifndef RADAR_PLOT_H
#define RADAR_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include "graphics_item.h"
#include <QCategoryAxis>
#include <QValueAxis>
#include <QLineSeries>

enum RadarType
{
	Radar = 0,  //雷达图
	Spider		//蜘蛛网图
};

enum PointTpye
{
	ScatterPoints = 0,	//散点图
	LinePoints			//连线图
};

enum FillType
{
	Fill = 0,	//填充
	Empty		//空
};

class GRAPH_EXPORT RadarPlot : public Plot
{
	Q_OBJECT

public:

	RadarPlot(QWidget* parent = nullptr);

	~RadarPlot();

	void set_radar(QStringList& lablelist);

	void add_radar(QList<double>& valuelist, const QString& name);

	void delete_radar(const QString& name);

protected:

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;

private:
	/** 角度值 */
	QCategoryAxis* m_angularAxis = nullptr;
	/** 雷达值 */
	QValueAxis* m_radialAxis = nullptr;
	/** 图类型 */
	RadarType m_radartype = Radar;
	/** 线类型 */
	PointTpye m_pointstype = LinePoints;
	/** 填充类型 */
	FillType m_filltype = Fill;
	/** 雷达项数 */
	int count = 0;
	/** 名称和系列映射 */
	QMap<QString, QLineSeries*> m_name2series;
};

#endif // RADAR_PLOT_H