#include "ThoiKhoaBieu.h"

CuaSoThoiKhoaBieu::CuaSoThoiKhoaBieu(QWidget* cuaSoMe) : QDialog(cuaSoMe) {
    setupUi(this);

    m_daLuu = false;
    m_soTiet = 0;

    connect(m_luu, SIGNAL(clicked()), this, SLOT(anNutLuu()));
    connect(m_thoat, SIGNAL(clicked()), this, SLOT(anNutThoat()));
    connect(m_tiet1, SIGNAL(currentIndexChanged(int)), this, SLOT(coThayDoi()));
    connect(m_tiet2, SIGNAL(currentIndexChanged(int)), this, SLOT(coThayDoi()));
    connect(m_tiet3, SIGNAL(currentIndexChanged(int)), this, SLOT(coThayDoi()));
    connect(m_tiet4, SIGNAL(currentIndexChanged(int)), this, SLOT(coThayDoi()));
    connect(m_tiet5, SIGNAL(currentIndexChanged(int)), this, SLOT(coThayDoi()));
}

QList<QString> CuaSoThoiKhoaBieu::cacTiet() {
    return m_cacTiet;
}

__int8 CuaSoThoiKhoaBieu::soTiet() {
    return m_soTiet;
}

void CuaSoThoiKhoaBieu::anNutLuu() {

     if(m_tiet1->currentText().isEmpty()) {
         QMessageBox::critical(this, tr("Lỗi"), tr("Phải có ít nhất 1 tiết (Tiết 1 không được bỏ trống!"));
         return;
     }

     m_cacTiet << m_tiet1->currentText();
     m_soTiet++;
     m_daLuu = true;

     if(!m_tiet2->currentText().isEmpty()) {
         m_cacTiet << m_tiet2->currentText();
         m_soTiet++;
         m_daLuu = true;
     }
     if(!m_tiet3->currentText().isEmpty() && !m_tiet2->currentText().isEmpty()) {
         m_cacTiet << m_tiet3->currentText();
         m_soTiet++;
         m_daLuu = true;
     }
     if(!m_tiet4->currentText().isEmpty() && !m_tiet3->currentText().isEmpty() && !m_tiet2->currentText().isEmpty()) {
         m_cacTiet << m_tiet4->currentText();
         m_soTiet++;
         m_daLuu = true;
     }
     if(!m_tiet5->currentText().isEmpty() && !m_tiet4->currentText().isEmpty() && !m_tiet3->currentText().isEmpty() && !m_tiet2->currentText().isEmpty()) {
         m_cacTiet << m_tiet5->currentText();
         m_soTiet++;
         m_daLuu = true;
     }

     if(m_tiet2->currentText().isEmpty() && (!m_tiet3->currentText().isEmpty() || !m_tiet4->currentText().isEmpty() || !m_tiet5->currentText().isEmpty())) {
         QMessageBox::critical(this, tr("Lỗi"), tr("Vui lòng điền đầy đủ các trường!"));
         m_cacTiet.clear();
         m_soTiet = 0;
         m_daLuu = false;
         return;
     }

     if(m_tiet3->currentText().isEmpty() && (!m_tiet4->currentText().isEmpty() || !m_tiet5->currentText().isEmpty())) {
         QMessageBox::critical(this, tr("Lỗi"), tr("Vui lòng điền đầy đủ các trường!"));
         m_cacTiet.clear();
         m_soTiet = 0;
         m_daLuu = false;
         return;
     }

     if(m_tiet4->currentText().isEmpty() && !m_tiet5->currentText().isEmpty()) {
         QMessageBox::critical(this, tr("Lỗi"), tr("Vui lòng điền đầy đủ các trường!"));
         m_cacTiet.clear();
         m_soTiet = 0;
         m_daLuu = false;
         return;
     }

     QMessageBox::information(this, tr("Thông báo"), tr("Đã lưu thời khóa biểu!"));
}

void CuaSoThoiKhoaBieu::coThayDoi() {
    m_daLuu = false;
}

void CuaSoThoiKhoaBieu::anNutThoat() {
    if(!m_daLuu) {
        int cauTraLoi = QMessageBox::question(this, tr("Thông báo"), tr("Bạn có muốn lưu các thay đổi?"));

        if(cauTraLoi == QMessageBox::Yes) {
            anNutLuu();
        }
        else {
            datLai();
        }
    }

    this->accept();
}

void CuaSoThoiKhoaBieu::datLai() {

}
