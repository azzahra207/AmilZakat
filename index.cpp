#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct pengguna{
    int id;
    string username;
    string password;
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
int menu(pengguna &user){
    system("cls");
    int hasil;
    cout << "=== BERANDA AMIL ZAKAT ==="<<endl;
    if(user.username=="AmilZakat"){
        cout << "1. Manajemen Pembayaran Zakat\n";
        cout << "2. Penyaluran Zakat\n";
        cout << "3. Monitoring Saldo Zakat\n";
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
int menuDashboard(pengguna &user){
    cout << "== PILIH MENU ==="<<endl;
    cout <<"1. Input Data\n";
    cout <<"2. Edit Data\n";
    cout <<"3. Kembali\n";
    int pilihan;
    cout << "Pilih Nomor: ";
    cin >> pilihan;
    return pilihan;
}
int menuJenisZakat(){
    system("cls");
    cout << "=== PILIH JENIS ZAKAT ==="<<endl;
    cout <<"1. Zakat Penghasilan\n";
    cout <<"2. Zakat Perhiasan\n";
    cout <<"3. Zakat Pertanian\n";
    cout <<"4. Zakat Tanaman/Perikanan\n";
    cout <<"5. Zakat Properti\n";
    cout <<"6. Zakat Rikaz\n";
    cout <<"7. Zakat Ternak\n";
    cout <<"8. Kembali\n";
    int pilihan;
    cout << "Pilihan: ";
    cin >> pilihan;
    return pilihan;
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
                     << "0" << endl; // wajibZakat default false
                file.close();
                cout << "Data berhasil disimpan!\n";
            } else {
                cout << "Gagal menyimpan data!\n";
            }
            break;
        }
        case 2:{
            perhiasan data;
            data.id_user = user.id;
            
            cout << "\n=== INPUT DATA PENGHASILAN ==="<<endl;
            cout << "Pekerjaan: ";
            cin.ignore();
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
                     << "0" << endl; // wajibZakat default false
                file.close();
                cout << "Data berhasil disimpan!\n";
            } else {
                cout << "Gagal menyimpan data!\n";
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
            
            // Simpan ke file
            ofstream file("ternak.txt", ios::app);
            if(file.is_open()){
                file << autoIncrement("ternak.txt") << " "
                     << data.id_user << " "
                     << data.nama << " "
                     << data.jumlah << " "
                     << "0" << endl; // wajibZakat default false
                file.close();
                cout << "Data berhasil disimpan!\n";
            } else {
                cout << "Gagal menyimpan data!\n";
            }
            break;
        }
        
        case 8:
            return;
            
        default:
            cout << "Menu belum tersedia!\n";
            break;
    }
    system("pause");
}
void kalkulatorZakat(pengguna &user){
    system("cls");
    cout << "=== KALKULATOR ZAKAT ==="<<endl;
    
    int pilihan = menuJenisZakat();
    
    switch(pilihan){
        case 1: { // Zakat Penghasilan
            penghasilan data;
            data.id_user = user.id;
            
            cout << "\n=== KALKULATOR ZAKAT PENGHASILAN ==="<<endl;
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
            
            long long zakat = zakatPenghasilan(data);
            cout << "\n=== HASIL PERHITUNGAN ==="<<endl;
            cout << "Status: " << (data.wajibZakat ? "WAJIB ZAKAT" : "Tidak Wajib Zakat") << endl;
            if(data.wajibZakat){
                cout << "Zakat yang harus dibayar: " << Rupiah(zakat) << endl;
            }
            break;
        }
        
        case 7: { // Zakat Ternak
            ternak data;
            data.id_user = user.id;
            
            cout << "\n=== KALKULATOR ZAKAT TERNAK ==="<<endl;
            cout << "Jenis ternak (unta/sapi/kambing): ";
            cin.ignore();
            getline(cin, data.nama);
            cout << "Jumlah ternak (ekor): ";
            cin >> data.jumlah;
            
            string hasil = zakatTernak(data);
            cout << "\n=== HASIL PERHITUNGAN ==="<<endl;
            cout << "Status: " << (data.wajibZakat ? "WAJIB ZAKAT" : "Tidak Wajib Zakat") << endl;
            cout << "Keterangan: " << hasil << endl;
            break;
        }
        
        case 8:
            return;
            
        default:
            cout << "Menu belum tersedia!\n";
            break;
    }
    system("pause");
}
void editData(pengguna &user){
    system("cls");
    cout << "=== EDIT DATA ==="<<endl;
    cout << "Fitur edit data belum diimplementasi.\n";
    cout << "Silakan gunakan input data baru untuk memperbarui.\n";
    system("pause");
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
void handleMenu(pengguna &user){
    bool isAdmin = user.username == "AmilZakat";
    int pilihanMenu;
    
    while(true){
        pilihanMenu = menu(user);
        
        switch(pilihanMenu){
            case 1:
                if(isAdmin){
                    cout << "Menu Admin - Manajemen Pembayaran Zakat\n";
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
                                kalkulatorZakat(user);
                                break;
                            case 4:
                                cout << "Kembali ke menu utama...\n";
                                break;
                            default:
                                cout << "Pilihan tidak valid!\n";
                                system("pause");
                                break;
                        }
                    } while(menuDash != 4);
                }
                break;
                
            case 2:
                if(isAdmin){
                    cout << "Menu Admin - Penyaluran Zakat\n";
                } else {
                    cout << "=== BAYAR ZAKAT ===\n";
                    tampilkanDashboard(user);
                }
                system("pause");
                break;
                
            case 3:
                if(isAdmin){
                    cout << "Menu Admin - Monitoring Saldo Zakat\n";
                } else {
                    kalkulatorZakat(user);
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
int autoIncrement(string nameFile){
    ifstream bacaDatabase2;
    int hasilId=1;
    string data[2];
    bacaDatabase2.open(nameFile);
    while(bacaDatabase2 >> hasilId >> data[0] >> data[1]){
        hasilId++;
    }
    bacaDatabase2.close();
    return hasilId;
}
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
    long long nisab=cariNisabLong("tanaman_produktif_dan_perikanan");
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
    long long nisab=cariNisabLong("properti");
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
                int jumlahEkor[2]; // usia 2 dan 1 tahun
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
    ifstream cek;
    cek.open("users.txt");
    while(cek >> id >> uname >> pass){
        if(uname == "AmilZakat") 
        adaAdmin = true;
    }
    cek.close();

    if(!adaAdmin){
        ofstream tulis("users.txt");
        tulis << 1 << " AmilZakat insyaAllahBarokah_2025\n";
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
        while(bacaUser1 >> pengguna.id >> pengguna.username >> pengguna.password){
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
        while(bacaUser3 >> pengguna.id >> user[0] >> user[1]){
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
            appendUser1 << pengguna.id << " " << pengguna.username << " " << pengguna.password << "\n";
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
