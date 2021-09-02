#ifndef CUASOCHINH_H
#define CUASOCHINH_H

#include <QtWidgets>
#include <QApplication>

class CuaSoQuanLi : public QMainWindow
{
    Q_OBJECT

public:
    CuaSoQuanLi();

public slots:
    void thoat(); //SLot thực hiện lưu file khi thoát đề phòng mất dữ liệu

private slots:
    void anNutThamGia();
    void anNutRoiKhoi();
    void xuatFile();
    void clickChonKhungDangThamGia();
    void clickChonKhungChuaThamGia();
    void xemTruocFile();
    void thongTinUngDung();

private:
    void khoiTaoGiaoDien();
    void khoiTaoThanhDanhMuc();
    void khoiTaoThanhCongCu();
    void khoiTaoThanhTrangThai();
    void layThongTinDanhSach();
    void khoiTaoNgayTheoDoi();

    //Các Action của menu tệp
    QAction *m_xemTruoc;
    QAction *m_xuatTep;

    //Các Action của menu chức năng
    QAction *m_tietHoc;

    //Các Action của menu trợ giúp
    QAction *m_veUngDung;
    QAction *m_veQt;

    QStringListModel *m_moHinhNguoiDungDangThamGia; //Lưu trữ mô hình người dùng đang tham gia
    QListView *m_khungNhinNguoiDungDangThamGia; //Khung nhìn người dùng đang tham gia

    QStringListModel *m_moHinhNguoiDungChuaThamGia; //Lưu trữ mô hình người dùng chưa tham gia
    QListView *m_khungNhinNguoiDungChuaThamGia; //Khung nhìn người dùng chưa tham gia

    QString m_thongTin; //Lưu trữ thông tin để xuất ra file

    QPushButton *m_roiKhoi; //Nút chọn khi ai đó thoát
    QPushButton *m_thamGia; //Nút chọn khi có người tham gia
};


#endif // CUASOCHINH_H
