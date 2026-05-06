#include <cstring>
#include <iostream>

using namespace std;

void example1()
{
    char str1[] = "1234567890"; // визначення рядка str1
    char str2[11]; // визначення рядка str2

    // без ініціалізації
    // в циклі, доки не зустрінеться кінець рядка, привласнюються поточному елементу str2 символ з str1
    int k = 0;
    for (int i = 0; str1[i] != '\0'; i++)
        str2[k++] = str1[i];
    str2[k] = '\0'; // копіюємо нуль-символ в кінець str2
    cout << str2 << '\n'; // друк рядка на екран
    // АБО
    int N = strlen(str1); //довжина рядка str1
    for (int i = 0; str1[i] != '\0'; i++)
        str2[i] = str1[i];
    str2[strlen(str1)] = '\0'; // копіюємо нуль-символ в кінець
    cout << str2;
}

void example2()
{
    char* S; //покажчик на char

    S = new char[10];
    char str[] = "str"; //визначена строка
    strncpy(S, str, 9); // копіювання не більше 9 символів
    S[9] = '\0'; // завершення строки символом '\0'
    cout << S << endl;
    char* S1 = new char[10];
    strncpy(S1, "stroka", 9); // копіювання не більше 9 символів
    S1[9] = '\0'; // завершення строки символом '\0'
    cout << S << endl;
    cout << S1 << endl;
    char* S2 = new char[5]{"1234"}; //символів <= 4
    cout << S2 << endl;
    char* S3 = new char[11]{"abcd"}; //символів <= 10

    delete[] S, delete[] S1, delete[] S2, delete[] S3, S = S1 = S2 = S3 = nullptr;
}

void example3()
{
    char* str = new char[10]{"PRIVET"};
    cout << str << endl; //PRIVET
    cout << *str << endl; //P
    cout << *(str + 1) << endl; //R
    cout << str + 1 << endl; //RIVET

    *(str + 2) = 'A';
    cout << str << endl; //PRAVET
    for (int i = 0; i < strlen(str); i++)
        cout << str[i] << " "; //P R А V E T

    delete[] str, str = nullptr;
}

void example4()
{
    int mas[5] = {1, 2, 3, 4, 5};
    char S1[] = "Hello";
    char* S2 = new char[5]{"John"};
    cout << mas << endl; //0042А9AС
    cout << S1 << endl; //Hello
    cout << S2 << endl; //John
    cout << *mas << endl; //1
    cout << *S1 << endl; //H
    cout << *S2 << endl; //J

    delete[] S2, S2 = nullptr;
}

void example5()
{
    char str[] = "Hello, world!";
    cout << str << endl;
    char* b;
    b = &str[7];
    cout << b << endl;   // друкує world!
    cout << *b << endl;  // друкує тільки w
    *b = 'M';
    cout << b << endl;   // друкує Morld!
    cout << str << endl; // друкує Hello, Morld!
}

void example6()
{
    cout << "\n=== getchar вводить символ, виводить символ ===\n";
    char ch = getchar(); // введення символу
    putchar(ch); // виведення символу
    cout << endl;

    // ============================================================
    cout << "\n========= strlen рахує довжину рядка ==========\n";
    char s1[20] = "qwerty";
    cout << strlen(s1) << endl;

    // ============================================================
    cout << "\n============ strcat об'єднує рядки ============\n";
    char s2[30] = "Hello";
    strcat(s2, " world");
    cout << s2 << endl;

    // ============================================================
    cout << "\n============ strcpy копіює рядок ==============\n";
    char s3[20];
    strcpy(s3, "test");
    cout << s3 << endl;

    // ============================================================
    cout << "\n========= strncpy копіює частину рядка ========\n";
    char s4[20];
    strncpy(s4, "abcdef", 3);
    s4[3] = '\0';
    cout << s4 << endl;

    // ============================================================
    cout << "\n============ strcmp порівнює рядки ============\n";
    cout << strcmp("abc", "abc") << endl;
    cout << strcmp("abc", "abd") << endl;

    // ============================================================
    cout << "\n========= strchr шукає символ у рядку =========\n";
    char s5[] = "PRIVET";
    char* p = strchr(s5, 'V');
    if (p != nullptr)
        cout << p << endl;

    // ============================================================
    cout << "\n======== strstr шукає підрядок у рядку ========\n";
    char* p1 = strstr(s5, "IV");
    if (p1 != nullptr)
        cout << p1 << endl;

    // ============================================================
    cout << "\n=== atoi та atof перетворюють рядок у число ===\n";
    cout << atoi("123") << endl;
    cout << atof("123.45") << endl;
}

void task1()
{
    char S[80];

    char gl[] = "aeouiyAEOUIY";
    int i, j;

    cout << "Введіть речення:\n";
    fgets(S, sizeof(S), stdin);

    S[strcspn(S, "\n")] = '\0';
    cout << "Введіть символ заміни:\n";

    char c;
    cin >> c;

    for (i = 0; i < strlen(S); i++)
        for (j = 0; j < strlen(gl); j++)
            if (S[i] == gl[j]) S[i] = c;

    puts(S);
}

/**
 *
 * @param S - вхідний рядок
 * @param S1 - рядок до
 * @param S2 - рядок після
 * @param ch - символ
 */
void task2(char* S, char* S1, char* S2, char ch)
{
    while (*S != ch && *S != '\0') // *S != '\0', Бо якщо символу ch у рядку нема, піде читати памʼять за межами рядка.
    {
        *S1 = *S;
        S1++;
        S++;
    }

    *S1 = '\0';

    if (*S == ch) S++;

    while (*S != '\0')
    {
        *S2 = *S;
        S2++;
        S++;
    }

    *S2 = '\0';
}

/**
 * hello world
 * hell
 *  world
 */
void task2()
{
    char S[80];

    fgets(S, sizeof(S), stdin);

    for (int i = 0; S[i] != '\0'; i++)
        if (S[i] == '\n')
        {
            S[i] = '\0';
            break;
        }

    char S1[80];
    char S2[80];

    char ch = 'o';

    task2(S, S1, S2, ch);

    puts(S1);
    puts(S2);
}

int task3()
{
    char ch;

    printf("Введіть символ: ");
    ch = getchar();

    printf("Введений символ: ");
    putchar(ch);
    putchar('\n');

    char str[] = "c language";

    for (int i = 0; str[i] != '\0'; i++)
        putchar(toupper(str[i]));

    putchar('\n');

    return 0;
}

int main()
{
    // example6();
       task3();

    return 0;
}
