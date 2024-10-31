#include "search.h"

int main() {
    fstream file = fstream("./data/testcase.txt", ios::in);
    string s;           // string to search in
    string t;           // string to search
    vector<string> res; // result
    
    getline(file, t);
    while ((file.eof())!=true)
    {
        getline(file, s);
        search(s,t,kmp,res);
    }
    
    // TODO: read the input from file('getline' is recommended)
    // for each line, call 'search' function.

    cout << "\033[32mString to search\033[0m: " << t << endl;   //\033[32m 用于将文本颜色更改为绿色。
    cout << "\033[32mResult\033[0m:" << endl;   //\033[0m用于将文本颜色重置为默认颜色（通常是终端的默认颜色）。
    for (const auto& str : res) {
        cout << str << std::endl;
    }
    // TODO: output the result

    file.close();   // Do not forget to close the file
    return 0;
}