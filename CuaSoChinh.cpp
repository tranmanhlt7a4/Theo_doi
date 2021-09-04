#include "CuaSoChinh.h"

CuaSoQuanLi::CuaSoQuanLi() : QMainWindow(nullptr) {

    //Tạo các thành phần của giao diện
    khoiTaoGiaoDien();
    khoiTaoThanhDanhMuc();
    khoiTaoThanhCongCu();
    khoiTaoThanhTrangThai();

    //Khởi tạo các cửa sổ
    m_cuaSoThoiKhoaBieu = new CuaSoThoiKhoaBieu(this);
    m_cuaSoXemTruoc = new CuaSoXemTruoc("", this);

    suaThoiKhoaBieu();

    setWindowIcon(QIcon(":/icons/icons/User.png"));
    setWindowTitle(tr("Trình theo dõi"));
    setMinimumSize(500, 300);
}

//Các phương thức private khởi tạo giao diện
void CuaSoQuanLi::khoiTaoGiaoDien() {

    //Lấy thông tin về danh sách học sinh cho vào mô hình chưa tham gia
    layThongTinDanhSach();

    //Khung nhìn học sinh đã tham gia
    QLabel *nhanDanhSachThamGia = new QLabel(tr("Danh sách học sinh đang tham gia:"));

    m_moHinhNguoiDungDangThamGia = new QStringListModel(QStringList());

    m_khungNhinNguoiDungDangThamGia = new QListView();
        m_khungNhinNguoiDungDangThamGia->setModel(m_moHinhNguoiDungDangThamGia);
        m_khungNhinNguoiDungDangThamGia->setEditTriggers(QAbstractItemView::NoEditTriggers);
        m_khungNhinNguoiDungDangThamGia->setSelectionMode(QAbstractItemView::ExtendedSelection);

    //Khung nhìn học sinh chưa tham gia
    QLabel *nhanDanhSachChuaThamGia = new QLabel(tr("Danh sách học sinh chưa tham gia:"));

    m_khungNhinNguoiDungChuaThamGia = new QListView();
        m_khungNhinNguoiDungChuaThamGia->setModel(m_moHinhNguoiDungChuaThamGia);
        m_khungNhinNguoiDungChuaThamGia->setEditTriggers(QAbstractItemView::NoEditTriggers);
        m_khungNhinNguoiDungChuaThamGia->setSelectionMode(QAbstractItemView::ExtendedSelection);

    //Các nút chức năng
    m_roiKhoi = new QPushButton(tr("Rời khỏi"));
        m_roiKhoi->setIcon(QIcon(":/icons/icons/UserQuit.png"));
        m_roiKhoi->setToolTip(tr("Đánh dấu người đang chọn là đã thoát"));
        m_roiKhoi->setCursor(Qt::PointingHandCursor);
        m_roiKhoi->setVisible(false);

    m_thamGia = new QPushButton(tr("Tham gia"));
        m_thamGia->setIcon(QIcon(":/icons/icons/Join.png"));
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
        m_xemTruoc->setIcon(QIcon(":/icons/icons/Documents.png"));

    m_xuatTep = new QAction(tr("Xuất"));
        m_xuatTep->setIcon(QIcon(":/icons/icons/Export.png"));
        m_xuatTep->setShortcut(QKeySequence(tr("Ctrl+E", "Phím tắt xuất file")));

    //Menu Tệp
    QMenu *menuTep = menuBar()->addMenu(tr("Tệp"));
        menuTep->addAction(m_xemTruoc);
        menuTep->addAction(m_xuatTep);

    //Tín hiệu của menu tệp
    connect(m_xemTruoc, SIGNAL(triggered(bool)), this, SLOT(xemTruocFile()));
    connect(m_xuatTep, SIGNAL(triggered(bool)), this, SLOT(xuatFile()));


    //Action menu chức năng
    QAction *suaThoiKhoaBieu = new QAction(tr("Sửa thời khóa biểu"));
        suaThoiKhoaBieu->setIcon(QIcon(":/icons/icons/Timetable.ico"));

    //Menu Chức năng
    QMenu *menuChucNang = menuBar()->addMenu(tr("Chức năng"));
        menuChucNang->addAction(suaThoiKhoaBieu);

    connect(suaThoiKhoaBieu, SIGNAL(triggered(bool)), this, SLOT(suaThoiKhoaBieu()));

    //Action menu trợ giúp
    m_veUngDung = new QAction(tr("Về ứng dụng"));
        m_veUngDung->setIcon(QIcon(":/icons/icons/Information.png"));
        m_veUngDung->setShortcut(QKeySequence(tr("Ctrl+B", "Phím tắt thông tin ứng dụng")));

    m_veQt = new QAction(tr("Về Qt"));
        m_veQt->setIcon(QIcon(":/icons/icons/LogoQt"));
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

//Phương thức private đọc thông tin thành viên
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
			m_danhSachThanhVien << tenDocDuoc;
        }
    }

    if(ten.isEmpty()) {
        ten << "";
		m_danhSachThanhVien << "";
		m_soThanhVien = 0;
    }

    m_vang = ten.size();
    m_gianDoan = 0;
	m_soThanhVien = m_danhSachThanhVien.size();
	
    m_danhSachVang.append(ten);

    m_danhSachChuaThamGia.append(ten);
    m_moHinhNguoiDungChuaThamGia = new QStringListModel(ten);
}

//Phương thức private tạo các thông tin
QString CuaSoQuanLi::taoThongTinTiet() {

    QString thongTinTiet;

    thongTinTiet += "\n\n";
    thongTinTiet += tr("Số tiết: ") + QString::number(m_cuaSoThoiKhoaBieu->cacTiet().size()) + "\n";
    //Ghi các tiết
    for(int i = 0; i < m_cuaSoThoiKhoaBieu->cacTiet().size(); i++) {
        thongTinTiet += tr("Tiết ") + QString::number(i + 1) + ": " + m_cuaSoThoiKhoaBieu->cacTiet().at(i) + "\n";
    }
    return thongTinTiet;
}

QString CuaSoQuanLi::taoNgayTheoDoi() {
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

    return ngayThangTV;
}

QString CuaSoQuanLi::taoThongTinThamGia() {
    QString thongTinThamGia;

    thongTinThamGia += "\n\nVắng: " + QString::number(m_vang) + "\n";

    if(m_vang != 0) {
        //Thêm thông tin các thành viên vắng mặt
        thongTinThamGia += "Các thành viên vắng (Không tham gia từ đầu đến cuối):\n";
        for(int i = 0; i < m_danhSachVang.size(); i++) {
            thongTinThamGia += m_danhSachVang[i] + "\n";
        }
    }
	
	//Thêm các thành viên học gián đoạn
    thongTinThamGia += "\nTham gia gián đoạn (Có vào học nhưng thoát sớm): " + QString::number(m_gianDoan) + "\n";

    if(m_gianDoan != 0) {
        thongTinThamGia += "Các thành viên học gián đoạn:\n";
        for(int i = 0; i < m_danhSachGianDoan.size(); i++) {
            thongTinThamGia += m_danhSachGianDoan[i] + "\n";
        }
    }
	return thongTinThamGia;
}

QString CuaSoQuanLi::taoThongTinCacThanhVien() {
	QString thongTinThanhVien = "\n\n";
	
    thongTinThanhVien += tr("Tổ ") + m_cuaSoThoiKhoaBieu->to() + tr(" có %n thành viên\n", "", m_soThanhVien);
	for(int i = 0; i < m_soThanhVien; i++) {
		thongTinThanhVien += m_danhSachThanhVien[i] + "\n";
	}
	
	return thongTinThanhVien;
}

//Các slot
void CuaSoQuanLi::anNutThamGia() {

    QItemSelectionModel *luaChon = m_khungNhinNguoiDungChuaThamGia->selectionModel();
    QModelIndexList danhSachDuocChon = luaChon->selectedIndexes();


    for(int i = 0; i < danhSachDuocChon.size(); i++) {
        QVariant doiTuongDuocChon = m_moHinhNguoiDungChuaThamGia->data(danhSachDuocChon[i], Qt::DisplayRole);

        bool hocGianDoan = false;

        //Kiểm tra xem có phải là học gián đoạn hay không
        for(int i = 0; i < m_danhSachGianDoan.size(); i++) {
            if(m_danhSachGianDoan[i] == doiTuongDuocChon.toString()) {
                hocGianDoan = true;
                break;
            }
        }

        //Thêm vào danh sách đang tham gia
        m_danhSachThamGia << doiTuongDuocChon.toString();

        //Xóa khỏi danh sách chưa tham gia;
        m_danhSachChuaThamGia.removeOne(doiTuongDuocChon.toString());

        if(!hocGianDoan) {
            m_vang--;
            m_danhSachVang.removeOne(doiTuongDuocChon.toString());
        }
    }

    //Đặt lại mô hình
    m_moHinhNguoiDungDangThamGia->setStringList(m_danhSachThamGia);
    m_moHinhNguoiDungChuaThamGia->setStringList(m_danhSachChuaThamGia);
}

void CuaSoQuanLi::anNutRoiKhoi() {
    QItemSelectionModel *luaChon = m_khungNhinNguoiDungDangThamGia->selectionModel();
    QModelIndexList danhSachDuocChon = luaChon->selectedIndexes();


    for(int i = 0; i < danhSachDuocChon.size(); i++) {
        QVariant doiTuongDuocChon = m_moHinhNguoiDungDangThamGia->data(danhSachDuocChon[i], Qt::DisplayRole);

        bool daCo = false;

        //Kiểm tra xem có trong danh sách học gián đoạn hay không
        for(int i = 0; i < m_danhSachGianDoan.size(); i++) {
            if(m_danhSachGianDoan[i] == doiTuongDuocChon.toString()) {
                daCo = true;
                break;
            }
        }

        if(!daCo) {
            //Thêm vào danh sách học gián đoạn
            m_danhSachGianDoan << doiTuongDuocChon.toString();
            m_gianDoan++;
        }

        //Thêm vào danh sách chưa tham gia
        m_danhSachChuaThamGia << doiTuongDuocChon.toString();

        //Xóa khỏi danh sách tham gia
        m_danhSachThamGia.removeOne(doiTuongDuocChon.toString());
    }

    //Đặt lại mô hình
    m_moHinhNguoiDungChuaThamGia->setStringList(m_danhSachChuaThamGia);
    m_moHinhNguoiDungDangThamGia->setStringList(m_danhSachThamGia);
}

void CuaSoQuanLi::xuatFile()  {
    QString duongDan = QFileDialog::getSaveFileName(this, tr("Lưu file"), "D:", tr("Text Documents (*.txt)"));

    if(duongDan.right(4) != ".txt") {
        return;
    }

    QFile banGhi(duongDan);

    if(!banGhi.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Lỗi"), tr("Không thể xuất file.<br><b>Lưu ý:</b> Nếu lưu file ở ổ C:. Vui lòng chạy chương trình bằng quyền quản trị viên!"));
        return;
    }

    QTextStream out(&banGhi);

    m_noiDung = taoNgayTheoDoi() + taoThongTinCacThanhVien() + taoThongTinTiet() + taoThongTinThamGia() + "\n\nGhi chú: \n" + m_cuaSoXemTruoc->ghiChu();

    out << m_noiDung;

    statusBar()->showMessage(tr("Đã lưu tệp"));
}

void CuaSoQuanLi::xemTruocFile() {
    m_cuaSoXemTruoc->setNoiDungHienThi(taoNgayTheoDoi() + taoThongTinCacThanhVien() + taoThongTinTiet() + taoThongTinThamGia());
    m_cuaSoXemTruoc->exec();
}

void CuaSoQuanLi::suaThoiKhoaBieu() {
    m_cuaSoThoiKhoaBieu->exec();
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

void CuaSoQuanLi::thongTinUngDung() {
    QString thongTin = tr("Ứng dụng theo dõi việc tham gia học trực tuyến của học sinh!");
    thongTin += tr("<br>Được hoàn thành ngày dd tháng mm năm yyyy");
    thongTin += tr("<br>Mã nguồn dự án có thể được tải về miễn phí <a href=\"https://github.com/tranmanhlt7a4/Theo_doi\">tại đây</a>.");
    QMessageBox::information(this, tr("Về ứng dụng này"), thongTin);
}

