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

// here's a tutorial available: http://www.digitalfanatics.org/projects/qt_tutorial/chapter09.html

// we are reading the file in using SAX

#include <iostream>

#include <QFile>
#include <QList>
#include <QtGui>
#include <QtXml>

class XmlBox
{
public:
  XmlBox(QString visible = "", QString opacity = "",
	 QString type = "", QString x = "", QString y = "",
	 QString width = "", QString height = "")
    : _visible(visible), _opacity(opacity), _type(type),
      _x(x), _y(y), _width(width), _height(height)
  {}

  XmlBox(const QDomElement& e)
  {
    _visible = e.attribute("visible", "");
    _opacity = e.attribute("opacity", "");
    _type = e.attribute("type", "");
    _x = e.attribute("x", "");
    _y = e.attribute("y", "");
    _width = e.attribute("width", "");
    _height = e.attribute("height", "");
  }

  QDomElement createXMLNode(QDomDocument& d)
  {
    QDomElement cn = d.createElement("box");

    cn.setAttribute("visible", _visible);
    cn.setAttribute("opacity", _opacity);
    cn.setAttribute("type", _type);
    cn.setAttribute("x", _x);
    cn.setAttribute("y", _y);
    cn.setAttribute("width", _width);
    cn.setAttribute("height", _height);

    return cn;
  }

private:
  QString _visible, _opacity, _type, _x, _y, _width, _height;
};

class MainFrame : public QFrame
{
public:
  void load(const QString& filename)
  {
    QFile file(filename);
    QDomDocument doc("XmlBox");

    if (!file.open(QIODevice::ReadOnly) || !doc.setContent( &file ))
      {
	QMessageBox::warning(this, "Loading", "Failed to load file.");
	return;
      }

    file.close();

    QDomElement root = doc.documentElement();
    if (root.tagName() != "boxes")
      {
	QMessageBox::warning(this, "Loading", "Invalid file.");
	return;
      }

    _boxes.clear();
    //lvBoxes->clear();

    QDomNode n = root.firstChild();
    while (!n.isNull())
      {
	QDomElement e = n.toElement();
	if (!e.isNull())
	  {
	    if (e.tagName() == "box")
	      {
		XmlBox b(e);
		_boxes.append(b);
		//lvBoxes->insertItem( new QListViewItem( lvBox, ... ) );
		std::cout << "appended" << std::endl;
	      }
	  }

	n = n.nextSibling();
      }
  }

  void	save(const QString& filename)
  {
    QDomDocument doc("XmlBox");
    QDomElement root = doc.createElement("boxes");
    doc.appendChild(root);

    for (QList<XmlBox>::iterator
	   it = _boxes.begin(),
	   end = _boxes.end();
	 it != end; ++it)
      {
	root.appendChild( it->createXMLNode(doc) );
      }

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly))
      {
	QMessageBox::warning(this, "Saving", "Failed to save file.");
	return;
      }

    QTextStream ts(&file);
    ts << doc.toString();

    file.close();
  }

private:
  QList<XmlBox> _boxes;
};

int	main(int ac, char** av)
{
  QApplication a(ac, av);

  MainFrame m;
  m.load("./test/xmlBox.xml");
  m.save("./test/xmlBox2.xml");

  return a.exec();
}
