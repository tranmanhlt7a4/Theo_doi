#ifndef CUASOXEMTRUOC_H
#define CUASOXEMTRUOC_H

#include <QtWidgets>

class CuaSoXemTruoc : public QDialog
{
public:
    CuaSoXemTruoc(const QString &noiDung, QWidget* cuaSoMe);

private:
    QTextEdit *m_khungHienThi;
};

#endif // CUASOXEMTRUOC_H
