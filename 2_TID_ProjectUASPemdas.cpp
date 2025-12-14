#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <ctime>
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
    long long piutang; 
    long long utang;
    long long kebutuhan;
    bool wajibZakat;
};
struct perhiasan{
    int id;
    int id_user;
    string nama;
    float berat;
    long long hargaPerGram; 
    bool wajibZakat;
};
struct tani{
    int id;
    int id_user;
    string nama;
    float berat; 
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
    string status; 
    int id_penerima;
    string keterangan;
};

struct mustahik {
    int id;
    string nama;
    string kategori; 
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



/////////////////////////////////// FUNGSI BANTUAN/////////////////////////////////
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
string replaceSpasi(const string &input) {
    char *result = new char[input.length() + 1];
    strcpy(result, input.c_str());
    for(int i = 0; result[i] != '\0'; i++) {
        if(result[i] == ' ') {
            result[i] = '_';
        }
    }
    string finalResult(result);
    delete[] result;
    return finalResult;
}
string replaceToSpasi(const string &input) {
    char *result = new char[input.length() + 1];
    strcpy(result, input.c_str());
    for(int i = 0; result[i] != '\0'; i++) {
        if(result[i] == '_') {
            result[i] = ' ';
        }
    }
    string finalResult(result);
    delete[] result;
    return finalResult;
}
void lower(string &str, int i = 0) {
    int jmlChar=str.length();
    if (i >= jmlChar) {
        return;
    }  
    if (str[i] >= 'A' && str[i] <= 'Z') {
        str[i] = str[i] + 32;
    }
    lower(str, i + 1);
}

string getTerjemahanNiat(string jenisZakat) {
    if (jenisZakat == "penghasilan" || jenisZakat == "perusahaan") {
        return "Aku niat mengeluarkan zakat penghasilanku, fardhu karena Allah Ta'ala";
    } else if (jenisZakat == "perhiasan" || jenisZakat == "emas" || jenisZakat == "perak") {
        return "Aku niat mengeluarkan zakat perhiasanku, fardhu karena Allah Ta'ala";
    } else if (jenisZakat == "pertanian" || jenisZakat == "beras_putih" || jenisZakat == "padi_gagang" || 
               jenisZakat == "padi_kretek" || jenisZakat == "kacang_hijau" || 
               jenisZakat == "kacang_tunggak") {
        return "Aku niat mengeluarkan zakat hasil pertanianku, fardhu karena Allah Ta'ala";
    } else if (jenisZakat == "tanaman_produktif_dan_perikanan") {
        return "Aku niat mengeluarkan zakat hasil kebunku, fardhu karena Allah Ta'ala";
    } else if (jenisZakat == "properti") {
        return "Aku niat mengeluarkan zakat propertiku, fardhu karena Allah Ta'ala";
    } else if (jenisZakat == "barang_temuan" || jenisZakat == "rikaz") {
        return "Aku niat mengeluarkan zakat barang temuanku, fardhu karena Allah Ta'ala";
    } else if (jenisZakat == "peternakan" || jenisZakat == "sapi" || jenisZakat == "kambing" || jenisZakat == "unta") {
        return "Aku niat mengeluarkan zakat ternakku, fardhu karena Allah Ta'ala";
    } else if (jenisZakat == "fitrah") {
        return "Aku niat mengeluarkan zakat fitrah untuk diriku, fardhu karena Allah Ta'ala";
    } else {
        return "Aku niat mengeluarkan zakat hartaku, fardhu karena Allah Ta'ala";
    }
}
long long cariNisabLong(string nama, int i=0){
    dataNisab datanisab;
    if(i>=15)
        return 0LL;
    else
    return (datanisab.nama[i]!=nama) ? cariNisabLong(nama,i+1) : (long long)datanisab.nisab[i];
}
float cariNisabFloat(string nama, int i = 0) {
    dataNisab datanisab;
    if(i >= 15){
        return 0;
    }
    if(datanisab.nama[i] == nama){
        return datanisab.nisab[i];
    } 
    return cariNisabFloat(nama, i+1);
}

string cariHaul(string nama, int i=0){
    dataNisab datanisab;
    if(i>=15){
        return 0;
    }
    else if(datanisab.nama[i]==nama){
        return (string)datanisab.haul[i];
    } else{
        return cariHaul(nama,i+1);
    }
}
float cariZakatFloat(string nama, int i=0){
    dataNisab datanisab;
    if(i>=15){
        return 0;
    }
    else if(datanisab.nama[i]==nama){
        return datanisab.wajibZakat[i]/100;
    } else{
        return cariZakatFloat(nama,i+1);
    }
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
                
            } else if(row.jumlah>5){
               string jenisUnta[4]={"bintu makhad","bintu labun", "hiqqah","hiqqah tua"};
                struct zakatUnta{
                    string hewan[3]={"unta betina","kambing","domba"};
                    int usia[3]={0,2,1};
                    int jumlahEkor[3]={0,1,1};  
                };
                zakatUnta zakatunta;
                for(int i=9;i<=19;i+=5){
                    if(row.jumlah>i){
                        zakatunta.jumlahEkor[1]++;
                        zakatunta.jumlahEkor[2]++;
                    }
                }
                if(row.jumlah>24){
                    zakatunta.jumlahEkor[1]=0;
                    zakatunta.jumlahEkor[2]=0;
                    zakatunta.jumlahEkor[0]++;
                }
                for(int i=24;i<=60;i+=10){
                    if(i==55){
                        i+=5;
                    }
                    if(row.jumlah>i){
                        zakatunta.usia[0]++;
                    }
                    if(i==24){
                        i++;
                    }
                }
                if(row.jumlah>75){
                    zakatunta.jumlahEkor[0]++;
                    zakatunta.usia[0]=2;
                }
                if(row.jumlah>90){
                    zakatunta.usia[0]++;
                }
                if(row.jumlah>120){
                    zakatunta.usia[0]--;
                    zakatunta.jumlahEkor[0]++;
                }
                string result;
                for (int i=0;i<3;i++){
                    if(zakatunta.jumlahEkor[i] > 0){
                        string strTemp = to_string(zakatunta.jumlahEkor[i])+ " ekor ";
                        strTemp += zakatunta.hewan[i];
                        int usia=zakatunta.usia[i];
                        strTemp += " ";
                        result+=strTemp;
                        if(zakatunta.hewan[i]=="unta betina"){
                            strTemp = (string)jenisUnta[usia-1];
                            strTemp += " ";
                            result+=strTemp;
                        }
                        strTemp="(usia ";
                        result+=strTemp;
                        strTemp = to_string(zakatunta.usia[i]) + " tahun) ";
                        result+=strTemp;
                        if(i==1){
                            result+="atau ";
                        }
                    }
                }
                return result;
            } else{
                return "Tidak wajib membayar zakat";
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
}
string padRight(string text, int width) {
    int textLen = (int)text.length();
    if(textLen >= width) {
        return text.substr(0, width);
    }

    return text + string(width - textLen, ' ');
}

string padLeft(string text, int width) {
    int textLen = (int)text.length();
    if(textLen >= width) {
        return text.substr(0, width);
    }
    return string(width - textLen, ' ') + text;
}
void loadTransaksiFromFile() {
    ifstream file("transaksi.txt");
    if(file.is_open()) {
        jumlahTransaksi = 0;
        string baris;
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
void riwayatPembayaranZakat(pengguna &user) {
    system("cls");
    cout << "=== RIWAYAT PEMBAYARAN ZAKAT " << user.username << " ===\n\n";
    
    bool adaRiwayat = false;
    int count = 0;

    cout << "+-----+------------+----------------------+----------------+------------+\n";
    cout << "| No  | Tanggal    | Jenis Zakat          | Jumlah         | Status     |\n";
    cout << "+-----+------------+----------------------+----------------+------------+\n";
    loadTransaksiFromFile();
    for(int i = 0; i < jumlahTransaksi; i++) {
        if(dataTransaksi[i].id_pembayar == user.id) {
            adaRiwayat = true;
            count++;
            
            string jenis = dataTransaksi[i].jenis_zakat;
            if(jenis.length() > 20) jenis = jenis.substr(0, 17) + "...";
            
            cout << "| " << padLeft(to_string(count), 3) << " "
                 << "| " << padRight(dataTransaksi[i].tanggal, 10)
                 << " | " << padRight(jenis, 20)
                 << " | " << padRight(Rupiah(dataTransaksi[i].jumlah), 14)
                 << " | " << padRight(dataTransaksi[i].status, 10) << " |\n";
        }
    }
    
    if(!adaRiwayat) {
        cout << "|                      BELUM ADA RIWAYAT PEMBAYARAN                    |\n";
    }
    
    cout << "+-----+------------+----------------------+----------------+------------+\n\n";
    
    long long totalDibayar = 0;
    for(int i = 0; i < jumlahTransaksi; i++) {
        if(dataTransaksi[i].id_pembayar == user.id && 
           dataTransaksi[i].status == "verified") {
            totalDibayar += dataTransaksi[i].jumlah;
        }
    }
    
    cout << "Total zakat yang telah dibayarkan: " << Rupiah(totalDibayar) << endl;
    
    cout << "\nTekan Enter untuk kembali...";
    cin.ignore();
    cin.get();
}
void panduanZakat() {
    system("cls");
    int pilihan;
    
    do {
        system("cls");
        cout << "=== PANDUAN ZAKAT ===\n\n";
        cout << "1. Syarat-Syarat Wajib Zakat\n";
        cout << "2. Jenis-Jenis Zakat\n";
        cout << "3. Nisab Zakat\n";
        cout << "4. Cara Menghitung Zakat\n";
        cout << "5. 8 Golongan Mustahik\n";
        cout << "6. Kembali\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        
        switch(pilihan) {
            case 1: {
                system("cls");
                cout << "=== SYARAT-SYARAT WAJIB ZAKAT ===\n\n";
                cout << "1. Islam\n";
                cout << "2. Merdeka (bukan budak)\n";
                cout << "3. Berakal dan baligh\n";
                cout << "4. Memiliki harta yang mencapai nisab\n";
                cout << "5. Harta dimiliki secara sempurna\n";
                cout << "6. Telah mencapai haul (1 tahun)\n";
                cout << "7. Kebutuhan pokok telah terpenuhi\n";
                cout << "8. Bebas dari hutang\n\n";
                cout << "Keterangan:\n";
                cout << "- Nisab: batas minimum harta yang wajib dizakati\n";
                cout << "- Haul: kepemilikan harta selama 1 tahun hijriyah\n";
                system("pause");
                break;
            }
            
            case 2: {
                system("cls");
                cout << "=== JENIS-JENIS ZAKAT ===\n\n";
                cout << "1. ZAKAT FITRAH\n";
                cout << "   - Dibayar di bulan Ramadhan\n";
                cout << "   - Sebesar 2.5 kg beras/gandum atau senilai\n";
                cout << "   - Wajib bagi setiap muslim\n\n";
                
                cout << "2. ZAKAT MAL (HARTA)\n";
                cout << "   a. Zakat Emas/Perak\n";
                cout << "      - Nisab emas: 85 gram\n";
                cout << "      - Nisab perak: 595 gram\n";
                cout << "      - Kadar: 2.5%\n\n";
                
                cout << "   b. Zakat Uang/Investasi\n";
                cout << "      - Nisab: senilai 85 gram emas\n";
                cout << "      - Kadar: 2.5%\n\n";
                
                cout << "   c. Zakat Pertanian\n";
                cout << "      - Nisab: 5 wasq (653 kg)\n";
                cout << "      - Kadar: 5% (irigasi berbayar) atau 10% (tadah hujan)\n\n";
                
                cout << "   d. Zakat Ternak\n";
                cout << "      - Sapi/kerbau: nisab 30 ekor\n";
                cout << "      - Kambing/domba: nisab 40 ekor\n";
                cout << "      - Unta: nisab 5 ekor\n\n";
                
                cout << "   e. Zakat Profesi\n";
                cout << "      - Nisab: senilai 85 gram emas per tahun\n";
                cout << "      - Kadar: 2.5% dari penghasilan bersih\n";
                system("pause");
                break;
            }
            
            case 3: {
                system("cls");
                cout << "=== NISAB ZAKAT ===\n\n";

                dataNisab nisab;
                cout << "+----+----------------------------+----------------+----------+\n";
                cout << "| No | Jenis Harta                | Nisab          | Satuan   |\n";
                cout << "+----+----------------------------+----------------+----------+\n";

                for(int i = 0; i < 15; i++) {
                    string jenis = replaceToSpasi(nisab.nama[i]);
                    if(jenis.length() > 25) jenis = jenis.substr(0, 22) + "...";
                    string strNisab;
                    if(nisab.nisab[i] == (long long)nisab.nisab[i]) {
                        strNisab = to_string((long long)nisab.nisab[i]);
                    } else {
                        strNisab = to_string(nisab.nisab[i]);
                        if(strNisab.length() > 10) {
                            strNisab = strNisab.substr(0, 10);
                        }
                    }

                    cout << "| " << padLeft(to_string(i+1), 2) << " "
                         << "| " << padRight(jenis, 26)
                         << "| " << padRight(strNisab, 14)
                         << "| " << padRight(nisab.satuan[i], 8) << " |\n";
                }
                cout << "+----+----------------------------+----------------+----------+\n\n";

                cout << "Keterangan:\n";
                cout << "- Nisab dalam satuan yang tertera\n";
                cout << "- Untuk zakat uang, nisab = senilai 85 gram emas\n";
                system("pause");
                break;
            }
            
            case 4: {
                system("cls");
                cout << "=== CARA MENGHITUNG ZAKAT ===\n\n";
                cout << "RUMUS UMUM:\n";
                cout << "Zakat = 2.5% x (Harta - Hutang - Kebutuhan Pokok)\n\n";
                
                cout << "CONTOH PERHITUNGAN:\n\n";
                cout << "1. Zakat Emas:\n";
                cout << "   - Emas yang dimiliki: 100 gram\n";
                cout << "   - Harga emas/gram: Rp 1.000.000\n";
                cout << "   - Total nilai: 100 x 1.000.000 = Rp 100.000.000\n";
                cout << "   - Zakat: 2.5% x Rp 100.000.000 = Rp 2.500.000\n\n";
                
                cout << "2. Zakat Penghasilan:\n";
                cout << "   - Gaji bulanan: Rp 10.000.000\n";
                cout << "   - Penghasilan setahun: 12 x 10.000.000 = Rp 120.000.000\n";
                cout << "   - Kebutuhan pokok setahun: Rp 60.000.000\n";
                cout << "   - Penghasilan bersih: 120.000.000 - 60.000.000 = Rp 60.000.000\n";
                cout << "   - Zakat: 2.5% x 60.000.000 = Rp 1.500.000\n\n";
                
                cout << "3. Zakat Pertanian:\n";
                cout << "   - Hasil panen: 1000 kg beras\n";
                cout << "   - Irigasi berbayar: ya\n";
                cout << "   - Zakat: 5% x 1000 kg = 50 kg beras\n";
                system("pause");
                break;
            }
            
            case 5: {
                system("cls");
                cout << "=== 8 GOLONGAN MUSTAHIK (PENERIMA ZAKAT) ===\n\n";
                cout << "1. FAKIR\n";
                cout << "   - Orang yang tidak memiliki harta dan pekerjaan\n";
                cout << "   - Tidak mampu memenuhi kebutuhan pokok\n\n";
                
                cout << "2. MISKIN\n";
                cout << "   - Memiliki harta/pekerjaan tapi tidak mencukupi\n";
                cout << "   - Penghasilan di bawah standar minimum\n\n";
                
                cout << "3. AMIL\n";
                cout << "   - Pengelola zakat (panitia, admin, dll)\n";
                cout << "   - Mendapat bagian dari zakat sebagai upah\n\n";
                
                cout << "4. MUALLAF\n";
                cout << "   - Orang yang baru masuk Islam\n";
                cout << "   - Diberi zakat untuk menguatkan iman\n\n";
                
                cout << "5. RIQAAB (HAMBASAHAYA)\n";
                cout << "   - Budak yang ingin memerdekakan diri\n";
                cout << "   - Di masa sekarang: membantu pekerja terikat\n\n";
                
                cout << "6. GHARIMIN\n";
                cout << "   - Orang yang berhutang untuk kebutuhan halal\n";
                cout << "   - Tidak mampu melunasi hutangnya\n\n";
                
                cout << "7. FISABILILLAH\n";
                cout << "   - Orang yang berjuang di jalan Allah\n";
                cout << "   - Aktivis dakwah, pendidikan Islam, dll\n\n";
                
                cout << "8. IBNU SABIL\n";
                cout << "   - Musafir yang kehabisan bekal\n";
                cout << "   - Pelajar/mahasiswa rantau yang kesulitan\n";
                system("pause");
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



void saveTransaksiToFile() {
    ofstream file("transaksi.txt");
    for(int i = 0; i < jumlahTransaksi; i++) {
        file << dataTransaksi[i].id << " "
             << dataTransaksi[i].id_pembayar << " "
             << dataTransaksi[i].jenis_zakat << " "
             << dataTransaksi[i].jumlah << " "
             << dataTransaksi[i].tanggal << " "
             << dataTransaksi[i].status << " "
             << dataTransaksi[i].id_penerima << " "
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
             << dataMustahik[i].tanggal_terakhir << " "
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
    time_t now = time(0);
    tm *ltm = localtime(&now);
    
    char frmDate[11];
    strftime(frmDate, sizeof(frmDate), "%Y-%m-%d", ltm);
    
    return string(frmDate);
}

/////////////////////////////////// FUNGSI MENU ADMIN/////////////////////////////////

void distribusiZakatKeMustahik() {
    system("cls");
    cout << "=== DISTRIBUSI ZAKAT KE MUSTAHIK ===\n\n";
    
    loadTransaksiFromFile();
    loadMustahikFromFile();
    
    pengguna admin;
    ifstream dataAmil("users.txt");
    if(dataAmil.is_open()) {
        dataAmil >> admin.id >> admin.username >> admin.password >> admin.saldo;
        dataAmil.close();
    }
    
    cout << "Saldo Zakat Tersedia: " << Rupiah(admin.saldo) << endl;
    cout << "============================\n";
    
    if(admin.saldo <= 0) {
        cout << "Tidak ada zakat yang siap didistribusikan.\n";
        system("pause");
        return;
    }
    
    cout << "\nDAFTAR MUSTAHIK:\n";
    cout << "===============\n";
    if(jumlahMustahik == 0) {
        cout << "Belum ada data mustahik.\n";
        cout << "Silakan tambah mustahik terlebih dahulu.\n";
        system("pause");
        return;
    }
    
    for(int i = 0; i < jumlahMustahik; i++) {
        cout << "ID: " << dataMustahik[i].id << endl
             << " | Nama: " << padRight(dataMustahik[i].nama, 20) << endl
             << " | Kategori: " << padRight(dataMustahik[i].kategori, 15) << endl
             << " | Total Diterima: " << Rupiah(dataMustahik[i].total_diterima) << endl;
    }
    
    long long nominalDistribusi;
    int idMustahik;
    
    cout << "\nMasukkan ID Mustahik penerima: ";
    cin >> idMustahik;
    cout << "Masukkan Nominal Distribusi (Rp): ";
    cin >> nominalDistribusi;
    
    if(nominalDistribusi <= 0) {
        cout << "Nominal distribusi harus lebih dari 0.\n";
        system("pause");
        return;
    }
    
    int idxMustahik = -1;
    for(int i = 0; i < jumlahMustahik; i++) {
        if(dataMustahik[i].id == idMustahik) {
            idxMustahik = i;
            break;
        }
    }
    
    if(admin.saldo < nominalDistribusi) {
        cout << "Saldo tidak mencukupi.\n";
        cout << "Saldo tersedia: " << Rupiah(admin.saldo) << endl;
        cout << "Kekurangan: " << Rupiah(nominalDistribusi - admin.saldo) << endl;
    } else if(idxMustahik == -1) {
        cout << "Mustahik dengan ID " << idMustahik << " tidak ditemukan.\n";
    } else {
        cout << "\n=== KONFIRMASI DISTRIBUSI ===\n";
        cout << "Penerima     : " << dataMustahik[idxMustahik].nama 
             << " (" << dataMustahik[idxMustahik].kategori << ")\n";
        cout << "Alamat       : " << dataMustahik[idxMustahik].alamat << endl;
        cout << "Nominal      : " << Rupiah(nominalDistribusi) << endl;
        cout << "Saldo sebelum: " << Rupiah(admin.saldo) << endl;
        cout << "Saldo sesudah: " << Rupiah(admin.saldo - nominalDistribusi) << endl;
        
        char konfirmasi;
        cout << "\nLanjutkan distribusi? (Y/T): ";
        cin >> konfirmasi;
        
        if(konfirmasi == 'Y' || konfirmasi == 'y') {
            pengguna users[10000];
            int jumlahUser = 0;
            
            ifstream bacaUser("users.txt");
            while(bacaUser >> users[jumlahUser].id 
                  >> users[jumlahUser].username 
                  >> users[jumlahUser].password 
                  >> users[jumlahUser].saldo) {
                jumlahUser++;
            }
            bacaUser.close();
            
            if(jumlahUser > 0) {
                users[0].saldo -= nominalDistribusi;
                admin.saldo = users[0].saldo;
            }
            
            ofstream tulisUser("users.txt");
            for(int i = 0; i < jumlahUser; i++) {
                tulisUser << users[i].id << " "
                         << users[i].username << " "
                         << users[i].password << " "
                         << users[i].saldo << endl;
            }
            tulisUser.close();
            
            transaksi t;
            t.id = (jumlahTransaksi == 0) ? 1 : dataTransaksi[jumlahTransaksi-1].id + 1;
            t.id_pembayar = 1; 
            t.jenis_zakat = "Distribusi";
            t.jumlah = nominalDistribusi;
            t.tanggal = getCurrentDate();
            t.status = "distributed";
            t.id_penerima = idMustahik;
            t.keterangan = "Distribusi zakat ke " + dataMustahik[idxMustahik].nama;
            
            dataTransaksi[jumlahTransaksi++] = t;
            
          dataMustahik[idxMustahik].total_diterima += nominalDistribusi;
            dataMustahik[idxMustahik].tanggal_terakhir = getCurrentDate();
            
            saveTransaksiToFile();
            saveMustahikToFile();
            updateSaldo();
            
            cout << "\nDistribusi berhasil!\n";
            cout << "Transaksi ID: " << t.id << endl;
            cout << "Mustahik: " << dataMustahik[idxMustahik].nama 
                 << " menerima " << Rupiah(nominalDistribusi) << endl;
            cout << "Saldo kas zakat sekarang: " << Rupiah(admin.saldo) << endl;
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
    
    cout << "+----------------------------------------------+\n";
    cout << "|            LAPORAN KEUANGAN ZAKAT            |\n";
    cout << "+----------------------------------------------+\n";
    cout << "| Total Zakat Masuk    : " << padRight(Rupiah(saldoZakat.total_masuk), 25) << " |\n";
    cout << "| Total Zakat Keluar   : " << padRight(Rupiah(saldoZakat.total_keluar), 25) << " |\n";
    cout << "| Saldo Akhir          : " << padRight(Rupiah(saldoZakat.saldo_akhir), 25) << " |\n";
    cout << "+----------------------------------------------+\n\n";
    
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
void tampilkanDataMustahik(){
    system("cls");
                cout << "=== DAFTAR MUSTAHIK ===\n\n";
                
                if(jumlahMustahik == 0) {
                    cout << "Belum ada data mustahik.\n";
                } else {
                    cout << "+-----+--------------------+--------------------+--------------------+--------------------+\n";
                    cout << "| ID  | Nama               | Kategori           | Total Diterima     | Tanggal Terakhir   |\n";
                    cout << "+-----+--------------------+--------------------+--------------------+--------------------+\n";
                    
                    for(int i = 0; i < jumlahMustahik; i++) {
                        string nama = replaceToSpasi(dataMustahik[i].nama);
                        if(nama.length() > 18) nama = nama.substr(0, 15) + "...";
                        
                        string kategori = replaceToSpasi(dataMustahik[i].kategori);
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
            case 1: {
                mustahik baru;
                cout << "\n=== TAMBAH MUSTAHIK ===\n";
                cout << "Nama: ";
                cin.ignore();
                getline(cin, baru.nama);
                lower(baru.nama);
                baru.nama=replaceSpasi(baru.nama);

                cout << "Kategori (fakir/miskin/amil/muallaf/riqab/gharimin/fisabilillah/ibnu sabil): ";
                getline(cin, baru.kategori);
                baru.kategori=replaceSpasi(baru.kategori);
                
                cout << "Alamat: ";
                getline(cin, baru.alamat);
                baru.alamat=replaceSpasi(baru.alamat);
                
                cout << "Telepon: ";
                getline(cin, baru.telepon);
                
                cout << "Keterangan: ";
                getline(cin, baru.keterangan);
                baru.keterangan=replaceSpasi(baru.keterangan);
                
                baru.id = (jumlahMustahik == 0) ? 1 : dataMustahik[jumlahMustahik-1].id + 1;
                baru.total_diterima = 0;
                baru.tanggal_terakhir = "-";
                
                dataMustahik[jumlahMustahik++] = baru;
                saveMustahikToFile();
                
                cout << "Mustahik berhasil ditambahkan! ID: " << baru.id << endl;
                system("pause");
                break;
            }
            
            case 2: {
                tampilkanDataMustahik();
                cout << "\nTekan Enter untuk kembali...";
                cin.ignore();
                cin.get();
                break;
                
            }
            
            case 3: { 
                tampilkanDataMustahik();
                int id;
                cout << "\nMasukkan ID Mustahik yang akan diedit: ";
                cin >> id;
                
                bool found = false;
                for(int i = 0; i < jumlahMustahik; i++) {
                    if(dataMustahik[i].id == id) {
                        string show;
                        found = true;
                        cout << "\nEdit Data Mustahik ID: " << id << endl;
                        show=replaceToSpasi(dataMustahik[i].nama);
                        cout << "Nama [" << show << "]: ";
                        cin.ignore();
                        string input;
                        getline(cin, input);
                        lower(input);
                        input = replaceSpasi(input);
                        if(!input.empty()) dataMustahik[i].nama = input;
                        
                        show=replaceToSpasi(dataMustahik[i].kategori);
                        cout << "Kategori [" << show << "]: ";
                        getline(cin, input);
                        lower(input);
                        input = replaceSpasi(input);
                        if(!input.empty()) dataMustahik[i].kategori = input;
                        
                        show=replaceToSpasi(dataMustahik[i].alamat);
                        cout << "Alamat [" << show << "]: ";
                        getline(cin, input);
                        lower(input);
                        input = replaceSpasi(input);
                        if(!input.empty()) dataMustahik[i].alamat = input;
                        
                        cout << "Telepon [" << dataMustahik[i].telepon << "]: ";
                        getline(cin, input);
                        if(!input.empty()) dataMustahik[i].telepon = input;
                        
                        show=replaceToSpasi(dataMustahik[i].keterangan);
                        cout << "Keterangan [" << show << "]: ";
                        getline(cin, input);
                        lower(input);
                        input = replaceSpasi(input);
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
            
            case 4: { 
                tampilkanDataMustahik();
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
            
            case 5: { 
                string keyword;
                cout << "\nMasukkan nama atau kategori mustahik: ";
                cin.ignore();
                getline(cin, keyword);
                lower(keyword);
                keyword = replaceSpasi(keyword);
                system("cls");
                cout << "=== HASIL PENCARIAN MUSTAHIK ===\n\n";
                
                bool found = false;
                for(int i = 0; i < jumlahMustahik; i++) {
                    if(dataMustahik[i].nama.find(keyword) != string::npos ||
                       dataMustahik[i].kategori.find(keyword) != string::npos) {
                        string show;
                        found = true;
                        cout << "ID: " << dataMustahik[i].id << endl;
                        show = replaceToSpasi(dataMustahik[i].nama);
                        cout << "Nama: " << show << endl;
                        show = replaceToSpasi(dataMustahik[i].kategori);
                        cout << "Kategori: " << show << endl;
                        show = replaceToSpasi(dataMustahik[i].alamat);
                        cout << "Alamat: " << show << endl;
                        cout << "Telepon: " << dataMustahik[i].telepon << endl;
                        cout << "Total Diterima: " << Rupiah(dataMustahik[i].total_diterima) << endl;
                        cout << "Tanggal Terakhir: " << dataMustahik[i].tanggal_terakhir << endl;
                        show = replaceToSpasi(dataMustahik[i].keterangan);
                        cout << "Keterangan: " << show << endl;
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
                continue;
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
    if(bulan.length() == 1) {
    bulan = "0" + bulan;
    }
    if(tahun.length() == 2) {
    tahun = "20" + tahun;
    }
    loadTransaksiFromFile();
    loadMustahikFromFile();
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
        if(dataTransaksi[i].tanggal.substr(5, 2) == bulan && dataTransaksi[i].tanggal.substr(0, 4) == tahun && dataTransaksi[i].status == "verified") {
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
    
    cout << "+---------------------------------------------------------------+\n";
    cout << "|                         DETAIL TRANSAKSI                             |\n";
    cout << "+---------------------------------------------------------------+\n";
    cout << "| Jumlah Transaksi Masuk   : " << padRight(to_string(countMasuk), 40) << " |\n";
    cout << "| Total Zakat Masuk        : " << padRight(Rupiah(totalMasuk), 40) << " |\n";
    cout << "| Jumlah Transaksi Keluar  : " << padRight(to_string(countKeluar), 40) << " |\n";
    cout << "| Total Zakat Keluar       : " << padRight(Rupiah(totalKeluar), 40) << " |\n";
    cout << "| Saldo Akhir              : " << padRight(Rupiah(totalMasuk - totalKeluar), 40) << " |\n";
    cout << "+---------------------------------------------------------------+\n\n";
    
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
                   dataTransaksi[i].status == "verified") {
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
            
            file << "\nDETAIL TRANSAKSI:\n";
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

/////////////////////////////////// MENU ADMIN UTAMA/////////////////////////////////
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
            cout << "2. Lihat Panduan Zakat" << endl;
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
                panduanZakat();
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
    cout << "=== DASHBOARD " << user.username << " ===" << endl;
    cout << "Nama  : " << user.username << endl;
    cout << "Saldo : " << Rupiah(user.saldo) << endl;
    cout << "==================================\n";
    
    loadTransaksiFromFile();
    long long totalZakatDibayar = 0;
    int jumlahBayar = 0;
    
    for(int i = 0; i < jumlahTransaksi; i++) {
        if(dataTransaksi[i].id_pembayar == user.id && 
           dataTransaksi[i].status == "verified") {
            totalZakatDibayar += dataTransaksi[i].jumlah;
            jumlahBayar++;
        }
    }
    
    cout << "\nSTATISTIK ZAKAT ANDA:\n";
    cout << "Jumlah pembayaran zakat : " << jumlahBayar << " kali\n";
    cout << "Total zakat dibayarkan  : " << Rupiah(totalZakatDibayar) << endl;
    
    cout << "\n==================================\n";
    cout << "PILIHAN MENU:\n";
    cout << "1. Lihat Riwayat Pembayaran Zakat\n";
    cout << "2. Panduan Zakat\n";
    cout << "3. Kalkulator Zakat\n";
    cout << "4. Top Up Saldo\n";
    cout << "5. Kembali ke Menu Utama\n";
    cout << "Pilihan: ";
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
    int pilihan;
    do {
        tampilkanDashboard(user);
        cin >> pilihan;
    } while(pilihan > 5 || pilihan < 1);
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
    cin.ignore();
    getline(cin,jenisZakat);
    jenisZakat = replaceSpasi(jenisZakat);
    cout << "Password: ";
    cin >> pass;
    
    if(user.password == pass){
        if(user.saldo<bayar){
            cout << "\nSaldo tidak mencukupi untuk membayar zakat!\n";
            cout << "Kurang: " << Rupiah(bayar - user.saldo) << endl;
            return;
        } else {
        cout << "============ BACA NIAT MEMBAYAR ZAKAT ============"<<endl;
            cout << getTerjemahanNiat(jenisZakat) << endl;
            cout << "=============================\n" << endl;
            
            char konfirmasi;
            cout << "Apakah Anda sudah membaca niat dan ingin melanjutkan pembayaran? (Y/T): ";
            cin >> konfirmasi;
            
            if(konfirmasi == 'Y' || konfirmasi == 'y') {
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
    }
    } else {
        cout << "Password salah! Gagal membayar zakat!" << endl;
    }
    
}

void inputData(pengguna &user){
    system("cls");
    cout << "=== INPUT DATA KEKAYAAN ==="<<endl;
    
    int pilihan = menuJenisZakat();
    
    switch(pilihan){
        case 1: { 
            penghasilan data;
            data.id_user = user.id;
            
            cout << "\n=== INPUT DATA PENGHASILAN ==="<<endl;
            cout << "Pekerjaan: ";
            cin.ignore();  
            getline(cin, data.pekerjaan);
            data.pekerjaan = replaceSpasi(data.pekerjaan);
            cout << "Modal usaha (Rp): ";
            cin >> data.modal;
            cout << "Gaji bulanan (Rp): ";
            cin >> data.gajiBulanan;
            cout << "Piutang yang bisa ditagih (Rp): ";
            cin >> data.piutang;
            cout << "Utang (Rp): ";
            cin >> data.utang;
            cout << "Kebutuhan pokok per bulan (Rp): ";
            cin >> data.kebutuhan;
            
            long long zakat = zakatPenghasilan(data);
            
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
            
            cout << "\n=== HASIL PERHITUNGAN ==="<<endl;
            cout << "Status: " << (data.wajibZakat ? "WAJIB ZAKAT" : "Tidak Wajib Zakat") << endl;
            if(data.wajibZakat){
                cout << "Zakat yang harus dibayar: " << Rupiah(zakat) << " " <<cariHaul("perusahaan") << endl;
                char bayarNow;
                cout << "Bayar Sekarang (Y/T)?";
                cin >> bayarNow;
                if(bayarNow=='Y' || bayarNow=='y'){
                    bayarZakat(user);
                }
            }
            break;
        }
        
        case 2: { 
            perhiasan data;
            data.id_user = user.id;
            
            cout << "\n=== INPUT DATA PERHIASAN ==="<<endl;
            cout << "Jenis Perhiasan : \n";
            cout << "1. emas\n";
            cout << "2. perak\n";
            cout << "Pilih Nomor: ";
            int namaPerhiasan;
            cin >> namaPerhiasan;
            
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
            
            long long zakat = zakatPerhiasan(data);
            
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
            
            cout << "\n=== HASIL PERHITUNGAN ==="<<endl;
            cout << "Status: " << (data.wajibZakat ? "WAJIB ZAKAT" : "Tidak Wajib Zakat") << endl;
            if(data.wajibZakat){
                cout << "Zakat yang harus dibayar: " << Rupiah(zakat) << endl;
                char bayarNow;
                cout << "Bayar Sekarang (Y/T)?";
                cin >> bayarNow;
                if(bayarNow=='Y' || bayarNow=='y'){
                    bayarZakat(user);
                }
            }
            break;
        }
        
        case 3: { 
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
            
            float zakat = zakatPertanian(data);
            
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
            
            cout << "\n=== HASIL PERHITUNGAN ==="<<endl;
            cout << "Status: " << (data.wajibZakat ? "WAJIB ZAKAT" : "Tidak Wajib Zakat") << endl;
            if(data.wajibZakat){
                cout << "Zakat yang harus dibayar: " << zakat << " kg" << endl;
            }
            break;
        }
        
        case 4: { 
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
            
            long long zakat = zakatTanaman(data);
            
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
            
            cout << "\n=== HASIL PERHITUNGAN ==="<<endl;
            cout << "Status: " << (data.wajibZakat ? "WAJIB ZAKAT" : "Tidak Wajib Zakat") << endl;
            if(data.wajibZakat){
                cout << "Zakat yang harus dibayar: " << Rupiah(zakat) << endl;
                char bayarNow;
                cout << "Bayar Sekarang (Y/T)?";
                cin >> bayarNow;
                if(bayarNow=='Y' || bayarNow=='y'){
                    bayarZakat(user);
                }
            }
            break;
        }
        
        case 5: { 
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
            
            long long zakat = zakatProperti(data);
            
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
            
            cout << "\n=== HASIL PERHITUNGAN ==="<<endl;
            cout << "Status: " << (data.wajibZakat ? "WAJIB ZAKAT" : "Tidak Wajib Zakat") << endl;
            if(data.wajibZakat){
                cout << "Zakat yang harus dibayar: " << Rupiah(zakat) << endl;
                char bayarNow;
                cout << "Bayar Sekarang (Y/T)?";
                cin >> bayarNow;
                if(bayarNow=='Y' || bayarNow=='y'){
                    bayarZakat(user);
                }
            }
            break;
        }
        
        case 6: { 
            rikaz data;
            data.id_user = user.id;
            
            cout << "\n=== INPUT HARTA TEMUAN (RIKAZ) ==="<<endl;
            cout << "Nama Barang: ";
            cin.ignore();
            getline(cin, data.barang);
            cout << "Harga Barang (Rp): ";
            cin >> data.hargaBarang;
            
            long long zakat = zakatRikaz(data);
            
            ofstream file("rikaz.txt", ios::app);
            if(file.is_open()){
                file << autoIncrement("rikaz.txt") << " "
                     << data.id_user << " "
                     << data.barang << " "
                     << data.hargaBarang << " "
                     << "0" << endl;
                file.close();
                cout << "Data berhasil disimpan!\n";
            } else {
                cout << "Gagal menyimpan data!\n";
            }
            
            cout << "\n=== HASIL PERHITUNGAN ==="<<endl;
            cout << "Status: " << (data.hargaBarang > 0 ? "WAJIB ZAKAT" : "Tidak Wajib Zakat") << endl;
            if(data.hargaBarang > 0){
                cout << "Zakat yang harus dibayar: " << Rupiah(zakat) << endl;
                char bayarNow;
                cout << "Bayar Sekarang (Y/T)?";
                cin >> bayarNow;
                if(bayarNow=='Y' || bayarNow=='y'){
                    bayarZakat(user);
                }
            }
            break;
        }
        
        case 7: { 
            ternak data;
            data.id_user = user.id;
            
            cout << "\n=== INPUT DATA TERNAK ==="<<endl;
            cout << "Jenis ternak (unta/sapi/kambing): ";
            cin.ignore();
            getline(cin, data.nama);
            cout << "Jumlah ternak (ekor): ";
            cin >> data.jumlah;
            
            string hasilZakat = zakatTernak(data);
            
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
            
            cout << "\n=== HASIL PERHITUNGAN ==="<<endl;
            cout << "Status: " << (data.wajibZakat ? "WAJIB ZAKAT" : "Tidak Wajib Zakat") << endl;
            cout << "Keterangan: " << hasilZakat << endl;
            break;
        }
        
        case 8: 
            return;
            
        default:
            cout << "Menu tidak valid!\n";
            break;
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
                                riwayatPembayaranZakat(user);
                                break;
                            case 2:
                                panduanZakat();
                                break;
                            case 3:
                                inputData(user); 
                                break;
                            case 4:
                                editData(user);
                                break;
                            case 5:
                                cout << "Kembali ke menu utama...\n";
                                break;
                            default:
                                cout << "Pilihan tidak valid!\n";
                                system("pause");
                                break;
                        }
                    } while(menuDash != 5);
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
    loadTransaksiFromFile();
    loadMustahikFromFile();
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
        cout << "Username (tidak boleh ada spasi): ";
        cin >> pengguna.username;
        
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
            while(true){
            cout << "Password (minimal 8 karakter): ";
            cin >> pengguna.password;
            if(pengguna.password.length()<8){
                cout << "Kurang dari 8 karakter"<<endl;
                continue;
            }
            string confirmPass;
            cout << "Konfirmasi password: "<<endl;
            cin >> confirmPass;
            if(pengguna.password!=confirmPass){
            cout << "Konfirmasi Password tidak sesuai"<<endl;
            } else{
                break;
            }
            };
            pengguna.id=autoIncrement("users.txt");
            ofstream appendUser1;
            pengguna.saldo=0;
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

