#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct pengguna{
    int id;
    string username;
    string password;
};
struct penghasilan{
    int id;
    int id_user;
    string pekerjaan;
    long long pendapatan;
    long long piutang; // yang kira-kira bisa ditagih
};
struct kebutuhan{
    int id;
    int id_user;
    long long modal;
    long long hutang;
    long long kebutuhan;
};
struct hartaLain{
    int id;
    int id_user;
    int id_perhiasan;
    int id_tani; //bahan pangan pokok
    int id_tanaman;
    int id_ternak;
    int id_penghasilan;
    int id_properti;
    int id_rikaz;
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
        174970433,
        30,
        40,
        5,
        174970433,
        174970433,
        174970433,
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
int menuDashboard(pengguna user){

}
void handleMenu(pengguna &user){
    bool isAdmin=user.username=="AmilZakat";
    int pilihanMenu;
    while(true){
        pilihanMenu=menu(user);
        switch(pilihanMenu){
            case 1:
                if(isAdmin){
                }else{
                    cout << "=== DASHBOARD ==="<<endl;
                    cout << "Nama : "<< user.username<<endl;
                    cout << "Penghasilan : "<<endl;
                    cout << "Harta Lainnya : "<<endl;
                    cout << "Total Kebutuhan : "<<endl;
                    cout << "Wajib Zakat : "<<endl;
                    cout << "Status : "<<endl;
                    cout << "Berhak menerima Zakat : "<<endl;
                    menuDashboard(user);
                }
            break;
            case 2:
                if(isAdmin){
                }else{

                }
            break;
            case 3:
                if(isAdmin){
                }else{

                }
            break;
            case 4:
                user = pengguna();
                cout << "Logout..\n";
            return;
            default:
                cout << "Pemilihan nomor tidak valid\n";
                system("pause");
                break;
        };
    };
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
