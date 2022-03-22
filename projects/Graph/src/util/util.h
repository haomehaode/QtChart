#ifndef UTIL_H
#define UTIL_H

#include "math_define.h"
#include "graph_global.h"

#include <QRectF>
#include <QList>

//宏定义：销毁指针
#define DELETE_PTR(p) if(p){delete p; p = nullptr;}
#define DELETE_PTR_LIST(list) { for (auto x : list) delete x; list.clear();}

//宏定义：double是否相等
#define DOUBLE_EQUAL(d1, d2) (fabs((d1)-(d2)) <= TOLERANCE)


class GRAPH_EXPORT Util
{
public:

    static QRectF bounding_rect(const QList<QPointF>& points);

    static void bounding_rect(const QList<QPointF>& points, double& xmin, double& xmax, double& ymin, double& ymax);

    static QRectF bounding_rect(const QList<QRectF>& rects);

    static void bounding_rect(const QRectF& rect, double& xmin, double& xmax, double& ymin, double& ymax);

    /**
    * 基于x轴向右，y轴向上，逆时针为正，
    * 计算向量p1p2的角度，范围是[0, 360)
    */
    static double angle(const QPointF& p1, const QPointF& p2);

    /**
    * 基于x轴向右，y轴向上，逆时针为正，
    * 基于坐标原点旋转点p，angle的范围是[0, 360)
    */
    static QPointF rotated(const QPointF& p, double angle);

    /** 求平均值*/
    static double average(QList<double>& list);

    /** 求最大值*/
	static double max(QList<double>& list);

    /** 求最小值*/
    static double min(QList<double>& list);

    static void cal_list(QList<double>& list,double &mean,double &sum,double &max,double &min);

    /** 求方差 */
    //若n个数据为总体，则求总体标准差，标准差公式根号内除以n；若n个数据为样本，则求样本标准差，标准差公式根号内除以（n - 1)。
    static double variance(QList<double>& list,double mean= DBL_MIN);

    /** 求标准差 */
    static double standard_deviation(QList<double>& list,double sigma2 = DBL_MIN);


	//计算正态累积分布函数
    //https://blog.csdn.net/weixin_42112208/article/details/81292610
    //https://stackoverflow.com/questions/2328258/cumulative-normal-distribution-function-in-c-c
    //注意负号，但是算的是左侧累积量，（1-该值）*2 //这算的是标准差为1 均值为0 的
    static double normal_cdf(double value);

	static double normal_z(double value);

	static double normsdist(double z);

	static double normsinv(double p);
};
#endif  //UTIL_H
