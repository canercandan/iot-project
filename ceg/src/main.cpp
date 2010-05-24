// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

/* IOT Copyleft (C) 2010 CEG development team
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

#include <QApplication>
#include <QMessageBox>

#include "LayerManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMessageBox::information(0, "Commandes", "Left | Right arrow = Horizontal Move\nUp | Down Arrow = Vertical move\nEnter = Zoom\nBackspace = unzoom\n1 = Simple Click\nAlt + F4 = Quit");
    LayerManager layerManager;
    layerManager.start();

    return (a.exec());
}
