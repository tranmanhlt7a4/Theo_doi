#include "CuaSoXemTruoc.h"

CuaSoXemTruoc::CuaSoXemTruoc(const QString &noiDung, QWidget* cuaSoMe) : QDialog(cuaSoMe) {

    m_daLuu = true;

    m_khungHienThi = new QTextEdit(noiDung);
    m_khungHienThi->setReadOnly(true);
    m_khungHienThi->setWordWrapMode(QTextOption::NoWrap);

    //Các nút
    m_nut = new QPushButton(tr("Sửa"));
        m_nut->setIcon(QIcon(":/icons/icons/Edit.png"));
        m_nut->setToolTip((tr("Sửa tệp này")));
        m_nut->setCursor(Qt::PointingHandCursor);

    m_thoat = new QPushButton(tr("Thoát"));
        m_thoat->setIcon(QIcon(":/icons/icons/Quit_v1.ico"));
        m_thoat->setCursor(Qt::PointingHandCursor);

    QHBoxLayout *lopSapXepCacNut = new QHBoxLayout();
        lopSapXepCacNut->addWidget(m_nut);
        lopSapXepCacNut->addWidget(m_thoat);
        lopSapXepCacNut->setAlignment(Qt::AlignRight);

    QVBoxLayout *lopChinh = new QVBoxLayout();
        lopChinh->addWidget(m_khungHienThi);
        lopChinh->addLayout(lopSapXepCacNut);

    setLayout(lopChinh);
    setWindowIcon(QIcon(":/icons/icons/Documents.png"));
    setWindowTitle(tr("Nhật kí theo dõi"));

    connect(m_nut, SIGNAL(clicked()), this, SLOT(anNut()));
    connect(m_thoat, SIGNAL(clicked()), this, SLOT(anNutThoat()));
    connect(m_khungHienThi, SIGNAL(textChanged()), this, SLOT(coThayDoi()));
}

QString CuaSoXemTruoc::noiDungHienThi() const {
    return m_khungHienThi->toPlainText();
}

void CuaSoXemTruoc::setNoiDung(const QString &noiDung) {
    m_khungHienThi->setPlainText(noiDung);
    m_daLuu = true;
}

void CuaSoXemTruoc::anNut() {

    if(m_nut->text() == tr("Sửa")) {
        m_nut->setText(tr("Lưu"));
        m_nut->setIcon(QIcon(":/icons/icons/Save.ico"));
        m_nut->setToolTip((tr("Lưu thay đổi")));
        m_nut->setCursor(Qt::PointingHandCursor);
        m_daLuu = false;
        m_khungHienThi->setReadOnly(false);
        m_noiDungTruocKhiSua = m_khungHienThi->toPlainText();
    }
    else {
        m_nut->setText(tr("Sửa"));
        m_nut->setIcon(QIcon(":/icons/icons/Edit.png"));
        m_nut->setToolTip((tr("Sửa tệp này")));
        m_nut->setCursor(Qt::PointingHandCursor);
        m_daLuu = true;
        m_khungHienThi->setReadOnly(true);
        m_noiDungTruocKhiSua = m_khungHienThi->toPlainText();
    }
}

void CuaSoXemTruoc::anNutThoat() {
    if(!m_daLuu) {
        int cauTraLoi = QMessageBox::question(this, tr("Lưu thay đổi"), tr("Bạn có muốn lưu các thay đổi!"));

        if(cauTraLoi == QMessageBox::Yes) {
            anNut();
        }
        else {
            while(m_khungHienThi->toPlainText() != m_noiDungTruocKhiSua) {
                m_khungHienThi->undo();
            }
        }
    }

    //Trả về giao diện nút sửa
    if(m_nut->text() == tr("Lưu")) {
        m_nut->setText(tr("Sửa"));
        m_nut->setIcon(QIcon(":/icons/icons/Edit.png"));
        m_nut->setToolTip((tr("Sửa tệp này")));
        m_nut->setCursor(Qt::PointingHandCursor);
        m_daLuu = true;
        m_khungHienThi->setReadOnly(true);
    }

    accept();
}

void CuaSoXemTruoc::coThayDoi() {
    m_daLuu = false;
}
