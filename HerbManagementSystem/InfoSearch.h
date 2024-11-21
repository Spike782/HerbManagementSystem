#pragma once
#include "herb_data_structure.h"

int SeqSearch(SqList& L, char* sname) {
    // 在顺序表L中顺序查找中药材英文名称等于sname的数据元素
    // 若找到，则返回该元素在表中的下标，否则返回-1
    int compare = 0; //记录比较次数
    for (int i = 0; i < L.length; i++) {
        compare++;
        if (strcmp(L.elem[i].sname, sname) == 0) {

            //返回该元素的下标
            return i;
        }
    }
    return -1;
}

double GetASL(SqList& L) {
    // 返回基于顺序表的顺序查找的ASL
    double totalComparisons = 0;

    for (int i = 0; i < L.length; i++) {
        totalComparisons += (i + 1);
    }

    return totalComparisons / L.length;
}

void Print(SqList& L, int pos) {
    // 输出中药材信息
    Herb* herb = &L.elem[pos];

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

void SortHerb(SqList& L) {
    // 将中药材信息按英文名称的字典序从小到大排序
    for (int i = 0; i < L.length - 1; ++i) {
        for (int j = 0; j < L.length - i - 1; ++j) {
            // 比较相邻两个中药材的英文名称
            if (strcmp(L.elem[j].sname, L.elem[j + 1].sname) > 0) {
                // 交换两个中药材的信息
                Herb temp = L.elem[j];
                L.elem[j] = L.elem[j + 1];
                L.elem[j + 1] = temp;
            }
        }
    }
}

int BinarySearch(SqList& L, char* sname) {
    // 在顺序表L中折半查找中药材英文名称等于sname的数据元素
    // 若找到，则返回该元素在表中的下标，否则返回-1
    int low = 0;
    int high = L.length - 1;
    int compare = 0; // 记录比较次数

    while (low <= high) {
        compare++;
        int mid = (low + high) / 2;

        if (strcmp(L.elem[mid].sname, sname) == 0) {
            return mid;
        }
        else if (strcmp(L.elem[mid].sname, sname) < 0) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    return -1;
}

double GetASLForBinary(SqList& L) {
    // 返回基于顺序表的折半查找的ASL
    double totalComparisons = 0;
    int success = 0;//查找的次数

    for (int i = 0; i < L.length; i++) {
        int low = 0;
        int high = L.length - 1;
        int compare = 0;

        while (low <= high) {
            compare++;
            int mid = (low + high) / 2;
            if (strcmp(L.elem[i].sname, L.elem[mid].sname) == 0) {
                success++;
                break;
            }
            else if (strcmp(L.elem[i].sname, L.elem[mid].sname) < 0) {
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        totalComparisons += compare;
    }

    if (success > 0) {
        return totalComparisons / success;
    }
    else {
        return 0;
    }
}

BSTNode* SearchBST(BSTree& T, char* sname) {
    // 查找对应中药材，查找成功返回对应的树结点，否则返回NULL
    if (T == NULL) {
        return NULL;
    }
    else if (strcmp(sname, T->data.sname) == 0) {
        return T;
    }
    else if (strcmp(sname, T->data.sname) < 0) {
        return SearchBST(T->lchild, sname);
    }
    else {
        return SearchBST(T->rchild, sname);
    }
}

int GetSumCmp(BSTree T, int sumCmp) {
    // 统计查找成功时的总比较次数
    if (!T) return 0;
    return sumCmp + GetSumCmp(T->lchild, sumCmp + 1) + GetSumCmp(T->rchild, sumCmp + 1);
    //每遍历一个结点，比较次数+1
}

double GetASL(BSTree& T, int count) {
    // 返回基于二叉排序树查找的ASL
    if (!count) return 0;
    return (double)GetSumCmp(T, 1) / count;
}

Herb* TrieSearch(TNode* root, char* sname) {
    // 基于字典树的查找
    // 如果查找成功则返回指向该中药材的指针，如果查找失败则返回NULL
    TNode* p = root;
    int len = strlen(sname);

    //逐个字符在字典树中查找对应的路径
    for (int i = 0; i < len; i++) {
        int index;
        //根据字符是空格、大写字母还是小写字母来确定在子节点数组中的索引
        if (sname[i] == ' ') {
            index = 52;
        }
        else if (sname[i] >= 'A' && sname[i] <= 'Z') {
            index = sname[i] - 'A' + 26;
        }
        else {
            index = sname[i] - 'a';
        }

        //如果当前字符对应的子节点不存在，则查找失败，返回NULL
        if (p->child[index] == NULL) {
            return NULL;
        }

        //动到当前字符对应的子节点，继续查找下一个字符
        p = p->child[index];
    }

    // 如果能顺利找到最后一个字符对应的节点，则返回该节点的herbPtr成员，即指向该中药材的指针，表示查找成功
    return p->herbPtr;
}

double GetASLForTrie(SqList& L) {
    // 计算查找成功时的平均查找长度ASL
      // 先构建字典树用于查找
    TNode* root = BuildTree(L);

    int totalComparisons = 0;
    int successfulSearches = 0;

    for (int i = 0; i < L.length; i++) {
        char* sname = L.elem[i].sname;
        Herb* result = TrieSearch(root, sname);

        if (result != NULL) {
            successfulSearches++;
            // 计算每次查找成功的比较次数，这里以字符比较次数为准
            int comparisons = strlen(sname);
            totalComparisons += comparisons;
        }
    }

    if (successfulSearches > 0) {
        return static_cast<double>(totalComparisons) / successfulSearches;
    }
    else {
        return 0;
    }
}

int SearchHash(HashTable HT, char* key) {
    // 在散列表HT中查找中药材英文名称等于key的元素
    // 若找到，则返回散列表的单元标号，否则返回-1
    int HashValue = Hash(key);
    int i = HashValue;
    int j = 0;

    while (j < m && HT.key[i].sname[0] != '\0'); {
        if (strcmp(HT.key[i].sname, key) == 0) {
            return i;
        }
        else {
            i = (i + 1) % m;
            j++;
        }
    }

    return -1;
}

double GetASL(HashTable HT, int sumCmp) {
    // 返回基于开放地址法的散列查找的ASL
    return static_cast<double>(sumCmp) / HT.length;
}

int SearchHL(LinkList* H, char* key) {
    // 在散列表HT中查找药材英文名称等于key的元素
    // 若找到，则返回散列表的单元标号，否则返回-1

        // 先计算key对应的哈希值（位置索引）
    int pos = Hash(key);

    // 获取散列表中索引为pos的链表的头节点指针，赋给cur
    LNode* cur = H[pos]->next;

    while (cur != nullptr) {
        if (strcmp(cur->data.sname, key) == 0) {
            return pos;
        }
        cur = cur->next;
    }
    return -1;
}

double GetASL(int sumCmp, int count) {
    // 返回基于链地址法的散列查找的ASL 
    double ASL = static_cast<double>(sumCmp) / count;
    return ASL;
}