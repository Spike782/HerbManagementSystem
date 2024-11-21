#pragma once
#include "herb_data_structure.h"

void ReadFileForSort(SqList& L, string filename) {
    // 从文件中读取中药材信息，将其按顺序存入L.elem指向的数组中
    ifstream infile(filename);
    char s[5000];
    int index = 1;
    while (infile.getline(s, sizeof(s), '#')) {
        stringstream streams(s);
        string ss;
        Herb temp;
        int type = 0;

        while (getline(streams, ss, '\n')) {
            if (ss.empty()) continue;
            switch (type) {
            case 0: strcpy(temp.name, ss.substr(10).c_str()); break;//草药名
            case 1: strcpy(temp.sname, ss.substr(10).c_str()); break;//英文名
            case 2: strcpy(temp.growth_habits, ss.substr(13).c_str()); break;//生长习性
            case 3: strcpy(temp.reproductive, ss.substr(13).c_str()); break;//繁殖方式
            case 4: strcpy(temp.field_management, ss.substr(13).c_str()); break;//田间管理
            case 5: strcpy(temp.pest_control, ss.substr(13).c_str()); break;//病虫防治
            case 6: strcpy(temp.harvesting, ss.substr(13).c_str()); break;//采收加工
            case 7: strcpy(temp.taste, ss.substr(7).c_str()); break;//性味
            case 8: {//归经
                stringstream stream(ss.substr(7));
                string channel;
                while (getline(stream, channel, ',')) {
                    temp.channel_tropism[temp.channel_tropism_num++] = channel;
                }
                break;
            }
            case 9: strcpy(temp.effect, ss.substr(7).c_str()); break;//功效
            case 10: strcpy(temp.functional_indications, ss.substr(13).c_str()); break;//功能主治
            default: break;
            }
            type++;
        }
        L.elem[index++] = temp;
        L.length++;
    }
    infile.close();

}

void InsertSort(SqList& L, int& kcn, int& rmn) {
    // 对顺序表L做直接插入排序，从后向前顺序比较
    // 注：L.elem[0]用做哨兵单元
    // 输出排序后的中药材英文名称、KCN和RMN

        // 将第一个元素作为已排序序列，从第二个元素开始插入排序
    for (int i = 2; i <= L.length; i++) {
        //如果当前元素比前一个元素小，执行插入排序
        if (strcmp(L.elem[i].sname, L.elem[i - 1].sname) < 0) {
            L.elem[0] = L.elem[i];
            int j = i - 1;
            rmn++;
            kcn++;

            //从后向前找插入位置
            while (strcmp(L.elem[0].sname, L.elem[j].sname) < 0) {
                L.elem[j + 1] = L.elem[j];
                j--;
                rmn++;
                kcn++;
            }

            L.elem[j + 1] = L.elem[0];
            rmn++;
        }
        //如果当前元素比前一个元素大就不执行插入排序
        else kcn++;
    }

    // 输出排序后的中药材英文名称、KCN和RMN
    for (int i = 1; i <= L.length; i++) {
        cout << L.elem[i].sname << endl;
    }
    cout << "总的关键字比较次数KCN为：" << kcn << endl;
    cout << "总的记录移动次数RMN为：" << rmn << endl;
}

void BInsertSort(SqList& L, int& kcn, int& rmn) {
    // 对顺序表做折半插入排序
    // 注：L.elem[0]用做哨兵单元
    // 输出排序后的中药材英文名称、KCN和RMN
    for (int i = 2; i <= L.length; i++) {
        Herb temp = L.elem[i];
        int low = 1, high = i - 1;

        // 将当前要插入的元素暂存到哨兵单元L.elem[0]
        L.elem[0] = temp;
        rmn++;

        // 折半查找合适的插入位置
        while (low <= high) {
            int mid = (low + high) / 2;
            if (strcmp(temp.sname, L.elem[mid].sname) < 0) {
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
            kcn++; // 每比较一次，关键字比较次数KCN加1
        }

        // 移动元素腾出插入位置
        for (int j = i - 1; j >= high + 1; j--) {
            L.elem[j + 1] = L.elem[j];
            rmn++; // 每移动一次记录，记录移动次数RMN加1
        }

        // 将暂存的元素插入到合适的位置
        L.elem[high + 1] = temp;
        rmn++;
    }

    // 输出排序后的中药材英文名称、KCN和RMN
    for (int i = 1; i <= L.length; i++) {
        cout << L.elem[i].sname << endl;
    }
    cout << "总的关键字比较次数KCN为：" << kcn << endl;
    cout << "总的记录移动次数RMN为：" << rmn << endl;
}

void BubbleSort(SqList& L, int& kcn, int& rmn) {
    // 对顺序表L做冒泡排序
    // 注：elem[0]闲置
    // 输出排序后的中药材英文名称、KCN和RMN
    bool swapped;

    for (int i = 1; i < L.length; i++) {
        swapped = false;

        for (int j = 1; j < L.length - i + 1; j++) {
            kcn++; // 每比较一次，关键字比较次数KCN加1
            if (strcmp(L.elem[j].sname, L.elem[j + 1].sname) > 0) {
                Herb temp = L.elem[j];
                L.elem[j] = L.elem[j + 1];
                L.elem[j + 1] = temp;
                rmn += 3;
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }


    for (int i = 1; i <= L.length; i++) {
        cout << L.elem[i].sname << endl;
    }
    cout << "总的关键字比较次数KCN为：" << kcn << endl;
    cout << "总的记录移动次数RMN为：" << rmn << endl;

}

int Partition(SqList& L, int low, int high, int& kcn, int& rmn) {
    // 对顺序表中的子表elem[low..high]进行一趟排序，返回枢轴位置
    L.elem[0] = L.elem[low];  // 使用第一个元素作为枢轴
    rmn++;

    while (low < high) {
        // 从右往左找第一个小于枢轴的元素
        while (low < high && strcmp(L.elem[high].sname, L.elem[0].sname) >= 0) {
            high--;
            kcn++;
        }
        // 将找到的小于枢轴的元素移到低端
        L.elem[low] = L.elem[high];
        rmn++;
        if (low < high) kcn++; //如果这个if成立，说明上一个while是因为关键字的比较而退出的，所以kcn++
        // 从左往右找第一个大于枢轴的元素
        while (low < high && strcmp(L.elem[low].sname, L.elem[0].sname) <= 0) {
            low++;
            kcn++;
        }
        // 将找到的大于枢轴的元素移到高端
        L.elem[high] = L.elem[low];
        rmn++;
        if (low < high) kcn++; //如果这个if成立，说明上一个while是因为关键字的比较而退出的，所以kcn++
    }
    // 将枢轴元素放回合适位置
    L.elem[low] = L.elem[0];
    rmn++;
    // 返回枢轴的最终位置
    return low;
}

void QSort(SqList& L, int low, int high, int& kcn, int& rmn) {
    // 调用前置初值：low=1; high=L.length;
    // 对顺序表L中的子序列L.elem[low.high]做快速排序
        // 如果子序列长度大于0（即low小于high），则继续进行排序
    if (low < high) {
        // 对当前子序列进行一趟划分，得到枢轴位置
        int pivotloc = Partition(L, low, high, kcn, rmn);

        // 递归地对枢轴左边的子序列进行快速排序
        QSort(L, low, pivotloc - 1, kcn, rmn);

        // 递归地对枢轴右边的子序列进行快速排序
        QSort(L, pivotloc + 1, high, kcn, rmn);
    }
}

void QuickSort(SqList& L) {
    // 对顺序表做快速排序
    // 输出排序后的中药材英文名称、KCN和RMN
    int kcn = 0;
    int rmn = 0;

    QSort(L, 1, L.length, kcn, rmn);

    for (int i = 1; i <= L.length; i++) {
        cout << L.elem[i].sname << endl;
    }

    cout << "总的关键字比较次数KCN为：" << kcn << endl;

    cout << "总的记录移动次数RMN为：" << rmn << endl;
}

// 归并操作函数，用于合并两个有序子表
void Merge(Herb arr[], int left, int mid, int right, int& kcn, int& rmn) {
    // left代表左子表的起始位置
    // mid代表左子表的结束位置
    // right代表右子表的结束位置
    int n1 = m - left + 1;//计算左子表的长度
    int n2 = right - m;//计算右子表的长度

    Herb* L = new Herb[n1];
    Herb* R = new Herb[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = arr[m + 1 + i];
    }

    int i = 0, j = 0, k = left;
    //比较两个临时数组L和R中的元素，将较小的元素依次放回原数组arr中
    while (i < n1 && j < n2) {
        kcn++;
        // 如果左子表当前元素的英文名小于等于右子表当前元素的英文名
        if (strcmp(L[i].sname, R[j].sname) <= 0) {
            arr[k] = L[i];
            i++;
        }
        // 如果右子表当前元素的英文名小于等于左子表当前元素的英文名 
        else {
            arr[k] = R[j];
            j++;
        }
        rmn++;
        k++;
    }
    // 如果左子表还有剩余元素，将其依次拷贝回原数组arr
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        rmn++;
    }
    // 如果右子表还有剩余元素，将其依次拷贝回原数组arr
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        rmn++;
    }

    delete[] L;
    delete[] R;
}

void MSort(Herb arr[], int left, int right, int& kcn, int& rmn) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        MSort(arr, left, mid, kcn, rmn);
        MSort(arr, mid + 1, right, kcn, rmn);
        Merge(arr, left, mid, right, kcn, rmn);
    }
}

void MergeSort(SqList& L, int& kcn, int& rmn) {
    //对顺序表做归并排序
    MSort(L.elem, 1, L.length, kcn, rmn);
    for (int i = 1; i <= L.length; i++) {
        cout << L.elem[i].sname << endl;
    }
    cout << "总的关键字比较次数KCN为：" << kcn << endl;
    cout << "总的记录移动次数RMN为：" << rmn;
}