#ifndef RADAR_PLOT_H
#define RADAR_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include "graphics_item.h"
#include <QCategoryAxis>
#include <QValueAxis>
#include <QLineSeries>
#include <QScatterSeries>
#include <QAreaSeries>

enum RadarType
{
	Radar = 0,  //雷达图
	Spider		//蜘蛛网图
};

enum DrawTpye
{
	Scatter = 0,	//散点图
	Line,			//连线图
	Area			//区域图
};

//////////////////////////////////////////////////////////////////////////////
/// 雷达图
class RadarItem :public GraphicsItem
{
	Q_OBJECT

public:
	RadarItem();
	void set_chart(QChart* chart);
	void set_radial(int radial);
	void set_angular(int angular);

protected:
	QRectF boundingRect() const override;
	void on_paint(QPainter* painter) override;

private:
	QChart* m_chart = nullptr;
	/** 雷达项数 */
	int m_angular = 5;
	/** 雷达圈数 */
	int m_radial = 6;
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

	void set_radar_type(RadarType type);


protected:

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;

private:
	/** 蜘蛛网图 */
	RadarItem* item = nullptr;
	/** 角度值/雷达项 */
	QCategoryAxis* m_angularAxis = nullptr;
	/** 雷达值/雷达圈数 */
	QValueAxis* m_radialAxis = nullptr;
	/** 图类型 */
	RadarType m_radartype = Spider;
	/** 线类型 */
	DrawTpye m_drawtype = Line;
	/** 雷达项数 */
	int count = 0;
	/** 名称和系列映射 */
	QMap<QString, QLineSeries*> m_name2series;
};

#endif // RADAR_PLOT_H