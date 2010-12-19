#include <QtGui>
#include <QtXml>
#include <QtXmlPatterns>

#include <QDebug>

int main(int ac, char** av)
{
    if ( ac < 3 ) { qDebug() << "Usage:" << av[0] << "[schema.xsd] [content.xml]"; return -1; }

    QApplication app(ac, av);

    char* schema_path = av[1];
    char* xml_path = av[2];

    QUrl schemaUrl( schema_path );

    QXmlSchema schema;

    schema.load( schemaUrl );

    if ( !schema.isValid() ) { return -1; }

    QFile file( xml_path );
    file.open( QIODevice::ReadOnly );

    QXmlSchemaValidator validator( schema );
    qDebug() << "instance document";
    if ( validator.validate( &file, QUrl::fromLocalFile( file.fileName() ) ) ) { qDebug() << "valid"; }
    else { qDebug() << "invalid"; }

    return 0;
}
