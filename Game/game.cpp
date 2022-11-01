#include <cstdlib>

#include <QLabel>

#include "game.h"

Game::Game(std::array<QBrush, 3> color) noexcept
{
	srand(time(NULL));
	for (int i = 1; i < 5; i += 2)									//Placement of blocked chips
	{
		for (int j = 0; j < 5; j += 2)
		{
			chip[i][j].setCube(Qt::black, i * SIZE, j * SIZE, Blocked);
			chip[i][j].game = this;
			addItem(&chip[i][j]);
		}
	}

	ushort num = 0, i, j;											
	do																//Placement of color chips
	{
		i = rand() % 5;
		j = rand() % 5;
		if (chip[i][j].getCondition() == Free)
		{
			chip[i][j].setCube(color[num % 3], i * SIZE, j * SIZE, Blocked);
			chip[i][j].game = this;
			addItem(&chip[i][j]);
			num++;
		}
	} while (num < 15);

	for (i = 0; i < 5; ++i)											//Placement of free chips
	{
		for (int j = 0; j < 5; ++j)
		{
			if (chip[i][j].getCondition() == Free)
			{
				chip[i][j].setCube(Qt::gray, i * SIZE, j * SIZE, Free);
				chip[i][j].game = this;
				addItem(&chip[i][j]);
			}
		}
	}

	QObject::connect(this, SIGNAL(gameEnd()), this, SLOT(createWinLabel()));
}

void Game::checkGameEnd() noexcept
{
	ushort l = 0;
	for (int i = 0; i < 5; i += 2)
	{
		for (int j = 1; j < 5; j++)
		{
			if (chip[i][0].getColor() == chip[i][j].getColor())
				l++;
		}
	}

	if (l == 12)
		emit gameEnd();
}

void Game::createWinLabel()
{
	QLabel* lose = new QLabel();

	lose->setText("Your win");
	lose->setFixedSize(5 * SIZE, 5 * SIZE);

	for (auto& i : items())
		removeItem(i);

	addWidget(lose);
}