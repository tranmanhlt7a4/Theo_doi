#include <QApplication>
#include <QTranslator>
#include <QObject>
#include "CuaSoChinh.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    CuaSoQuanLi cuaSo;
    cuaSo.show();

    QObject::connect(qApp, SIGNAL(aboutToQuit()), &cuaSo, SLOT(thoat()));
    return app.exec();


}
