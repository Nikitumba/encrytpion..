
#include <iostream>
#include <string>
#include <vector>
#include "fstream"

using namespace std;

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        std::cerr << "Error: Use three parameters\n";
        return 5;
    }
    const string mode(argv[1]); // Режим работы
    const string file_name(argv[2]); // Имя файла
    if (mode == "encryption") {
        string text;
        cout << "enter a text" << endl;
        getline(std::cin, text);
        vector<char> symbols;
        for (size_t i = 0; i < text.size(); i++) {
            symbols.push_back(static_cast<char>(text[i]));
        }
        int key;
        cout << "enter a key(key is integer)" << endl;
        cin >> key;
        srand(key);
        ofstream file;
        file.open(file_name, std::ios::binary);
        for (size_t i = 0; i < symbols.size(); i += 2) {
            int message;
            int XOR = rand();
            if (i + 1 >= symbols.size()) {
                message = (static_cast<int>(symbols[i]) << 8);
            } else {
                message = (static_cast<int>(symbols[i]) << 8) | (static_cast<int>(symbols[i + 1]));
            }
            int message_with_gamma =  message ^ XOR & 0xFFFF;
            int message_encrypted = ((message_with_gamma << 4) & 0xFFFF | (message_with_gamma >> 12) & 0xFFFF);
            char v = message_encrypted >> 8;
            char v1 = message_encrypted;
            file << v << v1;
        }
        file.close();
    } else if (mode == "decryption") {
        int key;
        cout << "enter a key(key is integer)" << endl;
        cin >> key;
        srand(key);
        ifstream file;
        file.open(file_name, std::ios::binary);
        string message;
        getline(file, message);
        vector<char> symbols(message.size());
        for (size_t i = 0; i != message.size(); ++i)
            symbols[i] = message[i];
        for (size_t i = 0; i < symbols.size(); i += 2) {
            int XOR = rand();
            int message_encrypt;
            if (i + 1 < symbols.size())
                message_encrypt = (static_cast<int>(symbols[i]) << 8) | (static_cast<int>(symbols[i + 1]));
            else
                message_encrypt = (static_cast<int>(symbols[i]) << 8);
            int message_with_gamma =
                    ((message_encrypt >> 4) & 0xFFFF) | ((message_encrypt << (16 - 4)) & 0xFFFF);
            int message_decrypt = message_with_gamma ^ XOR;
            char v = message_decrypt >> 8;
            char v1 = message_decrypt;
            cout << v << v1;
        }
        file.close();
    }
    return 0;
}