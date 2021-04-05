/*
Вариант 7. ОТЯП.

Конструкция 7 - условный оператор.

if <логическое выражение> then
<операторы>
[ elseif <логическое выражение> then <операторы> ]
end

<логическое выражение> → <выражение сравнения> |
<унарная логическая операция><выражение сравнения> |
<логическое выражение><бинарная логическая операция><выражение сравнения>
<выражение сравнения> → <операнд> | <операнд><операция сравнения><операнд>
<операция сравнения> → < | > | = | <>
<унарная логическая операция> → not
<бинарная логическая операция> → and | or
<операнд> → <идентификатор> | <константа>
<операторы> → <операторы>; <оператор> | <оператор>
<оператор> → <идентификатор> = <арифметическое выражение>
<арифметическое выражение> → <операнд> |
<арифметическое выражение><арифметическая операция><операнд>
<арифметическая операция> → + | - | / | *

???: not, and, or, +, -, /, *, =, <, >, =, <>, if, then, elseif, end, ;, *

Ключевое слово [kw]: not, and, or, if, then, elseif, end

Специальный символ [co]: <, >, <>
Специальный символ [eq]: =
Специальный символ [ao]: +, -, /, *
Специальный символ [sc]: ;

Константы [vl]: 
Идентификаторы [id]:
Мусор [wl]:

type:
0 kw
1 co
2 eq
3 ao
4 sc
5 vl
6 id
7 wl
*/
/*
Уровень 1
<логическое выражение> → <операнд> | <операнд><операция сравнения><операнд>
<операция сравнения> → < | > | <= | >= | = | <>
<операнд> → <идентификатор>|<константа>
<операторы> → <идентификатор> = <арифметическое выражение>
<арифметическое выражение> → <операнд> |
<арифметическое выражение><арифметическая операция><операнд>
<арифметическая операция> → + | –


Уровень 2
<логическое выражение> → <выражение сравнения> |
<логическое выражение><логическая операция><выражение сравнения>
<выражение сравнения> → <операнд> | <операнд><операция сравнения><операнд>
<операция сравнения> → < | > | = | <>
<логическая операция> → and | or
<операнд> → <идентификатор> | <константа>
<операторы> → <идентификатор> = <арифметическое выражение>
<арифметическое выражение> → <операнд> |
<арифметическое выражение><арифметическая операция><операнд>
<арифметическая операция> → + | – | / | *
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <ctype.h>

using namespace std;
const char* types[] = { "kw","co","eq","ao","sc","vl","id","wl" };
enum states { S, A,C,E, a,c,ao,eq,sc,co1,CO,r,t,ao2,eq2,sc2,co3,co4,e,E1,vl,f,co2,aos,eqs,scs,co1s,COs,aos2,eqs2,scs2};
states matrix[9][5]
{
   //  S,  A,      C,  E , CO ,   ,   ,   ,   ,   ,   ,   ,   ,    
       a,  A,      E,  E , f ,//  ,   ,   ,   ,   ,   ,   ,   ,           // буквы
       c,  A,      C,  E ,  E , //  ,   ,   ,   ,   ,   ,   ,   ,           // цыфры
       ao, aos, aos2, ao2 ,  E ,//   ,   ,   ,   ,   ,   ,   ,   ,           // /*+-
       eq, eqs, eqs2,  eq2 , E ,//   ,   ,   ,   ,   ,   ,   ,   ,           // =
       sc, scs, scs2, sc2  ,  E ,//   ,   ,   ,   ,   ,   ,   ,   ,           // ;
       co1,co1s,   E,  co3 ,  E , //  ,   ,   ,   ,   ,   ,   ,   ,           // >
       CO, COs,   E , co4  , E ,//   ,   ,   ,   ,   ,   ,   ,   ,           // <
       S,   r,   vl ,  e ,  E, //  ,   ,   ,   ,   ,   ,   ,   ,           // \n \0 \r \t ' '
       E1,   E,    E ,  E , E ,//   ,   ,   ,   ,   ,   ,   ,   ,           // other
};

struct Lex
{
    int type;
    char* lex;
};

char* inputFromFile()  // Получение данных из файла "input.txt"
{
    ifstream finp("input.txt");
    if (!finp.is_open()) throw("I went through the files, looking for the right one, but I didn't find it...\n");
    finp.seekg(0, ios::end);    // Смещение = 0 от конца буфера потока
    streamoff size = finp.tellg();
    finp.seekg(0, ios::beg);    // Смещение = 0 от начала буфера потока
    char* text = new char[(size_t)size + 1];
    finp.read(&text[0], size);
    text[size] = '\0';
    finp.close();
    return text;
}
int iskw(const char* const str)
{
    // Ключевое слово [kw]: not, and, or, if, then, elseif, end
    if (str == "not") return 0;
    if (str == "and") return 0;
    if (str == "or") return 0;
    if (str == "if") return 0;
    if (str == "then") return 0;
    if (str == "elseif") return 0;
    if (str == "end") return 0;
    return 6;
}
void add(vector<Lex>& v, const char* const text, int firstPos, int lastPos, int type)  // Создаёт слово с firstPos по lastPos не включительно и добавляет его в вектор
{
    Lex word;
    word.lex = new char[lastPos - firstPos + 1];
    for (size_t i = firstPos; i < (size_t)lastPos; ++i) word.lex[i - firstPos] = text[i];
    word.lex[lastPos - firstPos] = '\0';
    if (type == 6) { word.type = iskw(word.lex); }
    else if (type == 5){ (atoi(word.lex) > 32768) ? word.type = 7 : word.type = 5; }
    else word.type = type;
    v.push_back(word);
}

size_t whatLine(char c)  // Функция возвращает индекс строки в матрице состояний (отсчёт с нуля)
{
    if (isalpha(c)) return 0;
    if (isdigit(c)) return 1;
    if (c == '*'|| c == '/' || c == '+'|| c == '-') return 2;
    if (c == '=') return 3;
    if (c == ';') return 4;
    if (c == '>') return 5;
    if (c == '<') return 6;
    if (isspace(c) || iscntrl(c)) return 7;
    return 8;
}

void lexAnalysis(const char* const text, vector<Lex>& result)
{
    int position = 0;    // Индекс текущего символа из текста
    states state = states::S;  // Установлено начальное состояние S
//    states prevState = states::S;
    int firstPos = -1;  // Индекс начала палиндрома
    do {
        char currentChar = text[position];   // Текущий символ запоминаем
        state = matrix[whatLine(currentChar)][state];  // Меняем настроение
        switch (state) {
        case (S):  // Ну тут дальше всё очень очевидно
            break;
        case (a):
            firstPos = position;
            state = A;
            break;
        case (c):
            firstPos = position;
            state = C;
            break;
        case (A):
            break;
        case (r):
            (position - firstPos < 6) ? add(result, text, firstPos, position, 6) : add(result, text, firstPos, position, 7);
            state = S;
            break;
        case (e):
            add(result, text, firstPos, position, 7);
            state = S;
            break;
        case(vl):
            add(result, text, firstPos, position, 5);
            state = S;
            break;
        case (ao):
            add(result, text, position, position + 1, 3);
            state = S;
            break;
        case (eq):
            add(result, text, position, position + 1, 2);
            state = S;
            break;
        case (sc):
            add(result, text, position, position + 1, 4);
            state = S;
            break;
        case (co1):
            add(result, text, position, position + 1, 1);
            state = S;
            break;
        case (co2):
            add(result, text, position, position + 1, 1);
            state = S;
            break;
        case (aos):
            (position - firstPos < 6) ? add(result, text, firstPos, position, 6) : add(result, text, firstPos, position, 7);
            state = S;
            add(result, text, position, position + 1, 3);
            break;
        case (eqs):
            (position - firstPos < 6) ? add(result, text, firstPos, position, 6) : add(result, text, firstPos, position, 7);
            state = S;
            add(result, text, position, position + 1, 2);
            break;
        case (scs):
            (position - firstPos < 6) ? add(result, text, firstPos, position, 6) : add(result, text, firstPos, position, 7);
            state = S;
            add(result, text, position, position + 1, 4);
            break;
        case (co1s):
            (position - firstPos < 6) ? add(result, text, firstPos, position, 6) : add(result, text, firstPos, position, 7);
            state = S;
            add(result, text, position, position + 1, 1);
            break;
        case(E1):
            state = E;
            firstPos = position;
            break;
        //case (CO):
        //    firstPos = position;
        //    break;
        //case (f):
        //    firstPos = position;
        //    break;
        }
    } while (text[position++] != '\0');
}

void saveToFile(vector<Lex>& v)
{
    ofstream foutp("output.txt");   // Открытие выходного файла
    for (size_t i = 0; i < v.size(); ++i) foutp << v[i].lex << '[' << types[v[i].type] << ']' << ' ';
    foutp << endl;
    for (size_t i = 0; i < v.size(); ++i) if (v[i].type == 6) foutp << v[i].lex << ' ';
    foutp << endl;
    for (size_t i = 0; i < v.size(); ++i) if (v[i].type == 5) foutp << v[i].lex << ' ';
    foutp.close();  // Закрытие выходного файла
}

int main()
{
    char* text = inputFromFile();
    vector<Lex> v;
    lexAnalysis(text, v);
    saveToFile(v);
    for (size_t i = 0; i < v.size(); ++i) delete v[i].lex;
    delete[] text;
	return 0;
}