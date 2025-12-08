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
    int hasilId=1;
    ifstream bacaDatabase2;
    string data[3];
    bacaDatabase2.open(nameFile);
    while(bacaDatabase2 >> hasilId >> data[0] >> data[1] >> data[2]){
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
    long long nisab = cariNisabLong("perusahaan")*1000;
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
        if(dataTransaksi[i].status == "verified" || dataTransaksi[i].status == "distributed") {
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
void verifikasiPembayaranZakat() {
    system("cls");
    cout << "=== VERIFIKASI PEMBAYARAN ZAKAT ===\n\n";
    
    // Tampilkan transaksi pending
    bool adaPending = false;
    cout << "TRANSAKSI MENUNGGU VERIFIKASI:\n";
    cout << "===============================\n";
    
    for(int i = 0; i < jumlahTransaksi; i++) {
        if(dataTransaksi[i].status == "pending") {
            adaPending = true;
            cout << "ID Transaksi: " << dataTransaksi[i].id << endl;
            cout << "Pembayar ID: " << dataTransaksi[i].id_pembayar << endl;
            cout << "Jenis Zakat: " << dataTransaksi[i].jenis_zakat << endl;
            cout << "Jumlah: " << Rupiah(dataTransaksi[i].jumlah) << endl;
            cout << "Tanggal: " << dataTransaksi[i].tanggal << endl;
            cout << "---------------------------\n";
        }
    }
    
    if(!adaPending) {
        cout << "Tidak ada transaksi yang perlu diverifikasi.\n";
        system("pause");
        return;
    }
    
    int idTransaksi;
    cout << "\nMasukkan ID Transaksi untuk diverifikasi: ";
    cin >> idTransaksi;
    
    for(int i = 0; i < jumlahTransaksi; i++) {
        if(dataTransaksi[i].id == idTransaksi && dataTransaksi[i].status == "pending") {
            cout << "\nDetail Transaksi:\n";
            cout << "ID: " << dataTransaksi[i].id << endl;
            cout << "Pembayar: " << dataTransaksi[i].id_pembayar << endl;
            cout << "Jenis: " << dataTransaksi[i].jenis_zakat << endl;
            cout << "Jumlah: " << Rupiah(dataTransaksi[i].jumlah) << endl;
            
            char konfirmasi;
            cout << "\nVerifikasi transaksi ini? (Y/T): ";
            cin >> konfirmasi;
            
            if(konfirmasi == 'Y' || konfirmasi == 'y') {
                dataTransaksi[i].status = "verified";
                dataTransaksi[i].keterangan = " - Terverifikasi oleh admin";
                saveTransaksiToFile();
                updateSaldo();
                cout << "Transaksi berhasil diverifikasi!\n";
            } else {
                cout << "Verifikasi dibatalkan.\n";
            }
            system("pause");
            return;
        }
    }
    
    cout << "Transaksi tidak ditemukan atau sudah diverifikasi.\n";
    system("pause");
}

void distribusiZakatKeMustahik() {
    system("cls");
    cout << "=== DISTRIBUSI ZAKAT KE MUSTAHIK ===\n\n";
    
    // Tampilkan zakat yang sudah terverifikasi tapi belum didistribusi
    cout << "ZAKAT SIAP DIDISTRIBUSIKAN:\n";
    cout << "============================\n";
    
    // for(int i = 0; i < jumlahTransaksi; i++) {
    //     if(dataTransaksi[i].status == "verified") {
    //         adaZakatSiap = true;
    //         cout << "Jenis: " << dataTransaksi[i].jenis_zakat << endl;
    //         cout << "Jumlah: " << Rupiah(dataTransaksi[i].jumlah) << endl;
    //         cout << "---------------------------\n";
    //     }
    // }
    pengguna admin;
    cout << "Saldo Zakat: " << Rupiah(admin.saldo) << endl;
    
    
    if(admin.saldo<=0) {
        cout << "Tidak ada zakat yang siap didistribusikan.\n";
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
    long long nominalTransaksi;
    int idMustahik;
    cout << "Masukkan ID Mustahik penerima: ";
    cin >> idMustahik;
    cout << "\nMasukkan Nominal Transaksi: ";
    cin >> nominalTransaksi;
    
    // Cari transaksi
    // int idxTransaksi = -1;
    // for(int i = 0; i < jumlahTransaksi; i++) {
    //     if(dataTransaksi[i].id == idTransaksi && dataTransaksi[i].status == "verified") {
    //         idxTransaksi = i;
    //         break;
    //     }
    // }
    
    // Cari mustahik
    int idxMustahik = -1;
    for(int i = 0; i < jumlahMustahik; i++) {
        if(dataMustahik[i].id == idMustahik) {
            idxMustahik = i;
            break;
        }
    }
    
    if(admin.saldo<nominalTransaksi) {
        cout << "Saldo Tidak Mencukupi.\n";
    } else if(idxMustahik == -1) {
        cout << "Mustahik tidak ditemukan.\n";
    } else {
        cout << "\nKonfirmasi Distribusi:\n";
        cout << "Transaksi Zakat Mal"
             << " sebesar " << Rupiah(nominalTransaksi) << endl;
        cout << "Penerima: " << dataMustahik[idxMustahik].nama 
             << " (" << dataMustahik[idxMustahik].kategori << ")\n";
        
        char konfirmasi;
        cout << "Distribusikan zakat? (Y/T): ";
        cin >> konfirmasi;
        
        if(konfirmasi == 'Y' || konfirmasi == 'y') {
            // Update transaksi
            // dataTransaksi[idxTransaksi].status = "distributed";
            // dataTransaksi[idxTransaksi].id_penerima = idMustahik;
            // dataTransaksi[idxTransaksi].keterangan = " - Didistribusikan ke " + dataMustahik[idxMustahik].nama;
            
            // Update mustahik
            dataMustahik[idxMustahik].total_diterima += nominalTransaksi;
            dataMustahik[idxMustahik].tanggal_terakhir = getCurrentDate();
            
            // saveTransaksiToFile();
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
    
    // Buat garis atas
    cout << "+----------------------------------------------+\n";
    cout << "|            LAPORAN KEUANGAN ZAKAT            |\n";
    cout << "+----------------------------------------------+\n";
    cout << "| Total Zakat Masuk    : " << padRight(Rupiah(saldoZakat.total_masuk), 25) << " |\n";
    cout << "| Total Zakat Keluar   : " << padRight(Rupiah(saldoZakat.total_keluar), 25) << " |\n";
    cout << "| Saldo Akhir          : " << padRight(Rupiah(saldoZakat.saldo_akhir), 25) << " |\n";
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
int menu(pengguna &user){
    system("cls");
    int hasil;
    cout << "=== BERANDA APLIKASI ZAKAT ==="<<endl;
    if(user.username=="AmilZakat"){
       cout << "=== MENU ADMIN AMIL ZAKAT ===" << endl;
        cout << "1. Pengelolaan Zakat" << endl;
        cout << "2. Manajemen Data & Mustahik" << endl;
        cout << "3. Laporan & Evaluasi" << endl;
    } else{
    cout << "=== MENU UTAMA ==="<<endl;
    cout <<"1. Dashboard\n";
    cout <<"2. Bayar Zakat\n";
    cout <<"3. Kalkulator zakat\n";
}
cout <<"4. Logout\n";
cout <<"Pilih nomor: ";
cin >> hasil;
return hasil;
}


void menuAdminLengkap(int nomorPilihan) {
    // Load data saat pertama kali masuk
    loadTransaksiFromFile();
    loadMustahikFromFile();
    updateSaldo();
    
    int pilihan;
    
    do {
        system("cls");
        cout << "=== MENU ADMIN AMIL ZAKAT ===" << endl;
        switch(nomorPilihan){
            case 1:
            cout << "1. Distribusi Zakat ke Mustahik" << endl;
            cout << "2. Kirim Pengingat Zakat" << endl;
            break;
            case 2:
            cout << "3. Kelola Data Mustahik" << endl;
            cout << "4. Monitoring Saldo Kas Zakat" << endl;
            break;
            case 3:
            cout << "5. Generate Laporan Bulanan" << endl;
            break;
            default:
            cout << "parameter tidak valid"<<endl;
        }
        cout << "6. Kembali"<<endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        
        switch(pilihan) {
            case 1:
                distribusiZakatKeMustahik();
                break;
            case 2:
                kirimPengingatZakat();
                break;
            case 3:
                kelolaDataMustahik();
                break;
            case 4:
                monitoringSaldoKasZakat();
                break;
            case 5:
                generateLaporanBulanan();
                break;
            case 6:
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
    } while(pilihan != 6);
}


void tampilkanDashboard(pengguna &user){
    system("cls");
    cout << "=== DASHBOARD " << user.username << " ==="<<endl;
    cout << "Nama : " << user.username<<endl;
    cout << "Saldo : " << Rupiah(user.saldo)<<endl;
    
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
            
            // Hanya ambil data user ini menuDash
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

int menuDashboard(pengguna &user){
    tampilkanDashboard(user);
    cout << "== PILIH MENU ==="<<endl;
    cout <<"1. Input Data\n";
    cout <<"2. Top Up saldo\n";
    cout <<"3. Kembali\n";
    int pilihan;
    cout << "Pilih Nomor: ";
    cin >> pilihan;
    return pilihan;
}
void bayarZakat(pengguna &user){
    system("cls");
    long long bayar;
    string jenisZakat;
    string pass;
    
    cout << "=== BAYAR ZAKAT ===" << endl;
    cout << "Nominal Bayar (Rp): ";
    cin >> bayar;
    cout << "Jenis Zakat: ";
    cin >> jenisZakat;
    cout << "Password: ";
    cin >> pass;
    
    if(user.password == pass){
        if(user.saldo<bayar){
            cout << "\nSaldo tidak mencukupi untuk membayar zakat!\n";
            cout << "Kekurangan: " << Rupiah(bayar - user.saldo) << endl;
            system("pause");
            return;
        } else {
        user.saldo -= bayar;
        string amil[3];
        long long saldoAdmin;
        ifstream bacaAdmin("users.txt");
        bacaAdmin >> amil[0] >> amil[1] >> amil[2] >> saldoAdmin;
        saldoAdmin+=bayar;
        bacaAdmin.close();
        pengguna users[10000];
        int jumlahUser = 0;
        
        ifstream baca("users.txt");
        while(baca >> users[jumlahUser].id 
              >> users[jumlahUser].username 
              >> users[jumlahUser].password 
              >> users[jumlahUser].saldo){

            jumlahUser++;
        }
        baca.close();
        
        for(int i = 0; i < jumlahUser; i++){
            if(users[i].id == user.id){
                users[i].saldo = user.saldo;
                break;
            }
        }
        
        ofstream tulis("users.txt");
        for(int i = 0; i < jumlahUser; i++){
            if(i==0){
                tulis << users[i].id << " "
                      << users[i].username << " "
                      << users[i].password << " "
                      << saldoAdmin << endl;
            } else{
            tulis << users[i].id << " "
                  << users[i].username << " "
                  << users[i].password << " "
                  << users[i].saldo << endl;
            }
        }
        tulis.close();
        transaksi t;
        t.id = (jumlahTransaksi == 0) ? 1 : dataTransaksi[jumlahTransaksi-1].id + 1;
        t.id_pembayar = user.id;
        t.jenis_zakat = jenisZakat;
        t.jumlah = bayar;
        t.tanggal = getCurrentDate();
        t.status = "verified";
        t.id_penerima = 0;
        t.keterangan = "Pembayaran zakat " + jenisZakat + " oleh " + user.username;
        
        dataTransaksi[jumlahTransaksi++] = t;
        saveTransaksiToFile();
        
        cout << "Anda berhasil membayar zakat" << endl;
        cout << "Saldo Sekarang: " << Rupiah(user.saldo) << endl;
    }
    } else {
        cout << "Password salah! Gagal membayar zakat!" << endl;
    }
    
    system("pause");
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
                char bayarNow;
                cout << "Bayar Sekarang (Y/T)?";
                cin >> bayarNow;
                if(bayarNow=='Y' || bayarNow=='y'){
                    bayarZakat(user);
                    // saldo user dikurangi var zakat
                    // saldo admin ditambah var zakat
                    // 
                }
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


void editData(pengguna &user){
    system("cls");
    long long topUp;
    string pass;
    
    cout << "=== TOP UP SALDO ===" << endl;
    cout << "Masukkan Nominal top up (Rp): ";
    cin >> topUp;
    cout << "Password: ";
    cin >> pass;
    
    if(user.password == pass){
        user.saldo += topUp;
        
        pengguna users[10000];
        int jumlahUser = 0;
        
        ifstream baca("users.txt");
        while(baca >> users[jumlahUser].id 
              >> users[jumlahUser].username 
              >> users[jumlahUser].password 
              >> users[jumlahUser].saldo){
            jumlahUser++;
        }
        baca.close();
        
        for(int i = 0; i < jumlahUser; i++){
            if(users[i].id == user.id){
                users[i].saldo = user.saldo;
                break;
            }
        }
        
        ofstream tulis("users.txt");
        for(int i = 0; i < jumlahUser; i++){
            tulis << users[i].id << " "
                  << users[i].username << " "
                  << users[i].password << " "
                  << users[i].saldo << endl;
        }
        tulis.close();
        
        cout << "Saldo berhasil ditambahkan!" << endl;
        cout << "Saldo Sekarang: " << Rupiah(user.saldo) << endl;
        
    } else {
        cout << "Password salah! Saldo gagal ditambahkan!" << endl;
    }
    
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
                    menuAdminLengkap(1);
                    system("pause");
                } else {
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
                    menuAdminLengkap(2);
                } else {
                    cout << "=== BAYAR ZAKAT ===\n";
                    bayarZakat(user);
                }
                system("pause");
                break;
                
            case 3:
                if(isAdmin){
                    menuAdminLengkap(3);
                } else {
                    inputData(user);
                }
                break;
                
            case 4:
                user = pengguna();
                cout << "Logout berhasil..\n";
                return;
                
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
    long long saldo;
    ifstream cek;
    cek.open("users.txt");
    while(cek >> id >> uname >> pass >> saldo){
        if(uname == "AmilZakat") 
        adaAdmin = true;
    }
    cek.close();

    if(!adaAdmin){
        ofstream tulis("users.txt");
        tulis << 1 << " AmilZakat insyaAllahBarokah_2025 0 \n";
        tulis.close();
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
        ifstream bacaUser1;
        bacaUser1.open("users.txt");
        while(bacaUser1 >> pengguna.id >> pengguna.username >> pengguna.password >> pengguna.saldo){
            if(pengguna.username==user[0] && user[1] == pengguna.password){
                isLogin=true;
                break;
            }
        }
        bacaUser1.close();
        system("cls");
        if(isLogin){
            cout << pengguna.username << " berhasil Login\n";
        }else{
            cout << "Akun tidak ditemukan\n";
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
        while(bacaUser3 >> pengguna.id >> user[0] >> user[1] >> pengguna.saldo){
            if(user[0]==pengguna.username){
                cout << "username sudah digunakan, coba username lain\n";
                isUnique=false;
                break;
            }
        }
        if(isUnique){
            pengguna.id=autoIncrement("users.txt");
            ofstream appendUser1;
            appendUser1.open("users.txt", ios::app);
            appendUser1 << pengguna.id << " " << pengguna.username << " " << pengguna.password << " " << pengguna.saldo << "\n";
            appendUser1.close();
            cout << pengguna.username<< " Berhasil Register\n";
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
cout <<"Selesai"<<endl;
}

