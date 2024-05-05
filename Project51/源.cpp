#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;
// �����������
int generateRandomNumber(int maxNumber) {
    return rand() % maxNumber + 1;
}

// �������С��
double generateRandomDecimal(int maxNumber) {
    return (double)(rand() % maxNumber) + (double)(rand() % 100) / 100;
}

// ������ת��Ϊ�ַ���
 string intToString(int number) {
     string result;
    bool isNegative = false;

    if (number < 0) {
        isNegative = true;
        number = -number;
    }

    do {
        result = static_cast<char>('0' + number % 10) + result;
        number /= 10;
    } while (number > 0);

    if (isNegative) {
        result = "-" + result;
    }

    return result;
}

// ��������ת��Ϊ�ַ���
 string doubleToString(double number) {
     string result = intToString(static_cast<int>(number));

    if (number < 0) {
        number = -number;
    }

    double fraction = number - static_cast<int>(number);
    if (fraction > 0) {
        result += ".";
        const int maxDecimalPlaces = 6;
        for (int i = 0; i < maxDecimalPlaces; ++i) {
            fraction *= 10;
            int digit = static_cast<int>(fraction);
            result += static_cast<char>('0' + digit);
            fraction -= digit;
        }
    }

    return result;
}

// ��������������ʽ
 string generateExpression(int maxNumber, bool allowDecimal, bool allowParentheses) {
     string expression;
    int num1 = allowDecimal ? generateRandomDecimal(maxNumber) : generateRandomNumber(maxNumber);
    int num2 = allowDecimal ? generateRandomDecimal(maxNumber) : generateRandomNumber(maxNumber);
    char op = "+-*/"[rand() % 4];

    if (allowParentheses && rand() % 2 == 0) {
        expression = "(" + intToString(num1) + " " + op + " " + intToString(num2) + ")";
    }
    else {
        expression = intToString(num1) + " " + op + " " + intToString(num2);
    }

    return expression;
}

// ����ָ������������������Ŀ
 vector< string> generateMathProblems(int numProblems, int maxNumber, bool allowDecimal, bool allowParentheses) {
     vector< string> problems;
    for (int i = 0; i < numProblems; i++) {
        problems.push_back(generateExpression(maxNumber, allowDecimal, allowParentheses));
    }
    return problems;
}

// �����Ŀ���ļ�
void outputToFile(const  vector< string>& problems, const char* filename) {
     ofstream file(filename);
    if (file.is_open()) {
        for (const  string& problem : problems) {
            file << problem <<  endl;
        }
        file.close();
         cout << "��Ŀ��������ļ���" << filename <<  endl;
    }
    else {
         cerr << "�޷����ļ���" << filename <<  endl;
    }
}

int main() {
    srand(time(0)); // �����������

    int numProblems;
    int maxNumber;
    bool allowDecimal;
    bool allowParentheses;
    const char* outputMethod;

    // ��ȡ�û�����
     cout << "��������Ŀ����: ";
     cin >> numProblems;
     cout << "�����������: ";
     cin >> maxNumber;
     cout << "�Ƿ�����С����1-�ǣ�0-��: ";
     cin >> allowDecimal;
     cout << "�Ƿ��������ţ�1-�ǣ�0-��: ";
     cin >> allowParentheses;
     cout << "��ѡ�������ʽ��file-������ļ���print-��ӡ��: ";
    char method[10];
     cin >> method;
    outputMethod = method;

    // ������Ŀ
     vector< string> problems = generateMathProblems(numProblems, maxNumber, allowDecimal, allowParentheses);

    // �����Ŀ
    if (strcmp(outputMethod, "file") == 0) {
        outputToFile(problems, "math_problems.txt");
    }
    else if (strcmp(outputMethod, "print") == 0) {
         cout << "���ɵ���Ŀ��" <<  endl;
        for (const  string& problem : problems) {
             cout << problem <<  endl;
        }
    }
    else {
         cerr << "��Ч�������ʽѡ��" <<  endl;
    }

    return 0;
}
