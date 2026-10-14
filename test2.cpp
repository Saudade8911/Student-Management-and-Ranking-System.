#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <cctype>

using namespace std;

// ==================== CAU TRUC DU LIEU ====================

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

string tieuChi = "GPA + Tin chi";
int soDongLoi = 0;

// ==================== HAM HO TRO ====================

string trim(string s) {
    size_t dau = s.find_first_not_of(" \t\r\n");
    if (dau == string::npos) return "";

    size_t cuoi = s.find_last_not_of(" \t\r\n");
    return s.substr(dau, cuoi - dau + 1);
}

bool laSoThucHopLe(const string& s, double& x) {
    stringstream ss(s);
    ss >> x;

    return !ss.fail() && ss.eof();
}

bool laSoNguyenHopLe(const string& s, int& x) {
    stringstream ss(s);
    ss >> x;

    return !ss.fail() && ss.eof();
}

string csvField(string s) {
    string kq = "\"";

    for (char c : s) {
        if (c == '"') kq += "\"\"";
        else kq += c;
    }

    kq += "\"";
    return kq;
}

void inTieuDe() {
    cout << left
         << setw(5)  << "STT"
         << setw(14) << "MaSV"
         << setw(30) << "Ho ten"
         << right
         << setw(8)  << "GPA"
         << setw(12) << "Ren luyen"
         << setw(10) << "Tin chi"
         << "\n";

    cout << string(79, '-') << "\n";
}

void inSinhVien(const SinhVien& sv, int stt) {
    cout << left
         << setw(5)  << stt
         << setw(14) << sv.maSV
         << setw(30) << sv.hoTen
         << right << fixed << setprecision(2)
         << setw(8)  << sv.gpa
         << setw(12) << sv.diemRenLuyen
         << setw(10) << sv.soTinChi
         << "\n";
}

void inDanhSach(const vector<SinhVien>& ds) {
    if (ds.empty()) {
        cout << "Danh sach rong!\n";
        return;
    }

    inTieuDe();

    for (int i = 0; i < (int)ds.size(); i++) {
        inSinhVien(ds[i], i + 1);
    }

    cout << "\nTong so sinh vien: " << ds.size() << "\n";
}

void ghiTieuDeCSV(ostream& out) {
    out << "MaSV,HoTen,GPA,DiemRenLuyen,SoTinChi\n";
}

void ghiDongCSV(ostream& out, const SinhVien& sv) {
    out << csvField(sv.maSV) << ","
        << csvField(sv.hoTen) << ","
        << fixed << setprecision(2) << sv.gpa << ","
        << sv.diemRenLuyen << ","
        << sv.soTinChi << "\n";
}

// ==================== F1: DOC FILE TXT ====================
// Dinh dang moi dong:
// MaSV;HoTen;GPA;DiemRenLuyen;SoTinChi
//
// Vi du:
// SV001;Nguyen Van An;3.50;85;120

void F1_DocTXT() {
    dsGoc.clear();
    dsDat.clear();
    dsXepHang.clear();
    dsLoai.clear();
    soDongLoi = 0;

    ifstream file("sinhvien.txt");

    if (!file.is_open()) {
        cout << "Khong mo duoc file sinhvien.txt!\n";
        cout << "Hay dat file cung thu muc voi chuong trinh.\n";
        return;
    }

    string line;
    int dong = 0;
    int soDongDoc = 0;

    while (getline(file, line)) {
        dong++;
        line = trim(line);

        if (line.empty()) continue;

        // Bo qua dong tieu de neu co
        if (dsGoc.empty() && soDongDoc == 0 &&
            line.find("MaSV") != string::npos) {
            soDongDoc++;
            continue;
        }

        soDongDoc++;

        vector<string> truong;
        string phanTu;
        stringstream ss(line);

        while (getline(ss, phanTu, ';')) {
            truong.push_back(trim(phanTu));
        }

        // Xu ly truong hop dong ket thuc bang dau ;
        if (!line.empty() && line.back() == ';') {
            truong.push_back("");
        }

        if (truong.size() != 5) {
            cout << "Dong " << dong
                 << ": Sai so luong truong du lieu.\n";
            soDongLoi++;
            continue;
        }

        bool rong = false;

        for (const string& x : truong) {
            if (x.empty()) {
                rong = true;
                break;
            }
        }

        if (rong) {
            cout << "Dong " << dong
                 << ": Co truong du lieu rong.\n";
            soDongLoi++;
            continue;
        }

        SinhVien sv;
        sv.maSV = truong[0];
        sv.hoTen = truong[1];

        if (!laSoThucHopLe(truong[2], sv.gpa) ||
            !laSoThucHopLe(truong[3], sv.diemRenLuyen) ||
            !laSoNguyenHopLe(truong[4], sv.soTinChi)) {
            cout << "Dong " << dong
                 << ": GPA, diem ren luyen hoac tin chi khong hop le.\n";
            soDongLoi++;
            continue;
        }

        if (sv.gpa < 0 || sv.gpa > 4 ||
            sv.diemRenLuyen < 0 || sv.diemRenLuyen > 100 ||
            sv.soTinChi < 0) {
            cout << "Dong " << dong
                 << ": Du lieu nam ngoai pham vi cho phep.\n";
            soDongLoi++;
            continue;
        }

        bool trung = false;

        for (const SinhVien& x : dsGoc) {
            if (x.maSV == sv.maSV) {
                trung = true;
                break;
            }
        }

        if (trung) {
            cout << "Dong " << dong
                 << ": Ma sinh vien bi trung.\n";
            soDongLoi++;
            continue;
        }

        sv.thuTu = dong;
        dsGoc.push_back(sv);
    }

    file.close();

    cout << "\nDoc file hoan tat!\n";
    cout << "So sinh vien doc hop le: " << dsGoc.size() << "\n";
    cout << "So dong loi: " << soDongLoi << "\n";

    if (!dsGoc.empty()) {
        inDanhSach(dsGoc);
    }
}

// ==================== F2: LOC SINH VIEN ====================
// Dieu kien dat:
// GPA >= 2.0 va diem ren luyen >= 50

void F2_LocSinhVien() {
    dsDat.clear();
    dsXepHang.clear();
    dsLoai.clear();

    if (dsGoc.empty()) {
        cout << "Chua co du lieu. Hay chay F1 truoc!\n";
        return;
    }

    for (const SinhVien& sv : dsGoc) {
        if (sv.gpa >= 2.0 && sv.diemRenLuyen >= 50) {
            dsDat.push_back(sv);
        } else {
            SinhVienBiLoai item;
            item.sv = sv;

            if (sv.gpa < 2.0 && sv.diemRenLuyen < 50) {
                item.lyDo = "GPA va diem ren luyen khong dat";
            } else if (sv.gpa < 2.0) {
                item.lyDo = "GPA duoi 2.0";
            } else {
                item.lyDo = "Diem ren luyen duoi 50";
            }

            dsLoai.push_back(item);
        }
    }

    cout << "\nKet qua loc sinh vien:\n";
    cout << "So sinh vien dat: " << dsDat.size() << "\n";
    cout << "So sinh vien bi loai: " << dsLoai.size() << "\n";

    inDanhSach(dsDat);
}

// ==================== F3: SAP XEP ====================

bool dungTruoc(const SinhVien& a, const SinhVien& b) {
    if (a.gpa != b.gpa) {
        return a.gpa > b.gpa;
    }

    if (tieuChi == "GPA + Tin chi") {
        if (a.soTinChi != b.soTinChi) {
            return a.soTinChi > b.soTinChi;
        }

        return a.maSV < b.maSV;
    }

    // Neu chi xep theo GPA, giu thu tu ban dau khi GPA bang nhau
    return a.thuTu < b.thuTu;
}

void insertionSort(vector<SinhVien>& ds) {
    for (int i = 1; i < (int)ds.size(); i++) {
        SinhVien key = ds[i];
        int j = i - 1;

        while (j >= 0 && dungTruoc(key, ds[j])) {
            ds[j + 1] = ds[j];
            j--;
        }

        ds[j + 1] = key;
    }
}

void selectionSort(vector<SinhVien>& ds) {
    for (int i = 0; i < (int)ds.size() - 1; i++) {
        int viTri = i;

        for (int j = i + 1; j < (int)ds.size(); j++) {
            if (dungTruoc(ds[j], ds[viTri])) {
                viTri = j;
            }
        }

        if (viTri != i) {
            swap(ds[i], ds[viTri]);
        }
    }
}

void bubbleSort(vector<SinhVien>& ds) {
    for (int i = 0; i < (int)ds.size() - 1; i++) {
        bool doiCho = false;

        for (int j = 0; j < (int)ds.size() - i - 1; j++) {
            if (dungTruoc(ds[j + 1], ds[j])) {
                swap(ds[j], ds[j + 1]);
                doiCho = true;
            }
        }

        if (!doiCho) break;
    }
}

void F3_XepHang() {
    if (dsDat.empty()) {
        cout << "Danh sach dat dieu kien rong. Hay chay F2 truoc!\n";
        return;
    }

    int luaChon;

    cout << "\nCHON THUAT TOAN SAP XEP\n";
    cout << "1. Insertion Sort\n";
    cout << "2. Selection Sort\n";
    cout << "3. Bubble Sort\n";
    cout << "Lua chon: ";

    if (!(cin >> luaChon)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Lua chon khong hop le!\n";
        return;
    }

    dsXepHang = dsDat;

    switch (luaChon) {
        case 1:
            insertionSort(dsXepHang);
            cout << "Da sap xep bang Insertion Sort.\n";
            break;

        case 2:
            selectionSort(dsXepHang);
            cout << "Da sap xep bang Selection Sort.\n";
            break;

        case 3:
            bubbleSort(dsXepHang);
            cout << "Da sap xep bang Bubble Sort.\n";
            break;

        default:
            cout << "Lua chon khong hop le!\n";
            dsXepHang.clear();
            return;
    }

    inDanhSach(dsXepHang);
}

// ==================== F4: CHON TIEU CHI ====================

void F4_ChonTieuChi() {
    int luaChon;

    cout << "\nCHON TIEU CHI XEP HANG\n";
    cout << "1. GPA giam dan, neu bang nhau thi tin chi giam dan,\n";
    cout << "   neu tiep tuc bang nhau thi ma sinh vien tang dan.\n";
    cout << "2. Chi xep theo GPA giam dan; GPA bang nhau giu thu tu goc.\n";
    cout << "Lua chon: ";

    if (!(cin >> luaChon)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Lua chon khong hop le!\n";
        return;
    }

    if (luaChon == 1) {
        tieuChi = "GPA + Tin chi";
    } else if (luaChon == 2) {
        tieuChi = "GPA";
    } else {
        cout << "Lua chon khong hop le!\n";
        return;
    }

    dsXepHang.clear();

    cout << "Da chon tieu chi: " << tieuChi << "\n";
    cout << "Hay chay F3 de sap xep lai danh sach.\n";
}

// ==================== F5: TOP K VA THONG KE ====================

void F5_TopKVaThongKe() {
    if (dsXepHang.empty()) {
        cout << "Chua co danh sach xep hang. Hay chay F3 truoc!\n";
        return;
    }

    int k;

    cout << "Nhap K: ";

    if (!(cin >> k)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "K khong hop le!\n";
        return;
    }

    if (k <= 0) {
        cout << "K phai lon hon 0!\n";
        return;
    }

    int n = min(k, (int)dsXepHang.size());

    cout << "\nTOP " << n << " SINH VIEN\n";
    inTieuDe();

    for (int i = 0; i < n; i++) {
        inSinhVien(dsXepHang[i], i + 1);
    }

    double tongGPA = 0;
    double tongRenLuyen = 0;
    int datGioi = 0;
    int datKha = 0;
    int datTrungBinh = 0;

    for (const SinhVien& sv : dsXepHang) {
        tongGPA += sv.gpa;
        tongRenLuyen += sv.diemRenLuyen;

        if (sv.gpa >= 3.2) {
            datGioi++;
        } else if (sv.gpa >= 2.5) {
            datKha++;
        } else {
            datTrungBinh++;
        }
    }

    cout << "\nTHONG KE DANH SACH XEP HANG\n";
    cout << fixed << setprecision(2);
    cout << "Tong so sinh vien: " << dsXepHang.size() << "\n";
    cout << "GPA trung binh: "
         << tongGPA / dsXepHang.size() << "\n";
    cout << "Diem ren luyen trung binh: "
         << tongRenLuyen / dsXepHang.size() << "\n";
    cout << "GPA tu 3.2 tro len: " << datGioi << "\n";
    cout << "GPA tu 2.5 den duoi 3.2: " << datKha << "\n";
    cout << "GPA duoi 2.5: " << datTrungBinh << "\n";
}

// ==================== F6: XUAT BAO CAO ====================

void F6_XuatBaoCao() {
    if (dsGoc.empty()) {
        cout << "Chua co du lieu. Hay chay F1 truoc!\n";
        return;
    }

    // Xuat danh sach du lieu doc hop le
    ofstream valid("valid.csv");

    if (!valid.is_open()) {
        cout << "Khong tao duoc valid.csv!\n";
        return;
    }

    ghiTieuDeCSV(valid);

    for (const SinhVien& sv : dsGoc) {
        ghiDongCSV(valid, sv);
    }

    valid.close();

    // Xuat sinh vien khong dat dieu kien loc
    ofstream rejected("rejected.csv");

    if (!rejected.is_open()) {
        cout << "Khong tao duoc rejected.csv!\n";
        return;
    }

    rejected << "MaSV,HoTen,GPA,DiemRenLuyen,SoTinChi,LyDoLoai\n";

    for (const SinhVienBiLoai& item : dsLoai) {
        const SinhVien& sv = item.sv;

        rejected << csvField(sv.maSV) << ","
                 << csvField(sv.hoTen) << ","
                 << fixed << setprecision(2) << sv.gpa << ","
                 << sv.diemRenLuyen << ","
                 << sv.soTinChi << ","
                 << csvField(item.lyDo) << "\n";
    }

    rejected.close();

    // Xuat danh sach xep hang neu da thuc hien F3
    ofstream ranked("ranked.csv");

    if (!ranked.is_open()) {
        cout << "Khong tao duoc ranked.csv!\n";
        return;
    }

    ranked << "Hang,MaSV,HoTen,GPA,DiemRenLuyen,SoTinChi\n";

    for (int i = 0; i < (int)dsXepHang.size(); i++) {
        const SinhVien& sv = dsXepHang[i];

        ranked << i + 1 << ","
               << csvField(sv.maSV) << ","
               << csvField(sv.hoTen) << ","
               << fixed << setprecision(2) << sv.gpa << ","
               << sv.diemRenLuyen << ","
               << sv.soTinChi << "\n";
    }

    ranked.close();

    // Xuat thong ke
    ofstream summary("summary.txt");

    if (!summary.is_open()) {
        cout << "Khong tao duoc summary.txt!\n";
        return;
    }

    summary << "BAO CAO XEP HANG SINH VIEN\n";
    summary << "==========================\n";
    summary << "So dong loi khi doc file: " << soDongLoi << "\n";
    summary << "So sinh vien doc hop le: " << dsGoc.size() << "\n";
    summary << "So sinh vien dat dieu kien: " << dsDat.size() << "\n";
    summary << "So sinh vien bi loai: " << dsLoai.size() << "\n";
    summary << "Tieu chi xep hang: " << tieuChi << "\n";
    summary << "So sinh vien da xep hang: "
            << dsXepHang.size() << "\n";

    if (!dsXepHang.empty()) {
        double tongGPA = 0;
        double tongRenLuyen = 0;

        for (const SinhVien& sv : dsXepHang) {
            tongGPA += sv.gpa;
            tongRenLuyen += sv.diemRenLuyen;
        }

        summary << fixed << setprecision(2);
        summary << "GPA trung binh: "
                << tongGPA / dsXepHang.size() << "\n";
        summary << "Diem ren luyen trung binh: "
                << tongRenLuyen / dsXepHang.size() << "\n";
    }

    summary.close();

    cout << "\nXuat bao cao hoan tat!\n";
    cout << "Cac file duoc tao:\n";
    cout << "- valid.csv\n";
    cout << "- rejected.csv\n";
    cout << "- ranked.csv\n";
    cout << "- summary.txt\n";
}

// ==================== MENU CHUONG TRINH ====================

int main() {
    int chon;

    do {
        cout << "\n========== QUAN LY SINH VIEN ==========\n";
        cout << "1. F1 - Doc file TXT\n";
        cout << "2. F2 - Loc sinh vien\n";
        cout << "3. F3 - Sap xep danh sach\n";
        cout << "4. F4 - Chon tieu chi xep hang\n";
        cout << "5. F5 - Top K va thong ke\n";
        cout << "6. F6 - Xuat bao cao\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";

        if (!(cin >> chon)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Vui long nhap mot so!\n";
            continue;
        }

        switch (chon) {
            case 1:
                F1_DocTXT();
                break;

            case 2:
                F2_LocSinhVien();
                break;

            case 3:
                F3_XepHang();
                break;

            case 4:
                F4_ChonTieuChi();
                break;

            case 5:
                F5_TopKVaThongKe();
                break;

            case 6:
                F6_XuatBaoCao();
                break;

            case 0:
                cout << "Da thoat chuong trinh.\n";
                break;

            default:
                cout << "Lua chon khong hop le!\n";
        }

    } while (chon != 0);

    return 0;
}