#ifndef IXMLNODE_H
#define IXMLNODE_H

#include <QtXml>

// class QDomDocument;

class IXmlNode
{
public:
  virtual ~IXmlNode(){}

  virtual QDomElement createXMLNode(QDomDocument&) = 0;
};

#endif // !IXMLNODE_H
