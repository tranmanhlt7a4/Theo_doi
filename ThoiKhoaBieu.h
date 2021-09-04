#ifndef THOIKHOABIEU_H
#define THOIKHOABIEU_H

#include "ui_ThoiKhoaBieu.h"
#include <QtWidgets>

class CuaSoThoiKhoaBieu : public QDialog, private Ui::ThoiKhoaBieu
{
    Q_OBJECT

public:
    CuaSoThoiKhoaBieu(QWidget* cuaSoMe);
    QList<QString> cacTiet() const;
    int doDai() const;

private slots:
    void anNutLuu();
    void anNutThoat();
    void coThayDoi();

private:
    void datLai();

    QList<QString> m_cacTiet;
    int m_doDai; //Độ dài của các tiết học tính bằng kí tự
    bool m_daLuu;
};

#endif // THOIKHOABIEU_H
