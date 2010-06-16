#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>
#include <QApplication>
#include "builderwizard.h"

int     main(int argc, char** argv)
{
  QApplication app(argc, argv);

  QString translatorFileName = QLatin1String("qt_");
  translatorFileName += QLocale::system().name();

  QTranslator* translator = new QTranslator(&app);
  if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
    app.installTranslator(translator);

  BuilderWizard wizard(QObject::tr("Setup"));
  wizard.show();

  return app.exec();
}
