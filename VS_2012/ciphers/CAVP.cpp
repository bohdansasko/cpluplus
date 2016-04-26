#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <conio.h>
#include <Windows.h>

using std::cout;
using std::endl;

using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::abs;

bool readFromFile(const string fileName, string &s);									
bool saveToFile  (const string fileName, const string &s);

void exEvklid(int a, int b, int &x, int &y);											// Розширений алгоритм Евкліда

string squarePolibiya (const string &s, const bool encOrDec = true);					// Квадрат Полібія
string cipherOfCaesar (const string &s, int key, const bool encOrDec = true);			// Шифр Цезаря
string cipherOfAphina (const string &s, int a, int b, const bool encOrDec = true);		// Афінний шифр
string cipherOfVigener(const string &s, string keyword, const bool encOrDec = true);	// Шифр Віженера

int main(int argc, char *argv[]) {
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
	string contentOfFile = "";
	if (!readFromFile("message.txt", contentOfFile)) {		// Читання текстового файлу message.txt у змінну contentOfFile
		return 0;
	}

	// Квадрат Полібія
	const string FILENAME_POLIBIY = "polibiy.txt";
	string strEncPolibiy = squarePolibiya(contentOfFile);
	if (!saveToFile("enc_" + FILENAME_POLIBIY, strEncPolibiy)) {
		cout << "Error of saving to file!\n";
	}

	string strDecPolibiy = squarePolibiya(strEncPolibiy, false);
	if (!saveToFile("dec_" + FILENAME_POLIBIY, strDecPolibiy)) {
		cout << "Error of saving to file!\n";
	}

	// Шифр Цезаря
	const string FILENAME_CAESAR = "caesar.txt";
	string caesar = cipherOfCaesar(contentOfFile, 3);
	if ( !saveToFile( "enc_" + FILENAME_CAESAR,  caesar) ) {
		cout << "Error of saving to file!\n";
	}
	
	if ( !saveToFile( "dec_" + FILENAME_CAESAR, cipherOfCaesar(caesar, 3, false) ) ) {
		cout << "Error of saving to file!\n";
	}
	
	// Афінний шифр
	const string FILENAME_APHINA = "afina.txt";
	//contentOfFile = "ДО НАШОГО ";
	string aphine = cipherOfAphina(contentOfFile, 3, 5);
	//cout << aphine << endl;
	if ( !saveToFile( "enc_" + FILENAME_APHINA,  aphine) ) {
		cout << "Error of saving to file!\n";
	}
	aphine = cipherOfAphina(aphine, 3, 5, false);
	/*cout << aphine << endl;*/
	if ( !saveToFile( "dec_" + FILENAME_APHINA, aphine ) ) {
		cout << "Error of saving to file!\n";
	}

	// Шифр Віженера
	const string KW = "СТРАУСТРУП";
	const string FILENAME_VIZHENER = "vizhener.txt";

	string vizhener = cipherOfVigener(contentOfFile, KW);
	
	//cout << vizhener << endl;
	if ( !saveToFile( "enc_" + FILENAME_VIZHENER,  vizhener) ) {
		cout << "Error of saving to file!\n";
	}
	vizhener = cipherOfVigener(vizhener, KW, false);
	//cout << vizhener << endl;
	if ( !saveToFile( "dec_" + FILENAME_VIZHENER, vizhener ) ) {
		cout << "Error of saving to file!\n";
	}

	
	_getch();
    return 0;
}

bool readFromFile(const string fileName, string &s) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error opening file: " << fileName << "\n";
        return false;
    }

    string line = "";
    while(getline(file, line)) {
        s += line;
    }
    file.close();
	cout << "Read from file" << fileName << "...\n";
	
	return true;
}

bool saveToFile(const string fileName, const string &s) {
	ofstream file(fileName, ios::out);
    if (!file.is_open()) {
        cout << "Error opening file: " << fileName << "\n";
        return false;
    }
	file << s;
    file.close();

	cout << "Save to file " << fileName << "...\n";
	
	return true;
}

void exEvklid(int a, int b, int &x, int &y) {
    struct ab {
		int a;
		int b;
		ab(const int a, const int b) {
			this->a = a;
			this->b = b;
		}
	};

	std::vector<ab> v;
    while(true) {
        int a1 = a;
        if (a == 0) {
            x = 0; 
            y = 1;
            break;
        }
        v.push_back(ab(a, b));
        a = b % a;
        b = a1;
    }
    for (int i = v.size()-1; i >= 0; --i) {
        int x1 = x;
        x = y - (v[i].b / v[i].a) * x1;
        y = x1;
    }
}

string squarePolibiya(const string &s, const bool encOrDec) {
	if (s.empty()) 
		return "";

	const short MAX = 6;
	string cryptString = "";
	string square[MAX] = {"АБВГҐД",
                         "ЕЄЖЗИІ",
                         "ЇЙКЛМН",
                         "ОПРСТУ",
                         "ФХЦЧШЩ",
                         "ЬЮЯ., "};

	const unsigned int INPUT_STRING_LENGTH = s.length();

	for (unsigned int i = 0; i < INPUT_STRING_LENGTH; ++i) {
		for (unsigned int j = 0; j < MAX; ++j) {
			for (unsigned int k = 0; k < MAX; ++k) { 
				if (s[i] == square[j][k]) {
					if (encOrDec) {
						if ( (j+1) == MAX )
							cryptString += square[0][k];
						else 
							cryptString += square[j+1][k];
					} else {
						if ( j == 0 ) 
							cryptString += square[MAX-1][k];
						else 
							cryptString += square[j-1][k];
					}
				}
			}
		}
	}

	if (encOrDec) 
		cout << "Call squarePolibiya: ENCRYPTION\n";
	else
		cout << "Call squarePolibiya: DECRYPTION\n";

	return cryptString;
}

string cipherOfCaesar(const string &s, int k, const bool encOrDec) {
	if ( s.empty() || k < 1 ) 
		return "";

	if (!encOrDec)
		k *= -1;

	const unsigned short n = 36;							// Power of alphabet
	string cryptString = "";								// 
	const unsigned int INPUT_STRING_LENGTH = s.length();	// Count chars in string s
	
	for (unsigned int i = 0; i < INPUT_STRING_LENGTH; ++i) {
		cryptString += s[i] + k % n;
	}

	if (encOrDec) 
		cout << "Call cipherOfCaesar: ENCRYPTION\n";
	else
		cout << "Call cipherOfCaesar: DECRYPTION\n";

	return cryptString;
}

string cipherOfAphina(const string &s, int a, int b, const bool encOrDec) {
	if (s.empty()) 
		return "";

	string alphabet = "АБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЬЮЯ. ";
	const int COUNT_CHARS = alphabet.length();

 	int x = 0,	// a in minus one 
		y = 0;	
	int r = 0;

	exEvklid(a, COUNT_CHARS, x, y);
	
	r = a * x + COUNT_CHARS * y;
	if (r != 1) {
		cout << "NSD(a,b) != 1;\n";
		return "";
	}
	
	string cryptString = "";
	const unsigned int length = s.length();
	if (encOrDec) {		// Шифрування
		for (unsigned int i = 0; i < length; ++i) 
			for (unsigned int j = 0; j < COUNT_CHARS; ++j) 
				if (s[i] == alphabet[j]) {
					const int pos = (a * j + b) % COUNT_CHARS; 
					cryptString += alphabet[pos];
					break;
				}
	} else {			// Дешифрування
		cout << endl << endl; 
		for (unsigned int i = 0; i < length; ++i) 
			for (int j = 0; j < COUNT_CHARS; ++j)
				if (s[i] == alphabet[j]) {
					int pos = (j - b) * x % COUNT_CHARS; 
					if (pos < 0) 
						pos += COUNT_CHARS;
					
					cryptString += alphabet[pos];
					break;
				}
	}

	cout << "Call cipherOfAphina;\n\n\n";

	return cryptString;
}

string cipherOfVigener(const string &s, string keyword, const bool encOrDec) {
	if ( s.empty() || keyword.empty() ) {
		return "";
	}

	string alphabet		= "АБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЬЮЯ. ";
	string cryptString  = "";										// Містить зашифрований або розшифрований текст
	
	const unsigned int COUNT_CHARS_IN_ALP	= alphabet.length();
	const unsigned int INPUT_STRING_LENGTH	= s.length();
	const unsigned int NEW_LENGTH_KW = INPUT_STRING_LENGTH - keyword.length();

	for (unsigned int i = 0; i < NEW_LENGTH_KW; ++i)				// Розтягування ключого слова  на
		keyword += keyword[i];										// довжину ШТ((за)шифрований текст)
	
	for (unsigned int i = 0; i < INPUT_STRING_LENGTH; ++i) {		// Перебір всіх символів ШТ
		unsigned int j = 0;											
		for (; j < COUNT_CHARS_IN_ALP; ++j) {						// Пошук позиції символа ШТ
			if (s[i] == alphabet[j]) {								// у алфівіті
				break;
			}
		}

		unsigned int k = 0;
		for (k; j < COUNT_CHARS_IN_ALP; ++k) {						// Пошук позиції символа КС(ключогового слова)
			if (keyword[i] == alphabet[k]) {						// у алфівіті
				break;											
			}
		}

		int posChInAlp = 0;											// Позиція нового символу в алфавіті
		if (encOrDec) {												// Шифрування
			posChInAlp = (j + k) % COUNT_CHARS_IN_ALP; 
		} else {													// Дешифрування		
			posChInAlp = (j - k + COUNT_CHARS_IN_ALP) % COUNT_CHARS_IN_ALP; 
		}

		cryptString += alphabet[posChInAlp];			
	}

	if (encOrDec)
		cout << "Call cipherOfVigener: ENCRYPTION\n"; 
	else
		cout << "Call cipherOfVigener: DECRYPTION\n";
		
	return cryptString;
}