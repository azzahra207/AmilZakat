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
    bool HaveAccount;
    cout << "=== SELAMAT DATANG ===" << endl;
    cout << "=== APLIKASI AMIL ZAKAT ===" << endl;
    cout << "Sudah Punya Akun (true/false)? " << endl;
    cin >> boolalpha >> HaveAccount;
    if(HaveAccount){
        string username;
        string password;
        cout <<"--- Login Akun ---"<< endl;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;
        ifstream bacaUser1;
        bool isLogin=false;
        bacaUser1.open("users.txt");
        while(bacaUser1 >> pengguna.id >> pengguna.username >> pengguna.password){
            if(pengguna.username==username && password == pengguna.password){
                isLogin=true;
                cout << "Berhasil Login";
                break;
            }
        }
        bacaUser1.close();
    } else{
        ifstream bacaUser2;
        int lastId=0;
        bacaUser2.open("users.txt");
        while(bacaUser2 >> lastId >> pengguna.username >> pengguna.password){
            pengguna.id=lastId;
        }
        pengguna.id++;
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
    }

}