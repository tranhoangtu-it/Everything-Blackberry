# Everything-BlackBerry 🫐 — Tóm Tắt Tiếng Việt

> Kho lưu trữ toàn diện nhất về thiết bị, phần mềm và lịch sử BlackBerry.

---

## 🎯 Giới Thiệu

**Everything-BlackBerry** là một kho tài liệu mã nguồn mở, tổng hợp kiến thức kỹ thuật cao về các thiết bị BlackBerry — từ cách vượt qua màn hình kích hoạt cho đến hướng dẫn lập trình ứng dụng gốc trên nền tảng QNX.

Dù bạn là **người mới mua máy**, **lập trình viên** muốn xây dựng ứng dụng native, hay **nhà sưu tầm** đam mê lịch sử RIM — kho lưu trữ này có đủ mọi thứ bạn cần.

---

## 📡 Trạng Thái Năm 2026

| Dịch Vụ / Tính Năng | Trạng Thái | Ghi Chú |
|---------------------|-----------|---------|
| **Hạ tầng BlackBerry (BIS/BES)** | ❌ Đã dừng | Tắt ngày 4/1/2022 |
| **Hệ điều hành BB10** | ✅ Hoạt động | Dùng offline và Wi-Fi bình thường |
| **BlackBerry World** | ❌ Đã đóng | Dùng sideloading thay thế |
| **BBM** | ❌ Đã dừng | Tắt ngày 31/5/2019 |
| **Telegram (qua Bgram)** | ✅ Hoạt động | Lựa chọn nhắn tin tốt nhất |
| **Email (IMAP/SMTP)** | ✅ Hoạt động | Ứng dụng mail native BB10 vẫn dùng được |
| **Trình duyệt BB10** | ⚠️ Một phần | Cần sửa chứng chỉ SSL |
| **Android Runtime** | ✅ Hoạt động | Chạy được APK thời Android 4.3 |

---

## 📁 Cấu Trúc Kho Lưu Trữ

```
Everything-BlackBerry/
├── README.md                        ← Tài liệu chính (Tiếng Anh)
├── README_VN.md                     ← Bạn đang đọc file này
├── CONTRIBUTING.md                  ← Hướng dẫn đóng góp
├── LICENSE                          ← Giấy phép MIT
│
├── 01_Survival_Guide/               ← Hướng dẫn sinh tồn cho người mới
│   ├── Bypassing_Setup_Screen.md    ← Vượt qua màn hình kích hoạt BBID
│   ├── Sideloading_Masterclass.md   ← Cài ứng dụng .bar và .apk
│   ├── Certificates_Fix.md          ← Sửa lỗi chứng chỉ SSL/TLS
│   └── Working_Apps_Directory.md   ← Danh sách app còn hoạt động 2026
│
├── 02_Development_Suite/            ← Phát triển ứng dụng native BB10
│   ├── Cascades_Qt_Setup.md         ← Cài đặt Momentics IDE
│   ├── Hello_BlackBerry_Native.cpp  ← Ví dụ Hello World Cascades/Qt
│   ├── Native_UI_Patterns.md        ← Hub, Active Frames, cử chỉ Peek
│   └── Android_Runtime_Optimization.md
│
├── 03_Device_Museum/                ← Bảo tàng thiết bị
│   ├── devices_database.json        ← Cơ sở dữ liệu 20+ thiết bị
│   ├── Focus_Classic_Q20.md         ← Phân tích sâu: BlackBerry Classic
│   └── Focus_Passport.md           ← Phân tích sâu: BlackBerry Passport
│
├── 04_Tools_Archive/                ← Kho công cụ và firmware
│   ├── Autoloader_Directory.md      ← Danh mục firmware autoloader
│   └── PC_Software_Legacy.md       ← BB Link & Blend trên Win10/11
│
└── 05_Community_&_History/         ← Cộng đồng và lịch sử
    ├── Historical_Timeline.md       ← Dòng thời gian từ 1984 đến nay
    └── Resources_&_Links.md        ← Các nguồn tài nguyên tốt nhất
```

---

## 🚀 Bắt Đầu Nhanh

### Mới mua máy? Đọc theo thứ tự này:

1. **[Vượt qua màn hình Setup](01_Survival_Guide/Bypassing_Setup_Screen.md)** — Bước đầu tiên bắt buộc
2. **[Sửa chứng chỉ SSL](01_Survival_Guide/Certificates_Fix.md)** — Để trình duyệt hoạt động
3. **[Hướng dẫn Sideloading](01_Survival_Guide/Sideloading_Masterclass.md)** — Cài ứng dụng từ bên ngoài
4. **[Danh sách app hoạt động](01_Survival_Guide/Working_Apps_Directory.md)** — Biết cần cài gì

### Là lập trình viên?

1. **[Cài đặt Cascades/Qt](02_Development_Suite/Cascades_Qt_Setup.md)**
2. **[Ví dụ Hello World](02_Development_Suite/Hello_BlackBerry_Native.cpp)**
3. **[Kiến trúc UI native](02_Development_Suite/Native_UI_Patterns.md)**

---

## 🤝 Đóng Góp

Xem **[CONTRIBUTING.md](CONTRIBUTING.md)** để biết cách đóng góp hướng dẫn, sửa lỗi hoặc cập nhật dữ liệu thiết bị.

Mọi đóng góp dù nhỏ đều được đánh giá cao. Cộng đồng BlackBerry sống nhờ sự chia sẻ kiến thức của mọi người! 🫐

---

## 📜 Giấy Phép

Dự án này được phát hành dưới **Giấy phép MIT**. Xem file [LICENSE](LICENSE) để biết thêm.

---

*Dự án được duy trì bởi cộng đồng, không có sự liên kết với BlackBerry Limited hay TCL Communication.*
