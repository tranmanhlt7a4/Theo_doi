#include "ThoiKhoaBieu.h"

CuaSoThoiKhoaBieu::CuaSoThoiKhoaBieu(QWidget* cuaSoMe) : QDialog(cuaSoMe) {
    setupUi(this);

    m_daLuu = false;

    connect(m_luu, SIGNAL(clicked()), this, SLOT(anNutLuu()));
    connect(m_thoat, SIGNAL(clicked()), this, SLOT(anNutThoat()));
    connect(m_tiet1, SIGNAL(currentIndexChanged(int)), this, SLOT(coThayDoi()));
    connect(m_tiet2, SIGNAL(currentIndexChanged(int)), this, SLOT(coThayDoi()));
    connect(m_tiet3, SIGNAL(currentIndexChanged(int)), this, SLOT(coThayDoi()));
    connect(m_tiet4, SIGNAL(currentIndexChanged(int)), this, SLOT(coThayDoi()));
    connect(m_tiet5, SIGNAL(currentIndexChanged(int)), this, SLOT(coThayDoi()));
}

QList<QString> CuaSoThoiKhoaBieu::cacTiet() const {
    return m_cacTiet;
}

int CuaSoThoiKhoaBieu::doDai() const {
    return m_doDai;
}

void CuaSoThoiKhoaBieu::anNutLuu() {

    //Đặt lại
    m_cacTiet.clear();

     if(m_tiet1->currentText().isEmpty()) {
         QMessageBox::critical(this, tr("Lỗi"), tr("Phải có ít nhất 1 tiết (Tiết 1 không được bỏ trống!"));
         return;
     }

     m_cacTiet << m_tiet1->currentText();
     m_daLuu = true;

     if(!m_tiet2->currentText().isEmpty()) {
         m_cacTiet << m_tiet2->currentText();
         m_daLuu = true;
     }
     if(!m_tiet3->currentText().isEmpty() && !m_tiet2->currentText().isEmpty()) {
         m_cacTiet << m_tiet3->currentText();
         m_daLuu = true;
     }
     if(!m_tiet4->currentText().isEmpty() && !m_tiet3->currentText().isEmpty() && !m_tiet2->currentText().isEmpty()) {
         m_cacTiet << m_tiet4->currentText();
         m_daLuu = true;
     }
     if(!m_tiet5->currentText().isEmpty() && !m_tiet4->currentText().isEmpty() && !m_tiet3->currentText().isEmpty() && !m_tiet2->currentText().isEmpty()) {
         m_cacTiet << m_tiet5->currentText();
         m_daLuu = true;
     }

     if(m_tiet2->currentText().isEmpty() && (!m_tiet3->currentText().isEmpty() || !m_tiet4->currentText().isEmpty() || !m_tiet5->currentText().isEmpty())) {
         QMessageBox::critical(this, tr("Lỗi"), tr("Vui lòng điền đầy đủ các trường!"));
         m_cacTiet.clear();
         m_daLuu = false;
         return;
     }

     if(m_tiet3->currentText().isEmpty() && (!m_tiet4->currentText().isEmpty() || !m_tiet5->currentText().isEmpty())) {
         QMessageBox::critical(this, tr("Lỗi"), tr("Vui lòng điền đầy đủ các trường!"));
         m_cacTiet.clear();
         m_daLuu = false;
         return;
     }

     if(m_tiet4->currentText().isEmpty() && !m_tiet5->currentText().isEmpty()) {
         QMessageBox::critical(this, tr("Lỗi"), tr("Vui lòng điền đầy đủ các trường!"));
         m_cacTiet.clear();
         m_daLuu = false;
         return;
     }

     QMessageBox::information(this, tr("Thông báo"), tr("Đã lưu thời khóa biểu!\n Số tiết: %n", "", m_cacTiet.size()));

     //Cập nhật độ dài
     for(int i = 0; i < m_cacTiet.size(); i++) {
         m_doDai += m_cacTiet[i].size() + 9;
     }
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

    switch(m_cacTiet.size()) {
    case 1:
        m_tiet1->setCurrentText(m_cacTiet.at(0));
        m_tiet2->setCurrentText("");
        m_tiet3->setCurrentText("");
        m_tiet4->setCurrentText("");
        m_tiet5->setCurrentText("");
        break;
    case 2:
        m_tiet1->setCurrentText(m_cacTiet.at(0));
        m_tiet2->setCurrentText(m_cacTiet.at(1));
        m_tiet3->setCurrentText("");
        m_tiet4->setCurrentText("");
        m_tiet5->setCurrentText("");
        break;
    case 3:
        m_tiet1->setCurrentText(m_cacTiet.at(0));
        m_tiet2->setCurrentText(m_cacTiet.at(1));
        m_tiet3->setCurrentText(m_cacTiet.at(2));
        m_tiet4->setCurrentText("");
        m_tiet5->setCurrentText("");
        break;
    case 4:
        m_tiet1->setCurrentText(m_cacTiet.at(0));
        m_tiet2->setCurrentText(m_cacTiet.at(1));
        m_tiet3->setCurrentText(m_cacTiet.at(2));
        m_tiet4->setCurrentText(m_cacTiet.at(3));
        m_tiet5->setCurrentText("");
        break;
    case 5:
        m_tiet1->setCurrentText(m_cacTiet.at(0));
        m_tiet2->setCurrentText(m_cacTiet.at(1));
        m_tiet3->setCurrentText(m_cacTiet.at(2));
        m_tiet4->setCurrentText(m_cacTiet.at(3));
        m_tiet5->setCurrentText(m_cacTiet.at(4));
        break;
    default:
        m_tiet1->setCurrentText("");
        m_tiet2->setCurrentText("");
        m_tiet3->setCurrentText("");
        m_tiet4->setCurrentText("");
        m_tiet5->setCurrentText("");
    }
}
