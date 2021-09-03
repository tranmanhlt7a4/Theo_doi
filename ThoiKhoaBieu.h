#ifndef THOIKHOABIEU_H
#define THOIKHOABIEU_H

#include "ui_ThoiKhoaBieu.h"
#include <QtWidgets>

class CuaSoThoiKhoaBieu : public QDialog, private Ui::ThoiKhoaBieu
{
    Q_OBJECT

public:
    CuaSoThoiKhoaBieu(QWidget* cuaSoMe);
    QList<QString> cacTiet();
    __int8 soTiet();

private slots:
    void anNutLuu();
    void anNutThoat();
    void coThayDoi();

private:
    void datLai();

    QList<QString> m_cacTiet;
    __int8 m_soTiet;
    bool m_daLuu;
};

#endif // THOIKHOABIEU_H
