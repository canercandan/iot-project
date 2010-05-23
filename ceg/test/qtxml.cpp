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

#include <iostream>

#include <QFile>
#include <QList>
#include <QMessageBox>
#include <QString>
#include <QtXml>

#include <QtGui> // FIXME: trouver le moyen de le virer

class INode
{
public:
  ~INode(){}

  virtual QDomElement createXMLNode(QDomDocument&) = 0;
};

class Param : public INode
{
public:
  Param(QString name = "", QString value = "")
    : _name(name), _value(value)
  {}

  Param(const QDomElement& e)
  {
    _name = e.attribute("name");
    _value = e.attribute("value");
  }

  QDomElement createXMLNode(QDomDocument& d)
  {
    QDomElement cn = d.createElement("param");

    cn.setAttribute("name", _name);
    cn.setAttribute("value", _value);

    return cn;
  }

private:
  QString _name;
  QString _value;
};

class XmlBox : public INode
{
public:
  XmlBox(bool visible = "", unsigned int opacity = 0,
	 QString type = "", unsigned int x = 0, unsigned int y = 0,
	 unsigned int width = 0, unsigned int height = 0,
	 QString image = "", QString text = "", QString action = "")
    : _visible(visible), _opacity(opacity), _type(type),
      _x(x), _y(y), _width(width), _height(height),
      _image(image), _text(text), _action(action)
  {}

  XmlBox(const QDomElement& e)
  {
    if (e.hasAttribute("visible"))
      _visible = e.attribute("visible").toUInt();

    if (e.hasAttribute("opacity"))
      _opacity = e.attribute("opacity").toUInt();

    if (e.hasAttribute("type"))
      _type = e.attribute("type");

    if (e.hasAttribute("x"))
      _x = e.attribute("x").toUInt();
    if (e.hasAttribute("y"))
      _y = e.attribute("y").toUInt();

    if (e.hasAttribute("width"))
      _width = e.attribute("width").toUInt();
    if (e.hasAttribute("height"))
      _height = e.attribute("height").toUInt();

    if (e.hasAttribute("image"))
      _image = e.attribute("image");
    if (e.hasAttribute("text"))
      _text = e.attribute("text");

    if (e.hasAttribute("action"))
      _action = e.attribute("action");

    for (QDomNode n = e.firstChild(); !n.isNull(); n = n.nextSibling())
      {
	QDomElement e2 = n.toElement();
	if (e2.isNull())
	  continue;
	if (e2.tagName() != "param")
	  continue;

	Param p(e2);
	_params.append(p);
	std::cout << "param appended" << std::endl;
      }
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
    cn.setAttribute("image", _image);
    cn.setAttribute("text", _text);
    cn.setAttribute("action", _action);

    for (QList<Param>::iterator
	   it = _params.begin(),
	   end = _params.end();
	 it != end; ++it)
      {
	cn.appendChild( it->createXMLNode(d) );
      }

    return cn;
  }

private:
  bool _visible;

  unsigned int _opacity;

  QString _type;

  unsigned int _x;
  unsigned int _y;
  unsigned int _width;
  unsigned int _height;

  QString _image;
  QString _text;

  QString _action;

  QList<Param> _params;
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

    for (QDomNode n = root.firstChild(); !n.isNull(); n = n.nextSibling())
      {
	QDomElement e = n.toElement();
	if (e.isNull())
	  continue;
	if (e.tagName() != "box")
	  continue;

	XmlBox b(e);
	_boxes.append(b);
	//lvBoxes->insertItem( new QListViewItem( lvBox, ... ) );
	std::cout << "box appended" << std::endl;
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
