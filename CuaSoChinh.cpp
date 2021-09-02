#include "CuaSoChinh.h"
#include "CuaSoXemTruoc.h"

CuaSoQuanLi::CuaSoQuanLi() : QMainWindow(nullptr) {

    //Tạo các thành phần của giao diện
    khoiTaoGiaoDien();
    khoiTaoThanhDanhMuc();
    khoiTaoThanhCongCu();
    khoiTaoThanhTrangThai();

    //Tạo thông tin ngày tháng theo dõi
    khoiTaoNgayTheoDoi();

    setWindowIcon(QIcon(":/icons/User.png"));
    setWindowTitle(tr("Trình theo dõi"));
    setMinimumSize(500, 300);
}

void CuaSoQuanLi::khoiTaoGiaoDien() {

    //Lấy thông tin về danh sách học sinh cho vào mô hình chưa tham gia
    layThongTinDanhSach();

    //Khung nhìn học sinh đã tham gia
    QLabel *nhanDanhSachThamGia = new QLabel(tr("Danh sách học sinh đang tham gia:"));

    m_moHinhNguoiDungDangThamGia = new QStringListModel(QStringList(tr("Chưa có học sinh nào tham gia!")));

    m_khungNhinNguoiDungDangThamGia = new QListView();
        m_khungNhinNguoiDungDangThamGia->setModel(m_moHinhNguoiDungDangThamGia);
        m_khungNhinNguoiDungDangThamGia->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Khung nhìn học sinh chưa tham gia
    QLabel *nhanDanhSachChuaThamGia = new QLabel(tr("Danh sách học sinh chưa tham gia:"));

    m_khungNhinNguoiDungChuaThamGia = new QListView();
        m_khungNhinNguoiDungChuaThamGia->setModel(m_moHinhNguoiDungChuaThamGia);
        m_khungNhinNguoiDungChuaThamGia->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Các nút chức năng
    m_roiKhoi = new QPushButton(tr("Rời khỏi"));
        m_roiKhoi->setIcon(QIcon(":/icons/UserQuit.png"));
        m_roiKhoi->setToolTip(tr("Đánh dấu người đang chọn là đã thoát"));
        m_roiKhoi->setCursor(Qt::PointingHandCursor);
        m_roiKhoi->setVisible(false);

    m_thamGia = new QPushButton(tr("Tham gia"));
        m_thamGia->setIcon(QIcon(":/icons/Join.png"));
        m_thamGia->setToolTip(tr("Đánh dấu một người đang chọn là đã tham gia"));
        m_thamGia->setCursor(Qt::PointingHandCursor);
        m_thamGia->setVisible(false);

    QHBoxLayout *lopSapXepCacNut = new QHBoxLayout();
        lopSapXepCacNut->addWidget(m_thamGia);
        lopSapXepCacNut->addWidget(m_roiKhoi);
        lopSapXepCacNut->setAlignment(Qt::AlignCenter);

    QVBoxLayout *lopChinh = new QVBoxLayout();
        lopChinh->addWidget(nhanDanhSachThamGia);
        lopChinh->addWidget(m_khungNhinNguoiDungDangThamGia);
        lopChinh->addLayout(lopSapXepCacNut);
        lopChinh->addWidget(nhanDanhSachChuaThamGia);
        lopChinh->addWidget(m_khungNhinNguoiDungChuaThamGia);


    QWidget *giaoDien = new QWidget;
    giaoDien->setLayout(lopChinh);

    setCentralWidget(giaoDien);

    connect(m_thamGia, SIGNAL(clicked()), this, SLOT(anNutThamGia()));
    connect(m_roiKhoi, SIGNAL(clicked()), this, SLOT(anNutRoiKhoi()));
    connect(m_khungNhinNguoiDungDangThamGia, SIGNAL(clicked(const QModelIndex &)), this, SLOT(clickChonKhungDangThamGia()));
    connect(m_khungNhinNguoiDungChuaThamGia, SIGNAL(clicked(const QModelIndex &)), this, SLOT(clickChonKhungChuaThamGia()));
}

void CuaSoQuanLi::khoiTaoThanhDanhMuc() {
    //Các thao tác menu tệp
    m_xemTruoc = new QAction(tr("Xem trước file theo dõi"));
        m_xemTruoc->setShortcut(QKeySequence(tr("Ctrl+P", "Phím tắt xem trước file")));
        m_xemTruoc->setIcon(QIcon(":/icons/Documents.png"));

    m_xuatTep = new QAction(tr("Xuất"));
        m_xuatTep->setIcon(QIcon(":/icons/Export.png"));
        m_xuatTep->setShortcut(QKeySequence(tr("Ctrl+E", "Phím tắt xuất file")));

    //Menu Tệp
    QMenu *menuTep = menuBar()->addMenu(tr("Tệp"));
        menuTep->addAction(m_xemTruoc);
        menuTep->addAction(m_xuatTep);

    //Tín hiệu của menu tệp
    connect(m_xemTruoc, SIGNAL(triggered(bool)), this, SLOT(xemTruocFile()));
    connect(m_xuatTep, SIGNAL(triggered(bool)), this, SLOT(xuatFile()));


    //Menu Chức năng
    QMenu *menuChucNang = menuBar()->addMenu(tr("Chức năng"));


    //Action menu trợ giúp
    m_veUngDung = new QAction(tr("Về ứng dụng"));
        m_veUngDung->setIcon(QIcon(":/icons/Information.png"));
        m_veUngDung->setShortcut(QKeySequence(tr("Ctrl+B", "Phím tắt thông tin ứng dụng")));

    m_veQt = new QAction(tr("Về Qt"));
        m_veQt->setIcon(QIcon(":/icons/LogoQt"));
        m_veQt->setShortcut(QKeySequence(tr("Ctrl+Alt+B", "Phím tắt thông tin Qt")));

    //Menu Trợ giúp
    QMenu *menuTroGiup = menuBar()->addMenu(tr("?"));
        menuTroGiup->addAction(m_veUngDung);
        menuTroGiup->addAction(m_veQt);

    connect(m_veUngDung, SIGNAL(triggered(bool)), this, SLOT(thongTinUngDung()));
    connect(m_veQt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
}

void CuaSoQuanLi::khoiTaoThanhCongCu() {

}

void CuaSoQuanLi::khoiTaoThanhTrangThai() {
    statusBar()->showMessage(tr("Chào mừng"));
}

void CuaSoQuanLi::layThongTinDanhSach() {

    QFile danhSach("Member.txt");

    QStringList ten;

    if(!danhSach.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, tr("Lỗi"), tr("Không thể mở file danh sách để đọc"));
    }
    else {
        QTextStream in(&danhSach);

        while(!in.atEnd()) {
            QString tenDocDuoc;
            tenDocDuoc = in.readLine();
            ten << tenDocDuoc;
        }
    }

    if(ten.isEmpty()) {
        ten << "Không thể đọc file!";
    }

    m_moHinhNguoiDungChuaThamGia = new QStringListModel(ten);
}

void CuaSoQuanLi::anNutThamGia() {

}

void CuaSoQuanLi::anNutRoiKhoi() {

}

void CuaSoQuanLi::xuatFile() {
    QString duongDan = QFileDialog::getSaveFileName(this, tr("Lưu file"), "D:", tr("Text Documents (*.txt)"));

    QFile banGhi(duongDan);

    if(!banGhi.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Lỗi"), tr("Không thể xuất file.\n<b>Lưu ý:</b> Nếu lưu file ở ổ C:. Vui lòng chạy chương trình bằng quyền quản trị viên!"));
        return;
    }

    QTextStream out(&banGhi);

    out << m_thongTin;

    statusBar()->showMessage(tr("Đã lưu tệp"));
}

void CuaSoQuanLi::xemTruocFile() {
    CuaSoXemTruoc cuaSo(m_thongTin, this);
    cuaSo.exec();
}

void CuaSoQuanLi::clickChonKhungChuaThamGia() {
    if(m_roiKhoi->isVisible()) {
        m_roiKhoi->setVisible(false);
    }

    if(!m_thamGia->isVisible()) {
        m_thamGia->setVisible(true);
    }
}

void CuaSoQuanLi::clickChonKhungDangThamGia() {
    if(!m_roiKhoi->isVisible()) {
        m_roiKhoi->setVisible(true);
    }

    if(m_thamGia->isVisible()) {
        m_thamGia->setVisible(false);
    }
}

void CuaSoQuanLi::khoiTaoNgayTheoDoi() {
    QDate ngayThang;

    QString ngayThangTA = ngayThang.currentDate().toString(tr("ddd, ngày dd tháng MM năm yyyy"));
    QString ngayThangTV;

    if(ngayThangTA.left(3) == tr("Mon"))
    {
        ngayThangTV += tr("Thứ hai, ");
    }
    else if (ngayThangTA.left(3) == tr("Tue")) {
        ngayThangTV += tr("Thứ ba, ");
    }
    else if (ngayThangTA.left(3) == tr("Wed")) {
        ngayThangTV += tr("Thứ tư, ");
    }
    else if (ngayThangTA.left(3) == tr("Thu")) {
        ngayThangTV += tr("Thứ năm, ");
    }
    else if (ngayThangTA.left(3) == tr("Fri")) {
        ngayThangTV += tr("Thứ sáu, ");
    }
    else if (ngayThangTA.left(3) == tr("Sat")) {
        ngayThangTV += tr("Thứ bảy, ");
    }
    else if (ngayThangTA.left(3) == tr("Sun")) {
        ngayThangTV += tr("Chủ nhật, ");
    }

    ngayThangTV += ngayThangTA.right(ngayThangTA.size() - 5);

    m_thongTin = ngayThangTV + "\n";
}

void CuaSoQuanLi::thoat() {
    QFile temp("D:/temp.txt");

    if(temp.open(QIODevice::WriteOnly))
    {
        QTextStream out(&temp);
        out << m_thongTin;
    }
    else
    {
        return;
    }
}

void CuaSoQuanLi::thongTinUngDung() {
    QString thongTin = tr("<i>Ứng dụng theo dõi việc tham gia học trực tuyến của học sinh!</i>");
    thongTin += tr("<br><i>Được hoàn thành ngày dd tháng mm năm yyyy</i>");
    thongTin += tr("<br><i>Mã nguồn dự án có thể được tải về miễn phí <a href=\"https://github.com/tranmanhlt7a4/Theo_doi\">tại đây</a>.</i>");
    QMessageBox::information(this, tr("Về ứng dụng này"), thongTin);
}
