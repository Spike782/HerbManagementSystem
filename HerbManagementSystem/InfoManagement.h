#pragma once
#include "herb_data_structure.h"

// 操作撤回栈
struct OperationStack {
    SqList operation[10]; // 最多撤回五次操作
    int top = 0;         // 栈顶指针，初始化为 0 表示空栈
};

// 初始化撤回栈
void InitStack(OperationStack& S) {
    S.top = 0;
}

// 判断栈满
bool Isfull(OperationStack& S) {
    return S.top == 10;
}

// 释放操作栈内存
void FreeOperationStack(OperationStack& S) {
    // 遍历操作栈中的每个SqList元素并释放其内存
    for (int i = 0; i < S.top; i++) {
        FreeList(S.operation[i]);
    }
    S.top = 0;
}

//每次操作后更新撤回栈
void UpdateOperation(SqList& L, OperationStack &S) {
    if (Isfull(S)) {
        cout << "操作栈满，此次操作未更新！"<<endl;
        return;
    }
    SqList temp = L;
    S.operation[S.top++] = temp;
}

// 撤销上一次操作
bool Undo(SqList& L,OperationStack &S, string filename) {
    if (S.top == 0) return 0;
    
    FreeList(L); //先清空列表
    S.top--;

    L = S.operation[S.top];
    SaveFile(L, filename);
    cout << "成功撤销！" << endl;
    return true;
}

bool InsertHerb(SqList& L) {
    // 插入中药材信息，输入中药材的草药名、英文名、生长习性、繁殖方法、田间管理、病虫防治、采收加工、性味、归经、功效和功能主治信息
    // 如果插入成功，返回true，否则，返回false
    Herb temp;
    char ss[5000];
    int type = 0;
    while (cin.getline(ss, sizeof(ss), '\n')) {
        if (type == 0) { //草药名
            for (int i = 0; i < L.length; i++) {
                if (strcmp(L.elem[i].name, ss) == 0) {
                    return 0;
                }
            }
            strcpy(temp.name, ss);
        }
        else if (type == 1) { //英文名
            strcpy(temp.sname, ss);
        }
        else if (type == 2) { //生长习性
            strcpy(temp.growth_habits, ss);
        }
        else if (type == 3) { //繁殖方法
            strcpy(temp.reproductive, ss);
        }
        else if (type == 4) { //田间管理
            strcpy(temp.field_management, ss);
        }
        else if (type == 5) { //病虫防治
            strcpy(temp.pest_control, ss);
        }
        else if (type == 6) { //采收加工
            strcpy(temp.harvesting, ss);
        }
        else if (type == 7) { //性味
            strcpy(temp.taste, ss);
        }
        else if (type == 8) { //归经
            temp.channel_tropism_num = ss[0] - '0';
            for (int i = 0; i < temp.channel_tropism_num; i++) {
                cin.getline(ss, sizeof(ss), '\n');
                temp.channel_tropism[i] = ss;
            }
        }
        else if (type == 9) { //功效
            strcpy(temp.effect, ss);
        }
        else if (type == 10) { //功能主治
            strcpy(temp.functional_indications, ss);
            break;
        }
        type++;
    }
    L.elem[L.length++] = temp;
    return true;
}

Herb* DeleteHerb(SqList& L, char* name) {
    // 根据中文名称删除指定中药材信息
    // 如果删除成功，返回指向该食材信息的指针，否则，返回NULL
    for (int i = 0; i < L.length; i++) {
        if (strcmp(L.elem[i].name, name) == 0) {
            Herb deletedHerb = L.elem[i];
            for (int j = i; j < L.length - 1; j++) {
                L.elem[j] = L.elem[j + 1];
            }
            L.length--;
            return &deletedHerb;
        }
    }
    return NULL;
}

bool check(SqList& L, char* name) {
    for (int i = 0; i < L.length; i++) {
        if (strcmp(name, L.elem[i].name) == 0) {
            return false;
        }
    }
    return true;
}

bool ModifyHerb(SqList& L, char* name, string lines[], int n) {
    // 中药材归经信息修改，
    // 如果修改成功，返回true，否则，返回false
    for (int i = 0; i < L.length; i++) {
        if (strcmp(L.elem[i].name, name) == 0) {
            
            Herb oldHerb = L.elem[i];
            
            //清空原有的经归信息
            L.elem[i].channel_tropism_num = 0;

            //把新的信息写入
            for (int j = 0; j < n; j++) {
                L.elem[i].channel_tropism[L.elem[i].channel_tropism_num++] = lines[j];
            }
            Herb newHerb = L.elem[i];
            return true;
        }
    }
    return false;
}

Herb* getHerb(SqList& L, char* name) {
    // 返回指向修改后的中药材信息的指针
    for (int i = 0; i < L.length; i++) {
        if (strcmp(L.elem[i].name, name) == 0) {
            Herb* modified_herb = &L.elem[i];


            return modified_herb;
        }
    }
    return NULL;
}
