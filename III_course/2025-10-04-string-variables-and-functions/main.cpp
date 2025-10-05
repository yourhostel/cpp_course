#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

void test_printf();
void test_putchar();
void test_puts();
void vowel_counts();
void sort_strings_lex();

// Перше завдання
#define N 10
#define M 4
typedef struct {
    int id;
    string name;
    int marks[M];
} Student;
int all_good(const Student *s);
void print_table_good();

// Друге завдання
template <size_t K>
void print_array(const string (&a)[K]);
void sort_and_demo();


int main()
{
    // test_printf();
    // test_putchar();
    // test_puts();
    // vowel_counts();
    // sort_strings_lex();
    // print_table_good();
    sort_and_demo();

    return 0;
}

// Друге завдання
// Друк масиву
template <size_t K>
void print_array(const string (&a)[K])  // K вираховується компілятором
{
    for (const auto & i : a)
        cout << i << '\n';
}

// Ініціалізація, друк, сортування за size() (спадання), друк
void sort_and_demo()
{
    constexpr int L = 12;
    string a[L] = {
        "Привіт", "Алгоритми", "C++", "Сортування рядків", "Тест",
        "Лабораторна", "B(12)", "Я", "Україна", "Довгий рядок прикладу",
        "Код", "Рядок"
    };

    // Примітка: size() повертає кількість байтів у std::string (UTF-8 -> байти).
    cout << "Початковий масив:\n";
    print_array(a);
    cout << "-----\n";

    // Сортуємо in-place за спаданням довжини (size())
    sort(a, a + L, [](const string &x, const string &y) {
        return x.size() > y.size();
    });

    cout << "Відсортований масив (за size(), спадання):\n";
    print_array(a);
}

// Перше завдання
int all_good(const Student *s) {
    for (const int mark : s -> marks)
        if (mark < 4) return 0;
    return 1;
}

void print_table_good()
{
    Student a[N] = {
        {1, "Iванчук С.О.", {4,4,3,4}},
        {2, "Панченко І.А.", {5,4,4,5}},
        {3, "Заєць О.М.",    {3,4,4,4}},
        {4, "Вельбицький П.О.", {4,3,3,3}},
        {5, "Сидоренко В.Р.", {2,3,3,2}},
        {6, "Кравченко З.I.", {3,5,4,5}},
        {7, "Якубів Р.Н.",   {5,4,5,4}},
        {8, "Зоренко П.М.",  {4,2,3,3}},
        {9, "Берестяк Г.С.", {4,5,5,5}},
        {10,"Дячик Н.С.",    {5,5,4,4}}
    };

    printf("%5s | %-24s | %6s | %9s | %6s | %6s\n",
           "№", "Прiзвище", "Інформ", "Вищ. мат.", "Фізика", "Програм.");
    printf("----+-------------------+--------+-----------+--------+---------\n");

    for (auto & i : a) {
        if (!all_good(&i)) continue; // Перевірка успішності студента

        int with_name = 15 - static_cast<int>(i.name.size()) / 2;
        if (with_name < 0) with_name = 0;

        printf("%3d | %s%*s | %6d | %9d | %6d | %6d\n",
               i.id, i.name.c_str(), with_name, "",
               i.marks[0], i.marks[1], i.marks[2], i.marks[3]);
    }
}

void test_printf()
{   // Вирівнювання
    printf("|%-10s|\n", "hi");   // |hi        |
    printf("|%10s|\n", "hi");    // |        hi|
    // Ширина
    printf("|%5d|\n", 42);       // |   42|
    printf("|%2d|\n", 1234);     // |1234|
    // Точність
    printf("%.3f\n", 3.14159);   // 3.142
    printf("%.2s\n", "hello");   // he
    // Символ перетворення
    // d або i - ціле число
    // f - число з плаваючою крапкою
    // s - рядок (C-style, тобто char*)
    // c - один символ
    // x / X - ціле у шістнадцятковій
    // o - восьмирічне
    // % - сам знак %
    printf("%d\n", 255);          // 255
    printf("%x\n", 255);          // ff
    printf("%X\n", 255);          // FF
    printf("%f\n", 3.14159);      // 3.141590
    printf("%s\n", "Hello");      // Hello
    printf("%c\n", 'A');          // A
    printf("%o\n", 255);          // 377
    printf("%%\n");               // %
}


void test_putchar()
{
    putchar('a');        // a
    putchar('\n');       // новий рядок
    putchar('b');        // b
    putchar(getchar());  // ехо введеного символу
}

void test_puts()
{
    constexpr char str1[] = "abcdefgh";
    const auto str2 = "1234567890";

    puts("Вивід повідомлення"); // Вивід повідомлення\n
    puts(str1);                   // abcdefgh\n
    puts(str2);                   // 1234567890\n

    puts(&str1[4]);               // efgh\n
    puts(str2 + 6);             // 7890\n
}

// Підрахунок голосних у кожному рядку
#define KMAX 5
void vowel_counts()
{
    auto voc = "aAeEiIoOuUyY";
    const char *masstr[KMAX] = {"typedef", "while", "for", "unsigned", "float"};
    const char *ptr;

    for (int i = 0; i < KMAX; i++) {
        int k = 0;
        ptr = masstr[i];
        while ((ptr = strpbrk(ptr, voc)) != nullptr) {
            k++;
            ptr++; // щоб не зациклитись на тому самому символі
        }
        printf("masstr[%d] = \"%s\" -> голосних = %d\n", i, masstr[i], k);
    }
}

// Лексикографічне сортування масиву рядків
#define N_LEX 2
#define M_LEX 64
void sort_strings_lex()
{
    char masstr[N_LEX][M_LEX];
    int i;

    // Ввід рядків
    for (i = 0; i < N_LEX; i++) {
        if (fgets(masstr[i], M_LEX, stdin) == nullptr) { // fgets замість gets
            masstr[i][0] = '\0';
            continue;
        }
        // прибираємо '\n', якщо він є
        size_t len = strlen(masstr[i]);
        if (len > 0 && masstr[i][len - 1] == '\n') masstr[i][len - 1] = '\0';
    }

    // Сортування бульбашкою (лексикографічно)
    for (i = 0; i < N_LEX - 1; i++) {
        for (int j = i + 1; j < N_LEX; j++) {
            if (strcmp(masstr[i], masstr[j]) > 0) {
                char tmp[N_LEX];
                strcpy(tmp, masstr[i]);
                strcpy(masstr[i], masstr[j]);
                strcpy(masstr[j], tmp);
            }
        }
    }

    // Вивід відсортованого масиву
    puts("Відсортований масив:");
    for (i = 0; i < N_LEX; i++) puts(masstr[i]);
}
