#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct pengguna{
    int id;
    string username;
    string password;
};
void menu(){
    system("cls");
    cout << "=== BERANDA AMIL ZAKAT ==="<<endl;
    cout << "=== MENU UTAMA ==="<<endl;
    cout <<"1. Dashboard\n";
    cout <<"2. Bayar Zakat\n";
    cout <<"3. Kalkulator zakat\n";
    cout <<"Pilih nomor: ";
}
int main(){
    pengguna pengguna;
    char HaveAccount;
    bool isLogin=false;
    cout << "=== SELAMAT DATANG ===" << endl;
    cout << "=== APLIKASI AMIL ZAKAT ===" << endl;
    system("pause");
    do{
    system("cls");
    cout << "Sudah Punya Akun (Y/T)? " << endl;
    cin >> HaveAccount;
    if(HaveAccount=='Y' || HaveAccount=='y'){
        string user[2];
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
        ifstream bacaUser2;
        pengguna.id=1;
        bacaUser2.open("users.txt");
        while(bacaUser2 >> pengguna.id >> pengguna.username >> pengguna.password){
            pengguna.id++;
        }
        bacaUser2.close();
        ofstream appendUser1;
        appendUser1.open("users.txt", ios::app);
        cout <<"--- Registrasi Akun ---"<< endl;
        cout << "Username: ";
        cin >> pengguna.username;
        cout << "Password: ";
        cin >> pengguna.password;
        appendUser1 << pengguna.id << " " << pengguna.username << " " << pengguna.password << "\n";
        appendUser1.close();
        system("cls");
        cout << pengguna.username<< " Berhasil Register\n";
        isLogin=true;
    }
    system("pause");
}while(!isLogin);
    menu();
}
