#pragma once
#include<bits/stdc++.h>
#define MAXSIZE 10000
#define m 300
#define K 6
using namespace std;

struct Herb {
    char name[100]; // 草药名
    char sname[100]; // 英文名
    char growth_habits[5000]; // 生长习性
    char reproductive[5000]; // 繁殖方法
    char field_management[5000]; // 田间管理
    char pest_control[5000]; // 病虫防治
    char harvesting[5000]; // 采收加工
    char taste[5000]; // 性味
    string channel_tropism[6]; // 归经
    int channel_tropism_num = 0; // 归经数量
    char effect[5000]; // 功效
    char functional_indications[5000]; // 功能主治
};

typedef struct {
    Herb* elem; // 指向数组的指针
    int length; // 数组的长度
}SqList;

void InitList(SqList& L) {
    // 使用动态内存分配new进行初始化
    L.elem = new Herb[MAXSIZE];
    L.length = 0;
}

void FreeList(SqList& L) {
    // 释放内存
    delete[] L.elem;
    L.length = 0;
}

void ReadFile(SqList& L, string filename) {
    // 从文件中读取中药材信息，将其按顺序存入L.elem指向的数组中
    ifstream infile(filename);
    char s[5000];
    while (infile.getline(s, sizeof(s), '#')) {
        Herb temp;
        stringstream streams(s);
        string ss;
        int type = 0; //每次记录完一个类型，type自增，超过10后便会break，重置为1，重新记录第一个药材的信息
        while (getline(streams, ss, '\n')) {
            if (ss.empty()) continue; // 跳过空行，否则会读入空行，导致下面的substr越界
            switch (type) {
            case 0: // 草药名
                strcpy(temp.name, ss.substr(7).c_str());
                break;
            case 1: // 英文名
                strcpy(temp.sname, ss.substr(7).c_str());
                break;
            case 2: // 生长习性
                strcpy(temp.growth_habits, ss.substr(9).c_str());
                break;
            case 3: // 繁殖方法
                strcpy(temp.reproductive, ss.substr(9).c_str());
                break;
            case 4: // 田间管理
                strcpy(temp.field_management, ss.substr(9).c_str());
                break;
            case 5: // 病虫防治
                strcpy(temp.pest_control, ss.substr(9).c_str());
                break;
            case 6: // 采收加工
                strcpy(temp.harvesting, ss.substr(9).c_str());
                break;
            case 7: // 性味
                strcpy(temp.taste, ss.substr(5).c_str());
                break;
            case 8: { // 归经 需要加花括号，解决channel的生命周期问题
                string channel_data = ss.substr(5); // 去掉"归经:"前缀
                stringstream stream(channel_data);
                string channel;

                while (getline(stream, channel, ',')) { // 按逗号分割归经
                    temp.channel_tropism[temp.channel_tropism_num++] = channel;
                }
                break;
            }
            case 9: // 功效
                strcpy(temp.effect, ss.substr(5).c_str());
                break;
            case 10: // 功能主治
                strcpy(temp.functional_indications, ss.substr(9).c_str());
                break;
            default:
                break;
            }
            type++;
        }
        L.elem[L.length++] = temp;
    }
    infile.close();
}

void SaveFile(SqList& L, string filename) {
    // 保存中药材信息到文件
    ofstream outfile(filename);
    if (!outfile) {
        cout << "无法打开文件" << endl;
        return;
    }

    for (int i = 0; i < L.length; i++) {
        outfile << "草药名:" << L.elem[i].name << endl;
        outfile << "英文名:" << L.elem[i].sname << endl;
        outfile << "生长习性:" << L.elem[i].growth_habits << endl;
        outfile << "繁殖方法:" << L.elem[i].reproductive << endl;
        outfile << "田间管理:" << L.elem[i].field_management << endl;
        outfile << "病虫防治:" << L.elem[i].pest_control << endl;
        outfile << "采收加工:" << L.elem[i].harvesting << endl;
        outfile << "性味:" << L.elem[i].taste << endl;

        outfile << "归经:";
        for (int j = 0; j < L.elem[i].channel_tropism_num; j++) {
            outfile << L.elem[i].channel_tropism[j];
            if (j < L.elem[i].channel_tropism_num - 1) {
                outfile << ",";
            }
        }
        outfile << endl;

        outfile << "功效:" << L.elem[i].effect << endl;
        outfile << "功能主治: " << L.elem[i].functional_indications << endl;

        // 除了最后一个中药信息，其他信息后面添加换行的#号
        if (i < L.length - 1) {
            outfile << "#" << endl;
        }
    }

    outfile.close();
}

void Print(SqList& L) {
    // 输出中药材信息

    cout << "草药名:" << L.elem[L.length - 1].name << endl;
    cout << "英文名:" << L.elem[L.length - 1].sname << endl;
    cout << "生长习性:" << L.elem[L.length - 1].growth_habits << endl;
    cout << "繁殖方法:" << L.elem[L.length - 1].reproductive << endl;
    cout << "田间管理:" << L.elem[L.length - 1].field_management << endl;
    cout << "病虫防治:" << L.elem[L.length - 1].pest_control << endl;
    cout << "采收加工:" << L.elem[L.length - 1].harvesting << endl;
    cout << "性味:" << L.elem[L.length - 1].taste << endl;
    cout << "归经:";
    for (int j = 0; j < L.elem[L.length - 1].channel_tropism_num; j++) {
        cout << L.elem[L.length - 1].channel_tropism[j];
        if (j != L.elem[L.length - 1].channel_tropism_num - 1) {
            cout << ",";
        }
    }
    cout << endl;
    cout << "功效:" << L.elem[L.length - 1].effect << endl;
    cout << "功能主治:" << L.elem[L.length - 1].functional_indications << endl;

}

void Print(Herb* herb) {
    // 输出中药材信息
    cout << "草药名:" << herb->name << endl;
    cout << "英文名:" << herb->sname << endl;
    cout << "生长习性:" << herb->growth_habits << endl;
    cout << "繁殖方法:" << herb->reproductive << endl;
    cout << "田间管理:" << herb->field_management << endl;
    cout << "病虫防治:" << herb->pest_control << endl;
    cout << "采收加工:" << herb->harvesting << endl;
    cout << "性味:" << herb->taste << endl;
    cout << "归经:";
    for (int j = 0; j < herb->channel_tropism_num; j++) {
        cout << herb->channel_tropism[j];
        if (j < herb->channel_tropism_num - 1) {
            cout << ",";
        }
    }
    cout << endl;

    cout << "功效:" << herb->effect << endl;
    cout << "功能主治:" << herb->functional_indications << endl;
}

typedef struct BSTNode {
    Herb data;                  // 中药材信息
    struct BSTNode* lchild;     // 左孩子指针
    struct BSTNode* rchild;     // 右孩子指针
} BSTNode, * BSTree;

void InitBSTree(BSTree& T) {
    // 二叉排序树初始化
    T = NULL;
}

void InsertBST(BSTree& T, Herb e) {
    if (T == NULL) { // 创建根节点
        T = new BSTNode;
        T->data = e;
        T->lchild = T->rchild = NULL;
    }
    else if (strcmp(e.sname, T->data.sname) < 0) {
        InsertBST(T->lchild, e); // 递归插入到左子树
    }
    else if (strcmp(e.sname, T->data.sname) > 0) {
        InsertBST(T->rchild, e); // 递归插入到右子树
    }
}

int ReadFile(BSTree& T, string filename) {
    ifstream infile(filename);
    char s[10000];
    int count = 0;

    while (infile.getline(s, sizeof(s), '#')) {
        stringstream streams(s);
        string ss;
        Herb temp;
        int type = 0;
        temp.channel_tropism_num = 0; // 重置归经数量

        while (getline(streams, ss, '\n')) {
            if (ss.empty()) continue;
            switch (type) {
            case 0: // 草药名
                strcpy(temp.name, ss.substr(7).c_str());
                break;
            case 1: // 英文名
                strcpy(temp.sname, ss.substr(7).c_str());
                break;
            case 2: // 生长习性
                strcpy(temp.growth_habits, ss.substr(9).c_str());
                break;
            case 3: // 繁殖方法
                strcpy(temp.reproductive, ss.substr(9).c_str());
                break;
            case 4: // 田间管理
                strcpy(temp.field_management, ss.substr(9).c_str());
                break;
            case 5: // 病虫防治
                strcpy(temp.pest_control, ss.substr(9).c_str());
                break;
            case 6: // 采收加工
                strcpy(temp.harvesting, ss.substr(9).c_str());
                break;
            case 7: // 性味
                strcpy(temp.taste, ss.substr(5).c_str());
                break;
            case 8: { // 归经
                string channel_data = ss.substr(5);
                stringstream stream(channel_data);
                string channel;
                while (getline(stream, channel, ',')) {
                    if (temp.channel_tropism_num < 6) {
                        temp.channel_tropism[temp.channel_tropism_num++] = channel;
                    }
                }
                break;
            }
            case 9: // 功效
                strcpy(temp.effect, ss.substr(5).c_str());
                break;
            case 10: // 功能主治
                strcpy(temp.functional_indications, ss.substr(9).c_str());
                break;
            default:
                break;
            }
            type++;
        }
        InsertBST(T, temp);
        count++;
    }
    return count;
}

void Print(BSTNode* T) {
    // 输出中药材信息
    cout << "草药名:" << T->data.name << endl;
    cout << "英文名:" << T->data.sname << endl;
    cout << "生长习性:" << T->data.growth_habits << endl;
    cout << "繁殖方法:" << T->data.reproductive << endl;
    cout << "田间管理:" << T->data.field_management << endl;
    cout << "病虫防治:" << T->data.pest_control << endl;
    cout << "采收加工:" << T->data.harvesting << endl;
    cout << "性味:" << T->data.taste << endl;
    cout << "归经:";
    for (int j = 0; j < T->data.channel_tropism_num; j++) {
        cout << T->data.channel_tropism[j];
        if (j < T->data.channel_tropism_num - 1) {
            cout << ",";
        }
    }
    cout << endl;

    cout << "功效:" << T->data.effect << endl;
    cout << "功能主治:" << T->data.functional_indications << endl;

}

typedef struct TNode {
    // 定义字典树结构体
    Herb* herbPtr;              // 中药材指针
    struct TNode*
        child[53];    // 子结点的指针数组，由26个小写字母，26个大写字母，1个空格组成
} TNode, * TrieTree;

TNode* InitTNode() {
    // 初始化字典树结点
    TNode* p = new TNode;
    p->herbPtr = NULL;
    for (int i = 0; i < 53; i++) {
        p->child[i] = NULL;
    }
    return p;
}

TNode* BuildTree(SqList& L) {
    // 构建基于链式存储的字典树
    // 构建成功后返回指向根结点的指针
        // 创建字典树的根节点
    TNode* root = InitTNode();

    for (int i = 0; i < L.length; i++) {
        //每次从根节点开始构建当前中药材英文名对应的路径
        TNode* p = root;
        char* sname = L.elem[i].sname;
        int len = strlen(sname);

        //逐个字符处理当前中药材的英文名，在字典树中创建相应路径
        for (int j = 0; j < len; j++) {
            int index;
            //根据字符是空格、大写字母还是小写字母来确定在子节点数组中的索引
            if (sname[j] == ' ') {
                index = 52;
            }
            else if (sname[j] >= 'A' && sname[j] <= 'Z') {
                index = sname[j] - 'A' + 26;
            }
            else {
                index = sname[j] - 'a';
            }

            //如果当前字符对应的子节点不存在，则创建一个新的子节点
            if (p->child[index] == NULL) {
                p->child[index] = InitTNode();
            }

            //移动到当前字符对应的子节点，继续处理下一个字符
            p = p->child[index];
        }

        //将当前中药材信息的指针赋给最后到达的节点的herbPtr成员
        p->herbPtr = &L.elem[i];
    }

    //返回构建好的字典树的根节点指针
    return root;
}

typedef struct {
    // 开放地址法散列表的存储表示
    Herb* key;
    int length;
} HashTable;

void InitHT(HashTable& HT) {
    // 散列表初始化
    HT.key = new Herb[m];
    for (int i = 0; i < m; i++) {
        // 初始化散列表每个单元为空
        HT.key[i].sname[0] = '\0';
    }
    HT.length = 0;
}

int Hash(char* sname) {
    // 实现散列函数：字符串sname中各字符的下标（从0开始）的平方乘以字符对应的ASCII码值，相加后与299取余
    int sum = 0;
    for (int i = 0; i < strlen(sname); i++)
        sum += ((i) * (i) * int(sname[i]));
    return sum % 299;
}

void HTInsert(HashTable& HT, Herb h, int& sumCmp) {
    // 往散列表中插入新的中药材f
    // 在插入的过程中统计总的比较次数sumCmp
    int HashValue = Hash(h.sname);
    int i = HashValue;
    int j = 0;

    while (j < m) {
        if (HT.key[i].sname[0] == '\0') {
            // 如果当前位置为空，则插入
            HT.key[i] = h;
            HT.length++;
            sumCmp++;
            return;
        }
        else {
            sumCmp++;
            i = (i + 1) % m;
            j++;
        }
    }

}

void ReadFile(HashTable& HT, int& sumCmp, string filename) {
    // 从文件中读取中药材信息，将其存入散列表HT中
    ifstream infile(filename);
    if (!infile) {
        cout << "无法打开文件: " << filename << endl;
        return;
    }

    char s[5000];


    while (infile.getline(s, sizeof(s), '#')) {
        stringstream streams(s);
        string ss;
        Herb temp;
        int type = 0;

        while (getline(streams, ss, '\n')) {
            if (ss.empty()) continue;
            switch (type) {
            case 0: // 草药名
                strcpy(temp.name, ss.substr(7).c_str());
                break;
            case 1: // 英文名
                strcpy(temp.sname, ss.substr(7).c_str());
                break;
            case 2: // 生长习性
                strcpy(temp.growth_habits, ss.substr(9).c_str());
                break;
            case 3: // 繁殖方法
                strcpy(temp.reproductive, ss.substr(9).c_str());
                break;
            case 4: // 田间管理
                strcpy(temp.field_management, ss.substr(9).c_str());
                break;
            case 5: // 病虫防治
                strcpy(temp.pest_control, ss.substr(9).c_str());
                break;
            case 6: // 采收加工
                strcpy(temp.harvesting, ss.substr(9).c_str());
                break;
            case 7: // 性味
                strcpy(temp.taste, ss.substr(5).c_str());
                break;
            case 8: { // 归经
                string channel_data = ss.substr(5);
                stringstream stream(channel_data);
                string channel;

                while (getline(stream, channel, ',')) {
                    temp.channel_tropism[temp.channel_tropism_num++] = channel;
                }
                break;
            }
            case 9: // 功效
                strcpy(temp.effect, ss.substr(5).c_str());
                break;
            case 10: // 功能主治
                strcpy(temp.functional_indications, ss.substr(9).c_str());
                break;
            default:
                break;
            }
            type++;
        }

        HTInsert(HT, temp, sumCmp);
    }

    infile.close();
}

void Print(HashTable HT, int pos) {
    // 输出中药材信息
    if (pos >= 0 && pos < HT.length) {
        cout << "草药名:" << HT.key[pos].name << endl;
        cout << "英文名:" << HT.key[pos].sname << endl;
        cout << "生长习性:" << HT.key[pos].growth_habits << endl;
        cout << "繁殖方法:" << HT.key[pos].reproductive << endl;
        cout << "田间管理:" << HT.key[pos].field_management << endl;
        cout << "病虫防治:" << HT.key[pos].pest_control << endl;
        cout << "采收加工:" << HT.key[pos].harvesting << endl;
        cout << "性味:" << HT.key[pos].taste << endl;

        cout << "归经:";
        for (int j = 0; j < HT.key[pos].channel_tropism_num; j++) {
            cout << HT.key[pos].channel_tropism[j];
            if (j < HT.key[pos].channel_tropism_num - 1) {
                cout << ",";
            }
        }
        cout << endl;

        cout << "功效:" << HT.key[pos].effect << endl;
        cout << "功能主治:" << HT.key[pos].functional_indications << endl;
    }
}

typedef struct LNode {
    Herb data;                  // 食材信息
    struct LNode* next;         // 指向下一级结点
} LNode, * LinkList;

void InitList(LinkList* H) {
    // 链表初始化
    for (int i = 0; i < m; i++) {
        H[i] = new LNode;
        H[i]->next = nullptr;
    }
}

void ListInsert(LinkList* H, Herb f, int& sumCmp) {
    // 往散列表中插入新的中药材f
    // 在插入的过程中统计总的比较次数sumCmp
    int pos = Hash(f.sname);
    LNode* p = new LNode;
    if (!p) return;
    p->data = f;
    p->next = H[pos]->next; // 前插法
    H[pos]->next = p;

    //在链表中插入一个元素，则后面的元素比较次数也会增加，第一个节点比较一次，第二个节点比较2次
    int increase = 0;    // 一个链表共 i-1 个节点，插入一个节点成为 i 个节点，第i 个节点需比较 i 次，也就是比插入元素前多比较的次数
    while (p) {
        increase++;
        p = p->next;
    }
    sumCmp += increase;

}

int ReadFile(LinkList* H, int& sumCmp, string filename) {
    // 从文件中读取中药材信息，将其存入散列表中
    ifstream infile(filename);
    int count = 0;
    char s[5000];

    while (infile.getline(s, sizeof(s), '#')) {
        stringstream streams(s);
        string ss;
        Herb temp;
        int type = 0;

        while (getline(streams, ss, '\n')) {
            if (ss.empty()) continue;
            switch (type) {
            case 0: // 草药名
                strcpy(temp.name, ss.substr(7).c_str());
                break;
            case 1: // 英文名
                strcpy(temp.sname, ss.substr(7).c_str());
                break;
            case 2: // 生长习性
                strcpy(temp.growth_habits, ss.substr(9).c_str());
                break;
            case 3: // 繁殖方法
                strcpy(temp.reproductive, ss.substr(9).c_str());
                break;
            case 4: // 田间管理
                strcpy(temp.field_management, ss.substr(9).c_str());
                break;
            case 5: // 病虫防治
                strcpy(temp.pest_control, ss.substr(9).c_str());
                break;
            case 6: // 采收加工
                strcpy(temp.harvesting, ss.substr(9).c_str());
                break;
            case 7: // 性味
                strcpy(temp.taste, ss.substr(5).c_str());
                break;
            case 8: { // 归经
                string channel_data = ss.substr(5);
                stringstream stream(channel_data);
                string channel;

                while (getline(stream, channel, ',')) {
                    temp.channel_tropism[temp.channel_tropism_num++] = channel;
                }
                break;
            }
            case 9: // 功效
                strcpy(temp.effect, ss.substr(5).c_str());
                break;
            case 10: // 功能主治
                strcpy(temp.functional_indications, ss.substr(9).c_str());
                break;
            default:
                break;
            }
            type++;
        }
        ListInsert(H, temp, sumCmp);
        count++;
    }

    infile.close();
    return count;
}

void Print(LNode* T, char* sname) {
    // 输出中药材信息
    while (T != nullptr) {
        if (strcmp(T->data.sname, sname) == 0) {
            cout << "草药名:" << T->data.name << endl;
            cout << "英文名:" << T->data.sname << endl;
            cout << "生长习性:" << T->data.growth_habits << endl;
            cout << "繁殖方法:" << T->data.reproductive << endl;
            cout << "田间管理:" << T->data.field_management << endl;
            cout << "病虫防治:" << T->data.pest_control << endl;
            cout << "采收加工:" << T->data.harvesting << endl;
            cout << "性味:" << T->data.taste << endl;
            cout << "归经:";
            for (int i = 0; i < T->data.channel_tropism_num; i++) {
                cout << T->data.channel_tropism[i];
                if (i != T->data.channel_tropism_num - 1) cout << ",";
            }
            cout << endl;
            cout << "功效:" << T->data.effect << endl;
            cout << "功能主治:" << T->data.functional_indications << endl;
            return;
        }
        T = T->next;
    }
}
