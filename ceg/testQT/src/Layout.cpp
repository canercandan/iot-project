#include <iostream>

#include <QKeyEvent>
#include <QList>
#include <QGraphicsItem>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>

#include "Layout.h"
#include "MyAweSomeBox.h"

Layout::Layout( qreal x, qreal y, qreal width, qreal height, QObject * parent) :
		QGraphicsScene(x, y, width, height, parent)
{
	this->drawGrid(QApplication::desktop()->width(), QApplication::desktop()->height());
}

void    Layout::drawGrid(qreal width, qreal height, qreal posX, qreal posY)
{
	int nbGrid = 3;
	int tmpWidth = width / nbGrid;
	int tmpHeight = height / nbGrid;
	QMessageBox::information(0, "", "test");
	int rows = 0;
	while (rows++ < nbGrid)
	{
		int cols = 0;
		qreal x = posX;
		while (cols++ < nbGrid)
		{
			this->addItem(new MyAweSomeBox(x, posY, tmpWidth, tmpHeight));
			x += tmpWidth;
		}
		posY += tmpHeight;
	}
	QList<QGraphicsItem *> items =  this->items();
	items.first()->setFocus();
}

void    Layout::drawChild(QGraphicsItem * item)
{
	this->clearLayout();
	MyAweSomeBox * temp = dynamic_cast<MyAweSomeBox *>(item);
	if (temp)
		this->drawGrid(temp->rect().width(), temp->rect().height(), temp->rect().x(), temp->rect().y());
}

#include <cmath>

bool    Layout::drawParent(QGraphicsItem * item)
{
	MyAweSomeBox * temp = dynamic_cast<MyAweSomeBox *>(item);
	if (temp)
	{
		qreal posX = temp->rect().x() *  3, posY = temp->rect().y() * 3, width = temp->rect().width() * 3;
		int bigsize = (QApplication::desktop()->width() / (width));
		int level = 0;
		QString text;
		QMessageBox test;
		test.setText(text.setNum(temp->rect().width()));
		test.exec();
		while (bigsize >= 3)
		{
			text.setNum(bigsize);
			QMessageBox msg;
			msg.setText(text);
			msg.exec();
			bigsize = (floor(bigsize) / 3);
			level++;
		}
		if (!level)
		{
			return (false);
		}
		this->clearLayout();
		QDesktopWidget *desktop = QApplication::desktop();
		int Width = desktop->width() / level;
		int Height = desktop->height() / level;
		int posXtop = 0;
		int posYtop = 0;
		while (posYtop > posY || (posYtop + Width) < posY)
		{
			posYtop += Width;
		}
		while (posXtop > posX || (posXtop + Width) < posX)
		{
			posXtop += Height;
		}
		drawGrid(Width, Height, posXtop, posYtop);
	}
	return (true);
}

void Layout::keyPressEvent(QKeyEvent * keyEvent )
{

	QList<QGraphicsItem *> items =  this->items();
	int sizeList = items.size();
	switch (keyEvent->key())
	{
	case Qt::Key_Left:
	case Qt::Key_Right :
		{
			QGraphicsItem * focusItem = this->focusItem();
			int index = items.indexOf(focusItem) + 1;
			QList<QGraphicsItem *>::iterator it = items.begin();
			if (index < sizeList)
				it += index;
			(*it)->setFocus();
		}
		break;
	case Qt::Key_Up :
	case Qt::Key_Down:
		{
			QGraphicsItem * focusItem = this->focusItem();
			int index = items.indexOf(focusItem) + 3;
			QList<QGraphicsItem *>::iterator it = items.begin();
			it += ((index < sizeList) ? index : (index - sizeList));
			(*it)->setFocus();
		}
		break;
	case Qt::Key_Return :
		this->drawChild(this->focusItem());
		break;
	case Qt::Key_Backspace :
		this->drawParent(this->focusItem());
		break;
	}
}

void Layout::clearLayout()
{
	QList<QGraphicsItem *> items = this->items();
	QList<QGraphicsItem *>::iterator it = items.begin();
	for (; it != items.end();)
	{
		QList<QGraphicsItem *>::iterator itTemp = it;
		++itTemp;
		this->removeItem(*it);
		it = itTemp;
	}
}
