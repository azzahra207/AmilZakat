// zakat_wasm.cpp - Versi sederhana untuk WebAssembly
#include <emscripten.h>
#include <string>
#include <cmath>

using namespace std;

extern "C" {
    
    // Fungsi utama yang wajib ada
    EMSCRIPTEN_KEEPALIVE
    int main() {
        return 0;
    }
    
    // Format Rupiah
    EMSCRIPTEN_KEEPALIVE
    const char* format_rupiah(long long nilai) {
        string str = to_string(nilai);
        string result;
        int len = str.length();
        
        for (int i = 0; i < len; i++) {
            result = str[(len - i) - 1] + result;
            if ((i + 1) % 3 == 0 && len - i > 1) {
                result = "." + result;
            }
        }
        
        static char buffer[100];
        snprintf(buffer, sizeof(buffer), "Rp %s", result.c_str());
        return buffer;
    }
    
    // Zakat Penghasilan
    EMSCRIPTEN_KEEPALIVE
    const char* zakat_penghasilan(long long gaji_bulanan, long long kebutuhan) {
        static char result[500];
        long long nisab = 174970000; // 174.97 juta
        long total_setahun = gaji_bulanan * 12;
        long bersih = total_setahun - kebutuhan;
        
        if (bersih >= nisab) {
            long zakat = bersih * 0.025;
            snprintf(result, sizeof(result), 
                "ZAKAT PENGHASILAN\n"
                "=================\n"
                "Penghasilan setahun: %s\n"
                "Harta bersih: %s\n"
                "Nisab: %s\n"
                "Zakat (2.5%%): %s\n"
                "Status: WAJIB ZAKAT",
                format_rupiah(total_setahun),
                format_rupiah(bersih),
                format_rupiah(nisab),
                format_rupiah(zakat)
            );
        } else {
            snprintf(result, sizeof(result),
                "ZAKAT PENGHASILAN\n"
                "=================\n"
                "Penghasilan setahun: %s\n"
                "Harta bersih: %s\n"
                "Nisab: %s\n"
                "Status: BELUM WAJIB ZAKAT",
                format_rupiah(total_setahun),
                format_rupiah(bersih),
                format_rupiah(nisab)
            );
        }
        
        return result;
    }
    
    // Zakat Emas
    EMSCRIPTEN_KEEPALIVE
    const char* zakat_emas(float berat, long harga_gram) {
        static char result[500];
        float nisab = 77.5; // gram
        
        if (berat >= nisab) {
            long zakat = (berat * 0.025) * harga_gram;
            snprintf(result, sizeof(result),
                "ZAKAT EMAS\n"
                "==========\n"
                "Berat emas: %.2f gram\n"
                "Nisab: %.2f gram\n"
                "Harga/gram: %s\n"
                "Zakat (2.5%%): %s\n"
                "Status: WAJIB ZAKAT",
                berat, nisab, format_rupiah(harga_gram), format_rupiah(zakat)
            );
        } else {
            snprintf(result, sizeof(result),
                "ZAKAT EMAS\n"
                "==========\n"
                "Berat emas: %.2f gram\n"
                "Nisab: %.2f gram\n"
                "Status: BELUM WAJIB ZAKAT",
                berat, nisab
            );
        }
        
        return result;
    }
    
    // Login sederhana
    EMSCRIPTEN_KEEPALIVE
    int login_user(const char* username, const char* password) {
        string user = username;
        string pass = password;
        
        if (user == "AmilZakat" && pass == "insyaAllahBarokah_2025") {
            return 1; // Admin
        }
        
        if (user.length() > 0 && pass.length() > 0) {
            return 2; // User biasa
        }
        
        return 0; // Gagal
    }
}
