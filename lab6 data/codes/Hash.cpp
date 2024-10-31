#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
#define m 43

// 自定义哈希函数
int customHash(const string& key) {
    return (key.front() * 100 + key.back()) % 41;
}

// 将字符串转换为小写
string toLowercase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// 统计关键字出现的次数并更新哈希表
void countKeywords(const string& filename, int hashTable[], const vector<string>& keywords) {
    // 打开源文件
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "文件打不开" << endl;
        return;
    }

    // 逐行读取源文件
    string line;
    while (getline(file, line)) {
        // 将每行转换为小写
        line = toLowercase(line);
        // 在每行中查找关键字
        for (const string& keyword : keywords) {
            size_t pos = line.find(keyword);
            while (pos != string::npos) {
                int index = customHash(keyword);
                hashTable[index]++;
                pos = line.find(keyword, pos + 1);
            }
        }
    }
    file.close();
}

// 计算向量点积
double dotProduct(int* v1, int* v2) {
    double result = 0.0;
    for (size_t i = 0; i < m; ++i) {
        result += v1[i] * v2[i];
    }
    return result;
}

// 计算向量模长
double vectorLength(int* v) {
    double result = 0.0;
    for (size_t i = 0; i < m; ++i) {
        result += v[i] * v[i];
    }
    return sqrt(result);
}

int main() 
{
    // C语言关键字
    vector<string> keywords = {"auto", "break", "case", "char", "const", "continue", "default", "do",
                               "double", "else", "enum", "extern", "float", "for", "goto", "if",
                               "int", "long", "register", "return", "short", "signed", "sizeof", "static",
                               "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};

    // 创建哈希表数组并初始化为0
    int hashTable[6][m] = {0};

    // 统计两个源文件中关键字的出现次数并更新哈希表
    for (int i = 0; i <= 5; ++i) {
        string filename = "code (" + to_string(i) + ").cpp";
        countKeywords(filename, hashTable[i], keywords);
    }

    for (int i = 0; i <= 5; ++i) {
        for (int j = i + 1; j <= 5; ++j) {
            // 计算余弦相似度
            double dot = dotProduct(hashTable[i], hashTable[j]);
            double len1 = vectorLength(hashTable[i]);
            double len2 = vectorLength(hashTable[j]);
            double cosineSimilarity = dot / (len1 * len2);

            cout << "code (" << i << ")和code(" << j << ")的余弦相似度: " << cosineSimilarity << endl;

            // 计算向量的几何距离
            double distance = 0.0;
            for (size_t k = 0; k < m; ++k) {
                distance += pow(hashTable[i][k] - hashTable[j][k], 2);
            }
            distance = sqrt(distance);

            cout << "code (" << i << ")和code(" << j << ")的几何距离: " << distance << endl;
            if (cosineSimilarity>0.9&&distance<25)
            {
                cout << "code (" << i << ")和code(" << j << ")可能相似" << endl;
        }
            else
            cout << "code (" << i << ")和code(" << j << ")不相似" << endl;
    }
    }
    return 0;

}