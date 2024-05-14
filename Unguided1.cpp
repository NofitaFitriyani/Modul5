#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Class Mahasiswa untuk merepresentasikan entitas mahasiswa
class Mahasiswa {
public:
    string nim;
    int nilai;

    Mahasiswa(string nim, int nilai) {
        this->nim = nim;
        this->nilai = nilai;
    }
};

// Class HashTable untuk implementasi hash table
class HashTable {
private:
    static const int table_size = 10; // Ukuran tabel hash
    vector<Mahasiswa *> table[table_size];

public:
    // Fungsi hash
    int hash_function(string nim) {
        int sum = 0;
        for (char c : nim) {
            sum += c;
        }
        return sum % table_size;
    }

    // Menambah data mahasiswa
    void addData2311102001(Mahasiswa *mahasiswa) {
        int index = hash_function(mahasiswa->nim);
        table[index].push_back(mahasiswa);
    }

    // Menghapus data mahasiswa berdasarkan NIM
    void delData(string nim) {
        int index = hash_function(nim);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if ((*it)->nim == nim) {
                delete *it;
                table[index].erase(it);
                break;
            }
        }
    }

    // Mencari data mahasiswa berdasarkan NIM
    Mahasiswa *searchDataByNIM(string nim) {
        int index = hash_function(nim);
        for (Mahasiswa *mahasiswa : table[index]) {
            if (mahasiswa->nim == nim) {
                return mahasiswa;
            }
        }
        return nullptr;
    }

    // Mencari data mahasiswa berdasarkan rentang nilai (80 - 90)
    vector<Mahasiswa *> searchDataByRange(int nilai_min, int nilai_max) {
        vector<Mahasiswa *> hasil_pencarian;
        for (int i = 0; i < table_size; i++) {
            for (Mahasiswa *mahasiswa : table[i]) {
                if (mahasiswa->nilai >= nilai_min && mahasiswa->nilai <= nilai_max) {
                    hasil_pencarian.push_back(mahasiswa);
                }
            }
        }
        return hasil_pencarian;
    }
};

// Fungsi main
int main() {
    HashTable hash_table;
    while (true) {
        cout << "\nPilihan Menu:" << endl;
        cout << "1. Tambah Data Mahasiswa" << endl;
        cout << "2. Hapus Data Mahasiswa" << endl;
        cout << "3. Cari Mahasiswa Berdasarkan NIM" << endl;
        cout << "4. Cari Mahasiswa Berdasarkan Rentang Nilai (80-90)" << endl;
        cout << "5. Keluar" << endl;
        int pilihan;
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;

        if (pilihan == 1) {
            string nim;
            int nilai;
            cout << "Masukkan NIM: ";
            cin >> nim;
            cout << "Masukkan nilai: ";
            cin >> nilai;
            Mahasiswa *mahasiswa_baru = new Mahasiswa(nim, nilai);
            hash_table.addData2311102001(mahasiswa_baru);
            cout << "Data mahasiswa berhasil ditambahkan." << endl;
        } 
        else if (pilihan == 2) {
            string nim;
            cout << "Masukkan NIM : ";
            cin >> nim;
            hash_table.delData(nim);
            cout << "Data mahasiswa dengan NIM " << nim << " telah dihapus." << endl;
        } 
        else if (pilihan == 3) {
            string nim;
            cout << "Masukkan NIM : ";
            cin >> nim;
            Mahasiswa *mahasiswa = hash_table.searchDataByNIM(nim);
            if (mahasiswa != nullptr) {
                cout << "Mahasiswa dengan NIM " << nim << " ditemukan. Nilai: " << mahasiswa->nilai << endl;
            } else {
                cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan." << endl;
            }
        } 
        else if (pilihan == 4) {
            vector<Mahasiswa *> mahasiswa_ditemukan = hash_table.searchDataByRange(80, 90);
            if (!mahasiswa_ditemukan.empty()) {
                cout << "Mahasiswa dengan nilai antara 80 dan 90:" << endl;
                for (Mahasiswa *mahasiswa : mahasiswa_ditemukan) {
                    cout << "NIM: " << mahasiswa->nim << " Nilai: " << mahasiswa->nilai << endl;
                }
            } else {
                cout << "Tidak ada mahasiswa dengan nilai antara 80 dan 90." << endl;
            }
        } 
        else if (pilihan == 5) {
            cout << "Program selesai." << endl;
            break;
        } 
        else {
            cout << "Pilihan tidak valid. Silakan masukkan pilihan yang benar." << endl;
        }
    }
    return 0;
}
