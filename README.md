# Quản lý và Xếp hạng Sinh viên – Bài tập lớn / Thực hành C++

## 1. Giới thiệu

Chương trình cài đặt hệ thống **Quản lý và Xếp hạng Sinh viên** bằng ngôn ngữ C++.

Chương trình hỗ trợ đọc dữ liệu sinh viên từ file văn bản, kiểm tra tính hợp lệ, lọc điều kiện, sắp xếp theo nhiều thuật toán khác nhau, thống kê học lực, chọn tiêu chí linh hoạt và xuất báo cáo ra các định dạng file CSV/TXT.

## 2. Cấu trúc dữ liệu

### 2.1. Cấu trúc SinhVien và SinhVienBiLoai

    struct SinhVien {
        string maSV;
        string hoTen;
        double gpa = 0;
        double diemRenLuyen = 0;
        int soTinChi = 0;
        int thuTu = 0;
    };

    struct SinhVienBiLoai {
        SinhVien sv;
        string lyDo;
    };

    vector<SinhVien> dsGoc;
    vector<SinhVien> dsDat;
    vector<SinhVien> dsXepHang;
    vector<SinhVienBiLoai> dsLoai;

Trong đó:
- `maSV`: Mã định danh của sinh viên.
- `hoTen`: Họ và tên sinh viên.
- `gpa`: Điểm trung bình tích lũy ($0 - 4$).
- `diemRenLuyen`: Điểm rèn luyện ($0 - 100$).
- `soTinChi`: Số tín chỉ đã tích lũy.
- `thuTu`: Lưu lại thứ tự đọc ban đầu để phục vụ ổn định thuật toán sắp xếp.

### 2.2. Cách tổ chức dữ liệu

Dữ liệu được quản lý tập trung thông qua các `vector` của Standard Template Library (STL), giúp linh hoạt trong việc thêm, xóa, lọc và sắp xếp danh sách sinh viên mà không bị giới hạn cứng số lượng phần tử.

## 3. Các chức năng

Chương trình cung cấp các chức năng chính sau:

- **F1 - Đọc file TXT**: Đọc file `sinhvien.txt`, kiểm tra lỗi dữ liệu đầu vào và bắt các trường hợp ngoại lệ.
- **F2 - Lọc sinh viên**: Lọc danh sách sinh viên đạt điều kiện (`GPA >= 2.0` và `Điểm rèn luyện >= 50`) và lưu danh sách sinh viên bị loại kèm lý do.
- **F3 - Sắp xếp danh sách**: Sắp xếp danh sách đạt điều kiện sử dụng 3 thuật toán: Insertion Sort, Selection Sort, Bubble Sort.
- **F4 - Chọn tiêu chí xếp hạng**: Cho phép người dùng chuyển đổi giữa các tiêu chí ưu tiên khi sắp xếp.
- **F5 - Top K và thống kê**: Hiển thị top $K$ sinh viên xuất sắc nhất và thống kê các chỉ số học lực toàn danh sách.
- **F6 - Xuất báo cáo**: Tự động tạo các file báo cáo (`valid.csv`, `rejected.csv`, `ranked.csv`, `summary.txt`).

## 4. Các hàm chính

| Hàm | Chức năng |
|---|---|
| `trim()` | Xóa khoảng trắng thừa ở đầu và cuối chuỗi. |
| `laSoThucHopLe()` / `laSoNguyenHopLe()` | Kiểm tra tính hợp lệ của kiểu dữ liệu số. |
| `F1_DocTXT()` | Đọc và kiểm tra lỗi file `sinhvien.txt`. |
| `F2_LocSinhVien()` | Phân loại sinh viên đạt/không đạt điều kiện. |
| `dungTruoc()` | Hàm so sánh hai sinh viên theo tiêu chí sắp xếp hiện hành. |
| `insertionSort()` | Thuật toán sắp xếp chèn. |
| `selectionSort()` | Thuật toán sắp xếp chọn. |
| `bubbleSort()` | Thuật toán sắp xếp nổi bọt. |
| `F3_XepHang()` | Thực thi thuật toán sắp xếp do người dùng lựa chọn. |
| `F4_ChonTieuChi()` | Thay đổi tiêu chí xếp hạng. |
| `F5_TopKVaThongKe()` | Hiển thị top $K$ sinh viên và thống kê học lực. |
| `F6_XuatBaoCao()` | Xuất toàn bộ kết quả ra các file CSV/TXT. |

## 5. Cách chạy chương trình

### 5.1. Biên dịch

Sử dụng trình biên dịch hỗ trợ C++11 trở lên.

    g++ main.cpp -o StudentManagement

### 5.2. Chạy chương trình

Chuẩn bị file `sinhvien.txt` cùng thư mục, sau đó chạy file thực thi:

Trên Windows:

    StudentManagement.exe

## 6. Kiểm thử

Các chức năng được kiểm thử với file dữ liệu mẫu và các trường hợp lỗi dữ liệu.

| STT | Chức năng kiểm thử | Kết quả mong đợi |
|---|---|---|
| 1 | Đọc file TXT hợp lệ | Đọc thành công, đếm đúng số sinh viên và bắt lỗi dữ liệu sai. |
| 2 | Lọc sinh viên | Tách chính xác danh sách đạt và danh sách bị loại kèm lý do. |
| 3 | Sắp xếp (Insertion Sort) | Sắp xếp chính xác theo tiêu chí giảm dần của GPA/Tín chỉ. |
| 4 | Sắp xếp (Selection Sort) | Sắp xếp chính xác bằng thuật toán chọn. |
| 5 | Sắp xếp (Bubble Sort) | Sắp xếp chính xác bằng thuật toán nổi bọt. |
| 6 | Chọn tiêu chí 1 | Ưu tiên GPA $\rightarrow$ Tín chỉ $\rightarrow$ Mã sinh viên. |
| 7 | Chọn tiêu chí 2 | Ưu tiên GPA, giữ nguyên thứ tự gốc nếu GPA bằng nhau. |
| 8 | Hiển thị Top K | In ra đúng $K$ sinh viên đứng đầu bảng xếp hạng. |
| 9 | Thống kê học lực | Tính toán chính xác điểm trung bình và phân loại học lực. |
| 10 | Xuất báo cáo | Tạo đầy đủ 4 file báo cáo `valid.csv`, `rejected.csv`, `ranked.csv`, `summary.txt`. |

## 7. Ví dụ cấu trúc file dữ liệu (`sinhvien.txt`)

Mỗi dòng biểu diễn một sinh viên, các trường cách nhau bởi dấu chấm phẩy (`;`):

    MaSV;HoTen;GPA;DiemRenLuyen;SoTinChi
    SV001;Nguyen Van An;3.50;85;120
    SV002;Tran Thi Binh;2.80;60;90
    SV003;Le Hoang Cuong;1.90;45;60

## 8. Đặc điểm của chương trình

- Sử dụng cấu trúc dữ liệu `struct` và `vector` của C++ STL giúp quản lý bộ nhớ linh hoạt.
- Tích hợp cơ chế kiểm tra lỗi dòng dữ liệu đầu vào chặt chẽ (phòng chống lỗi định dạng, tràn phạm vi, trùng mã sinh viên).
- Cung cấp tính năng tùy chọn nhiều thuật toán sắp xếp kinh điển.
- Hỗ trợ xuất báo cáo tự động ra các định dạng chuẩn (`.csv`, `.txt`) phục vụ lưu trữ.
- Giao diện console trực quan, dễ thao tác thông qua hệ thống menu số từ `0` đến `6`.

## 9. Thông tin sinh viên

- **Họ và tên:** Phạm Tùng Lâm
- **Mã sinh viên:** A52505
- **Lớp:** TC3801
- **Học phần:** Cấu trúc dữ liệu và giải thuật
- **Bài thực hành:** Quản lý và Xếp hạng Sinh viên
