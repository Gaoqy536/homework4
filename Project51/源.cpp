#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;
// 生成随机整数
int generateRandomNumber(int maxNumber) {
    return rand() % maxNumber + 1;
}

// 生成随机小数
double generateRandomDecimal(int maxNumber) {
    return (double)(rand() % maxNumber) + (double)(rand() % 100) / 100;
}

// 将整数转换为字符串
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

// 将浮点数转换为字符串
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

// 生成四则运算表达式
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

// 生成指定数量的四则运算题目
 vector< string> generateMathProblems(int numProblems, int maxNumber, bool allowDecimal, bool allowParentheses) {
     vector< string> problems;
    for (int i = 0; i < numProblems; i++) {
        problems.push_back(generateExpression(maxNumber, allowDecimal, allowParentheses));
    }
    return problems;
}

// 输出题目到文件
void outputToFile(const  vector< string>& problems, const char* filename) {
     ofstream file(filename);
    if (file.is_open()) {
        for (const  string& problem : problems) {
            file << problem <<  endl;
        }
        file.close();
         cout << "题目已输出到文件：" << filename <<  endl;
    }
    else {
         cerr << "无法打开文件：" << filename <<  endl;
    }
}

int main() {
    srand(time(0)); // 设置随机种子

    int numProblems;
    int maxNumber;
    bool allowDecimal;
    bool allowParentheses;
    const char* outputMethod;

    // 获取用户输入
     cout << "请输入题目数量: ";
     cin >> numProblems;
     cout << "请输入最大数: ";
     cin >> maxNumber;
     cout << "是否允许小数（1-是，0-否）: ";
     cin >> allowDecimal;
     cout << "是否允许括号（1-是，0-否）: ";
     cin >> allowParentheses;
     cout << "请选择输出方式（file-输出到文件，print-打印）: ";
    char method[10];
     cin >> method;
    outputMethod = method;

    // 生成题目
     vector< string> problems = generateMathProblems(numProblems, maxNumber, allowDecimal, allowParentheses);

    // 输出题目
    if (strcmp(outputMethod, "file") == 0) {
        outputToFile(problems, "math_problems.txt");
    }
    else if (strcmp(outputMethod, "print") == 0) {
         cout << "生成的题目：" <<  endl;
        for (const  string& problem : problems) {
             cout << problem <<  endl;
        }
    }
    else {
         cerr << "无效的输出方式选择" <<  endl;
    }

    return 0;
}
