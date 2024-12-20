#include <iostream>
#include <windows.h>
#include <random>

using namespace std;

void setUtf8Encoding()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

///Задача 1.

// Функція Евкліда для знаходження НСД
int gcd(int a, int b)
{
    while (b != 0)
    {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

// Функція для розкладання числа на прості множники
vector<int> primeFactors(int n)
{
    vector<int> factors;
    for (int i = 2; i * i <= n; ++i)
    {
        if (n % i == 0)
        {
            factors.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) factors.push_back(n);
    return factors;
}

// Функція Ейлера
int phi(int n)
{
    vector<int> primes = primeFactors(n);
    double result = n;
    for (int p : primes)
    {
        result *= (1.0 - 1.0 / p);
    }
    return static_cast<int>(result);
}

// Функція для пошуку чисел, які задовольняють умову
vector<int> findNumbers(int n, int d)
{
    vector<int> numbers;
    int n_prime = n / d; // Скорочуємо масштаб задачі
    for (int k = 1; k <= n_prime; ++k)
    {
        // Перебираємо тільки кратні d
        if (gcd(k, n_prime) == 1)
        {
            // Перевіряємо НСД з n_prime
            numbers.push_back(k * d); // Відновлюємо x = k * d
        }
    }
    return numbers;
}

// Функція для розв'язання задачі
void solveTask()
{
    int n = 1176, d = 42;

    // Обчислюємо n'
    int n_prime = n / d;

    // Обчислюємо функцію Ейлера
    int result = phi(n_prime);

    // Виводимо кількість чисел
    cout << "Кількість чисел: " << result << endl;

    // Знаходимо всі числа
    vector<int> numbers = findNumbers(n, d);

    // Формуємо рядок для виведення чисел
    cout << "Числа: ";
    for (int num : numbers)
    {
        cout << num << " ";
    }
    cout << endl;
}

///Задача 2.

// Функція для розшифрування однієї літери
char decryptLetter(char letter, int k)
{
    if (isalpha(static_cast<unsigned char>(letter)))
    {
        // Перевіряємо, чи є символ літерою
        char base = isupper(static_cast<unsigned char>(letter)) ? 'A' : 'a'; // Визначаємо базу
        return static_cast<char>((letter - base - k + 26) % 26 + base); // Розрахунок нової літери
    }
    return letter; // Повертаємо символ без змін, якщо це не літера
}

// Функція для розшифрування повідомлення
string decryptMessage(const string& message, int k)
{
    string decrypted;
    for (char letter : message)
    {
        decrypted += decryptLetter(letter, k); // Розшифровуємо кожну літеру
    }
    return decrypted;
}

// Функція для введення рядка і ключа, та розшифрування повідомлення
void processDecryption() {
    string encryptedMessage;
    int k;

    // Запитуємо зашифроване повідомлення
    cout << "Введіть зашифроване повідомлення:\n";
    getline(cin, encryptedMessage);

    // Запитуємо ключ шифрування
    cout << "Введіть ключ (зсув):\n";
    cin >> k;

    // Розшифровуємо повідомлення
    string decryptedMessage = decryptMessage(encryptedMessage, k);

    // Виводимо результат
    cout << "Розшифроване повідомлення: " << decryptedMessage << endl;
}

void processDecryptionWithCycle() {
    string encryptedMessage;
    int maxK;

    // Введення зашифрованого повідомлення
    cout << "Введіть зашифроване повідомлення:\n";
    getline(cin, encryptedMessage);

    // Введення максимального значення зсуву
    cout << "Введіть максимальне значення зсуву k:\n";
    cin >> maxK;

    // Виводимо результати для всіх значень k від 0 до maxK
    cout << "Результати розшифрування:" << endl;
    for (int k = 0; k <= maxK; ++k) {
        string decryptedMessage = decryptMessage(encryptedMessage, k);
        cout << "k = " << k << ": " << decryptedMessage << endl;
    }
}

int main()
{
    // setlocale(LC_ALL, "uk_UA"); // for my Linux system.
    setUtf8Encoding(); // for my Windows system.

    //solveTask();
    processDecryptionWithCycle();
    return 0;
}
