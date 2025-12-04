#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct pengguna{
    int id;
    string username;
    string password;
    long long saldo;
};

struct dataNisab{
    string jenis[15]= {
        "perhiasan",
        "perhiasan",
        "tani",
        "tani",
        "tani",
        "tani",
        "tani",
        "tanaman",
        "ternak",
        "ternak",
        "ternak",
        "ternak",
        "penghasilan",
        "properti",
        "rikaz"
    };
    string nama[15] = {
        "emas",
        "perak",
        "beras_putih",
        "padi_gagang",
        "padi_kretek",
        "kacang_hijau",
        "kacang_tunggak",
        "tanaman_produktif_dan_perikanan",
        "sapi",
        "kambing",
        "unta",
        "ternak_lain",
        "perusahaan",
        "properti",
        "barang_temuan",
    };
    float nisab[15] = {
        77.5,
        543.35,
        815.758,
        1631.516,
        1323.132,
        780.036,
        756.697,
        174970, // ribu
        30,
        40,
        5,
        174970,
        174970,
        174970,
        0,
    };
    string satuan[15] = {
        "gr",
        "gr",
        "kg",
        "kg",
        "kg",
        "kg",
        "kg",
        "rupiah",
        "ekor",
        "ekor",
        "ekor",
        "rupiah",
        "rupiah",
        "rupiah",
        "-",
    };
    string haul[15] = {
        "pertahun",
        "pertahun",
        "perpanen",
        "perpanen",
        "perpanen",
        "perpanen",
        "perpanen",
        "perpanen",
        "pertahun",
        "pertahun",
        "pertahun",
        "pertahun",
        "pertahun",
        "pertahun",
        "langsung"
    };
    float wajibZakat[15] = {
        2.5,
        2.5,
        5, // jika irigasi berbayar
        5, // jika irigasi berbayar
        5, // jika irigasi berbayar
        5, // jika irigasi berbayar
        5, // jika irigasi berbayar
        2.5,
        0, // menyesuaikan fungsi
        0, // menyesuaikan fungsi
        0, // menyesuaikan fungsi
        2.5,
        2.5,
        2.5,
        20
    }; // satuan %
    };
struct penghasilan{
    int id;
    int id_user;
    string pekerjaan;
    long long modal;
    long long gajiBulanan;
    long long piutang; // yang kira-kira bisa ditagih
    long long utang;
    long long kebutuhan;
    bool wajibZakat;
};
struct perhiasan{
    int id;
    int id_user;
    string nama;
    float berat; // gr
    long long hargaPerGram; // gr
    bool wajibZakat;
};
struct tani{
    int id;
    int id_user;
    string nama;
    float berat; // kg
    bool bayarIrigasi;
    bool wajibZakat;
};
struct tanaman{
    int id;
    int id_user;
    long long bibit;
    long long nuqud;
    long long piutang;
    long long utang;
    bool wajibZakat;
};
struct properti{
    int id;
    int id_user;
    long long biayaTanah; 
    long long biayaTanahBangunan; 
    long long biayaBahanBaku; 
    long long nuqud; 
    long long piutang;
    long long utang;
    bool wajibZakat;
};
struct rikaz{
    int id;
    int id_user;
    string barang;
    long long hargaBarang; //dikira-kira dalam rupiah
};
struct ternak{
    int id;
    int id_user;
    string nama; // kambing / sapi / unta
    int jumlah; 
    bool wajibZakat;
};

struct transaksi {
    int id;
    int id_pembayar;
    string jenis_zakat;
    long long jumlah;
    string tanggal;
    string status; // "pending", "verified", "distributed"
    int id_penerima; // 0 = belum didistribusi
    string keterangan;
};

struct mustahik {
    int id;
    string nama;
    string kategori; // fakir, miskin, amil, muallaf, riqab, gharimin, fisabilillah, ibnu sabil
    string alamat;
    string telepon;
    string keterangan;
    long long total_diterima;
    string tanggal_terakhir;
};

struct pengingat {
    int id_user;
    string jenis_zakat;
    string tanggal_akhir_haul;
    bool sudah_dibayar;
};

struct saldo {
    long long total_masuk;
    long long total_keluar;
    long long saldo_akhir;
};
struct ItemZakat {
        string deskripsi;     // Contoh: "Zakat Penghasilan - Karyawan"
        long long jumlah;     // Jumlah dalam Rupiah
        string jenis;         // "penghasilan", "perhiasan", "ternak"
        int id_data;          // ID data di file
    };
    

transaksi dataTransaksi[1000];
mustahik dataMustahik[100];
saldo saldoZakat;
int jumlahTransaksi = 0;
int jumlahMustahik = 0;

// ==================== FUNGSI BANTUAN ====================
string Rupiah(long long uang){
    string strUang =to_string(uang);
    string hasil;
    int sizeUang=strUang.length();
    for(int i=0;i<sizeUang;i++){
        hasil = strUang[(sizeUang-i)-1]+hasil;
        if((i+1)%3==0 && sizeUang-i>1){
            hasil = "."+hasil;
        }
    }
    return "Rp. "+hasil;
}
int autoIncrement(string nameFile){
    ifstream bacaDatabase2;
    int hasilId=1;
    string line;
    bacaDatabase2.open(nameFile);
    
    if(!bacaDatabase2.is_open()) {
        return 1; 
    }
    
    while(getline(bacaDatabase2, line)) {
        hasilId++;
    }
    bacaDatabase2.close();
    return hasilId;
}

long long cariNisabLong(string nama){
    dataNisab datanisab;
    long long nisab;
    for(int i=0;i<15;i++){
        if(datanisab.nama[i]==nama){
            nisab=(long long)datanisab.nisab[i];
            break;
        }
    }
    return nisab;
}
float cariNisabFloat(string nama){
    dataNisab datanisab;
    float nisab;
    for(int i=0;i<15;i++){
        if(datanisab.nama[i]==nama){
            nisab=datanisab.nisab[i];
            break;
        }
    }
    return nisab;
}
float cariZakatFloat(string nama){
    dataNisab datanisab;
    float wajibZakat;
    for(int i=0;i<15;i++){
        if(datanisab.nama[i]==nama){
            wajibZakat=datanisab.wajibZakat[i];
            break;
        }
    }
    return wajibZakat/100;
}
long long zakatPenghasilan(penghasilan &row){
    long long nisab = cariNisabLong("perusahaan");
    long long bruto = row.gajiBulanan*12+row.piutang;
    long long netto = bruto-(row.kebutuhan+row.utang+row.modal);
    if(netto>=nisab){
        row.wajibZakat=true;
        return (long long)(cariZakatFloat("perusahaan")*netto);
    } else{
        row.wajibZakat=false;
        return 0;
    }
};
long long zakatPerhiasan(perhiasan &row){
    string namaHarta=row.nama;
    float nisab=cariNisabFloat(namaHarta);
    if(row.berat>=nisab){
        row.wajibZakat=true;
        return (long long)((cariZakatFloat(namaHarta)*row.berat)*row.hargaPerGram);
    } else{
        row.wajibZakat=false;
        return 0;
    }
};
long long zakatTanaman(tanaman &row){
    long long nisab=cariNisabLong("tanaman_produktif_dan_perikanan")*1000;
    long long bruto = row.bibit+row.nuqud+row.piutang;
    long long netto = bruto - row.utang;
    if(netto>=nisab){
        row.wajibZakat=true;
        return (long long)(cariZakatFloat("tanaman_produktif_dan_perikanan")*netto);
    } else{
        row.wajibZakat=false;
        return 0;
    }
};
float zakatPertanian(tani &row){
    string namaHarta=row.nama;
    float nisab=cariNisabFloat(namaHarta);
    float wajibZakat=cariZakatFloat(namaHarta);
    if(row.berat>=nisab){
        row.wajibZakat=true;
        if(row.bayarIrigasi){
            return row.berat*wajibZakat;
        } else{
            return row.berat*(wajibZakat+0.05);
        }
    } else{
        row.wajibZakat=false;
        return 0;
    }
};
long long zakatProperti(properti &row){
    long long nisab=cariNisabLong("properti")*1000;
    float wajibZakat=cariZakatFloat("properti");
    long long bruto = row.biayaTanah + row.biayaTanahBangunan + row.biayaBahanBaku +row.nuqud + row.piutang;
    long long netto = bruto - row.utang;
    if(netto>=nisab){
        row.wajibZakat=true;
        return netto*wajibZakat;
    } else{
        row.wajibZakat=false;
        return 0;
    }
};
long long zakatRikaz(rikaz &row){
    float wajibZakat=cariZakatFloat("barang_temuan");
    return row.hargaBarang*wajibZakat;
};

string zakatTernak(ternak &row){
    float nisab = cariNisabFloat(row.nama);
    if(row.jumlah>=nisab){
        row.wajibZakat=true;
        if(row.nama=="unta"){
            if(row.jumlah>=140){
                int jumlahEkor[2]; // usia 3 dan 2 tahun
                int sisaEkor[2]; // pembagi 50 dan 40
                string hasil;
                jumlahEkor[0]=row.jumlah / 50;
                sisaEkor[0]=row.jumlah%50;
                jumlahEkor[1]=row.jumlah/40;
                sisaEkor[1]=row.jumlah%40;
                int minSisa[3]; // jml50, jml40, sisa
                if(sisaEkor[0]==0){
                    hasil="Wajib membayar "+to_string(jumlahEkor[0]);
                    return hasil +" ekor unta hiqqah (usia 3 tahun)";
                } else if(sisaEkor[1]==0){
                    hasil="Wajib membayar "+to_string(jumlahEkor[1]);
                    return hasil +" ekor unta bintu labun (usia 2 tahun)";
                }  else {
                    minSisa[0] = jumlahEkor[0]; // hiqqah
                    minSisa[1] = 0;             // labun
                    minSisa[2] = sisaEkor[0];   // sisa
                                
                    int tempHiqqah = jumlahEkor[0];
                    int tempLabun  = 0;
                    int tempSisa   = sisaEkor[0];
                                
                    while(tempHiqqah >= 0) {
                        tempSisa = row.jumlah - (tempHiqqah * 50 + tempLabun * 40);
                        while(tempSisa>=40){
                            tempLabun++;
                            tempSisa-=40;
                        }
                        if(tempSisa < minSisa[2]) {
                            minSisa[0] = tempHiqqah;
                            minSisa[1] = tempLabun;
                            minSisa[2] = tempSisa;
                        }
                        if(tempSisa <= 0){

                            break;
                        }
                        tempHiqqah--;
                        tempLabun++;
                    }

                        hasil = "Wajib membayar " + to_string(minSisa[0]) + " ekor unta hiqqah (usia 3 tahun)";
                        if(minSisa[1] > 0)
                            hasil += " dan " + to_string(minSisa[1]) + " ekor unta bintu labun (usia 2 tahun)";
                        return hasil;
                    }     
                
            } else if(row.jumlah>120){
                return "3 ekor unta betina bintu labun (usia 2 tahun)";
            } else if(row.jumlah>90){
                return "2 ekor unta betina hiqqah (usia 3 tahun)";
            } else if(row.jumlah>75){
                return "2 ekor unta betina bintu labun (usia 2 tahun)";
            } else if(row.jumlah>60){
                return "1 ekor unta betina hiqqah (usia 4 tahun)";
            } else if(row.jumlah>45){
                return "1 ekor unta betina hiqqah (usia 3 tahun)";
            } else if(row.jumlah>35){
                return "1 ekor unta betina bintu labun (usia 2 tahun)";
            } else if(row.jumlah>24){
                return "1 ekor unta betina Bintu makhad (usia 1 tahun)";
            } else if(row.jumlah>19){
                return "4 ekor kambing umur 2 tahun, atau 4 ekor domba umur 1 tahun";
            } else if(row.jumlah>14){
                return "3 ekor kambing umur 2 tahun, atau 3 ekor domba umur 1 tahun";
            } else if(row.jumlah>9){
                return "2 ekor kambing umur 2 tahun, atau 2 ekor domba umur 1 tahun";
            } else {
                return "1 ekor kambing umur 2 tahun, atau 1 ekor domba umur 1 tahun";
            }
            
        } else if(row.nama=="sapi"){
            if(row.jumlah>=60){
                int jumlahEkor[2]; // usia 2 dan 1 tahun Zakat
                int sisaEkor[2]; // pembagi 40 dan 30
                string hasil;
                jumlahEkor[0]=row.jumlah / 40;
                sisaEkor[0]=row.jumlah%40;
                jumlahEkor[1]=row.jumlah/30;
                sisaEkor[1]=row.jumlah%30;
                int minSisa[3]; // jml50, jml40, sisa
                if(sisaEkor[0]==0){
                    hasil="Wajib membayar "+to_string(jumlahEkor[0]);
                    return hasil +" ekor sapi musinnah (usia 2 tahun)";
                } else if(sisaEkor[1]==0){
                    hasil="Wajib membayar "+to_string(jumlahEkor[1]);
                    return hasil +" ekor sapi tabi' (usia 1 tahun)";
                }  else {
                    minSisa[0] = jumlahEkor[0]; // musinnah
                    minSisa[1] = 0;             // tabi'
                    minSisa[2] = sisaEkor[0];   // sisa
                                
                    int tempMusinnah = jumlahEkor[0];
                    int tempTabi  = 0;
                    int tempSisa   = sisaEkor[0];
                                
                    while(tempMusinnah >= 0) {
                        tempSisa = row.jumlah - (tempMusinnah * 40 + tempTabi * 30);
                        while(tempSisa>=30){
                            tempTabi++;
                            tempSisa-=30;
                        }
                        if(tempSisa < minSisa[2]) {
                            minSisa[0] = tempMusinnah;
                            minSisa[1] = tempTabi;
                            minSisa[2] = tempSisa;
                        }
                        if(tempSisa <= 0){

                            break;
                        }
                        tempMusinnah--;
                        tempTabi++;
                    }

                        hasil = "Wajib membayar " + to_string(minSisa[0]) + " ekor sapi musinnah (usia 2 tahun)";
                        if(minSisa[1] > 0)
                            hasil += " dan " + to_string(minSisa[1]) + " ekor sapi bintu tabi' (usia 1 tahun)";
                        return hasil;
                    }     
            } else if(row.jumlah>=40){
                return "1 ekor sapi musinnah (usia 2 tahun)";
            } else {
                return "1 ekor sapi tabi' (usia 1 tahun)";
            }

        } else if(row.nama=="kambing"){
            if(row.jumlah>=500){
                int hasil=row.jumlah/100;
                string strHasil ="Wajib membayar "+to_string(hasil);
                strHasil+=" ekor kambing usia 2 tahun atau domba usia 1 tahun";
                return strHasil;
            } else if(row.jumlah>=400){
                return "Wajib membayar 4 ekor kambing usia 2 tahun atau domba usia 1 tahun";
            } else if(row.jumlah>200){
                return "Wajib membayar 3 ekor kambing usia 2 tahun atau domba usia 1 tahun";
            } else if(row.jumlah>120){
                return "Wajib membayar 2 ekor kambing usia 2 tahun atau domba usia 1 tahun";
            } else {
                return "Wajib membayar 1 ekor kambing usia 2 tahun atau domba usia 1 tahun";
            }
        } else {
            return "input tidak valid";
        }
    } else{
        row.wajibZakat=false;
        return "Tidak Wajib Membayar Zakat";
    }
};

string padString(string str, int length) {
    if(str.length() > length) {
        return str.substr(0, length - 3) + "...";
    }
    
    string result = str;
    for(int i = str.length(); i < length; i++) {
        result += " ";
    }
    return result;
}

string padNumber(long long num, int length) {
    string str = to_string(num);
    if(str.length() > length) {
        return str.substr(0, length - 3) + "...";
    }
    
    string result = str;
    for(int i = str.length(); i < length; i++) {
        result = " " + result;
    }
    return result;
}

string padRight(string str, int length) {
    if(str.length() >= length) {
        return str.substr(0, length);
    }
    
    string result = str;
    for(int i = str.length(); i < length; i++) {
        result += " ";
    }
    return result;
}

string padLeft(string str, int length) {
    if(str.length() >= length) {
        return str.substr(0, length);
    }
    
    string result = "";
    for(int i = str.length(); i < length; i++) {
        result += " ";
    }
    result += str;
    return result;
}

void loadTransaksiFromFile() {
    ifstream file("transaksi.txt");
    if(file.is_open()) {
        jumlahTransaksi = 0;
        transaksi t;
        string status;
        while(file >> t.id >> t.id_pembayar >> t.jenis_zakat >> t.jumlah 
              >> t.tanggal >> status >> t.id_penerima) {
            getline(file, t.keterangan);
            t.status = status;
            dataTransaksi[jumlahTransaksi++] = t;
        }
        file.close();
    }
}

void saveTransaksiToFile() {
    ofstream file("transaksi.txt");
    for(int i = 0; i < jumlahTransaksi; i++) {
        file << dataTransaksi[i].id << " "
             << dataTransaksi[i].id_pembayar << " "
             << dataTransaksi[i].jenis_zakat << " "
             << dataTransaksi[i].jumlah << " "
             << dataTransaksi[i].tanggal << " "
             << dataTransaksi[i].status << " "
             << dataTransaksi[i].id_penerima
             << dataTransaksi[i].keterangan << endl;
    }
    file.close();
}

void loadMustahikFromFile() {
    ifstream file("mustahik.txt");
    if(file.is_open()) {
        jumlahMustahik = 0;
        mustahik m;
        while(file >> m.id >> m.nama >> m.kategori >> m.alamat 
              >> m.telepon >> m.total_diterima >> m.tanggal_terakhir) {
            getline(file, m.keterangan);
            dataMustahik[jumlahMustahik++] = m;
        }
        file.close();
    }
}

void saveMustahikToFile() {
    ofstream file("mustahik.txt");
    for(int i = 0; i < jumlahMustahik; i++) {
        file << dataMustahik[i].id << " "
             << dataMustahik[i].nama << " "
             << dataMustahik[i].kategori << " "
             << dataMustahik[i].alamat << " "
             << dataMustahik[i].telepon << " "
             << dataMustahik[i].total_diterima << " "
             << dataMustahik[i].tanggal_terakhir
             << dataMustahik[i].keterangan << endl;
    }
    file.close();
}

void updateSaldo() {
    saldoZakat.total_masuk = 0;
    saldoZakat.total_keluar = 0;
    
    for(int i = 0; i < jumlahTransaksi; i++) {
        if(dataTransaksi[i].status == "paid" || dataTransaksi[i].status == "distributed") {
            saldoZakat.total_masuk += dataTransaksi[i].jumlah;
        }
        if(dataTransaksi[i].status == "distributed") {
            saldoZakat.total_keluar += dataTransaksi[i].jumlah;
        }
    }
    saldoZakat.saldo_akhir = saldoZakat.total_masuk - saldoZakat.total_keluar;
}

string getCurrentDate() {
    return "2024-01-15";
}

// ==================== FUNGSI MENU ADMIN ====================
// ==================== FUNGSI MENU ADMIN (TANPA VERIFIKASI) ====================
void lihatSemuaTransaksi() {
    system("cls");
    cout << "=== DAFTAR SEMUA TRANSAKSI ===\n\n";
    
    // Load data terbaru
    loadTransaksiFromFile();
    
    if(jumlahTransaksi == 0) {
        cout << "Belum ada transaksi.\n";
        system("pause");
        return;
    }
    
    cout << "JUMLAH TRANSAKSI: " << jumlahTransaksi << "\n\n";
    
    // Hitung statistik
    int suksesCount = 0, distributedCount = 0, totalCount = 0;
    long long totalSukses = 0, totalDistributed = 0;
    
    for(int i = 0; i < jumlahTransaksi; i++) {
        totalCount++;
        if(dataTransaksi[i].status == "sukses") {
            suksesCount++;
            totalSukses += dataTransaksi[i].jumlah;
        } else if(dataTransaksi[i].status == "distributed") {
            distributedCount++;
            totalDistributed += dataTransaksi[i].jumlah;
        }
    }
    
    cout << "STATISTIK:\n";
    cout << "==========\n";
    cout << "Total Transaksi    : " << totalCount << endl;
    cout << "Transaksi Sukses   : " << suksesCount << " (" << Rupiah(totalSukses) << ")\n";
    cout << "Sudah Didistribusi : " << distributedCount << " (" << Rupiah(totalDistributed) << ")\n";
    cout << "Belum Didistribusi : " << (suksesCount - distributedCount) 
         << " (" << Rupiah(totalSukses - totalDistributed) << ")\n\n";
    
    cout << "DETAIL TRANSAKSI:\n";
    cout << "=================\n";
    
    for(int i = 0; i < jumlahTransaksi; i++) {
        cout << "ID: " << dataTransaksi[i].id << endl;
        cout << "Pembayar ID: " << dataTransaksi[i].id_pembayar << endl;
        cout << "Jenis: " << dataTransaksi[i].jenis_zakat << endl;
        cout << "Jumlah: " << Rupiah(dataTransaksi[i].jumlah) << endl;
        cout << "Tanggal: " << dataTransaksi[i].tanggal << endl;
        cout << "Status: " << dataTransaksi[i].status << endl;
        if(dataTransaksi[i].id_penerima != 0) {
            cout << "Penerima ID: " << dataTransaksi[i].id_penerima << endl;
        }
        cout << "Keterangan: " << dataTransaksi[i].keterangan << endl;
        cout << "---------------------------\n";
    }
    
    cout << "\nTekan Enter untuk kembali...";
    cin.ignore();
    cin.get();
}

void distribusiZakatKeMustahik() {
    system("cls");
    cout << "=== DISTRIBUSI ZAKAT KE MUSTAHIK ===\n\n";
    
    // Load data terbaru
    loadTransaksiFromFile();
    
    // Cari zakat dengan status "sukses" yang belum didistribusi
    bool adaZakatSiap = false;
    cout << "ZAKAT SIAP DIDISTRIBUSIKAN (Status: sukses):\n";
    cout << "=============================================\n";
    
    for(int i = 0; i < jumlahTransaksi; i++) {
        if(dataTransaksi[i].status == "sukses" && dataTransaksi[i].id_penerima == 0) {
            adaZakatSiap = true;
            cout << "ID Transaksi: " << dataTransaksi[i].id << endl;
            cout << "Jenis: " << dataTransaksi[i].jenis_zakat << endl;
            cout << "Jumlah: " << Rupiah(dataTransaksi[i].jumlah) << endl;
            cout << "Tanggal: " << dataTransaksi[i].tanggal << endl;
            cout << "---------------------------\n";
        }
    }
    
    if(!adaZakatSiap) {
        cout << "Tidak ada zakat yang siap didistribusikan.\n";
        cout << "Pastikan ada transaksi dengan status 'sukses'.\n";
        system("pause");
        return;
    }
    
    // Tampilkan daftar mustahik
    cout << "\nDAFTAR MUSTAHIK:\n";
    cout << "===============\n";
    for(int i = 0; i < jumlahMustahik; i++) {
        cout << "ID: " << dataMustahik[i].id << endl;
        cout << "Nama: " << dataMustahik[i].nama << endl;
        cout << "Kategori: " << dataMustahik[i].kategori << endl;
        cout << "Total Diterima: " << Rupiah(dataMustahik[i].total_diterima) << endl;
        cout << "---------------------------\n";
    }
    
    int idTransaksi, idMustahik;
    cout << "\nMasukkan ID Transaksi yang akan didistribusikan: ";
    cin >> idTransaksi;
    cout << "Masukkan ID Mustahik penerima: ";
    cin >> idMustahik;
    
    // Cari transaksi
    int idxTransaksi = -1;
    for(int i = 0; i < jumlahTransaksi; i++) {
        if(dataTransaksi[i].id == idTransaksi && dataTransaksi[i].status == "sukses" && dataTransaksi[i].id_penerima == 0) {
            idxTransaksi = i;
            break;
        }
    }
    
    // Cari mustahik
    int idxMustahik = -1;
    for(int i = 0; i < jumlahMustahik; i++) {
        if(dataMustahik[i].id == idMustahik) {
            idxMustahik = i;
            break;
        }
    }
    
    if(idxTransaksi == -1) {
        cout << "Transaksi tidak ditemukan atau sudah didistribusikan.\n";
    } else if(idxMustahik == -1) {
        cout << "Mustahik tidak ditemukan.\n";
    } else {
        cout << "\nKonfirmasi Distribusi:\n";
        cout << "Transaksi: " << dataTransaksi[idxTransaksi].jenis_zakat 
             << " sebesar " << Rupiah(dataTransaksi[idxTransaksi].jumlah) << endl;
        cout << "Penerima: " << dataMustahik[idxMustahik].nama 
             << " (" << dataMustahik[idxMustahik].kategori << ")\n";
        
        char konfirmasi;
        cout << "Distribusikan zakat? (Y/T): ";
        cin >> konfirmasi;
        
        if(konfirmasi == 'Y' || konfirmasi == 'y') {
            // Update transaksi
            dataTransaksi[idxTransaksi].status = "distributed";
            dataTransaksi[idxTransaksi].id_penerima = idMustahik;
            dataTransaksi[idxTransaksi].keterangan = " - Didistribusikan ke " + dataMustahik[idxMustahik].nama;
            
            // Update mustahik
            dataMustahik[idxMustahik].total_diterima += dataTransaksi[idxTransaksi].jumlah;
            dataMustahik[idxMustahik].tanggal_terakhir = getCurrentDate();
            
            saveTransaksiToFile();
            saveMustahikToFile();
            updateSaldo();
            
            cout << "Distribusi zakat berhasil!\n";
        } else {
            cout << "Distribusi dibatalkan.\n";
        }
    }
    system("pause");
}

void monitoringSaldoKasZakat() {
    system("cls");
    cout << "=== MONITORING SALDO KAS ZAKAT ===\n\n";
    
    updateSaldo();
    
    // Hitung berdasarkan status baru
    long long totalSukses = 0, totalDistributed = 0;
    int countSukses = 0, countDistributed = 0;
    
    for(int i = 0; i < jumlahTransaksi; i++) {
        if(dataTransaksi[i].status == "sukses" || dataTransaksi[i].status == "distributed") {
            totalSukses += dataTransaksi[i].jumlah;
            countSukses++;
        }
        if(dataTransaksi[i].status == "distributed") {
            totalDistributed += dataTransaksi[i].jumlah;
            countDistributed++;
        }
    }
    
    // Buat garis atas
    cout << "+----------------------------------------------+\n";
    cout << "|            LAPORAN KEUANGAN ZAKAT            |\n";
    cout << "+----------------------------------------------+\n";
    cout << "| Total Zakat Masuk    : " << padRight(Rupiah(totalSukses), 25) << " |\n";
    cout << "| Total Zakat Keluar   : " << padRight(Rupiah(totalDistributed), 25) << " |\n";
    cout << "| Saldo Tersedia       : " << padRight(Rupiah(totalSukses - totalDistributed), 25) << " |\n";
    cout << "+----------------------------------------------+\n";
    cout << "| Transaksi Masuk      : " << padRight(to_string(countSukses), 25) << " |\n";
    cout << "| Transaksi Keluar     : " << padRight(to_string(countDistributed), 25) << " |\n";
    cout << "| Siap Distribusi      : " << padRight(to_string(countSukses - countDistributed), 25) << " |\n";
    cout << "+----------------------------------------------+\n\n";
    
    // Detail transaksi terakhir
    cout << "10 TRANSAKSI TERAKHIR:\n";
    cout << "======================\n";
    
    int count = 0;
    for(int i = jumlahTransaksi - 1; i >= 0 && count < 10; i--) {
        cout << (count + 1) << ". " << padRight(dataTransaksi[i].tanggal, 12)
             << " - " << padRight(dataTransaksi[i].jenis_zakat, 20)
             << " - " << padRight(Rupiah(dataTransaksi[i].jumlah), 15)
             << " - " << dataTransaksi[i].status << endl;
        count++;
    }
    
    if(count == 0) {
        cout << "Belum ada transaksi.\n";
    }
    
    cout << "\nTekan Enter untuk kembali...";
    cin.ignore();
    cin.get();
}

void kelolaDataMustahik() {
    system("cls");
    int pilihan;
    
    do {
        system("cls");
        cout << "=== KELOLA DATA MUSTAHIK ===\n\n";
        cout << "1. Tambah Mustahik\n";
        cout << "2. Tampilkan Semua Mustahik\n";
        cout << "3. Edit Data Mustahik\n";
        cout << "4. Hapus Mustahik\n";
        cout << "5. Cari Mustahik\n";
        cout << "6. Kembali\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        
        switch(pilihan) {
            case 1: { // Tambah Mustahik
                mustahik baru;
                cout << "\n=== TAMBAH MUSTAHIK ===\n";
                cout << "Nama: ";
                cin.ignore();
                getline(cin, baru.nama);
                
                cout << "Kategori (fakir/miskin/amil/muallaf/riqab/gharimin/fisabilillah/ibnu sabil): ";
                getline(cin, baru.kategori);
                
                cout << "Alamat: ";
                getline(cin, baru.alamat);
                
                cout << "Telepon: ";
                getline(cin, baru.telepon);
                
                cout << "Keterangan: ";
                getline(cin, baru.keterangan);
                
                baru.id = (jumlahMustahik == 0) ? 1 : dataMustahik[jumlahMustahik-1].id + 1;
                baru.total_diterima = 0;
                baru.tanggal_terakhir = "-";
                
                dataMustahik[jumlahMustahik++] = baru;
                saveMustahikToFile();
                
                cout << "Mustahik berhasil ditambahkan! ID: " << baru.id << endl;
                system("pause");
                break;
            }
            
            case 2: { // Tampilkan Semua Mustahik
                system("cls");
                cout << "=== DAFTAR MUSTAHIK ===\n\n";
                
                if(jumlahMustahik == 0) {
                    cout << "Belum ada data mustahik.\n";
                } else {
                    // Header tabel
                    cout << "+-----+--------------------+--------------------+--------------------+--------------------+\n";
                    cout << "| ID  | Nama               | Kategori           | Total Diterima     | Tanggal Terakhir   |\n";
                    cout << "+-----+--------------------+--------------------+--------------------+--------------------+\n";
                    
                    for(int i = 0; i < jumlahMustahik; i++) {
                        string nama = dataMustahik[i].nama;
                        if(nama.length() > 18) nama = nama.substr(0, 15) + "...";
                        
                        string kategori = dataMustahik[i].kategori;
                        if(kategori.length() > 18) kategori = kategori.substr(0, 15) + "...";
                        
                        string total = Rupiah(dataMustahik[i].total_diterima);
                        if(total.length() > 18) total = total.substr(0, 15) + "...";
                        
                        string tanggal = dataMustahik[i].tanggal_terakhir;
                        if(tanggal.length() > 18) tanggal = tanggal.substr(0, 15) + "...";
                        
                        cout << "| " << padLeft(to_string(dataMustahik[i].id), 3) << " "
                             << "| " << padRight(nama, 18) << " "
                             << "| " << padRight(kategori, 18) << " "
                             << "| " << padRight(total, 18) << " "
                             << "| " << padRight(tanggal, 18) << " |\n";
                    }
                    cout << "+-----+--------------------+--------------------+--------------------+--------------------+\n";
                }
                
                cout << "\nTekan Enter untuk kembali...";
                cin.ignore();
                cin.get();
                break;
            }
            
            case 3: { // Edit Data Mustahik
                int id;
                cout << "\nMasukkan ID Mustahik yang akan diedit: ";
                cin >> id;
                
                bool found = false;
                for(int i = 0; i < jumlahMustahik; i++) {
                    if(dataMustahik[i].id == id) {
                        found = true;
                        cout << "\nEdit Data Mustahik ID: " << id << endl;
                        cout << "Nama [" << dataMustahik[i].nama << "]: ";
                        cin.ignore();
                        string input;
                        getline(cin, input);
                        if(!input.empty()) dataMustahik[i].nama = input;
                        
                        cout << "Kategori [" << dataMustahik[i].kategori << "]: ";
                        getline(cin, input);
                        if(!input.empty()) dataMustahik[i].kategori = input;
                        
                        cout << "Alamat [" << dataMustahik[i].alamat << "]: ";
                        getline(cin, input);
                        if(!input.empty()) dataMustahik[i].alamat = input;
                        
                        cout << "Telepon [" << dataMustahik[i].telepon << "]: ";
                        getline(cin, input);
                        if(!input.empty()) dataMustahik[i].telepon = input;
                        
                        cout << "Keterangan [" << dataMustahik[i].keterangan << "]: ";
                        getline(cin, input);
                        if(!input.empty()) dataMustahik[i].keterangan = input;
                        
                        saveMustahikToFile();
                        cout << "Data berhasil diupdate!\n";
                        break;
                    }
                }
                
                if(!found) {
                    cout << "Mustahik dengan ID " << id << " tidak ditemukan.\n";
                }
                system("pause");
                break;
            }
            
            case 4: { // Hapus Mustahik
                int id;
                cout << "\nMasukkan ID Mustahik yang akan dihapus: ";
                cin >> id;
                
                bool found = false;
                for(int i = 0; i < jumlahMustahik; i++) {
                    if(dataMustahik[i].id == id) {
                        found = true;
                        cout << "\nYakin ingin menghapus mustahik: " << dataMustahik[i].nama << "? (Y/T): ";
                        char konfirmasi;
                        cin >> konfirmasi;
                        
                        if(konfirmasi == 'Y' || konfirmasi == 'y') {
                            // Geser elemen array
                            for(int j = i; j < jumlahMustahik - 1; j++) {
                                dataMustahik[j] = dataMustahik[j + 1];
                            }
                            jumlahMustahik--;
                            saveMustahikToFile();
                            cout << "Mustahik berhasil dihapus.\n";
                        } else {
                            cout << "Penghapusan dibatalkan.\n";
                        }
                        break;
                    }
                }
                
                if(!found) {
                    cout << "Mustahik dengan ID " << id << " tidak ditemukan.\n";
                }
                system("pause");
                break;
            }
            
            case 5: { // Cari Mustahik
                string keyword;
                cout << "\nMasukkan nama atau kategori mustahik: ";
                cin.ignore();
                getline(cin, keyword);
                
                system("cls");
                cout << "=== HASIL PENCARIAN MUSTAHIK ===\n\n";
                
                bool found = false;
                for(int i = 0; i < jumlahMustahik; i++) {
                    if(dataMustahik[i].nama.find(keyword) != string::npos ||
                       dataMustahik[i].kategori.find(keyword) != string::npos) {
                        found = true;
                        cout << "ID: " << dataMustahik[i].id << endl;
                        cout << "Nama: " << dataMustahik[i].nama << endl;
                        cout << "Kategori: " << dataMustahik[i].kategori << endl;
                        cout << "Alamat: " << dataMustahik[i].alamat << endl;
                        cout << "Telepon: " << dataMustahik[i].telepon << endl;
                        cout << "Total Diterima: " << Rupiah(dataMustahik[i].total_diterima) << endl;
                        cout << "Tanggal Terakhir: " << dataMustahik[i].tanggal_terakhir << endl;
                        cout << "Keterangan: " << dataMustahik[i].keterangan << endl;
                        cout << "---------------------------\n";
                    }
                }
                
                if(!found) {
                    cout << "Tidak ditemukan mustahik dengan kata kunci: " << keyword << endl;
                }
                
                cout << "\nTekan Enter untuk kembali...";
                cin.get();
                break;
            }
            
            case 6:
                return;
                
            default:
                cout << "Pilihan tidak valid!\n";
                system("pause");
                break;
        }
    } while(pilihan != 6);
}

void generateLaporanBulanan() {
    system("cls");
    cout << "=== GENERATE LAPORAN BULANAN ===\n\n";
    
    string bulan, tahun;
    cout << "Masukkan bulan (MM): ";
    cin >> bulan;
    cout << "Masukkan tahun (YYYY): ";
    cin >> tahun;
    
    // Filter transaksi berdasarkan bulan/tahun
    long long totalMasuk = 0, totalKeluar = 0;
    int countMasuk = 0, countKeluar = 0;
    
    cout << "\n";
    cout << "+---------------------------------------------------------------+\n";
    cout << "|                   LAPORAN ZAKAT BULAN " << bulan << "/" << tahun << "                  |\n";
    cout << "+---------------------------------------------------------------+\n";
    
    // Transaksi Masuk
    cout << "|                    TRANSAKSI MASUK                          |\n";
    cout << "+---------------------------------------------------------------+\n";
    
    for(int i = 0; i < jumlahTransaksi; i++) {
        if(dataTransaksi[i].tanggal.substr(5, 2) == bulan && 
           dataTransaksi[i].tanggal.substr(0, 4) == tahun &&
           (dataTransaksi[i].status == "verified" || dataTransaksi[i].status == "distributed")) {
            countMasuk++;
            totalMasuk += dataTransaksi[i].jumlah;
            cout << "| " << padRight(dataTransaksi[i].tanggal, 10)
                 << " - " << padRight(dataTransaksi[i].jenis_zakat, 20)
                 << " - " << padRight(Rupiah(dataTransaksi[i].jumlah), 15) << " |\n";
        }
    }
    
    if(countMasuk == 0) {
        cout << "| Tidak ada transaksi masuk                              |\n";
    }
    
    // Transaksi Keluar
    cout << "+---------------------------------------------------------------+\n";
    cout << "|                    TRANSAKSI KELUAR                         |\n";
    cout << "+---------------------------------------------------------------+\n";
    
    for(int i = 0; i < jumlahTransaksi; i++) {
        if(dataTransaksi[i].tanggal.substr(5, 2) == bulan && 
           dataTransaksi[i].tanggal.substr(0, 4) == tahun &&
           dataTransaksi[i].status == "distributed") {
            countKeluar++;
            totalKeluar += dataTransaksi[i].jumlah;
            
            // Cari nama mustahik
            string namaPenerima = "Tidak diketahui";
            for(int j = 0; j < jumlahMustahik; j++) {
                if(dataMustahik[j].id == dataTransaksi[i].id_penerima) {
                    namaPenerima = dataMustahik[j].nama;
                    break;
                }
            }
            
            if(namaPenerima.length() > 20) namaPenerima = namaPenerima.substr(0, 17) + "...";
            
            cout << "| " << padRight(dataTransaksi[i].tanggal, 10)
                 << " - " << padRight(namaPenerima, 20)
                 << " - " << padRight(Rupiah(dataTransaksi[i].jumlah), 15) << " |\n";
        }
    }
    
    if(countKeluar == 0) {
        cout << "| Tidak ada transaksi keluar                             |\n";
    }
    
    // Summary
    cout << "+---------------------------------------------------------------+\n";
    cout << "|                         SUMMARY                             |\n";
    cout << "+---------------------------------------------------------------+\n";
    cout << "| Jumlah Transaksi Masuk   : " << padRight(to_string(countMasuk), 40) << " |\n";
    cout << "| Total Zakat Masuk        : " << padRight(Rupiah(totalMasuk), 40) << " |\n";
    cout << "| Jumlah Transaksi Keluar  : " << padRight(to_string(countKeluar), 40) << " |\n";
    cout << "| Total Zakat Keluar       : " << padRight(Rupiah(totalKeluar), 40) << " |\n";
    cout << "| Saldo Akhir              : " << padRight(Rupiah(totalMasuk - totalKeluar), 40) << " |\n";
    cout << "+---------------------------------------------------------------+\n\n";
    
    // Opsi export ke file
    char exportFile;
    cout << "Export laporan ke file? (Y/T): ";
    cin >> exportFile;
    
    if(exportFile == 'Y' || exportFile == 'y') {
        string filename = "Laporan_Zakat_" + bulan + "_" + tahun + ".txt";
        ofstream file(filename);
        
        if(file.is_open()) {
            file << "LAPORAN ZAKAT BULAN " << bulan << "/" << tahun << "\n";
            file << "========================================\n\n";
            file << "TRANSAKSI MASUK:\n";
            file << "----------------\n";
            
            for(int i = 0; i < jumlahTransaksi; i++) {
                if(dataTransaksi[i].tanggal.substr(5, 2) == bulan && 
                   dataTransaksi[i].tanggal.substr(0, 4) == tahun &&
                   (dataTransaksi[i].status == "verified" || dataTransaksi[i].status == "distributed")) {
                    file << dataTransaksi[i].tanggal << " - " 
                         << dataTransaksi[i].jenis_zakat << " - " 
                         << Rupiah(dataTransaksi[i].jumlah) << "\n";
                }
            }
            
            file << "\nTRANSAKSI KELUAR:\n";
            file << "-----------------\n";
            
            for(int i = 0; i < jumlahTransaksi; i++) {
                if(dataTransaksi[i].tanggal.substr(5, 2) == bulan && 
                   dataTransaksi[i].tanggal.substr(0, 4) == tahun &&
                   dataTransaksi[i].status == "distributed") {
                    
                    string namaPenerima = "Tidak diketahui";
                    for(int j = 0; j < jumlahMustahik; j++) {
                        if(dataMustahik[j].id == dataTransaksi[i].id_penerima) {
                            namaPenerima = dataMustahik[j].nama;
                            break;
                        }
                    }
                    
                    file << dataTransaksi[i].tanggal << " - " 
                         << namaPenerima << " - " 
                         << Rupiah(dataTransaksi[i].jumlah) << "\n";
                }
            }
            
            file << "\nSUMMARY:\n";
            file << "--------\n";
            file << "Jumlah Transaksi Masuk  : " << countMasuk << "\n";
            file << "Total Zakat Masuk       : " << Rupiah(totalMasuk) << "\n";
            file << "Jumlah Transaksi Keluar : " << countKeluar << "\n";
            file << "Total Zakat Keluar      : " << Rupiah(totalKeluar) << "\n";
            file << "Saldo Akhir             : " << Rupiah(totalMasuk - totalKeluar) << "\n";
            
            file.close();
            cout << "Laporan berhasil diexport ke file: " << filename << endl;
        } else {
            cout << "Gagal membuat file laporan.\n";
        }
    }
    
    cout << "\nTekan Enter untuk kembali...";
    cin.ignore();
    cin.get();
}

void kirimPengingatZakat() {
    system("cls");
    cout << "=== KIRIM PENGINGAT ZAKAT ===\n\n";
    
    // Cari pengguna yang memiliki harta wajib zakat tapi belum bayar
    ifstream fileHarta("penghasilan.txt");
    if(!fileHarta.is_open()) {
        cout << "Belum ada data harta pengguna.\n";
        system("pause");
        return;
    }
    
    cout << "DAFTAR PENGINGAT ZAKAT YANG PERLU DIKIRIM:\n";
    cout << "==========================================\n\n";
    
    // Ini contoh sederhana, dalam implementasi real perlu cek haul
    cout << "Pengingat akan dikirim ke pengguna yang:\n";
    cout << "1. Memiliki harta melebihi nisab\n";
    cout << "2. Belum membayar zakat tahun ini\n";
    cout << "3. Sudah melewati masa haul (1 tahun)\n\n";
    
    // Simulasi data
    cout << "Contoh pesan pengingat:\n";
    cout << "-----------------------\n";
    cout << "Kepada Yth. Bapak/Ibu Muzakki,\n";
    cout << "Ini adalah pengingat bahwa Anda memiliki kewajiban zakat.\n";
    cout << "Silakan bayar zakat melalui aplikasi Amil Zakat.\n";
    cout << "Terima kasih.\n\n";
    
    char konfirmasi;
    cout << "Kirim pengingat ke semua pengguna? (Y/T): ";
    cin >> konfirmasi;
    
    if(konfirmasi == 'Y' || konfirmasi == 'y') {
        // Simpan log pengiriman
        ofstream logFile("log_pengingat.txt", ios::app);
        logFile << getCurrentDate() << " - Pengingat zakat dikirim ke semua pengguna\n";
        logFile.close();
        
        cout << "Pengingat berhasil dikirim!\n";
    } else {
        cout << "Pengiriman dibatalkan.\n";
    }
    
    system("pause");
}

// ==================== MENU ADMIN UTAMA ====================
void menuAdminLengkap() {
    // Load data saat pertama kali masuk
    loadTransaksiFromFile();
    loadMustahikFromFile();
    updateSaldo();
    
    int pilihan;
    
    do {
        system("cls");
        cout << "=== MENU ADMIN AMIL ZAKAT ===" << endl;
        cout << "Transaksi: " << jumlahTransaksi << " | ";
        cout << "Mustahik: " << jumlahMustahik << " | ";
        cout << "Saldo: " << Rupiah(saldoZakat.saldo_akhir) << endl;
        cout << "----------------------------------" << endl;
        cout << "1. Lihat Semua Transaksi" << endl;  // Ganti dari "Verifikasi"
        cout << "2. Distribusi Zakat ke Mustahik" << endl;
        cout << "3. Monitoring Saldo Kas Zakat" << endl;
        cout << "4. Kelola Data Mustahik" << endl;
        cout << "5. Generate Laporan Bulanan" << endl;
        cout << "6. Kirim Pengingat Zakat" << endl;
        cout << "7. Kembali" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        
        switch(pilihan) {
            case 1:
                lihatSemuaTransaksi();
                break;
            case 2:
                distribusiZakatKeMustahik();
                break;
            case 3:
                monitoringSaldoKasZakat();
                break;
            case 4:
                kelolaDataMustahik();
                break;
            case 5:
                generateLaporanBulanan();
                break;
            case 6:
                kirimPengingatZakat();
                break;
            case 7:
                // Save semua data sebelum keluar
                saveTransaksiToFile();
                saveMustahikToFile();
                cout << "Kembali ke menu utama...\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
                system("pause");
                break;
        }
    } while(pilihan != 7);
}

int menu(pengguna &user){
    system("cls");
    int hasil;
    cout << "=== BERANDA APLIKASI ZAKAT ==="<<endl;
    if(user.username=="AmilZakat"){
        cout << "=== MENU ADMIN AMIL ZAKAT ===" << endl;
        cout << "1. Lihat Semua Transaksi" << endl;
        cout << "2. Distribusi Zakat ke Mustahik" << endl;
        cout << "3. Monitoring Saldo Kas Zakat" << endl;
        cout << "4. Kelola Data Mustahik" << endl;
        cout << "5. Generate Laporan Bulanan" << endl;
        cout << "6. Kirim Pengingat Zakat" << endl;
        cout << "7. Kembali" << endl;
    } else{
    cout << "=== MENU UTAMA ==="<<endl;
    cout <<"1. Dashboard\n";
    cout <<"2. Bayar Zakat\n";
    cout <<"3. Kalkulator zakat\n";
    cout <<"4. Top Up Saldo\n";
    cout <<"5. Riwayat Transaksi\n";
}
cout <<"6. Logout\n";
cout <<"Pilih nomor: ";
cin >> hasil;
return hasil;
}


void tampilkanDashboard(pengguna &user){
    system("cls");
    cout << "=== DASHBOARD " << user.username << " ==="<<endl;
    
    // Hitung total penghasilan dari file
    long long totalPenghasilan = 0;
    long long totalZakat = 0;
    bool adaData = false;
    
    ifstream filePenghasilan("penghasilan.txt");
    if(filePenghasilan.is_open()){
        penghasilan data;
        string pekerjaan;
        while(filePenghasilan >> data.id >> data.id_user >> pekerjaan 
              >> data.modal >> data.gajiBulanan >> data.piutang 
              >> data.utang >> data.kebutuhan){
            
            // Hanya ambil data user ini
            if(data.id_user == user.id){
                data.pekerjaan = pekerjaan;
                // Hitung zakat penghasilan
                long long zakat = zakatPenghasilan(data);
                totalPenghasilan += data.gajiBulanan * 12;
                totalZakat += zakat;
                adaData = true;
            }
        }
        filePenghasilan.close();
    }
    
    if(adaData){
        cout << "Total Penghasilan Pertahun: " << Rupiah(totalPenghasilan) << endl;
        cout << "Total Zakat yang Harus Dibayar: " << Rupiah(totalZakat) << endl;
        cout << "Status: " << (totalZakat > 0 ? "WAJIB ZAKAT" : "Tidak Wajib Zakat") << endl;
    } else {
        cout << "Belum ada data penghasilan yang diinput.\n";
        cout << "Silakan input data terlebih dahulu di menu Dashboard.\n";
    }
    
    cout << "\nTekan Enter untuk kembali...";
    cin.ignore();
    cin.get();
}
int menuJenisZakat(){
    system("cls");
    cout << "=== PILIH JENIS ZAKAT ==="<<endl;
    cout <<"1. Zakat Penghasilan/perusahaan\n";
    cout <<"2. Zakat Perhiasan\n";
    cout <<"3. Zakat Pertanian\n";
    cout <<"4. Zakat Tanaman/Perikanan/ternak (selain sapi, kambing, unta)\n";
    cout <<"5. Zakat Properti\n";
    cout <<"6. Zakat Rikaz\n";
    cout <<"7. Zakat Ternak (sapi, unta, kambing)\n";
    cout <<"8. Kembali\n";
    int pilihan;
    cout << "Pilihan: ";
    cin >> pilihan;
    return pilihan;
}
// Fungsi untuk cek dan update saldo pengguna
bool cekDanKurangiSaldo(pengguna &user, long long jumlah) {
    cout << "\n=== DEBUG CEK SALDO ===\n";
    cout << "User ID: " << user.id << endl;
    cout << "User saldo di memory: " << Rupiah(user.saldo) << endl;
    cout << "Jumlah potong: " << Rupiah(jumlah) << endl;
    
    ifstream fileUser("users.txt");
    if(!fileUser.is_open()) {
        cout << "❌ ERROR: File users.txt tidak ditemukan!\n";
        return false;
    }
    
    ofstream tempFile("temp_users.txt");
    if(!tempFile.is_open()) {
        cout << "❌ ERROR: Gagal membuat file temporary!\n";
        fileUser.close();
        return false;
    }
    
    bool success = false;
    pengguna tempUser;
    int count = 0;
    
    cout << "\nIsi file users.txt:\n";
    while(fileUser >> tempUser.id >> tempUser.username >> tempUser.password >> tempUser.saldo) {
        count++;
        cout << count << ". ID:" << tempUser.id << " User:" << tempUser.username 
             << " Saldo:" << Rupiah(tempUser.saldo) << endl;
        
        if(tempUser.id == user.id) {
            cout << "✓ Found user!\n";
            if(tempUser.saldo >= jumlah) {
                tempUser.saldo -= jumlah;
                user.saldo = tempUser.saldo;
                success = true;
                cout << "✓ Saldo cukup, akan dipotong\n";
                cout << "  Saldo lama: " << Rupiah(tempUser.saldo + jumlah) << endl;
                cout << "  Saldo baru: " << Rupiah(tempUser.saldo) << endl;
            } else {
                cout << "✗ Saldo tidak cukup!\n";
                cout << "  Saldo tersedia: " << Rupiah(tempUser.saldo) << endl;
                cout << "  Kebutuhan: " << Rupiah(jumlah) << endl;
            }
        }
        tempFile << tempUser.id << " " << tempUser.username << " "
                 << tempUser.password << " " << tempUser.saldo << endl;
    }
    
    fileUser.close();
    tempFile.close();
    
    if(success) {
        if(remove("users.txt") != 0) {
            cout << "❌ ERROR: Gagal menghapus file lama\n";
            remove("temp_users.txt");
            return false;
        }
        if(rename("temp_users.txt", "users.txt") != 0) {
            cout << "❌ ERROR: Gagal rename file\n";
            return false;
        }
        cout << "✅ Saldo berhasil dipotong!\n";
        cout << "✅ File users.txt berhasil diupdate\n";
    } else {
        cout << "✗ Gagal memotong saldo\n";
        remove("temp_users.txt");
    }
    
    cout << "=== END DEBUG ===\n\n";
    return success;
}

// Fungsi untuk menambah saldo (misal dari top up)
bool tambahSaldo(pengguna &user, long long jumlah) {
    cout << "\n=== DEBUG TOP UP ===\n";
    cout << "User ID: " << user.id << endl;
    cout << "User saldo di memory: " << Rupiah(user.saldo) << endl;
    cout << "Jumlah top up: " << Rupiah(jumlah) << endl;
    
    ifstream fileUser("users.txt");
    if(!fileUser.is_open()) {
        cout << "❌ ERROR: File users.txt tidak ditemukan!\n";
        return false;
    }
    
    ofstream tempFile("temp_users.txt");
    if(!tempFile.is_open()) {
        cout << "❌ ERROR: Gagal membuat file temporary!\n";
        fileUser.close();
        return false;
    }
    
    bool success = false;
    pengguna tempUser;
    int count = 0;
    
    cout << "\nIsi file users.txt:\n";
    while(fileUser >> tempUser.id >> tempUser.username >> tempUser.password >> tempUser.saldo) {
        count++;
        cout << count << ". ID:" << tempUser.id << " User:" << tempUser.username 
             << " Saldo:" << Rupiah(tempUser.saldo) << endl;
        
        if(tempUser.id == user.id) {
            cout << "✓ Found user!\n";
            tempUser.saldo += jumlah;
            user.saldo = tempUser.saldo;
            success = true;
            cout << "✓ Saldo akan ditambah\n";
            cout << "  Saldo lama: " << Rupiah(tempUser.saldo - jumlah) << endl;
            cout << "  Saldo baru: " << Rupiah(tempUser.saldo) << endl;
        }
        tempFile << tempUser.id << " " << tempUser.username << " "
                 << tempUser.password << " " << tempUser.saldo << endl;
    }
    
    fileUser.close();
    tempFile.close();
    
    if(success) {
        if(remove("users.txt") != 0) {
            cout << "❌ ERROR: Gagal menghapus file lama\n";
            remove("temp_users.txt");
            return false;
        }
        if(rename("temp_users.txt", "users.txt") != 0) {
            cout << "❌ ERROR: Gagal rename file\n";
            return false;
        }
        cout << "✅ Saldo berhasil ditambahkan!\n";
        cout << "✅ File users.txt berhasil diupdate\n";
    } else {
        cout << "✗ Gagal menambah saldo (user tidak ditemukan)\n";
        remove("temp_users.txt");
    }
    
    cout << "=== END DEBUG ===\n\n";
    return success;
}
// ==================== FUNGSI PROSES BAYAR SEMUA ====================
void prosesBayarSemua(pengguna &user, ItemZakat daftarZakat[], int jumlahItem, long long total) {
    system("cls");
    cout << "=== BAYAR SEMUA ZAKAT SEKALIGUS ===\n\n";
    
    // TAMPILKAN SALDO USER
    cout << "Saldo Anda: " << Rupiah(user.saldo) << endl;
    cout << "Total Pembayaran: " << Rupiah(total) << "\n\n";
    
    if(user.saldo < total) {
        cout << "❌ SALDO TIDAK CUKUP!\n";
        cout << "Kekurangan: " << Rupiah(total - user.saldo) << endl;
        
        char topup;
        cout << "\nIngin top up saldo? (Y/T): ";
        cin >> topup;
        
        if(topup == 'Y' || topup == 'y') {
            long long jumlahTopup;
            cout << "Masukkan jumlah top up: ";
            cin >> jumlahTopup;
            
            if(tambahSaldo(user, jumlahTopup)) {
                cout << "Top up berhasil! Saldo baru: " << Rupiah(user.saldo) << endl;
                system("pause");
                // Coba lagi pembayaran
                prosesBayarSemua(user, daftarZakat, jumlahItem, total);
                return;
            } else {
                cout << "Gagal top up!\n";
                system("pause");
                return;
            }
        } else {
            cout << "Pembayaran dibatalkan.\n";
            system("pause");
            return;
        }
    }
    
    cout << "Rincian:\n";
    for(int i = 0; i < jumlahItem; i++) {
        cout << "- " << daftarZakat[i].deskripsi << endl;
        cout << "  " << Rupiah(daftarZakat[i].jumlah) << endl;
    }
    
    char konfirmasi;
    cout << "\nKonfirmasi pembayaran semua zakat? (Y/T): ";
    cin >> konfirmasi;
    
    if(konfirmasi == 'Y' || konfirmasi == 'y') {
        // CEK DAN KURANGI SALDO
        if(cekDanKurangiSaldo(user, total)) {
            // Buat SATU transaksi untuk semua zakat
            transaksi baru;
            baru.id = (jumlahTransaksi == 0) ? 1 : dataTransaksi[jumlahTransaksi-1].id + 1;
            baru.id_pembayar = user.id;
            baru.jenis_zakat = "Multiple Zakat Types";
            baru.jumlah = total;
            baru.tanggal = getCurrentDate();
            baru.status = "sukses";  // ⭐⭐ LANGSUNG SUKSES, TIDAK PERLU VERIFIKASI ⭐⭐
            baru.id_penerima = 0;
            baru.keterangan = "Pembayaran semua zakat sekaligus - Saldo terpotong";
            
            // Simpan ke array transaksi
            dataTransaksi[jumlahTransaksi++] = baru;
            
            // Simpan ke file
            saveTransaksiToFile();
            
            system("cls");
            cout << "\n=======================================\n";
            cout << "|     PEMBAYARAN BERHASIL DIPROSES!     |\n";
            cout << "|=======================================|\n";
            cout << "| Total          : " << padRight(Rupiah(total), 22) << "|\n";
            cout << "| Saldo Terpotong: " << padRight(Rupiah(total), 22) << "|\n";
            cout << "| Saldo Baru     : " << padRight(Rupiah(user.saldo), 22) << "|\n";
            cout << "| ID Transaksi   : " << padRight(to_string(baru.id), 22) << "|\n";
            cout << "| Status         : SUKSES (Langsung)    |\n";
            cout << "=========================================\n";
            
        } else {
            cout << "Gagal memotong saldo!\n";
        }
        
    } else {
        cout << "\nPembayaran dibatalkan.\n";
    }
    
    cout << "\nTekan Enter untuk kembali...";
    cin.ignore();
    cin.get();
}

void prosesBayarPerJenis(pengguna &user, ItemZakat daftarZakat[], int jumlahItem) {
    int pilihan;
    
    do {
        system("cls");
        cout << "=== PILIH ZAKAT UNTUK DIBAYAR ===\n\n";
        cout << "Saldo Anda: " << Rupiah(user.saldo) << "\n\n";
        
        // Tampilkan daftar zakat
        for(int i = 0; i < jumlahItem; i++) {
            cout << (i+1) << ". " << daftarZakat[i].deskripsi << endl;
            cout << "    " << Rupiah(daftarZakat[i].jumlah) << endl;
            cout << "    -------------------------\n";
        }
        
        cout << "0. Kembali\n\n";
        cout << "Pilih nomor zakat (0 untuk kembali): ";
        cin >> pilihan;
        
        if(pilihan == 0) {
            return;
        }
        
        if(pilihan < 1 || pilihan > jumlahItem) {
            cout << "Pilihan tidak valid!\n";
            system("pause");
            continue;
        }
        
        int idx = pilihan - 1;
        
        // KONFIRMASI PEMBAYARAN
        system("cls");
        cout << "=== KONFIRMASI PEMBAYARAN ===\n\n";
        cout << "Saldo Anda    : " << Rupiah(user.saldo) << endl;
        cout << "Jenis Zakat   : " << daftarZakat[idx].deskripsi << endl;
        cout << "Jumlah        : " << Rupiah(daftarZakat[idx].jumlah) << endl;
        
        // Cek saldo cukup
        if(user.saldo < daftarZakat[idx].jumlah) {
            cout << "\n❌ SALDO TIDAK CUKUP!\n";
            cout << "Kekurangan: " << Rupiah(daftarZakat[idx].jumlah - user.saldo) << endl;
            
            char topup;
            cout << "Ingin top up saldo? (Y/T): ";
            cin >> topup;
            
            if(topup == 'Y' || topup == 'y') {
                long long jumlahTopup;
                cout << "Masukkan jumlah top up: ";
                cin >> jumlahTopup;
                
                if(tambahSaldo(user, jumlahTopup)) {
                    cout << "Top up berhasil! Saldo baru: " << Rupiah(user.saldo) << endl;
                } else {
                    cout << "Gagal top up!\n";
                }
            }
            system("pause");
            continue;
        }
        
        cout << "\nLanjutkan pembayaran? (Y/T): ";
        char konfirmasi;
        cin >> konfirmasi;
        
        if(konfirmasi == 'Y' || konfirmasi == 'y') {
            // Kurangi saldo
            if(cekDanKurangiSaldo(user, daftarZakat[idx].jumlah)) {
                // Buat transaksi
                transaksi baru;
                baru.id = (jumlahTransaksi == 0) ? 1 : dataTransaksi[jumlahTransaksi-1].id + 1;
                baru.id_pembayar = user.id;
                baru.jenis_zakat = daftarZakat[idx].deskripsi;
                baru.jumlah = daftarZakat[idx].jumlah;
                baru.tanggal = getCurrentDate();
                baru.status = "sukses";  // ⭐⭐ LANGSUNG SUKSES ⭐⭐
                baru.id_penerima = 0;
                baru.keterangan = "Pembayaran zakat individual - Saldo terpotong";
                
                // Simpan
                dataTransaksi[jumlahTransaksi++] = baru;
                saveTransaksiToFile();
                
                cout << "\n=========================================\n";
                cout << "     PEMBAYARAN BERHASIL!\n";
                cout << "=========================================\n";
                cout << "Saldo Terpotong : " << Rupiah(daftarZakat[idx].jumlah) << endl;
                cout << "Saldo Baru      : " << Rupiah(user.saldo) << endl;
                cout << "ID Transaksi    : " << baru.id << endl;
                cout << "Status          : SUKSES (Langsung diproses)\n";
                cout << "=========================================\n";
                
            } else {
                cout << "Gagal memotong saldo!\n";
            }
            
        } else {
            cout << "\nPembayaran dibatalkan.\n";
        }
        
        cout << "\nBayar zakat lain? (Y/T): ";
        cin >> konfirmasi;
        
        if(konfirmasi != 'Y' && konfirmasi != 'y') {
            return;
        }
        
    } while(true);
}

void bayarZakat(pengguna &user) {
    system("cls");
    cout << "=== BAYAR ZAKAT ===\n\n";
    cout << "Saldo Anda: " << Rupiah(user.saldo) << "\n\n";
    loadTransaksiFromFile();
    ItemZakat daftarZakat[50];  // Array statis
    int jumlahItem = 0;
    long long totalSemua = 0;
    
    // 1. CEK DAN HITUNG ZAKAT PENGHASILAN
    ifstream filePenghasilan("penghasilan.txt");
    if(filePenghasilan.is_open()) {
        penghasilan data;
        string pekerjaan;
        
        while(filePenghasilan >> data.id >> data.id_user >> pekerjaan 
              >> data.modal >> data.gajiBulanan >> data.piutang 
              >> data.utang >> data.kebutuhan) {
            
            if(data.id_user == user.id) {
                data.pekerjaan = pekerjaan;
                data.wajibZakat = false;
                
                // HITUNG ZAKAT SEKALI
                long long zakat = zakatPenghasilan(data);
                
                if(data.wajibZakat && jumlahItem < 50) {
                    daftarZakat[jumlahItem].deskripsi = "Zakat Penghasilan - " + data.pekerjaan;
                    daftarZakat[jumlahItem].jumlah = zakat;
                    daftarZakat[jumlahItem].jenis = "penghasilan";
                    daftarZakat[jumlahItem].id_data = data.id;
                    jumlahItem++;
                    totalSemua += zakat;
                }
            }
        }
        filePenghasilan.close();
    }
    
    // 2. CEK DAN HITUNG ZAKAT PERHIASAN padRight
    ifstream filePerhiasan("perhiasan.txt");
    if(filePerhiasan.is_open()) {
        perhiasan data;
        
        while(filePerhiasan >> data.id >> data.id_user >> data.nama 
              >> data.berat >> data.hargaPerGram) {
            
            if(data.id_user == user.id) {
                data.wajibZakat = false;
                
                // HITUNG ZAKAT SEKALI
                long long zakat = zakatPerhiasan(data);
                
                if(data.wajibZakat && jumlahItem < 50) {
                    daftarZakat[jumlahItem].deskripsi = "Zakat Perhiasan " + data.nama;
                    daftarZakat[jumlahItem].jumlah = zakat;
                    daftarZakat[jumlahItem].jenis = "perhiasan";
                    daftarZakat[jumlahItem].id_data = data.id;
                    jumlahItem++;
                    totalSemua += zakat;
                }
            }
        }
        filePerhiasan.close();
    }
    
    // 3. CEK DAN HITUNG ZAKAT TERNAK
    ifstream fileTernak("ternak.txt");
    if(fileTernak.is_open()) {
        ternak data;
        
        while(fileTernak >> data.id >> data.id_user >> data.nama >> data.jumlah) {
            
            if(data.id_user == user.id) {
                data.wajibZakat = false;
                
                // HITUNG ZAKAT SEKALI (untuk ternak, hasilnya string)
                string hasil = zakatTernak(data);
                
                if(data.wajibZakat && jumlahItem < 50) {
                    // Untuk ternak, minta konversi ke uang
                    cout << "\n=== KONVERSI ZAKAT TERNAK ===\n";
                    cout << "Jenis: " << data.nama << endl;
                    cout << "Jumlah: " << data.jumlah << " ekor" << endl;
                    cout << "Keterangan: " << hasil << endl;
                    
                    long long nilaiUang;
                    cout << "Masukkan nilai dalam Rupiah: ";
                    cin >> nilaiUang;
                    
                    if(nilaiUang > 0) {
                        daftarZakat[jumlahItem].deskripsi = "Zakat Ternak " + data.nama + " - " + hasil;
                        daftarZakat[jumlahItem].jumlah = nilaiUang;
                        daftarZakat[jumlahItem].jenis = "ternak";
                        daftarZakat[jumlahItem].id_data = data.id;
                        jumlahItem++;
                        totalSemua += nilaiUang;
                    }
                }
            }
        }
        fileTernak.close();
    }
    
    // CEK APAKAH ADA ZAKAT YANG WAJIB DIBAYAR
    if(jumlahItem == 0) {
        cout << "Tidak ada zakat yang wajib dibayar.\n";
        cout << "Silakan input data harta terlebih dahulu.\n\n";
        cout << "Tekan Enter untuk kembali...";
        cin.ignore();
        cin.get();
        return;
    }
    
    // TAMPILKAN ZAKAT YANG WAJIB DIBAYAR
    cout << "ZAKAT YANG WAJIB DIBAYAR:\n";
    cout << "=========================\n\n";
    
    for(int i = 0; i < jumlahItem; i++) {
        cout << (i+1) << ". " << daftarZakat[i].deskripsi << endl;
        cout << "    Jumlah: " << Rupiah(daftarZakat[i].jumlah) << endl;
        cout << "    -------------------------\n";
    }
    
    cout << "\nTOTAL SEMUA: " << Rupiah(totalSemua) << "\n\n";
    
    // PILIHAN PEMBAYARAN
    int pilihanMenu;
    cout << "PILIH OPSI PEMBAYARAN:\n";
    cout << "1. Bayar Semua Zakat Sekaligus\n";
    cout << "2. Bayar Per Jenis Zakat\n";
    cout << "3. Kembali ke Menu Utama\n";
    cout << "Pilihan: ";
    cin >> pilihanMenu;
    
    switch(pilihanMenu) {
        case 1:
            prosesBayarSemua(user, daftarZakat, jumlahItem, totalSemua);
            break;
        case 2:
            prosesBayarPerJenis(user, daftarZakat, jumlahItem);
            break;
        case 3:
            return;
        default:
            cout << "Pilihan tidak valid!\n";
            system("pause");
    }
}
void topUpSaldo(pengguna &user) {
    system("cls");
    cout << "=== TOP UP SALDO ===\n\n";
    cout << "Saldo saat ini: " << Rupiah(user.saldo) << endl;
    
    long long jumlah;
    cout << "Masukkan jumlah top up: ";
    cin >> jumlah;
    
    if(jumlah <= 0) {
        cout << "Jumlah tidak valid!\n";
        system("pause");
        return;
    }
    
    if(tambahSaldo(user, jumlah)) {
        cout << "\n✅ TOP UP BERHASIL!\n";
        cout << "Jumlah : " << Rupiah(jumlah) << endl;
        cout << "Saldo baru : " << Rupiah(user.saldo) << endl;
    } else {
        cout << "Gagal top up!\n";
    }
    
    cout << "\nTekan Enter untuk kembali...";
    cin.ignore();
    cin.get();
}
void inputData(pengguna &user){
    system("cls");
    cout << "=== INPUT DATA KEKAYAAN ==="<<endl;
    
    int pilihan = menuJenisZakat();
    
    switch(pilihan){
        case 1: { // Zakat Penghasilan
            penghasilan data;
            data.id_user = user.id;
            
            cout << "\n=== INPUT DATA PENGHASILAN ==="<<endl;
            cout << "Pekerjaan: ";
            cin.ignore();  // PERBAIKAN: tambah cin.ignore()
            getline(cin, data.pekerjaan);
            cout << "Modal usaha (Rp): ";
            cin >> data.modal;
            cout << "Gaji bulanan (Rp): ";
            cin >> data.gajiBulanan;
            cout << "Piutang yang bisa ditagih (Rp): ";
            cin >> data.piutang;
            cout << "Utang (Rp): ";
            cin >> data.utang;
            cout << "Kebutuhan pokok per tahun (Rp): ";
            cin >> data.kebutuhan;
            
            // Hitung zakat
            long long zakat = zakatPenghasilan(data);
            
            // Simpan ke file
            ofstream file("penghasilan.txt", ios::app);
            if(file.is_open()){
                file << autoIncrement("penghasilan.txt") << " "
                     << data.id_user << " "
                     << data.pekerjaan << " "
                     << data.modal << " "
                     << data.gajiBulanan << " "
                     << data.piutang << " "
                     << data.utang << " "
                     << data.kebutuhan << " "
                     << (data.wajibZakat ? "1" : "0") << endl;
                file.close();
                cout << "Data berhasil disimpan!\n";
            } else {
                cout << "Gagal menyimpan data!\n";
            }
            
            // Tampilkan hasil
            cout << "\n=== HASIL PERHITUNGAN ==="<<endl;
            cout << "Status: " << (data.wajibZakat ? "WAJIB ZAKAT" : "Tidak Wajib Zakat") << endl;
            if(data.wajibZakat){
                cout << "Zakat yang harus dibayar: " << Rupiah(zakat) << endl;
            }
            break;
        }
        
        case 2: { // Zakat Perhiasan - PERBAIKAN: Hapus do-while yang salah
            perhiasan data;
            data.id_user = user.id;
            
            cout << "\n=== INPUT DATA PERHIASAN ==="<<endl;
            cout << "Jenis Perhiasan : \n";
            cout << "1. emas\n";
            cout << "2. perak\n";
            cout << "Pilih Nomor: ";
            int namaPerhiasan;
            cin >> namaPerhiasan;
            
            // PERBAIKAN: Gunakan if-else, bukan do-while switch
            if(namaPerhiasan == 1){
                data.nama = "emas";
            } else if(namaPerhiasan == 2){
                data.nama = "perak";
            } else {
                cout << "Input tidak valid!\n";
                system("pause");
                return;
            }
            
            cout << "Berat Perhiasan (gr): ";
            cin >> data.berat;
            cout << "Harga per Gram (Rp): ";
            cin >> data.hargaPerGram;
            
            // Hitung zakat
            long long zakat = zakatPerhiasan(data);
            
            // Simpan ke file
            ofstream file("perhiasan.txt", ios::app);
            if(file.is_open()){
                file << autoIncrement("perhiasan.txt") << " "
                     << data.id_user << " "
                     << data.nama << " "
                     << data.berat << " "
                     << data.hargaPerGram << " "
                     << (data.wajibZakat ? "1" : "0") << endl;
                file.close();
                cout << "Data berhasil disimpan!\n";
            } else {
                cout << "Gagal menyimpan data!\n";
            }
            
            // Tampilkan hasil
            cout << "\n=== HASIL PERHITUNGAN ==="<<endl;
            cout << "Status: " << (data.wajibZakat ? "WAJIB ZAKAT" : "Tidak Wajib Zakat") << endl;
            if(data.wajibZakat){
                cout << "Zakat yang harus dibayar: " << Rupiah(zakat) << endl;
            }
            break;
        }
        
        case 3: { // Zakat Pertanian - PERBAIKAN: Hapus do-while yang salah
            tani data;
            data.id_user = user.id;
            
            cout << "\n=== INPUT DATA PERTANIAN BAHAN PANGAN POKOK ==="<<endl;
            cout << "Nama tanaman: \n";
            cout << "1. Beras putih\n";
            cout << "2. Padi gagang\n";
            cout << "3. Padi Kretek\n";
            cout << "4. Kacang hijau\n";
            cout << "5. Kacang tunggak\n";
            cout << "Pilih Nomor: ";
            int namaTanaman;
            cin >> namaTanaman;
            
            if(namaTanaman == 1){
                data.nama = "beras_putih";
            } else if(namaTanaman == 2){
                data.nama = "padi_gagang";
            } else if(namaTanaman == 3){
                data.nama = "padi_kretek";
            } else if(namaTanaman == 4){
                data.nama = "kacang_hijau";
            } else if(namaTanaman == 5){
                data.nama = "kacang_tunggak";
            } else {
                cout << "Input tidak valid!\n";
                system("pause");
                return;
            }
            
            cout << "Berat Hasil Panen (kg): ";
            cin >> data.berat;
            char bayar;
            cout << "Ada Biaya irigasi? (Y/T): ";
            cin >> bayar;
            data.bayarIrigasi = (bayar == 'Y' || bayar == 'y');
            
            // Hitung zakat
            float zakat = zakatPertanian(data);
            
            // Simpan ke file
            ofstream file("pertanian.txt", ios::app);
            if(file.is_open()){
                file << autoIncrement("pertanian.txt") << " "
                     << data.id_user << " "
                     << data.nama << " "
                     << data.berat << " "
                     << (data.bayarIrigasi ? "1" : "0") << " "
                     << (data.wajibZakat ? "1" : "0") << endl;
                file.close();
                cout << "Data berhasil disimpan!\n";
            } else {
                cout << "Gagal menyimpan data!\n";
            }
            
            // Tampilkan hasil
            cout << "\n=== HASIL PERHITUNGAN ==="<<endl;
            cout << "Status: " << (data.wajibZakat ? "WAJIB ZAKAT" : "Tidak Wajib Zakat") << endl;
            if(data.wajibZakat){
                cout << "Zakat yang harus dibayar: " << zakat << " kg" << endl;
            }
            break;
        }
        
        case 4: { // Zakat Tanaman/Perikanan
            tanaman data;
            data.id_user = user.id;
            
            cout << "\n=== INPUT DATA TANAMAN PRODUKTIF ATAU PERIKANAN ==="<<endl;
            cout << "Biaya bibit (Rp): ";
            cin >> data.bibit;
            cout << "Biaya Simpanan / Nuqud jika ada (Rp): ";
            cin >> data.nuqud;
            cout << "Piutang yang bisa ditagih(Rp): ";
            cin >> data.piutang;
            cout << "Utang yang belum dibayar (Rp): ";
            cin >> data.utang;
            
            // Hitung zakat
            long long zakat = zakatTanaman(data);
            
            // Simpan ke file
            ofstream file("tanaman.txt", ios::app);
            if(file.is_open()){
                file << autoIncrement("tanaman.txt") << " "
                     << data.id_user << " "
                     << data.bibit << " "
                     << data.nuqud << " "
                     << data.piutang << " "
                     << data.utang << " "
                     << (data.wajibZakat ? "1" : "0") << endl;
                file.close();
                cout << "Data berhasil disimpan!\n";
            } else {
                cout << "Gagal menyimpan data!\n";
            }
            
            // Tampilkan hasil
            cout << "\n=== HASIL PERHITUNGAN ==="<<endl;
            cout << "Status: " << (data.wajibZakat ? "WAJIB ZAKAT" : "Tidak Wajib Zakat") << endl;
            if(data.wajibZakat){
                cout << "Zakat yang harus dibayar: " << Rupiah(zakat) << endl;
            }
            break;
        }
        
        case 5: { // Zakat Properti
            properti data;
            data.id_user = user.id;
            
            cout << "\n=== INPUT HARTA PROPERTI ==="<<endl;
            cout << "Biaya tanah (Rp): ";
            cin >> data.biayaTanah;
            cout << "Biaya tanah dan bangunan (Rp): ";
            cin >> data.biayaTanahBangunan;
            cout << "Biaya bahan baku bangunan (Rp): ";
            cin >> data.biayaBahanBaku;
            cout << "Biaya Simpanan / Nuqud jika ada (Rp): ";
            cin >> data.nuqud;
            cout << "Piutang yang bisa ditagih(Rp): ";
            cin >> data.piutang;
            cout << "Utang yang belum dibayar (Rp): ";
            cin >> data.utang;
            
            // Hitung zakat
            long long zakat = zakatProperti(data);
            
            // Simpan ke file
            ofstream file("properti.txt", ios::app);
            if(file.is_open()){
                file << autoIncrement("properti.txt") << " "
                     << data.id_user << " "
                     << data.biayaTanah << " "
                     << data.biayaTanahBangunan << " "
                     << data.biayaBahanBaku << " "
                     << data.nuqud << " "
                     << data.piutang << " "
                     << data.utang << " "
                     << (data.wajibZakat ? "1" : "0") << endl;
                file.close();
                cout << "Data berhasil disimpan!\n";
            } else {
                cout << "Gagal menyimpan data!\n";
            }
            
            // Tampilkan hasil
            cout << "\n=== HASIL PERHITUNGAN ==="<<endl;
            cout << "Status: " << (data.wajibZakat ? "WAJIB ZAKAT" : "Tidak Wajib Zakat") << endl;
            if(data.wajibZakat){
                cout << "Zakat yang harus dibayar: " << Rupiah(zakat) << endl;
            }
            break;
        }
        
        case 6: { // Zakat Rikaz
            rikaz data;
            data.id_user = user.id;
            
            cout << "\n=== INPUT HARTA TEMUAN (RIKAZ) ==="<<endl;
            cout << "Nama Barang: ";
            cin.ignore();  // PERBAIKAN: tambah cin.ignore()
            getline(cin, data.barang);
            cout << "Harga Barang (Rp): ";
            cin >> data.hargaBarang;
            
            // Hitung zakat
            long long zakat = zakatRikaz(data);
            
            // Simpan ke file
            ofstream file("rikaz.txt", ios::app);
            if(file.is_open()){
                file << autoIncrement("rikaz.txt") << " "
                     << data.id_user << " "
                     << data.barang << " "
                     << data.hargaBarang << " "
                     << "0" << endl; // Rikaz selalu wajib zakat jika ada barang
                file.close();
                cout << "Data berhasil disimpan!\n";
            } else {
                cout << "Gagal menyimpan data!\n";
            }
            
            // Tampilkan hasil
            cout << "\n=== HASIL PERHITUNGAN ==="<<endl;
            cout << "Status: " << (data.hargaBarang > 0 ? "WAJIB ZAKAT" : "Tidak Wajib Zakat") << endl;
            if(data.hargaBarang > 0){
                cout << "Zakat yang harus dibayar: " << Rupiah(zakat) << endl;
            }
            break;
        }
        
        case 7: { // Zakat Ternak
            ternak data;
            data.id_user = user.id;
            
            cout << "\n=== INPUT DATA TERNAK ==="<<endl;
            cout << "Jenis ternak (unta/sapi/kambing): ";
            cin.ignore();
            getline(cin, data.nama);
            cout << "Jumlah ternak (ekor): ";
            cin >> data.jumlah;
            
            // Hitung zakat
            string hasilZakat = zakatTernak(data);
            
            // Simpan ke file
            ofstream file("ternak.txt", ios::app);
            if(file.is_open()){
                file << autoIncrement("ternak.txt") << " "
                     << data.id_user << " "
                     << data.nama << " "
                     << data.jumlah << " "
                     << (data.wajibZakat ? "1" : "0") << endl;
                file.close();
                cout << "Data berhasil disimpan!\n";
            } else {
                cout << "Gagal menyimpan data!\n";
            }
            
            // Tampilkan hasil
            cout << "\n=== HASIL PERHITUNGAN ==="<<endl;
            cout << "Status: " << (data.wajibZakat ? "WAJIB ZAKAT" : "Tidak Wajib Zakat") << endl;
            cout << "Keterangan: " << hasilZakat << endl;
            break;
        }
        
        case 8: // Kembali
            return;
            
        default:
            cout << "Menu tidak valid!\n";
            break;
    }
    system("pause");
}
void riwayatTransaksi(pengguna &user) {
    system("cls");
    cout << "=== RIWAYAT TRANSAKSI ===" << endl;
    cout << "Saldo Anda: " << Rupiah(user.saldo) << "\n\n";
    
    // Load transaksi
    loadTransaksiFromFile();
    
    cout << "TRANSAKSI ANDA:\n";
    cout << "============================================\n";
    
    bool adaTransaksi = false;
    for(int i = 0; i < jumlahTransaksi; i++) {
        if(dataTransaksi[i].id_pembayar == user.id) {
            adaTransaksi = true;
            cout << "ID: " << dataTransaksi[i].id << endl;
            cout << "Jenis: " << dataTransaksi[i].jenis_zakat << endl;
            cout << "Jumlah: " << Rupiah(dataTransaksi[i].jumlah) << endl;
            cout << "Tanggal: " << dataTransaksi[i].tanggal << endl;
            cout << "Status: " << dataTransaksi[i].status << endl;
            cout << "Keterangan: " << dataTransaksi[i].keterangan << endl;
            cout << "--------------------------------------------\n";
        }
    }
    
    if(!adaTransaksi) {
        cout << "Belum ada transaksi.\n";
    }
    
    // Summary
    long long totalSudahBayar = 0;
    for(int i = 0; i < jumlahTransaksi; i++) {
        if(dataTransaksi[i].id_pembayar == user.id && 
           (dataTransaksi[i].status == "verified" || dataTransaksi[i].status == "distributed")) {
            totalSudahBayar += dataTransaksi[i].jumlah;
        }
    }
    
    cout << "\nTOTAL SUDAH DIBAYAR: " << Rupiah(totalSudahBayar) << endl;
    
    cout << "\nTekan Enter untuk kembali...";
    cin.ignore();
    cin.get();
}
// Tambah menu ini di menu utama user (non-admin)
void menuUser(pengguna &user) {
    int pilihan;
    
    do {
        system("cls");
        cout << "=== MENU " << user.username << " ===\n\n";
        cout << "Saldo Anda: " << Rupiah(user.saldo) << "\n\n";
        cout << "1. Dashboard\n";
        cout << "2. Bayar Zakat\n";
        cout << "3. Kalkulator Zakat\n";
        cout << "4. Top Up Saldo\n";
        cout << "5. Riwayat Transaksi\n";
        cout << "6. Logout\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        
        switch(pilihan) {
            case 1:
                tampilkanDashboard(user);
                break;
            case 2:
                bayarZakat(user);
                break;
            case 3:
                inputData(user);
                break;
            case 4:
                topUpSaldo(user);
                break;
            case 5:
                riwayatTransaksi(user);
                break;
            case 6:
                cout << "Logout berhasil...\n";
                system("pause");
                return;
            default:
                cout << "Pilihan tidak valid!\n";
                system("pause");
                break;
        }
    } while(true);
}



// ==================== FUNGSI BANTUAN FORMATTING ====================
// string padRight(string str, int length) {
//     if(str.length() >= length) {
//         return str.substr(0, length);
//     }
    
//     string result = str;
//     for(int i = str.length(); i < length; i++) {
//         result += " ";
//     }
//     return result;
// }
int menuDashboard(pengguna &user){
    tampilkanDashboard(user);
    cout << "== PILIH MENU ==="<<endl;
    cout <<"1. Input Data\n";
    cout <<"2. Edit Data\n";
    cout <<"3. Kembali\n";
    int pilihan;
    cout << "Pilih Nomor: ";
    cin >> pilihan;
    return pilihan;
}



void editData(pengguna &user){
    system("cls");
    cout << "=== EDIT DATA ==="<<endl;
    cout << "Fitur edit data belum diimplementasi.\n";
    cout << "Silakan gunakan input data baru untuk memperbarui.\n";
    system("pause");
}
void handleMenu(pengguna &user){
    bool isAdmin = user.username == "AmilZakat";
    int pilihanMenu;
    
    while(true){
        pilihanMenu = menu(user);
        
        switch(pilihanMenu){
            case 1:
                if(isAdmin){
                    menuAdminLengkap();
                    system("pause");
                } else {
                    menuUser(user);
                    int menuDash;
                    do {
                        menuDash = menuDashboard(user);
                        
                        switch(menuDash){
                            case 1:
                                inputData(user);
                                break;
                            case 2:
                                editData(user);
                                break;
                            case 3:
                                cout << "Kembali ke menu utama...\n";
                                break;
                            default:
                                cout << "Pilihan tidak valid!\n";
                                system("pause");
                                break;
                        }
                    } while(menuDash != 3);
                }
                break;
                
            case 2:
                if(isAdmin){
                    distribusiZakatKeMustahik();
                } else {
                    bayarZakat(user);
                }
                system("pause");
                break;
                
            case 3:
                if(isAdmin){
                    monitoringSaldoKasZakat();
                } else {
                    inputData(user);
                }
                break;
                
            case 4:
                if(isAdmin){
                    kelolaDataMustahik();
                } else {
                    topUpSaldo(user);  // Non-admin: top up saldo
                }
                break;

                case 5:
                if(isAdmin){
                    generateLaporanBulanan();
                } else {
                    riwayatTransaksi(user);  // Non-admin: riwayat transaksi
                }
                break;
                
            case 6:  // Logout untuk non-admin
                if(isAdmin){
                    kirimPengingatZakat();  // Admin: menu 6 = pengingat
                } else {
                    user = pengguna();
                    cout << "Logout berhasil..\n";
                    return;
                }
                break;
                
            case 7:  // Logout untuk admin
                if(isAdmin){
                    user = pengguna();
                    cout << "Logout berhasil..\n";
                    return;
                }
                break;
                
            default:
                cout << "Pemilihan nomor tidak valid\n";
                system("pause");
                break;
        }
    }
}

int main(){
    dataNisab dataNisab;
    ofstream catatNisab;
    catatNisab.open("dataNisab.txt");
    for(int i=0;i<15;i++){
        catatNisab << i+1 <<" "<< dataNisab.jenis[i] <<" "<< dataNisab.nama[i] <<" "<< dataNisab.nisab[i] <<" "<< dataNisab.satuan[i] <<" "<< dataNisab.haul[i] <<" "<< dataNisab.wajibZakat[i] <<" "<<endl;
    }
    catatNisab.close();
    pengguna pengguna;
    bool adaAdmin = false;
    int id;
    string uname, pass;
    long long saldoAdmin;
    ifstream cek;
    cek.open("users.txt");
    while(cek >> id >> uname >> pass >> saldoAdmin) {
        if(uname == "AmilZakat") {
            adaAdmin = true;
            cout << "Admin ditemukan. Saldo admin: " << Rupiah(saldoAdmin) << endl;
        }
    }
    cek.close();

    if(!adaAdmin){
        ofstream tulis("users.txt");
        tulis << 1 << " " << "AmilZakat" << " " << "insyaAllahBarokah_2025" << " " << 0 << "\n";
        tulis.close();
        cout << "Admin default dibuat.\n";
    }
    char HaveAccount;
    cout << "=== SELAMAT DATANG ===" << endl;
    cout << "=== APLIKASI AMIL ZAKAT ===" << endl;
    system("pause");
    while(true){
        bool isLogin=false;
    do{
    system("cls");
    cout << "Sudah Punya Akun (Y/T)? " << endl;
    cin >> HaveAccount;
    string user[2];
    if(HaveAccount=='Y' || HaveAccount=='y'){
    cout <<"--- Login Akun ---"<< endl;
    cout << "Username: ";
    cin >> user[0];
    cout << "Password: ";
    cin >> user[1];
    
    ifstream bacaUser1("users.txt");
    bool found = false;
    
    while(bacaUser1 >> pengguna.id >> pengguna.username >> pengguna.password >> pengguna.saldo) {
        cout << "DEBUG: Read user - " << pengguna.username << " saldo: " 
             << Rupiah(pengguna.saldo) << endl;
        
        if(pengguna.username == user[0] && pengguna.password == user[1]) {
            found = true;
            isLogin = true;
            break;
        }
    }
    bacaUser1.close();
    
    system("cls");
    if(isLogin){
        cout << pengguna.username << " berhasil Login\n";
        cout << "ID User: " << pengguna.id << endl;
        cout << "Saldo Anda: " << Rupiah(pengguna.saldo) << endl;
    } else {
        cout << "Akun tidak ditemukan atau password salah\n";
    }       
} else{
        cout <<"--- Registrasi Akun ---"<< endl;
        cout << "Username: ";
        cin >> pengguna.username;
        cout << "Password: ";
        cin >> pengguna.password;
        ifstream bacaUser3;
        bool isUnique=true;
        bacaUser3.open("users.txt");
        while(bacaUser3 >> pengguna.id >> user[0] >> user[1]){
            if(user[0]==pengguna.username){
                cout << "username sudah digunakan, coba username lain\n";
                isUnique=false;
                break;
            }
        }
        if(isUnique){
            pengguna.id=autoIncrement("users.txt");
            pengguna.saldo=0;
            ofstream appendUser1;
            appendUser1.open("users.txt", ios::app);
            appendUser1 << pengguna.id << " " << pengguna.username << " " << pengguna.password << " "<<pengguna.saldo<< "\n";
            appendUser1.close();
            cout << pengguna.username<< " Berhasil \n";
            isLogin=true;
        }
        bacaUser3.close();
    }
    system("pause");
}while(!isLogin);
handleMenu(pengguna);
    char isQuit;
    cout << "Apakah Anda ingin keluar? (Y?T): ";
    cin >> isQuit;
    if(isQuit=='Y' || isQuit=='y'){
        break;
    } else{
        continue;
    }
}
system("cls");
cout <<"Selesai"<<endl;
}
