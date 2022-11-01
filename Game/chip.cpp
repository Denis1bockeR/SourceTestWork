#include <array>

#include <QGraphicsObject>

#include "game.h"

Chip::Chip() noexcept
	: QGraphicsRectItem(), QObject()
{
	con = Free;
	game = nullptr;
	animChipTimer = new QTimer();
}
Chip::~Chip()
{
	delete animChipTimer;
}

void Chip::setCube(QBrush color, ushort x, ushort y, Condition con) noexcept
{
	this->con = con;
	this->color = color;
	setBrush(color);
	setRect(0, 0, SIZE, SIZE);
	setPos(x, y);
}

void Chip::keyPressEvent(QKeyEvent* event)
{
	Chip* i;

	switch (event->nativeVirtualKey())
	{
	case Qt::Key_A:
		if (x() != 0)
		{
			i = game->getChip(y() / SIZE, (x() / SIZE) - 1);

			itemUpdate(i);
		}
		break;
	case Qt::Key_D:
		if (x() != 5 * SIZE)
		{
			i = game->getChip(y() / SIZE, (x() / SIZE) + 1);

			itemUpdate(i);
		}
		break;
	case Qt::Key_W:
		if (y() != 0)
		{
			i = game->getChip((y() / SIZE) - 1, x() / SIZE);

			itemUpdate(i);
		}
		break;
	case Qt::Key_S:
		if (y() != 5 * SIZE)
		{
			i = game->getChip((y() / SIZE) + 1, x() / SIZE);

			itemUpdate(i);
		}
		break;
	}
}
void Chip::itemUpdate(Chip* i) noexcept
{
	if (i->brush() != Qt::black)
	{
		QBrush col = i->getColor();

		i->setBrush(color);
		i->setColor(color);

		color = col;

		if (i->con == Free)
		{
			i->updateCon(Blocked);
			updateCon(Free);
		}
	}

	animChipTimer->stop();
	setBrush(color);
	clearFocus();

	game->checkGameEnd();
}

void Chip::mousePressEvent(QGraphicsSceneMouseEvent* event) noexcept
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Chip* ch = game->getChip(i, j);
			if (ch->animChipTimer->isActive())
			{
				ch->animChipTimer->stop();
				ch->setBrush(ch->color);
			}
		}
	}

	if ((color != Qt::black) && (color != Qt::gray))
	{
		setFlag(QGraphicsItem::ItemIsFocusable);
		setAcceptHoverEvents(true);
		setFocus();

		QObject::connect(animChipTimer, SIGNAL(timeout()), this, SLOT(animSelectedChip()));
		animChipTimer->start(250);
	}
};
void Chip::animSelectedChip() noexcept
{
	if (brush() == color)
	{
		setBrush(Qt::white);
		return;
	}
	
	setBrush(color);
}