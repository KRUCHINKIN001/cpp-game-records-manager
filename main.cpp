#include <iostream>
#include <fstream>
#include <cstring>
#include <clocale>
#include <limits>

using namespace std;

const char* FILENAME = "records.dat";

// Структура, которая будет записываться в бинарный файл
struct Record {
    char name[20];
    int score;
    int level;
};

// Docstring: Добавляет новую запись в конец бинарного файла.
void addRecord() {
    Record rec;
    string tempName;

    cout << "Введите имя игрока (до 19 символов): ";
    cin >> tempName;

    // Безопасное копирование строки в массив char
    strncpy(rec.name, tempName.c_str(), 19);
    rec.name[19] = '\0'; // Гарантируем нуль-терминатор

    cout << "Введите количество очков: ";
    cin >> rec.score;

    cout << "Введите уровень: ";
    cin >> rec.level;

    // Открываем файл в бинарном режиме для добавления в конец
    ofstream file(FILENAME, ios::binary | ios::app);

    if (!file) {
        cout << "Ошибка: не удалось открыть файл для записи!" << endl;
        return;
    }

    // Записываем структуру в файл
    file.write(reinterpret_cast<const char*>(&rec), sizeof(Record));
    file.close();

    cout << "Рекорд успешно добавлен!" << endl;
}

// Docstring: Читает и выводит все записи из бинарного файла.
void showAllRecords() {
    ifstream file(FILENAME, ios::binary);

    if (!file) {
        cout << "Файл с рекордами пуст или не существует." << endl;
        return;
    }

    Record rec;
    bool hasRecords = false;

    cout << "\n--- ВСЕ РЕКОРДЫ ---" << endl;

    // Читаем файл по одной структуре, пока не дойдем до конца
    while (file.read(reinterpret_cast<char*>(&rec), sizeof(Record))) {
        cout << "Имя: " << rec.name
             << " | Очки: " << rec.score
             << " | Уровень: " << rec.level << endl;
        hasRecords = true;
    }

    if (!hasRecords) {
        cout << "Записей не найдено." << endl;
    }

    file.close();
}

// Docstring: Ищет записи по имени игрока в бинарном файле.
void findRecordByName() {
    ifstream file(FILENAME, ios::binary);

    if (!file) {
        cout << "Файл с рекордами пуст или не существует." << endl;
        return;
    }

    string searchName;
    cout << "Введите имя для поиска: ";
    cin >> searchName;

    Record rec;
    bool found = false;

    cout << "\n--- РЕЗУЛЬТАТЫ ПОИСКА ---" << endl;

    while (file.read(reinterpret_cast<char*>(&rec), sizeof(Record))) {
        if (searchName == rec.name) {
            cout << "Имя: " << rec.name
                 << " | Очки: " << rec.score
                 << " | Уровень: " << rec.level << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Игрок с именем '" << searchName << "' не найден." << endl;
    }

    file.close();
}

// Docstring: Очищает бинарный файл (удаляет все записи).
void clearAllRecords() {
    // Открываем в режиме trunc (обрезает файл до нуля байт)
    ofstream file(FILENAME, ios::binary | ios::trunc);

    if (!file) {
        cout << "Ошибка при очистке файла!" << endl;
        return;
    }

    file.close();
    cout << "Все рекорды успешно удалены!" << endl;
}

int main() {
    // Установка русской кодировки
    setlocale(LC_ALL, "Russian");

    int choice;

    do {
        cout << "\n=== МЕНЕДЖЕР РЕКОРДОВ ===" << endl;
        cout << "1. Добавить новый рекорд" << endl;
        cout << "2. Показать все рекорды" << endl;
        cout << "3. Найти рекорд по имени" << endl;
        cout << "4. Удалить все рекорды" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";

        cin >> choice;

        // Очистка потока ввода на случай ввода букв вместо цифр
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка: введите число!" << endl;
            continue;
        }

        switch (choice) {
            case 1: addRecord(); break;
            case 2: showAllRecords(); break;
            case 3: findRecordByName(); break;
            case 4: clearAllRecords(); break;
            case 0:


cout << "Выход из программы." << endl; break;
            default: cout << "Ошибка: неверный пункт меню!" << endl;
        }
    } while (choice != 0);

    return 0;
}
