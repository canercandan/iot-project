// #include <QtXml>
#include "BoxParameter.h"

BoxParameter::BoxParameter(QString name /*= ""*/, QString value /*= ""*/)
  : _name(name), _value(value)
{}

BoxParameter::BoxParameter(const QDomElement& e)
{
  _name = e.attribute("name");
  _value = e.attribute("value");
}

QDomElement BoxParameter::createXMLNode(QDomDocument& d)
{
  QDomElement cn = d.createElement("param");

  cn.setAttribute("name", _name);
  cn.setAttribute("value", _value);

  return cn;
}
