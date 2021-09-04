#ifndef CUASOCHINH_H
#define CUASOCHINH_H

#include <QtWidgets>
#include <QApplication>
#include "CuaSoXemTruoc.h"
#include "ThoiKhoaBieu.h"

class CuaSoQuanLi : public QMainWindow
{
    Q_OBJECT

public:
    CuaSoQuanLi();

private slots:
    void anNutThamGia();
    void anNutRoiKhoi();
    void xuatFile();
    void clickChonKhungDangThamGia();
    void clickChonKhungChuaThamGia();
    void xemTruocFile();
    void suaThoiKhoaBieu();
    void thongTinUngDung();

private:
    void khoiTaoGiaoDien();
    void khoiTaoThanhDanhMuc();
    void khoiTaoThanhCongCu();
    void khoiTaoThanhTrangThai();
	
	//Phương thức  đọc thông tin thành viên
    void layThongTinDanhSach();

	//Các phương thức tạo thông tin
    QString taoNgayTheoDoi();
    QString taoThongTinTiet() ;
    QString taoThongTinThamGia();
    QString taoThongTinCacThanhVien();

    //Các Action của menu tệp
    QAction *m_xemTruoc;
    QAction *m_xuatTep;

    //Các Action của menu chức năng
    QAction *m_tietHoc;

    //Các Action của menu trợ giúp
    QAction *m_veUngDung;
    QAction *m_veQt;

    //Các thuộc tính lưu thông tin để xuất ra file
    __int8 m_vang;
    __int8 m_gianDoan;

    QList<QString> m_danhSachThamGia; //Danh sách chứa các thành viên đang tham gia làm thông tin cho mô hình
    QList<QString> m_danhSachChuaThamGia; //Danh sách chứa các thành viên chưa tham gia làm thông tin cho mô hình
    QList<QString> m_danhSachGianDoan; //Danh sách chứa các thành viên tham gia gián đoạn
    QList<QString> m_danhSachVang; //Danh sách chứa các thành viên vắng
	
	//Thông tin chung về tổ
	QList<QString> m_danhSachThanhVien; //Danh sách chứa toàn bộ thành viên trong tổ
	__int8 m_soThanhVien; //Chứa số thành viên

    //Các mô hình và khung nhìn
    QStringListModel *m_moHinhNguoiDungDangThamGia; //Lưu trữ mô hình người dùng đang tham gia
    QListView *m_khungNhinNguoiDungDangThamGia; //Khung nhìn người dùng đang tham gia

    QStringListModel *m_moHinhNguoiDungChuaThamGia; //Lưu trữ mô hình người dùng chưa tham gia
    QListView *m_khungNhinNguoiDungChuaThamGia; //Khung nhìn người dùng chưa tham gia

    QString m_noiDung; //Lưu trữ thông tin để xuất ra file

    QPushButton *m_roiKhoi; //Nút chọn khi ai đó thoát
    QPushButton *m_thamGia; //Nút chọn khi có người tham gia

    //Các cửa sổ
    CuaSoThoiKhoaBieu *m_cuaSoThoiKhoaBieu;
    CuaSoXemTruoc *m_cuaSoXemTruoc;
};


#endif // CUASOCHINH_H
