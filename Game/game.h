#ifndef _GAME_H_
#define _GAME_H_

#include <QGraphicsScene>

#include "chip.h"

class Game : public QGraphicsScene
{
	Q_OBJECT

public:
	explicit Game(std::array<QBrush, 3> color) noexcept;
	~Game() = default;

	void checkGameEnd() noexcept;

	inline Chip* getChip(ushort x,ushort y) noexcept { return &chip[y][x]; };
signals:
	void gameEnd();
private:
	std::array<std::array<Chip, 5>, 5> chip;

	friend class Chip;
private slots:
	void createWinLabel();
};

#endif // !_GAME_H_
