#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsView>
#include <QComboBox>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QApplication::setDesktopSettingsAware(false);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    a.setApplicationName("FapMan");
    a.setOrganizationName("Lauttaniemi");
    a.setOrganizationDomain("127.0.0.1");

    w.setWindowIcon(QIcon(":res/images/icon16x16.png"));
    w.setWindowIcon(QIcon(":res/images/icon64x64.png"));

    QGraphicsTextItem* noob=    w.ui
            //w->scene->addText("Hello world!");


    w.show();

    return a.exec();
}
