#ifndef __SEARCH_H
#define __SEARCH_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
/**
 * @brief search the string t in s using search_algorithm
 * @param s the string to search in
 * @param t the string to search
 * @param search_algorithm the search algorithm
 * @return res the result
 */
void search(const string &s, const string &t, int (*search_algorithm)(const string &, const string &, const int), vector<string> &res) {
    int start = 0;
    vector<string> result;
    string ret;
    while (true) {
        int pos = search_algorithm(s, t, start);
        if (pos == -1) 
            break;
        ret += s.substr(start, pos-start) + "\033[31m" + t + "\033[0m";
        start = pos + t.size();
    }
    ret += s.substr(start);
    res.push_back(ret);
}

/**
 * @brief search the string t in s using brute force algorithm
 * @return the position of the first occurrence of t in s, -1 if not found
 */
int bf(const string &s, const string &t, const int start) {
    if (start<0 || start > (int)(s.size()-t.size())) return -1;
    int i=start, j=0;
    while ( i<(int)s.size() && j<(int)t.size() )
    {
        if (s[i]==t[j])
        {
            i++;j++;
        }
        else
        {
            i=i-j+1;j=0;
        }
    }
    if(j==(int)t.size()) return i-j;
    else return -1;
    // TODO: implement brute force algorithm
}

/**
 * @brief get the next array of the string t
 */
vector<int> get_next(const string &t) {
    int k=-1,j=0;
    vector<int> next(t.size(), 0);
    next[0] = -1;
    while(j < (int)t.size()) {
        if(k == -1 || t[j] == t[k]) {
            ++j, ++k;
            if(t[j] != t[k])
                next[j] = k;
            else
                next[j] = next[k];
        }
        else    
            k = next[k];
    }
    return next;
    // TODO: implement get_next algorithm
}


/**
 * @brief kmp algorithm
 */
int kmp(const string &s, const string &t, const int start) {
    static vector<int> next;    // next array
    if (next.empty()) {
        next = get_next(t);
    }
    int i=start,j=0;
    while (i < (int)s.size()&&j < (int)t.size())
    {
        if (j==-1||s[i]==t[j])
        {
            i++;j++;
        }
        else j=next[j];
        if (j==(int)t.size()) return i-j;
    }
    return -1;
    // TODO: implement kmp algorithm
}

#endif /* search.h */