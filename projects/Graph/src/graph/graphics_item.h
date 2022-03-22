#ifndef GRAPHICS_ITEM_H
#define GRAPHICS_ITEM_H

#include "QGraphicsItem"

class ChartView;

class GraphicsItem : public QGraphicsObject
{
public:
	/** 构造函数 */
	GraphicsItem();
	/** 设置所属视图 */
	void set_view(ChartView* view);
	/** 获取所属视图 */
	ChartView* view();
	/**
	* 图元数据变更时可手动调用该接口以应用新的数据，
	* 图元绘制前会自动调用该接口以便显示正确的形状。
	*/
	void apply();

protected:
	/** 绘图区域 */
	virtual QRectF boundingRect() const override;
	/** 绘图函数 */
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	/** 克隆，由子类实现 */
	virtual GraphicsItem* clone() { return nullptr; }
	/** 数据更新计算包围盒，由子类实现 */
	virtual void on_apply() {}
	/** 绘制图像，由子类实现 */
	virtual void on_paint(QPainter* painter) {}

private:
	/** 所属视图 */
	ChartView* m_view = nullptr;
};

#endif // GRAPHICS_ITEM_H