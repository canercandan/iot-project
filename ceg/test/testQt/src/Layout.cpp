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
	QString text;
	QMessageBox test;
	if (temp)
	{
		qreal width = temp->rect().width() * 3;
		int bigsize = (QApplication::desktop()->width() / (width));
		int level = 0;
		test.setText(text.setNum(temp->rect().width()));
		/*test.exec();*/
		while (bigsize >= 3)
		{
			text.setNum(bigsize);
			bigsize = (floor(bigsize) / 3);
			level++;
				}
		if (!level)
		{
			return (false);
		}
				level--;
		this->clearLayout();
		QDesktopWidget *desktop = QApplication::desktop();
		int Width = desktop->width();
		for (int i = 0; i < level; i++)
		{
			Width = Width / 3;
		}
		int Height = desktop->height();
		for (int i = 0; i < level; i++)
		{
			Height = Height / 3;
		}
/*
		text.setNum(Width);
		text += " = WidthFF += ";
		test.setText(text);
		test.exec();
		text.setNum(Height);
		text += " = HeightFF += ";
		test.setText(text);
		test.exec();
*/

		int posXtop = 0;
		int posYtop = 0;
/*
		text.setNum(temp->rect().y());
		text += " = posY 1";
		test.setText(text);
		test.exec();
		text.setNum(temp->rect().y() + temp->rect().height());
		text += " = posY 2";
		test.setText(text);
		test.exec();
		text.setNum(temp->rect().x());
		text += " = posX 1";
		test.setText(text);
		test.exec();
		text.setNum(temp->rect().x() + temp->rect().width());
		text += " = posX 2";
		test.setText(text);
		test.exec();
		*/
/*
				text.setNum(temp->rect().width());
				text += " = tmpWidth";
				test.setText(text);
				test.exec();

				text.setNum(Width);
				text += " = Width";
				test.setText(text);
				test.exec();

				text.setNum(temp->rect().height());
				text += " = tmpHeight";
				test.setText(text);
				test.exec();

				text.setNum(Height);
				text += " = Height";
				test.setText(text);
				test.exec();*/

				int i= 1;
				while (/*posYtop - 5 < temp->rect().y() && */((posYtop + Height) < temp->rect().y() + temp->rect().height()/* + 3 || (posYtop + Height) < temp->rect().y() - 3*/)/* + temp->rect().height()*/)
		{
						posYtop += Height;
						i++;
		}
				text.setNum(i);
				text += " = i";
				test.setText(text);
				test.exec();
				/*
		text.setNum(posYtop);
		text += " = posYtop";
		test.setText(text);
		test.exec();
		*/
				while (/*posXtop - 5 < temp->rect().x() && */((posXtop + Width) < temp->rect().x() + temp->rect().width()/* + 3 || (posXtop + Width) < temp->rect().x() - 3*/)/* + */)
		{
			posXtop += Width;
		}
		/*
		text.setNum(posXtop);
		text += " = posXtop";
		test.setText(text);
		test.exec();
		*/
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
