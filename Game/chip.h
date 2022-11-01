#ifndef _CHIP_H_
#define _CHIP_H_

#include <QObject>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QTimer>

#define SIZE 30

enum Condition { Blocked, Free };

class Game;

class Chip : public QObject, public QGraphicsRectItem
{
	Q_OBJECT

public:
	Game* game;
public:
	explicit Chip() noexcept;
	~Chip();

	void setCube(QBrush color, ushort x, ushort y, Condition con) noexcept;

	constexpr inline Condition getCondition() const noexcept { return con; };
	constexpr inline void updateCon(Condition con) noexcept { this->con = con; };
	inline QBrush getColor() const noexcept { return color; };
	inline void setColor(QBrush color)noexcept { this->color = color; };
private:
	Condition con;
	QBrush color;

	QTimer* animChipTimer;
private:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) noexcept;
	void keyPressEvent(QKeyEvent* event);
	
	void itemUpdate(Chip* i) noexcept;
private slots:
	void animSelectedChip() noexcept;
};

#endif // !_CHIP_H_
