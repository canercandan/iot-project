#include <QtGui>
#include <QtXml>
#include <QtXmlPatterns>

#include <QDebug>

class MainWindow : public QMainWindow
{
public:
    MainWindow()
    {
	QUrl schemaUrl("./schema.xsd");

	QXmlSchema schema;

	schema.load( schemaUrl );

	if ( schema.isValid() )
	    {
		QFile file("menu.xml");
		file.open( QIODevice::ReadOnly );

		QXmlSchemaValidator validator( schema );
		if ( validator.validate( &file, QUrl::fromLocalFile( file.fileName() ) ) )
		    {
			qDebug() << "instance document is valid";
		    }
		else
		    {
			qDebug() << "instance document is invalid";
		    }
	    }
    }
};

int main(int ac, char** av)
{
    QApplication app(ac, av);

    MainWindow window;

    app.exec();

    return 0;
}
