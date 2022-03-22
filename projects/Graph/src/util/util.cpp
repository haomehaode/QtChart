#include "util.h"

#include <QLineF>
#include <QMatrix>
#include "qmath.h"

QRectF Util::bounding_rect(const QList<QPointF>& points)
{
	double xmin, xmax, ymin, ymax;
	bounding_rect(points, xmin, xmax, ymin, ymax);
	return QRectF(QPointF(xmin, ymin), QPointF(xmax, ymax));
}

void Util::bounding_rect(const QList<QPointF>& points, double& xmin, double& xmax, double& ymin, double& ymax)
{
	xmin = INT_MAX;
	xmax = INT_MIN;
	ymin = INT_MAX;
	ymax = INT_MIN;

	for (auto& p : points)
	{
		if (p.x() < xmin) xmin = p.x();
		if (p.x() > xmax) xmax = p.x();
		if (p.y() < ymin) ymin = p.y();
		if (p.y() > ymax) ymax = p.y();
	}
}

QRectF Util::bounding_rect(const QList<QRectF>& rects)
{
	QList<QPointF> pts;
	for (auto r : rects)
	{
		pts.append(r.topLeft());
		pts.append(r.bottomRight());
	}
	return Util::bounding_rect(pts);
}

void Util::bounding_rect(const QRectF& rect,
	double& xmin, double& xmax, double& ymin, double& ymax)
{
	QList<QPointF> pts;
	pts.append(rect.topLeft());
	pts.append(rect.bottomRight());
	bounding_rect(pts, xmin, xmax, ymin, ymax);
}


double Util::angle(const QPointF& p1, const QPointF& p2)
{
	//QLineF基于y轴向下，而我们是y轴向上，所以需要变化y轴的方向
	QPointF _p1 = QPointF(p1.x(), -p1.y());
	QPointF _p2 = QPointF(p2.x(), -p2.y());
	return QLineF(_p1, _p2).angle();
}

QPointF Util::rotated(const QPointF& p, double angle)
{
	double rad = angle * ADEGREE;
	QMatrix mat(cos(rad),sin(rad), -sin(rad), cos(rad),0,0);
	return mat.map(p);
}

double Util::average(QList<double>& list)
{
	double sum = 0;
	for (int i = 0; i < list.size(); i++) // 求和
		sum += list[i];
	return sum / list.size();
}

double Util::max(QList<double>& list)
{
	double max = DBL_MIN;
	for (auto& item : list) 
	{
		if (max < item)
			max = item;
	}
	return max;
}

double Util::min(QList<double>& list)
{
	double min = DBL_MAX;
	for (auto& item : list)
	{
		if (min > item)
			min = item;
	}
	return min;
}

void Util::cal_list(QList<double>& list, double& mean, double& sum, double& max, double& min)
{
	min = DBL_MAX; max = DBL_MIN; sum = 0;
	for (int i = 0; i < list.size(); i++) // 求和
	{
		if (max < list[i])
			max = list[i];
		if (min > list[i])
			min = list[i];
		sum += list[i];
	}
	mean = sum / list.size();
}

double Util::variance(QList<double>& list, double mean/*= DBL_MIN*/)
{
	double sum = 0;
	double average = mean != DBL_MIN ? mean : Util::average(list);
	for (int i = 0; i < list.size(); i++)
		sum += pow(list[i] - average, 2);
	return sum / (list.size() - 1);
}

double Util::standard_deviation(QList<double>& list, double sigma2 /*= DBL_MIN*/)
{
	double variance = sigma2 != DBL_MIN ? sigma2 : Util::variance(list);
	return sqrt(variance);
}

double Util::normal_cdf(double value)
{
	return 0.5 * erfc(-value * M_SQRT1_2);
}

double Util::normal_z(double value)
{
	const double       A1 = 0.31938153;
	const double       A2 = -0.356563782;
	const double       A3 = 1.781477937;
	const double       A4 = -1.821255978;
	const double       A5 = 1.330274429;
	const double RSQRT2PI = 0.39894228040143267793994605993438;

	double
		K = 1.0 / (1.0 + 0.2316419 * fabs(value));

	double
		cnd = RSQRT2PI * exp(-0.5 * value * value) *
		(K * (A1 + K * (A2 + K * (A3 + K * (A4 + K * A5)))));

	if (value > 0)
		cnd = 1.0 - cnd;

	return cnd;
}

double Util::normsdist(double z)
{
	if (z > 6)
		return 1;
	if (z < -6)
		return 0;
	double  gamma = 0.231641900, a1 = 0.319381530, a2 = -0.356563782, a3 = 1.781477973, a4 = -1.821255978, a5 = 1.330274429;
	double x = abs(z);
	double t = 1 / (1 + gamma * x);
	double n = 1 - (1 / (sqrt(2 * PI)) * exp(-z * z / 2)) * (a1 * t + a2 * pow(t, 2) + a3 * pow(t, 3) + a4 * pow(t, 4) + a5 * pow(t, 5));
	if (z < 0)
		return 1.0 - n;
	return n;
}

double Util::normsinv(double p)
{
	double LOW = 0.02425;
	double HIGH = 0.97575;
	double a[] = { -3.969683028665376e+01, 2.209460984245205e+02,-2.759285104469687e+02, 1.383577518672690e+02,-3.066479806614716e+01, 2.506628277459239e+00 };
	double b[] = { -5.447609879822406e+01, 1.615858368580409e+02,-1.556989798598866e+02, 6.680131188771972e+01,-1.328068155288572e+01 };
	double c[] = { -7.784894002430293e-03, -3.223964580411365e-01,-2.400758277161838e+00, -2.549732539343734e+00,4.374664141464968e+00, 2.938163982698783e+00 };
	double d[] = { 7.784695709041462e-03, 3.224671290700398e-01,2.445134137142996e+00, 3.754408661907416e+00 };
	double q, r;
	if (p < LOW) {
		q = sqrt(-2 * log(p));
		return (((((c[0] * q + c[1]) * q + c[2]) * q + c[3]) * q + c[4]) * q + c[5]) / ((((d[0] * q + d[1]) * q + d[2]) * q + d[3]) * q + 1);
	}
	else if (p > HIGH) {
		q = sqrt(-2 * log(1 - p));
		return -(((((c[0] * q + c[1]) * q + c[2]) * q + c[3]) * q + c[4]) * q + c[5]) / ((((d[0] * q + d[1]) * q + d[2]) * q + d[3]) * q + 1);
	}
	else {
		q = p - 0.5;
		r = q * q;
		return (((((a[0] * r + a[1]) * r + a[2]) * r + a[3]) * r + a[4]) * r + a[5]) * q / (((((b[0] * r + b[1]) * r + b[2]) * r + b[3]) * r + b[4]) * r + 1);
	}
}
