#include "CuaSoXemTruoc.h"

CuaSoXemTruoc::CuaSoXemTruoc(const QString &noiDung, QWidget* cuaSoMe) : QDialog(cuaSoMe) {

    QLabel *nhanChinh = new QLabel(tr("Nội dung file"));
    m_khungHienThi = new QTextEdit(noiDung);
    m_khungHienThi->setReadOnly(true);
    m_khungHienThi->setWordWrapMode(QTextOption::NoWrap);
	
    QLabel *nhan = new QLabel(tr("Ghi chú (Thông tin này sẽ được bổ sung vào cuối file khi xuất)"));
	
    m_khungGhiChu = new QTextEdit();
    m_khungGhiChu->setWordWrapMode(QTextOption::NoWrap);

    QVBoxLayout *lopChinh = new QVBoxLayout();
        lopChinh->addWidget(nhanChinh);
        lopChinh->addWidget(m_khungHienThi);
        lopChinh->addWidget(nhan);
        lopChinh->addWidget(m_khungGhiChu);

    setLayout(lopChinh);
    setWindowIcon(QIcon(":/icons/icons/Documents.png"));
    setWindowTitle(tr("Nhật kí theo dõi"));
    setMinimumSize(300, 400);
}

QString CuaSoXemTruoc::noiDungHienThi() const {
    return m_khungHienThi->toPlainText();
}

void CuaSoXemTruoc::setNoiDungHienThi(const QString &noiDung) {
    m_khungHienThi->setPlainText(noiDung);
}

QString CuaSoXemTruoc::ghiChu() const {
    return m_khungGhiChu->toPlainText();
}

