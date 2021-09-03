#include "CuaSoXemTruoc.h"

CuaSoXemTruoc::CuaSoXemTruoc(const QString &noiDung, QWidget* cuaSoMe) : QDialog(cuaSoMe) {

    setModal(false);

    m_khungHienThi = new QTextEdit(noiDung);
    m_khungHienThi->setReadOnly(true);
    m_khungHienThi->setWordWrapMode(QTextOption::NoWrap);
    m_khungHienThi->setFont(QFont("Time News Roman"));

    QVBoxLayout *lopChinh = new QVBoxLayout();
        lopChinh->addWidget(m_khungHienThi);

    setLayout(lopChinh);
    setWindowIcon(QIcon(":/icons/icons/Documents.png"));
    setWindowTitle(tr("Nhật kí theo dõi"));
}
