#ifndef CUASOXEMTRUOC_H
#define CUASOXEMTRUOC_H

#include <QtWidgets>

class CuaSoXemTruoc : public QDialog
{
public:
    CuaSoXemTruoc(const QString &noiDung, QWidget* cuaSoMe);
    QString noiDungHienThi() const;
    void setNoiDungHienThi(const QString &noiDung);
    QString ghiChu() const;

private:
    QTextEdit *m_khungHienThi;
    QTextEdit *m_khungGhiChu;
};

#endif // CUASOXEMTRUOC_H
