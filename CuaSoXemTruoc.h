#ifndef CUASOXEMTRUOC_H
#define CUASOXEMTRUOC_H

#include <QtWidgets>

class CuaSoXemTruoc : public QDialog
{
    Q_OBJECT

public:
    CuaSoXemTruoc(const QString &noiDung, QWidget* cuaSoMe);
    QString noiDungHienThi() const;
    void setNoiDung(const QString &noiDung);

private slots:
    void anNut();
    void anNutThoat();
    void coThayDoi();

private:
    QTextEdit *m_khungHienThi;
    QString m_noiDungTruocKhiSua;
    QPushButton *m_nut; //Lưu hoặc sửa
    QPushButton *m_thoat;
    bool m_daLuu;
};

#endif // CUASOXEMTRUOC_H
