
#include <QBrush>
#include "SizeGripItem.h"
#include <QStyleOptionGraphicsItem>

SizeGripItem::HandleItem::HandleItem(int positionFlags, SizeGripItem* parent)
    : QGraphicsRectItem(-4, -4, 8, 8, parent),
      positionFlags_(positionFlags),
      parent_(parent)
{
    setBrush(QBrush(Qt::lightGray));
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    //setFlag(ItemSendsGeometryChanges);
}

int SizeGripItem::HandleItem::positionFlags() const
{
    return positionFlags_;
}

QVariant SizeGripItem::HandleItem::itemChange(GraphicsItemChange change,const QVariant &value)
{
    QVariant retVal = value;

    if (change == ItemPositionChange)
    {
        retVal = restrictPosition(value.toPointF());
    }
    else if (change == ItemPositionHasChanged)
    {
        QPointF pos = value.toPointF();

        switch (positionFlags_)
        {
            case TopLeft:
                parent_->setTopLeft(pos);
                break;
            case Top:
                parent_->setTop(pos.y());
                break;
            case TopRight:
                parent_->setTopRight(pos);
                break;
            case Right:
                parent_->setRight(pos.x());
                break;
            case BottomRight:
                parent_->setBottomRight(pos);
                break;
            case Bottom:
                parent_->setBottom(pos.y());
                break;
            case BottomLeft:
                parent_->setBottomLeft(pos);
                break;
            case Left:
                parent_->setLeft(pos.x());
                break;
        }
    }

    return retVal;
}

QPointF SizeGripItem::HandleItem::restrictPosition(const QPointF& newPos)
{
    QPointF retVal = pos();

    if (positionFlags_ & Top || positionFlags_ & Bottom)
        retVal.setY(newPos.y());

    if (positionFlags_ & Left || positionFlags_ & Right)
        retVal.setX(newPos.x());

    if (positionFlags_ & Top && retVal.y() > parent_->rect_.bottom())
        retVal.setY(parent_->rect_.bottom());
    else if (positionFlags_ & Bottom && retVal.y() < parent_->rect_.top())
        retVal.setY(parent_->rect_.top());

    if (positionFlags_ & Left && retVal.x() > parent_->rect_.right())
        retVal.setX(parent_->rect_.right());
    else if (positionFlags_ & Right && retVal.x() < parent_->rect_.left())
        retVal.setX(parent_->rect_.left());

    return retVal;
}

SizeGripItem::SizeGripItem(Resizer* resizer, QGraphicsItem* parent)
    : QGraphicsItem(parent),
      resizer_(resizer)
{
    if (parentItem())
        rect_ = parentItem()->boundingRect();

    handleItems_.append(new HandleItem(TopLeft, this));
    handleItems_.append(new HandleItem(Top, this));
    handleItems_.append(new HandleItem(TopRight, this));
    handleItems_.append(new HandleItem(Right, this));
    handleItems_.append(new HandleItem(BottomRight, this));
    handleItems_.append(new HandleItem(Bottom, this));
    handleItems_.append(new HandleItem(BottomLeft, this));
    handleItems_.append(new HandleItem(Left, this));
    updateHandleItemPositions();
}

SizeGripItem::~SizeGripItem()
{
    if (resizer_)
        delete resizer_;
}

QRectF SizeGripItem::boundingRect() const
{
    return rect_;
}

void SizeGripItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    //if (parentItem()->isSelected())
    //{
    //    foreach(HandleItem * item, handleItems_)
    //        item->setVisible(true);
    //}
    //else
    //{
    //    foreach(HandleItem * item, handleItems_)
    //        item->setVisible(false);
    //}
}

void SizeGripItem::setTopLeft(const QPointF& pos)
{
	rect_.setTopLeft(pos);
	doResize();
}

void SizeGripItem::setTop(qreal y)
{
	rect_.setTop(y);                   
	doResize();
}

void SizeGripItem::setTopRight(const QPointF& pos)
{
	rect_.setTopRight(pos);
	doResize();
}

void SizeGripItem::setRight(qreal x)
{
	rect_.setRight(x);
	doResize();
}

void SizeGripItem::setBottomRight(const QPointF& pos)
{
	rect_.setBottomRight(pos);
	doResize();
}

void SizeGripItem::setBottom(qreal y)
{
	rect_.setBottom(y);
	doResize();
}

void SizeGripItem::setBottomLeft(const QPointF& pos)
{
	rect_.setBottomLeft(pos);
	doResize();
}

void SizeGripItem::setLeft(qreal x)
{
	rect_.setLeft(x);
	doResize();
}

void SizeGripItem::doResize()
{
    if (resizer_)
    {
        (*resizer_)(parentItem(), rect_);
        updateHandleItemPositions();
    }
}

void SizeGripItem::updateHandleItemPositions()
{
    foreach (HandleItem* item, handleItems_)
    {
        item->setFlag(ItemSendsGeometryChanges, false);

        switch (item->positionFlags())
        {
            case TopLeft:
                item->setPos(rect_.topLeft());
                break;
            case Top:
                item->setPos(rect_.left() + rect_.width() / 2 - 1, rect_.top());
                break;
            case TopRight:
                item->setPos(rect_.topRight());
                break;
            case Right:
                item->setPos(rect_.right(), rect_.top() + rect_.height() / 2 - 1);
                break;
            case BottomRight:
                item->setPos(rect_.bottomRight());
                break;
            case Bottom:
                item->setPos(rect_.left() + rect_.width() / 2 - 1, rect_.bottom());
                break;
            case BottomLeft:
                item->setPos(rect_.bottomLeft());
                break;
            case Left:
                item->setPos(rect_.left(),
                             rect_.top() + rect_.height() / 2 - 1);
                break;
        }

        item->setFlag(ItemSendsGeometryChanges, true);
    }
}
