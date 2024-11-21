#pragma once
#include "herb_data_structure.h"

void GetNext(const char* T, int next[]) {
    // 计算子串T的next数组
    int len = strlen(T);
    int i = 0, j = -1;
    next[0] = -1;

    while (i < len) {
        if (j == -1 || T[i] == T[j]) {
            i++;
            j++;
            next[i] = j;
        }
        else {
            j = next[j];
        }
    }
}

bool KMP(const char* S, const char* T, int next[]) {
    // 利用模式串T的next数组求子串T在主串S中是否存在
    // 如果查找成功则返回true，如果查找失败则返回false
    GetNext(T, next);
    int i = 0;
    int j = 0;
    int slen = strlen(S);
    int tlen = strlen(T);

    while (i < slen) {
        if (j == -1 || S[i] == T[j]) {
            i++;
            j++;
        }
        else {
            j = next[j];
        }
        if (j == tlen) {
            return true;
        }
    }
    return false;
}

bool SearchList(SqList& L, char* keyword, int next[]) {
    // 遍历顺序表中药材的生长习性和繁殖方法信息，调用KMP算法
    // 如果在中药材中查找成功则返回true，如果查找失败则返回false
    bool flag = 0;
    for (int i = 0; i < L.length; i++) {
        if (KMP(L.elem[i].growth_habits, keyword, next)) {
            cout << L.elem[i].name << endl;
            flag = 1;
        }
        if (KMP(L.elem[i].reproductive, keyword, next)) {
            cout << L.elem[i].name << endl;
            flag = 1;
        }
    }
    if (flag) return true;
    return false;
}