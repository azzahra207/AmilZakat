// WebAssembly Module
let cppModule = null;
let currentUser = null;
let wasmLoaded = false;

// DOM Elements
const loginModal = document.getElementById('loginModal');
const wasmStatus = document.getElementById('wasmStatus');
const resultContent = document.getElementById('resultContent');
const loading = document.getElementById('loading');

// Inisialisasi
window.addEventListener('DOMContentLoaded', () => {
    loadCppProgram();
    updateLoginButton();
    
    // Set default zakat type
    selectZakatType('penghasilan');
});

// Load WebAssembly Program
async function loadCppProgram() {
    try {
        updateWasmStatus('loading', 'Memuat engine C++...');
        loading.style.display = 'block';
        resultContent.innerHTML = '';
        
        // Load WASM file
        const response = await fetch('wasm/program.wasm');
        if (!response.ok) {
            throw new Error(`Gagal memuat file WASM: ${response.status}`);
        }
        
        const bytes = await response.arrayBuffer();
        
        // Setup imports untuk WebAssembly
        const imports = {
            env: {
                // Fungsi untuk output dari C++
                printToConsole: (ptr) => {
                    if (cppModule && cppModule.memory) {
                        const memory = new Uint8Array(cppModule.memory.buffer);
                        let str = '';
                        let i = ptr;
                        while (memory[i] !== 0) {
                            str += String.fromCharCode(memory[i]);
                            i++;
                        }
                        console.log("C++:", str);
                        addToConsole(str);
                    }
                },
                
                // Fungsi untuk alert dari C++
                alertMessage: (ptr) => {
                    if (cppModule && cppModule.memory) {
                        const memory = new Uint8Array(cppModule.memory.buffer);
                        let str = '';
                        let i = ptr;
                        while (memory[i] !== 0) {
                            str += String.fromCharCode(memory[i]);
                            i++;
                        }
                        alert(str);
                    }
                },
                
                // Memory management
                memory: new WebAssembly.Memory({ initial: 256 }),
                abort: (msg, file, line, column) => {
                    console.error(`C++ Error: ${msg} at ${file}:${line}:${column}`);
                }
            }
        };
        
        // Instantiate WebAssembly
        const { instance } = await WebAssembly.instantiate(bytes, imports);
        cppModule = instance.exports;
        
        // Inisialisasi program C++
        if (cppModule._main) {
            cppModule._main();
        }
        
        wasmLoaded = true;
        updateWasmStatus('online', 'Engine C++ siap digunakan!');
        loading.style.display = 'none';
        
        // Tampilkan pesan selamat datang
        showResult({
            title: '✅ Engine C++ Dimuat',
            message: 'Program C++ Amil Zakat berhasil dimuat di browser Anda menggunakan WebAssembly.',
            amount: 'Sistem siap menghitung zakat',
            type: 'success'
        });
        
        console.log('✅ WebAssembly loaded successfully!');
        
    } catch (error) {
        console.error('❌ Error loading WebAssembly:', error);
        updateWasmStatus('offline', `Gagal memuat: ${error.message}`);
        loading.style.display = 'none';
        
        showResult({
            title: '❌ Engine C++ Gagal Dimuat',
            message: 'Coba reload halaman atau gunakan browser yang mendukung WebAssembly.',
            type: 'error'
        });
    }
}

// Update WebAssembly Status
function updateWasmStatus(status, message) {
    const statusElement = wasmStatus;
    statusElement.className = `status ${status}`;
    statusElement.innerHTML = `<i class="fas fa-circle"></i> ${message}`;
}

// Add message to console
function addToConsole(message) {
    const consoleDiv = document.getElementById('console');
    if (consoleDiv) {
        const p = document.createElement('p');
        p.textContent = `C++: ${message}`;
        p.style.color = '#4CAF50';
        p.style.fontFamily = 'monospace';
        p.style.margin = '5px 0';
        consoleDiv.appendChild(p);
    }
}

// Tampilkan Hasil Perhitungan
function showResult(data) {
    resultContent.innerHTML = '';
    loading.style.display = 'none';
    
    const resultDiv = document.createElement('div');
    resultDiv.className = `result-item ${data.type || 'info'}`;
    
    let html = `
        <div class="result-header">
            <h4>${data.title}</h4>
            ${data.amount ? `<div class="result-amount">${data.amount}</div>` : ''}
        </div>
        <div class="result-details">
            <p>${data.message}</p>
    `;
    
    if (data.details) {
        html += `<ul style="margin-top: 10px;">`;
        data.details.forEach(detail => {
            html += `<li>${detail}</li>`;
        });
        html += `</ul>`;
    }
    
    html += `</div>`;
    resultDiv.innerHTML = html;
    resultContent.appendChild(resultDiv);
}

// Fungsi Login/Register
function toggleLogin() {
    loginModal.style.display = 'flex';
}

function closeModal() {
    loginModal.style.display = 'none';
}

function openTab(tabName) {
    // Hide all tab contents
    document.querySelectorAll('.tab-content').forEach(tab => {
        tab.classList.remove('active');
    });
    
    // Remove active class from all tab buttons
    document.querySelectorAll('.tab-btn').forEach(btn => {
        btn.classList.remove('active');
    });
    
    // Show selected tab
    document.getElementById(tabName).classList.add('active');
    
    // Activate corresponding button
    event.target.classList.add('active');
}

async function login() {
    const username = document.getElementById('loginUsername').value;
    const password = document.getElementById('loginPassword').value;
    
    if (!username || !password) {
        alert('Username dan password harus diisi!');
        return;
    }
    
    try {
        // Simulasi login dengan WebAssembly
        if (cppModule && cppModule.loginUser) {
            const result = cppModule.loginUser(username, password);
            if (result) {
                currentUser = {
                    username: username,
                    isAdmin: username === 'AmilZakat'
                };
                
                updateLoginButton();
                closeModal();
                
                showResult({
                    title: '✅ Login Berhasil',
                    message: `Selamat datang ${username}!`,
                    type: 'success'
                });
                
                if (currentUser.isAdmin) {
                    setTimeout(() => {
                        alert('Anda login sebagai Admin Amil Zakat');
                    }, 500);
                }
            } else {
                alert('Login gagal! Username atau password salah.');
            }
        } else {
            // Fallback jika WebAssembly belum siap
            if (username === 'AmilZakat' && password === 'insyaAllahBarokah_2025') {
                currentUser = {
                    username: username,
                    isAdmin: true
                };
                updateLoginButton();
                closeModal();
                alert('Login admin berhasil!');
            } else {
                currentUser = {
                    username: username,
                    isAdmin: false
                };
                updateLoginButton();
                closeModal();
                alert(`Login berhasil sebagai ${username}!`);
            }
        }
    } catch (error) {
        console.error('Login error:', error);
        alert('Terjadi kesalahan saat login.');
    }
}

function register() {
    const username = document.getElementById('regUsername').value;
    const password = document.getElementById('regPassword').value;
    const confirmPassword = document.getElementById('regConfirmPassword').value;
    
    if (!username || !password) {
        alert('Semua field harus diisi!');
        return;
    }
    
    if (password !== confirmPassword) {
        alert('Password dan konfirmasi password tidak cocok!');
        return;
    }
    
    // Simulasi registrasi
    currentUser = {
        username: username,
        isAdmin: false
    };
    
    updateLoginButton();
    closeModal();
    
    showResult({
        title: '✅ Registrasi Berhasil',
        message: `Akun ${username} berhasil dibuat!`,
        type: 'success'
    });
}

function updateLoginButton() {
    const authBtn = document.querySelector('.auth-btn');
    if (currentUser) {
        authBtn.innerHTML = `<i class="fas fa-user-check"></i> ${currentUser.username}`;
        if (currentUser.isAdmin) {
            authBtn.style.background = '#d32f2f';
        }
    } else {
        authBtn.innerHTML = `<i class="fas fa-user"></i> Masuk`;
        authBtn.style.background = '';
    }
}

// Fungsi Kalkulator Zakat
function selectZakatType(type) {
    // Hide all forms
    document.querySelectorAll('.zakat-form').forEach(form => {
        form.classList.remove('active');
    });
    
    // Show selected form
    document.getElementById(`form-${type}`).classList.add('active');
    
    // Update active card
    document.querySelectorAll('.zakat-card').forEach(card => {
        card.style.transform = '';
        card.style.boxShadow = '';
    });
    
    event.currentTarget.style.transform = 'translateY(-5px)';
    event.currentTarget.style.boxShadow = '0 10px 25px rgba(0, 0, 0, 0.15)';
}

function calculateZakatPenghasilan() {
    if (!wasmLoaded) {
        alert('Engine C++ belum dimuat. Tunggu sebentar...');
        return;
    }
    
    const gaji = parseInt(document.getElementById('gajiBulanan').value) || 0;
    const kebutuhan = parseInt(document.getElementById('kebutuhanTahunan').value) || 0;
    const utang = parseInt(document.getElementById('utangPenghasilan').value) || 0;
    const piutang = parseInt(document.getElementById('piutangPenghasilan').value) || 0;
    
    if (gaji <= 0) {
        alert('Masukkan gaji bulanan yang valid!');
        return;
    }
    
    loading.style.display = 'block';
    resultContent.innerHTML = '';
    
    // Simulasi perhitungan dengan C++
    setTimeout(() => {
        // Ini adalah contoh perhitungan sederhana
        // Di implementasi real, ini akan memanggil fungsi C++
        const nisab = 174970 * 1000; // 174.970 juta
        const penghasilanSetahun = gaji * 12;
        const netto = penghasilanSetahun + piutang - (kebutuhan + utang);
        
        let zakat = 0;
        let isWajib = false;
        
        if (netto >= nisab) {
            zakat = netto * 0.025; // 2.5%
            isWajib = true;
        }
        
        showResult({
            title: isWajib ? '✅ WAJIB ZAKAT' : 'ℹ️ Belum Wajib Zakat',
            message: isWajib 
                ? `Anda wajib membayar zakat penghasilan karena harta bersih melebihi nisab.`
                : `Harta bersih Anda belum mencapai nisab (Rp ${formatRupiah(nisab)}).`,
            amount: isWajib ? formatRupiah(Math.round(zakat)) : '-',
            type: isWajib ? 'success' : 'info',
            details: [
                `Penghasilan setahun: Rp ${formatNumber(penghasilanSetahun)}`,
                `Harta bersih: Rp ${formatNumber(netto)}`,
                `Nisab: Rp ${formatNumber(nisab)}`,
                `Persentase zakat: 2.5%`
            ]
        });
        
        loading.style.display = 'none';
    }, 1500);
}

function calculateZakatEmas() {
    if (!wasmLoaded) {
        alert('Engine C++ belum dimuat. Tunggu sebentar...');
        return;
    }
    
    const jenis = document.getElementById('jenisLogam').value;
    const berat = parseFloat(document.getElementById('beratLogam').value) || 0;
    const harga = parseInt(document.getElementById('hargaPerGram').value) || 0;
    
    if (berat <= 0 || harga <= 0) {
        alert('Masukkan data yang valid!');
        return;
    }
    
    loading.style.display = 'block';
    
    setTimeout(() => {
        const nisab = jenis === 'emas' ? 77.5 : 543.35; // gram
        const isWajib = berat >= nisab;
        const zakat = isWajib ? (berat * 0.025) * harga : 0;
        
        showResult({
            title: isWajib ? '✅ WAJIB ZAKAT' : 'ℹ️ Belum Wajib Zakat',
            message: isWajib 
                ? `Anda wajib membayar zakat ${jenis} karena memiliki ${berat} gram (nisab: ${nisab} gram).`
                : `Berat ${jenis} Anda belum mencapai nisab (${nisab} gram).`,
            amount: isWajib ? formatRupiah(Math.round(zakat)) : '-',
            type: isWajib ? 'success' : 'info',
            details: [
                `Jenis: ${jenis === 'emas' ? 'Emas' : 'Perak'}`,
                `Berat: ${berat} gram`,
                `Nisab: ${nisab} gram`,
                `Harga per gram: Rp ${formatNumber(harga)}`,
                `Persentase zakat: 2.5%`
            ]
        });
        
        loading.style.display = 'none';
    }, 1500);
}

function calculateZakatTernak() {
    if (!wasmLoaded) {
        alert('Engine C++ belum dimuat. Tunggu sebentar...');
        return;
    }
    
    const jenis = document.getElementById('jenisTernak').value;
    const jumlah = parseInt(document.getElementById('jumlahTernak').value) || 0;
    
    if (jumlah <= 0) {
        alert('Masukkan jumlah ternak yang valid!');
        return;
    }
    
    loading.style.display = 'block';
    
    setTimeout(() => {
        let nisab = 0;
        let keterangan = '';
        let isWajib = false;
        
        switch (jenis) {
            case 'sapi':
                nisab = 30;
                isWajib = jumlah >= nisab;
                if (isWajib) {
                    if (jumlah >= 60) {
                        keterangan = '1 ekor sapi musinnah (usia 2 tahun)';
                    } else if (jumlah >= 40) {
                        keterangan = '1 ekor sapi tabi\' (usia 1 tahun)';
                    } else {
                        keterangan = '1 ekor sapi musinnah (usia 2 tahun)';
                    }
                }
                break;
                
            case 'kambing':
                nisab = 40;
                isWajib = jumlah >= nisab;
                if (isWajib) {
                    if (jumlah >= 500) {
                        keterangan = `${Math.floor(jumlah/100)} ekor kambing`;
                    } else if (jumlah >= 400) {
                        keterangan = '4 ekor kambing';
                    } else if (jumlah >= 200) {
                        keterangan = '3 ekor kambing';
                    } else if (jumlah >= 120) {
                        keterangan = '2 ekor kambing';
                    } else {
                        keterangan = '1 ekor kambing';
                    }
                }
                break;
                
            case 'unta':
                nisab = 5;
                isWajib = jumlah >= nisab;
                if (isWajib) {
                    keterangan = 'Sesuai ketentuan unta';
                }
                break;
        }
        
        showResult({
            title: isWajib ? '✅ WAJIB ZAKAT' : 'ℹ️ Belum Wajib Zakat',
            message: isWajib 
                ? `Anda wajib membayar zakat ternak ${jenis} karena memiliki ${jumlah} ekor (nisab: ${nisab} ekor).`
                : `Jumlah ternak ${jenis} Anda belum mencapai nisab (${nisab} ekor).`,
            amount: isWajib ? keterangan : '-',
            type: isWajib ? 'success' : 'info',
            details: [
                `Jenis ternak: ${jenis}`,
                `Jumlah: ${jumlah} ekor`,
                `Nisab: ${nisab} ekor`
            ]
        });
        
        loading.style.display = 'none';
    }, 1500);
}

function calculateZakatPertanian() {
    if (!wasmLoaded) {
        alert('Engine C++ belum dimuat. Tunggu sebentar...');
        return;
    }
    
    const jenis = document.getElementById('jenisPanen').value;
    const berat = parseInt(document.getElementById('beratPanen').value) || 0;
    const irigasi = document.getElementById('irigasiBayar').value === 'true';
    
    if (berat <= 0) {
        alert('Masukkan berat hasil panen yang valid!');
        return;
    }
    
    loading.style.display = 'block';
    
    setTimeout(() => {
        let nisab = 0;
        let namaPanen = '';
        
        switch (jenis) {
            case 'beras_putih': nisab = 815.758; namaPanen = 'Beras Putih'; break;
            case 'padi_gagang': nisab = 1631.516; namaPanen = 'Padi Gagang'; break;
            case 'padi_kretek': nisab = 1323.132; namaPanen = 'Padi Kretek'; break;
            case 'kacang_hijau': nisab = 780.036; namaPanen = 'Kacang Hijau'; break;
        }
        
        const isWajib = berat >= nisab;
        const persentase = irigasi ? 5 : 10;
        const zakat = isWajib ? (berat * persentase / 100) : 0;
        
        showResult({
            title: isWajib ? '✅ WAJIB ZAKAT' : 'ℹ️ Belum Wajib Zakat',
            message: isWajib 
                ? `Anda wajib membayar zakat pertanian karena hasil panen ${berat} kg melebihi nisab (${nisab} kg).`
                : `Hasil panen Anda belum mencapai nisab (${nisab} kg).`,
            amount: isWajib ? `${zakat.toFixed(2)} kg` : '-',
            type: isWajib ? 'success' : 'info',
            details: [
                `Jenis: ${namaPanen}`,
                `Berat panen: ${berat} kg`,
                `Nisab: ${nisab} kg`,
                `Irigasi berbayar: ${irigasi ? 'Ya (5%)' : 'Tidak (10%)'}`
            ]
        });
        
        loading.style.display = 'none';
    }, 1500);
}

// Helper Functions
function formatNumber(num) {
    return num.toString().replace(/\B(?=(\d{3})+(?!\d))/g, ".");
}

function formatRupiah(num) {
    return `Rp ${formatNumber(num)}`;
}

function scrollToCalculator() {
    document.getElementById('calculator').scrollIntoView({ 
        behavior: 'smooth' 
    });
}

// Close modal jika klik di luar
window.onclick = function(event) {
    if (event.target == loginModal) {
        closeModal();
    }
}
