#ifndef GRAPHICSCURSORITEM_H
#define GRAPHICSCURSORITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPen>
#include <QRectF>
#include <QPainter>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>

class GraphicsCursorItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    GraphicsCursorItem( int height, const QPen& pen );
    int cursorPos() const { return pos().x(); }
    void setCursorPos( int position );

protected:
    virtual QRectF boundingRect() const;
    virtual void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0 );
    virtual QVariant itemChange( GraphicsItemChange change, const QVariant& value );

private:
    int m_height;
    QPen m_pen;
    QRectF m_boundingRect;

signals:
    void cursorPositionChanged( int pos );
};

#endif // GRAPHICSCURSORITEM_H