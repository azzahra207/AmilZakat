#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct pengguna{
    int id;
    string username;
    string password;
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
void handleMenu(pengguna &user){
    bool isAdmin=user.username=="AmilZakat";
    int pilihanMenu;
    while(true){
        pilihanMenu=menu(user);
        switch(pilihanMenu){
            case 1:
                if(isAdmin){
                }else{

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

int main(){
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
            ifstream bacaUser2;
            pengguna.id=1;
            bacaUser2.open("users.txt");
            while(bacaUser2 >> pengguna.id >> user[0] >> user[1]){
                pengguna.id++;
            }
            bacaUser2.close();
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
