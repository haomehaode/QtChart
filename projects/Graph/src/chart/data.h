#ifndef DATA_H
#define DATA_H

/** 概率结构 */
struct Probability
{
	/** 分位数 */
	int index;
	/** 理论值 */
	double theory;
	/** 理论CDF */
	double theory_cdf;
	/** 理论Z值 */
	double theory_z;
	/** 实际值 */
	double reality;
	/** 实际CDF */
	double reality_cdf;
	/** 实际Z值 */
	double reality_z;
};

/** 评分方法 */
enum ScoreType
{
	Blom,
	Benard,
	Hazen,
	VanDerWaerden,
	KaplanMeier
};

/** 股票图数据 */
struct CandlestickData
{
	CandlestickData(double timestamp, double open, double high, double low, double close)
	{
		m_timestamp = timestamp;
		m_open = open;
		m_high = high;
		m_low = low;
		m_close = close;
	}
	double m_timestamp;
	double m_open;
	double m_high;
	double m_low;
	double m_close;
};

/** 柱状图数据 */
struct PieData
{
	PieData(QString name, double value)
	{
		m_name = name;
		m_value = value;
	}
	QString m_name;
	double m_value;
};

/** 3d数据 */
struct ThirdDData
{
	ThirdDData(double x, double y,double z)
	{
		m_x = x;
		m_y = y;
		m_z = z;
	}
	double m_x;
	double m_y;
	double m_z;
};

/** 箱型图数据 */
struct BoxData
{
	QString m_name;
	QList<double> m_value_list;
};

/** 条形图 */
enum BoxBarType
{
	MEAN,
	SUM,
	MAX,
	MIN
};

#endif //DATA_H
