#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "Stack.cpp"

#define ASCII_SIZE 128

using namespace std;
  
// Huffman树的节点
typedef struct  {
    char data; // 字符
    int weight; // 频率
    int parent;
    int left;
    int right;
} HTNode;
typedef HTNode *HuffTree;

void Print(void){
    printf("[I]:Initialization\n");
    printf("[E]:Encoding\n");
    printf("[D]:Decoding\n");
    printf("[P]:Print\n");
    printf("[T]:Tree Printing\n");
    printf("[Q]:Quit\n");
}

// 统计文件中字符的出现次数并按ASCII码顺序输出到控制台
void countCharacters(const char* filename, int* &frequencyMap) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("文件不存在\n");
        return;
    }

    char c;
    while ((c = fgetc(file)) != EOF) {
        frequencyMap[(int)c]++;
    }
    fclose(file);
}

void print_frequency(int* &frequencyMap)
{
    printf("频率:\n");
    for (int i = 0; i < ASCII_SIZE; ++i) {
        if (frequencyMap[i] != 0) {
            printf("Character [%c] : %d\n", (char)i, frequencyMap[i]);
            if ((char)i=='\n')
            printf("Character [\\n] : %d\n", frequencyMap[i]);
        }
    }
}
//在构建霍夫曼树时用于筛选权重最小的两个值
void Select(HuffTree HT, int i, int &s1, int &s2){//i是从count+1开始的
    s1 = 0;
    s2 = 0;
    for (int j = 1; j < i; j++)
    {
        if (HT[j].parent==0 && s1==0)
        {
            s1=j;
            continue;
        }
        if(HT[j].parent==0 && HT[j].weight<HT[s1].weight)
        s1 = j;
    }
    for (int j = 1; j < i; j++)
    {
        if (j==s1) continue;
        if (HT[j].parent==0 && s2==0)
        {
            s2=j;
            continue;
        }
        if(HT[j].parent==0 && HT[j].weight<HT[s2].weight)
        s2 = j;
    }
}
//计算有效的字符总个数
int calculate_frequencyMap(int* frequencyMap){
    int i, count = 0;
    for (i = 0; i < ASCII_SIZE; ++i) {
        if (frequencyMap[i] > 0) {
            count++;
        }
    }
    return count;
}
// 构建Huffman树
void HuffmanTree(HuffTree &HT, int* frequencyMap, int count) {
    int i=0, j=1;
    int knots = 2*count - 1;
    int s1;
    int s2;
    HT = new HTNode[knots+1];
    for (i = 0; i < ASCII_SIZE; ++i)
    {   if (frequencyMap[i] > 0){
        HT[j].data = (char)i;
        HT[j].weight = frequencyMap[i];
        HT[j].left = HT[j].right = HT[j].parent =0;
        j++;
    }
    }
    while (j <= knots)
    {
        HT[j].weight = 0;
        HT[j].left = HT[j].right = HT[j].parent =0;
        HT[j].data = '$';
        j++;
    }
    
    for (i = count+1; i <= knots; i++)
    {
        Select(HT,i,s1,s2);
        HT[i].left = s1;
        HT[i].right = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
        HT[s1].parent = HT[s2].parent = i;
    }
}
//循环输入体，中序遍历Huffman树
void saveToFileHelper(HuffTree HT, FILE* fp, int root) {
    if (root != 0) {
        if (HT[root].data == '\n') {
            fprintf(fp, "id=%2d ,data=\\n ,weight=%4d ,parent=%2d, lc=%2d ,rc=%2d\n", root, HT[root].weight, HT[root].parent, HT[root].left, HT[root].right);
        } else
        {
            fprintf(fp, "id=%2d ,data=%c ,weight=%4d ,parent=%2d, lc=%2d ,rc=%2d\n", root, HT[root].data, HT[root].weight, HT[root].parent, HT[root].left, HT[root].right);
        }
        saveToFileHelper(HT, fp, HT[root].left);
        saveToFileHelper(HT, fp, HT[root].right);
    }
}
//将Huffman树存储进文件
void saveHuffmanTreeToFile(HuffTree HT, const char* filename, int root) {
    FILE* fp = fopen(filename, "w"); // 使用 "w" 模式，每次调用函数时清空文件
    if (fp == NULL) {
        printf("文件不存在\n");
        return;
    }
    fclose(fp);

    FILE* file = fopen(filename, "a");
    saveToFileHelper(HT, file, root);

    fclose(file);
}

void Coding(HuffTree HT,int root, char **&HC, Stack &s){
    char ch;
    if(root != 0){
        if(HT[root].left==0){
            s.Push('\0');
            HC[root] = new char[s.size+1];
            strcpy(HC[root], s.elem);
            s.Pop(ch);
        }
    s.Push('0');
    Coding(HT, HT[root].left, HC, s);
    s.Pop(ch);
    s.Push('1');
    Coding(HT, HT[root].right, HC, s);
    s.Pop(ch);
    }
}

void HuffmanCoding(HuffTree HT, char **&HC, int count){
    Stack s(count);
    HC = new char*[count+1];
    Coding(HT, 2*count-1, HC, s);
}

void saveHCtofile(char **&HC, const char* filename, int count, HuffTree HT){
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("文件不存在\n");
        return;
    }
    fclose(file);

    FILE* fp = fopen(filename, "a");
    for (int i = 1; i <= count; i++)
    {
        if (HT[i].data == '\n')
        {
            fprintf(fp, "\\n:%s\n",HC[i]);
        }
        else   
        fprintf(fp, "%c:%s\n",HT[i].data, HC[i]);
    }
    fclose(fp);
}

void Encode(const char* filename_tobe, const char* filename_code, char **HC, int count, HuffTree HT){
    FILE* file = fopen(filename_code, "w");
    if (file == NULL) {
        printf("文件不存在\n");
        return;
    }
    fclose(file);

    FILE* fp = fopen(filename_tobe, "r");
    FILE* fq = fopen(filename_code, "a"); 
    
    char c;
    int i;

    while ((c = fgetc(fp)) != EOF)
    {
        for (i = 1; i <= count; i++)
        {
            if (HT[i].data == c)
            break;
        }
        fprintf(fq, "%s", HC[i]);
    }
    fclose(fp);
    fclose(fq);
}

void Decoding(const char* filename_tobe, const char* filename_code, HuffTree HT, int root){
    FILE* file = fopen(filename_code, "w");
    if (file == NULL) {
        printf("文件不存在\n");
        return;
    }
    fclose(file);

    FILE* fp = fopen(filename_tobe, "r");
    FILE* fq = fopen(filename_code, "a");

    char c;
    int r=root;

    while ((c = fgetc(fp)) != EOF)
    {
        if(c == '0')
        r = HT[r].left;
        else
        r = HT[r].right;
        if(HT[r].left == 0)
        {
            fprintf(fq, "%c", HT[r].data);
            r=root;
        }
    }
    fclose(fp);
    fclose(fq);
}

void printToFileHelper(HuffTree HT, FILE* fp, int root,char **HC,int n) {
    if (root != 0) {
        if (n == 0)
        {
            fprintf(fp, "|-%2d\n", root);
        }
        else
        {
        for (int i = 0; i < n-1; i++)
        {
                fprintf(fp, "  ");
        }
        if (HT[root].data == '$')
        {
            fprintf(fp, " |-%2d\n", root);
        }
        else{
        if (HT[root].data == '\n') {
            fprintf(fp, " |-\\n:weight=%4d ,%s\n",HT[root].weight,HC[root]);
        } else
        {
            fprintf(fp, " |-%c:weight=%4d ,%s\n",HT[root].data, HT[root].weight,HC[root]);
        }
        }
        }
        printToFileHelper(HT, fp, HT[root].left, HC, n+1);
        printToFileHelper(HT, fp, HT[root].right, HC, n+1);
    }
}

void printHuffmanTreeToFile(HuffTree HT, const char* filename, int root, char **HC) {
    FILE* fp = fopen(filename, "w"); // 使用 "w" 模式，每次调用函数时清空文件
    if (fp == NULL) {
        printf("文件不存在\n");
        return;
    }
    fclose(fp);

    FILE* file = fopen(filename, "a");
    int n=0;
    printToFileHelper(HT, file, root, HC, n);

    fclose(file);
}

void read_hfmTree(const char* filename, HuffTree &HT, int root){
    //FILE *fp=fopen(filename, "r");

    HT = new HTNode[root+1];
    int id, weight, parent, lc, rc;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "无法打开文件。" << endl;
        return ;
    }

    std::string line;
    while (std::getline(file, line)) {
        // 使用字符串流解析每一行数据
        std::istringstream iss(line);
        
        // 解析每一行数据
        char comma; // 用于吸收逗号和空格
        std::string data_str; // 用于存储字符串数据
        iss >> std::skipws >> std::noskipws >> id >> comma >> comma
            >> data_str >> comma >> weight >> comma
            >> parent >> comma >> lc >> comma >> rc;

        if (data_str[0]=='\n')
    {
        HT[id].data='\n';
    }
    else HT[id].data=data_str[0];
        
        HT[id].weight=weight, HT[id].parent=parent,HT[id].left=lc,HT[id].right=rc;
    }
    file.close();
    //fclose(fp);

}

void transform(const char* filename_tobe, const char* filename_code){
    FILE* file = fopen(filename_code, "w");
    if (file == NULL) {
        printf("文件不存在\n");
        return;
    }
    fclose(file);

    FILE* fp = fopen(filename_tobe, "r");
    FILE* fq = fopen(filename_code, "a");

    int i=0;
    char c;
    while ((c=getc(fp)) != EOF)
    {
        i++;
        fprintf(fq, "%c",c);
        if (i == 50)
        {
        fprintf(fq, "\n");
        i=0;
        }
    }
    fclose(fp);
    fclose(fq);
}

int main() {
    int *frequencyMap;
    frequencyMap = new int[ASCII_SIZE];
    for (int i = 0; i < ASCII_SIZE; i++)
    frequencyMap[i]=0;
    
    char choice;
    HuffTree HT;
    char **HC;


    while(1){
        Print();
        scanf("%c", &choice);
        if (choice=='Q') break;
        switch(choice){
            case 'I':
                // 统计文件中字符的出现次数
                countCharacters("ToBeTran.txt", frequencyMap);
                //输出到控制台
                print_frequency(frequencyMap);
                //构建Huffman树
                HuffmanTree(HT, frequencyMap, calculate_frequencyMap(frequencyMap));
                //把Huffman树保存进文件
                saveHuffmanTreeToFile(HT, "hfmTree.txt", 2*calculate_frequencyMap(frequencyMap)-1);
                break;
            case 'E':
                countCharacters("ToBeTran.txt", frequencyMap);
                HuffmanTree(HT, frequencyMap, calculate_frequencyMap(frequencyMap));
                HuffmanCoding(HT, HC, calculate_frequencyMap(frequencyMap));
                saveHCtofile(HC, "HCfile.txt", calculate_frequencyMap(frequencyMap), HT);
                //对源文件进行编码
                Encode("ToBeTran.txt","CodeFile.txt",HC, calculate_frequencyMap(frequencyMap),HT);
                break;
            case 'D':
                countCharacters("ToBeTran.txt", frequencyMap);
                HuffmanTree(HT, frequencyMap, calculate_frequencyMap(frequencyMap));
                HuffmanCoding(HT, HC, calculate_frequencyMap(frequencyMap));
                //解码
                Decoding("CodeFile.txt", "TextFile.txt", HT, 2*calculate_frequencyMap(frequencyMap)-1);
                break;
            case 'P':
                //转换
                transform("CodeFile.txt","CodeFile50.txt");
                break;
            case 'T':
                countCharacters("ToBeTran.txt", frequencyMap);
                HuffmanTree(HT, frequencyMap, calculate_frequencyMap(frequencyMap));
                HuffmanCoding(HT, HC, calculate_frequencyMap(frequencyMap));
                //打印霍夫曼树
                printHuffmanTreeToFile(HT, "TreePrint.txt", 2*calculate_frequencyMap(frequencyMap)-1,HC);
                break;
        }
    }

    return 0;
}