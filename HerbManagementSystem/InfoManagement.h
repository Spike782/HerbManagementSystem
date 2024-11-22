#pragma once
#include "herb_data_structure.h"

// 定义一个枚举类型ActionType，表示可能的操作类型
enum ActionType {
    INSERT, // 插入操作
    DELETE, // 删除操作
    MODIFY  // 修改操作
};

struct Operation {
    ActionType action; // 操作类型
    Herb herb;         // 相关的中草药信息（对于 INSERT 和 DELETE）
    Herb oldHerb;      // 修改前的中草药信息（仅适用于 MODIFY）
    int position;      // 操作位置
};

// 操作栈
struct OperationStack {
    Operation operations[MAX_HISTORY]; // 存储操作
    int top;                           // 栈顶指针，初始化为 -1 表示空栈
};

// 初始化操作栈
void InitStack(OperationStack& S) {
    S.top = -1;
}

// 判断栈是否为空
bool IsEmpty(const OperationStack& S) {
    return S.top == -1;
}

// 判断栈是否已满
bool IsFull(const OperationStack& S) {
    return S.top == MAX_HISTORY - 1;
}

// 入栈操作
bool Push(OperationStack& S, const Operation& op) {
    if (IsFull(S)) {
        return false; // 栈满
    }
    S.operations[++S.top] = op;
    return true;
}

// 出栈操作
bool Pop(OperationStack& S, Operation& op) {
    if (IsEmpty(S)) {
        return false; // 栈空
    }
    op = S.operations[S.top--];
    return true;
}

// 撤销上一次操作
bool Undo(SqList& L, OperationStack& S) {
    if (IsEmpty(S)) {
        cout << "没有可撤销的操作。" << endl;
        return false;
    }

    Operation lastOp;
    Pop(S, lastOp);// 弹出操作记录

    if (lastOp.action == INSERT) {
        // 撤销插入：删除最后一个元素
        L.length--;
    }
    else if (lastOp.action == DELETE) {
        // 撤销删除：在指定位置插入
        for (int i = L.length; i > lastOp.position; i--) {
            L.elem[i] = L.elem[i - 1];
        }
        L.elem[lastOp.position] = lastOp.herb;
        L.length++;
    }
    else if (lastOp.action == MODIFY) {
        // 撤销修改：还原修改前的数据
        L.elem[lastOp.position] = lastOp.oldHerb;
    }

    cout << "操作已撤销。" << endl;
    return true;
}

bool InsertHerb(SqList& L, OperationStack& stack) {
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
    // 记录插入操作
    Operation op = { INSERT, temp, L.length - 1 };
    Push(stack, op);
    return true;
}

Herb* DeleteHerb(SqList& L, char* name, OperationStack& stack) {
    // 根据中文名称删除指定中药材信息
    // 如果删除成功，返回指向该食材信息的指针，否则，返回NULL
    for (int i = 0; i < L.length; i++) {
        if (strcmp(L.elem[i].name, name) == 0) {
            Herb deletedHerb = L.elem[i];
            for (int j = i; j < L.length - 1; j++) {
                L.elem[j] = L.elem[j + 1];
            }
            L.length--;
            Operation op = { DELETE, deletedHerb,{}, i };
            Push(stack, op);
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

bool ModifyHerb(SqList& L, char* name, string lines[], int n, OperationStack& stack) {
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
            // 将修改操作记录到栈
            Operation op = { MODIFY, newHerb, oldHerb, i };
            Push(stack, op);
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


