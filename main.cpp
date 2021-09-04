#include <QApplication>
#include <QTranslator>
#include <QObject>
#include "CuaSoChinh.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    CuaSoQuanLi cuaSo;
    cuaSo.show();

    return app.exec();
}
