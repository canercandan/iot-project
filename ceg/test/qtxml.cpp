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

#include <QtGui>
#include <QtXml>

class XmlBoxParser : public QXmlDefaultHandler
{
public:
  bool startDocument()
  {
    _inXmlBox = false;
    return true;
  }

  bool endDocument(const QString&, const QString&, const QString& name)
  {
    if (name == "xmlbox") {_inXmlBox = false;}
    return true;
  }

  bool startElement(const QString&, const QString&, const QString& name, const QXmlAttributes& attrs)
  {
    if (_inXmlBox && name == "box")
      {
	QString visible, opacity, type, x, y, width, height;

	for (int i = 0; i < attrs.count(); ++i)
	  {
	    QString localName = attrs.localName(i);
	    QString value = attrs.value(i);

	    if (localName == "visible"){visible = value;}
	    else if (localName == "opacity"){opacity = value;}
	    else if (localName == "type"){type = value;}
	    else if (localName == "x"){x = value;}
	    else if (localName == "y"){y = value;}
	    else if (localName == "width"){width = value;}
	    else if (localName == "height"){height = value;}
	  }

	QMessageBox::information(0, "Box",
				 "visible = " + visible + "\n" +
				 "opacity = " + opacity + "\n" +
				 "type = " + type + "\n" +
				 "x = " + x + "\n" +
				 "y = " + y + "\n" +
				 "width = " + width + "\n" +
				 "height = " + height + "\n");
      }
    else if (name == "xmlbox")
      {
	_inXmlBox = true;
      }
    return true;
  }

private:
  bool _inXmlBox;
};

int	main(int ac, char** av)
{
  QApplication a(ac, av);

  XmlBoxParser handler;

  QFile file("./test/xmlBox.xml");
  QXmlInputSource source( &file );

  QXmlSimpleReader reader;
  reader.setContentHandler( &handler );

  reader.parse(source);

  return a.exec();
}
