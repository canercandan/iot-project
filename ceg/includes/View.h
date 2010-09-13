// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

/* IOT Copyright (C) 2010 CEG development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * Authors: CEG <ceg@ionlythink.com>, http://www.ionlythink.com
 */

#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class MainController;
class IAction;
class Systray;

/**
 * \brief Implementation de QGraphicsView, Widget Qt representant une scene
 */

 /**
 * Sera supprimer plutard, utilise pour debuger avec le clavier
 * Une vue est associe  a une scene
 * Lorsque que le clavier est utilise, elle creer une MoveAction et la transmet au MainController
 */
class View : public QGraphicsView
{
    Q_OBJECT
public:
    View(MainController &, Systray &);
    ~View();

    void                initialize();

protected:
    virtual void	keyPressEvent(QKeyEvent* keyEvent);
    virtual void	closeEvent(QCloseEvent *);

signals:
    void actionEmitted(IAction &); //signal d'action
    void triggered();

private:
    MainController & _mainC;
};

#endif // !VIEW_H
