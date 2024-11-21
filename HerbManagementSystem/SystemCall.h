#pragma once
#include "herb_data_structure.h"
#include "InfoManagement.h"
#include "InfoSearch.h"
#include "KMP.h"
#include "InfoSort.h"
#include "BuildMap.h"
#include "ComputeSimilarity.h"
#include "cluster.h"

void SystemCall();
void HerbADM();
void HerbSearch();
void HerbSort();
void HerbManagement();
void CreateKG();
void ClusterAndClassification();



void SeqSearch() {
    cout << "输入选择：" << endl;
    cout << "1. 基于顺序表的顺序查找" << endl;
    cout << "0. 返回" << endl;
    
    char choice;
    cin >> choice;
    if (choice == '0') {
        system("cls");
        HerbSearch();
    }
    else if (choice == '1') {
        SqList L;
        InitList(L);
        string originFilename = "D:/Data-241110/herb.txt";
        ReadFile(L, originFilename);
        getchar();
        char sname[100];
        cout << "请输入要查找的中草药英文名：";
        cin.getline(sname, 100);
        int pos = SeqSearch(L, sname);
        if (pos != -1) {
            system("cls");
            Print(L, pos);
            double ASL = GetASL(L);
            cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
        }
        else {
            cout << "查找失败" << endl;
        }
        FreeList(L);
        SeqSearch();
    }
    else {
        cout << "输入有误，请重新输入：" << endl;
        SeqSearch();
    }
}

void BinarySearch() {
    cout << "输入选择：" << endl;
    cout << "1. 基于顺序表的折半查找" << endl;
    cout << "0. 返回" << endl;
    
    char choice;
    cin >> choice;
    if (choice == '0') {
        system("cls");
        HerbSearch();
    }
    else if (choice == '1') {
        SqList L;
        InitList(L);
        string originFilename = "D:/Data-241110/herb.txt";
        ReadFile(L, originFilename);
        getchar();
        char sname[100];
        cout << "请输入要查找的中草药英文名：";
        cin.getline(sname, 100);
        int pos = SeqSearch(L, sname);
        if (pos != -1) {
            system("cls");
            Print(L, pos);
            double ASL = GetASLForBinary(L);
            cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
        }
        else {
            cout << "查找失败" << endl;
        }
        FreeList(L);
        BinarySearch();
    }
    else {
        cout << "输入有误，请重新输入：" << endl;
        BinarySearch();
    }
}

void SearchBST() {
    cout << "输入选择：" << endl;
    cout << "1. 基于二叉排序树的查找" << endl;
    cout << "0. 返回" << endl;

    char choice;
    cin >> choice;
    if (choice == '0') {
        system("cls");
        HerbSearch();
    }
    else if (choice == '1') {
        BSTree T = nullptr;
        InitBSTree(T);
        int count = 0;
        string originFilename = "D:/Data-241110/herb.txt";
        count = ReadFile(T, originFilename);
        getchar();
        char sname[100];
        cout << "请输入要查找的中草药英文名：";
        cin.getline(sname, 100);
        BSTNode* t = SearchBST(T, sname);
        if (t != nullptr) {
            system("cls");
            Print(t);
            double ASL = GetASL(T, count);
            cout << "ASL为：" << fixed << setprecision(2) << ASL;
        }
        else
            cout << "查找失败";
        SearchBST();
    }
    else {
        cout << "输入有误，请重新输入：" << endl;
        SearchBST();
    }

}

void TrieSearch() {
    cout << "输入选择：" << endl;
    cout << "1. 基于字典树的查找" << endl;
    cout << "0. 返回" << endl;

    char choice;
    cin >> choice;
    if (choice == '0') {
        system("cls");
        HerbSearch();
    }
    else if (choice == '1') {
        SqList L;
        InitList(L);
        string originFilename = "D:/Data-241110/herb.txt";
        ReadFile(L, originFilename);
        TNode* root = BuildTree(L);
        getchar();
        char* sname = new char[100];
        cout << "请输入要查找的中草药英文名：";
        cin.getline(sname, 100);
        Herb* herb = TrieSearch(root, sname);
        if (herb != nullptr) {
            system("cls");
            Print(herb);
            double ASL = GetASLForTrie(L);
            cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
        }
        else
            puts("查找失败");
        FreeList(L);
        TrieSearch();
    }
    else {
        cout << "输入有误，请重新输入：" << endl;
        TrieSearch();
    }
}

void SearchHash() {
    cout << "输入选择：" << endl;
    cout << "1. 基于开放地址法的散列查找" << endl;
    cout << "0. 返回" << endl;

    char choice;
    cin >> choice;
    if (choice == '0') {
        system("cls");
        HerbSearch();
    }
    else if (choice == '1') {
        HashTable HT;
        InitHT(HT);
        string filename = "D:/Data-241110/herb.txt";
        int sumCmp = 0; // 在插入的过程中统计比较次数，便于计算ASL
        ReadFile(HT, sumCmp, filename);
        getchar();
        char sname[100]; // 输入要查找的中药材英文名称
        cout << "请输入要查找的中草药英文名：";
        cin.getline(sname, 100);
        int pos = SearchHash(HT, sname);
        if (pos != -1) {
            system("cls");
            Print(HT, pos);
            double ASL = GetASL(HT, sumCmp);
            cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
        }
        else {
            cout << "查找失败" << endl;
        }
        SearchHash();
    }
    else {
        cout << "输入有误，请重新输入：" << endl;
        SearchHash();
    }
}

void SearchHL() {
    cout << "输入选择：" << endl;
    cout << "1. 基于链地址法的散列查找" << endl;
    cout << "0. 返回" << endl;

    char choice;
    cin >> choice;
    if (choice == '0') {
        system("cls");
        HerbSearch();
    }
    else if (choice == '1') {
        LinkList H[300];
        InitList(H);
        string filename = "D:/Data-241110/herb.txt";
        int count = 0;	// 记录中药材数据的总数
        int sumCmp = 0; // 在插入的过程中统计比较次数，便于计算ASL
        count = ReadFile(H, sumCmp, filename);
        getchar();
        char sname[100]; // 输入要查找的中药材英文名称
        cin.getline(sname, 100);
        int pos = SearchHL(H, sname);
        if (pos != -1) {
            LinkList p = H[pos]->next; // 查找成功，将p指向单链表头结点
            system("cls");
            Print(p, sname);
            double ASL = GetASL(sumCmp, count);
            cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
        }
        else {
            cout << "查找失败" << endl;
        }
        SearchHL();
    }
    else {
        cout << "输入有误，请重新输入：" << endl;
        SearchHL();
    }
}

void KMP() {
    cout << "输入选择：" << endl;;
    cout << "1. 基于KMP算法的中药材关键信息查询" << endl;
    cout << "0. 返回" << endl;

    char choice;
    cin >> choice;
    if (choice == '0') {
        system("cls");
        HerbManagement();
    }
    else if (choice == '1') {
        SqList L;
        InitList(L);
        ReadFile(L, "D:/Data-241110/herb.txt");
        getchar();
        char* keyword = new char[100];
        cout << "输入感兴趣的关键字：";
        cin.getline(keyword, 100);
        int next[10000];
        for (int i = 0; i < 10000; i++)
            next[i] = 0;
        GetNext(keyword, next);
        if (!SearchList(L, keyword, next))
            cout << "无匹配" << endl;
        FreeList(L);
        KMP();
    }
    else {
        cout << "输入有误，请重新输入：" << endl;
        KMP();
    }
}

void InsertSort() {
    cout << "输入选择：" << endl;
    cout << "1. 基于直接插入排序的中药材信息排序" << endl; 
    cout << "0. 返回" << endl;
    
    char choice;
    cin >> choice;
    if (choice == '0') {
        system("cls");
        HerbSort();
    }
    else if (choice == '1') {
        SqList L;
        InitList(L);
        string filename = "D:/Data-241110/herb.txt";
        ReadFile(L, filename);
        int kcn = 0;
        int rmn = 0;
        InsertSort(L, kcn, rmn);
        FreeList(L);
        InsertSort();
    }
    else {
        cout << "输入有误，请重新输入：" << endl;
        InsertSort();
    }
}

void BInsertSort() {
    cout << "输入选择：" << endl;
    cout << "1. 基于折半插入排序的中药材信息排序" << endl;
    cout << "0. 返回" << endl;

    char choice;
    cin >> choice;
    if (choice == '0') {
        system("cls");
        HerbSort();
    }
    else if (choice == '1') {
        SqList L;
        InitList(L);
        string filename = "D:/Data-241110/herb.txt";
        ReadFile(L, filename);
        int kcn = 0;
        int rmn = 0;
        BInsertSort(L, kcn, rmn);
        FreeList(L);
        BInsertSort();
    }
    else {
        cout << "输入有误，请重新输入：" << endl;
        BInsertSort();
    }
}

void BubbleSort() {
    cout << "输入选择：" << endl;
    cout << "1. 基于冒泡排序的中药材信息排序" << endl;
    cout << "0. 返回" << endl;

    char choice;
    cin >> choice;
    if (choice == '0') {
        system("cls");
        HerbSort();
    }
    else if (choice == '1') {
        SqList L;
        InitList(L);
        string filename = "D:/Data-241110/herb.txt";
        ReadFile(L, filename);
        int kcn = 0;
        int rmn = 0;
        BubbleSort(L, kcn, rmn);
        FreeList(L);
        BubbleSort();
    }
    else {
        cout << "输入有误，请重新输入：" << endl;
        BubbleSort();
    }
}

void MergeSort() {
    cout << "输入选择：" << endl;
    cout << "1. 基于归并排序的中药材信息排序" << endl;
    cout << "0. 返回" << endl;

    char choice;
    cin >> choice;
    if (choice == '0') {
        system("cls");
        HerbSort();
    }
    else if (choice == '1') {
        SqList L;
        InitList(L);
        string filename = "D:/Data-241110/herb.txt";
        ReadFile(L, filename);
        int kcn = 0;
        int rmn = 0;
        MergeSort(L, kcn, rmn);
        FreeList(L);
        MergeSort();
    }
    else {
        cout << "输入有误，请重新输入：" << endl;
        MergeSort();
    }
}

void QuickSort() {
    cout << "输入选择：" << endl;
    cout << "1. 基于快速排序的中药材信息排序" << endl;
    cout << "0. 返回" << endl;

    char choice;
    cin >> choice;
    if (choice == '0') {
        system("cls");
        HerbSort();
    }
    else if (choice == '1') {
        SqList L;
        InitList(L);
        string filename = "D:/Data-241110/herb.txt";
        ReadFile(L, filename);
        QuickSort(L);
        FreeList(L);
        QuickSort();
    }
    else {
        cout << "输入有误，请重新输入：" << endl;
        QuickSort();
    }
}

void computeSimilarity() {
    cout << "输入选择：" << endl;
    cout << "1. 基于散列表的相似中药材匹配" << endl;
    cout << "0. 返回" << endl;

    char choice;
    cin >> choice;
    if (choice == '0') {
        system("cls");
        HerbManagement();
    }
    else if (choice == '1') {
        HashTable_FV HT;
        InitHT(HT);
        string filename = "D:/Data-241110/herb.txt";
        ReadFile(HT, filename);
        getchar();
        char sname1[100], sname2[100];
        // 输入要查找的药材英文名称
        cout << "输入要查找的药材1英文名：";
        cin.getline(sname1, 100);
        cout << endl;
        cout << "输入要查找的药材2英文名：";
        cin.getline(sname2, 100);
        int p1 = SearchHash(HT, sname1), p2 = SearchHash(HT, sname2);
        if (p1 != -1 && p2 != -1) {
            Print(HT, p1);
            Print(HT, p2);
            computeSimilarity(HT, p1, p2);
        }

        else {
            cout << "匹配失败" << endl;
        }
        computeSimilarity();
    }
    else {
        cout << "输入有误，请重新输入：" << endl;
        computeSimilarity();
    }
}

void EntityRecognition() {
    cout << "输入选择：" << endl;
    cout << "1. 基于规则的实体识别" << endl;
    cout << "0. 返回" << endl;
    
    char choice;
    cin >> choice;
    if (choice == '0') {
        system("cls");
        CreateKG();
    }
    else if (choice == '1') {
        char* keyword = new char[100];
        char text[10000];
        getchar();
        cout << "请输入规则：";
        cin.getline(keyword, 100);
        cout << endl;
        cout << "请输入一段非结构化文本：" << endl;
        cin.getline(text, 10000);
        if (!EntityRecognition(text, keyword))
            cout << "无匹配" << endl;;
        EntityRecognition();
    }
    else {
        cout << "输入有误，请重新输入：" << endl;
        EntityRecognition();
    }
}

void RelationExtraction() {
    cout << "输入选择：" << endl;
    cout << "1. 基于规则的关系抽取" << endl;
    cout << "0. 返回" << endl;
    
    char choice;
    cin >> choice;
    if (choice == '0') {
        system("cls");
        CreateKG();
    }
    else if (choice == '1') {
        char* entity1 = new char[100];
        char* entity2 = new char[100];
        char text[10000];
        Relation* r = new Relation[10];;
        InitRelation(r);
        getchar();
        cout << "请输入第一个实体：";
        cin.getline(entity1, 100);
        cout << endl;
        cout << "请输入第二个实体：";
        cin.getline(entity2, 100);
        cout << endl;
        cout << "请输入一段非结构化文本：";
        cin.getline(text, 10000);
        if (!RelationExtraction(text, entity1, entity2, r))
            cout << "实体之间不存在关系" << endl;
        RelationExtraction();
    }
    else {
        cout << "输入有误，请重新输入：" << endl;
        RelationExtraction();
    }
}

void CreateUDG() {
    cout << "输入选择：" << endl;
    cout << "1. 基于邻接表的知识图谱构建" << endl;
    cout << "0. 返回" << endl;

    char choice;
    cin >> choice;
    if (choice == '0') {
        system("cls");
        CreateKG();
    }
    else if (choice == '1') {
        ALGraph G;
        InitALGraph(G);
        CreateAdjList(G, "D:/Data-241110/entity.txt");
        CreateUDG(G, "D:/Data-241110/relation.txt");
        PrintGraph(G);
        CreateUDG();
    }
    else {
        cout << "输入有误，请重新输入：" << endl;
        CreateUDG();
    }
}

void QuestionAnswering() {
    
    cout << "输入选择：" << endl;
    cout << "1. 基于路径推理的知识图谱多跳问答" << endl;
    cout << "0. 返回" << endl;

    char choice;
    cin >> choice;
    if (choice == '0') {
        system("cls");
        CreateKG();
    }
    else if (choice == '1') {
        ALGraph G;
        InitALGraph(G);
        CreateAdjList(G, "D:/Data-241110/entity.txt");
        CreateUDG(G, "D:/Data-241110/relation.txt");
        string entityToSearch;
        cout << "请输入一个中药材信息：";
        cin >> entityToSearch;
        SearchHerbsByEntity(G, entityToSearch);
    }
    else {
        cout << "输入有误，请重新输入：" << endl;
        QuestionAnswering();
    }
}

void hierarchicalClustering() {
    cout << "输入选择：" << endl;
    cout << "1. 基于树结构的层次聚类分析" << endl;
    cout << "0. 返回" << endl;
    char choiceD;
    cin >> choiceD;
    if (choiceD == '0') {
        ClusterAndClassification();
    }
    else if (choiceD == '1') {
        string words[MAX_WORDS];
        int wordCount = 0;

        getchar();
        readWordsFromFile("D:/Data-241110/clusterData.txt", words, wordCount);

        // Define a threshold
        int threshold = 8; //预设的距离阈值，这个值可以改变聚类树的层次结构
        getchar();
        cout << "输入你想设置的距离阈值：（默认为8）" << endl;
        cin >> threshold;
        hierarchicalClustering(words, wordCount, threshold);
        hierarchicalClustering();
    }
    else {
        cout << "输入有误，请重新输插入：" << endl;
        hierarchicalClustering();
    }
}

void detectCommunities() {
    cout << "输入选择：" << endl;
    cout << "1. 基于图结构的社团检测聚类分析" << endl;
    cout << "0. 返回" << endl;
    char choiceD;
    cin >> choiceD;
    if (choiceD == '0') {
        ClusterAndClassification();
    }
    else if (choiceD == '1') {
        ALGraphC graph;

        string words[MAX_WORDS];
        int wordCount = 0;

        getchar();
        readWordsFromFile("D:/Data-241110/clusterData.txt", words, wordCount);

        createGraph(&graph, words, wordCount);
        detectCommunities(&graph);

        detectCommunities();
    }
    else {
        cout << "输入有误，请重新输插入：" << endl;
        detectCommunities();
    }
}

void PrimMST() {
    cout << "输入选择：" << endl;
    cout << "1. 基于最小生成树的变色龙聚类分析" << endl;
    cout << "0. 返回" << endl;
    char choiceD;
    cin >> choiceD;
    if (choiceD == '0') {
        ClusterAndClassification();
    }
    else if (choiceD == '1') {
        AMGraph G;
        string words[MAX_WORDS];
        int wordCount = 0;
        getchar();
        // 从文件读取词语
        readWordsFromFile("D:/Data-241110/clusterData.txt", words, wordCount);
        // 构建距离矩阵（完全图）从words中读取数据
        buildDistanceMatrix(G, words, wordCount);
        // 使用Prim算法构建最小生成树
        PrimMST(G);
        // 计算所有边距离并存储
        Edge edges[MAX_WORDS * MAX_WORDS];
        int edgeCount = calculateEdges(G, edges);
        // 对边按距离进行降序排序
        sortEdgesDescending(edges, edgeCount);
        // 删除最大距离的k-1条边
        removeLargestEdges(G, edges, K);
        // 输出聚类结果
        outputClusters(G);

        cout << "输出完毕，返回上一层：" << endl;
        ClusterAndClassification();
    }
    else {
        cout << "输入有误，请重新输入：" << endl;
        PrimMST();
    }
}

void createDecisionTree() {
    cout << "输入选择：" << endl;
    cout << "1. 基于决策树的分类分析" << endl;
    cout << "0. 退回上一步" << endl;
    char choiceD;
    cin >> choiceD;
    if (choiceD == '0') {
        ClusterAndClassification();
    }
    else if (choiceD == '1') {
        SqList L;
        InitList(L);
        string originFilename = "D:/Data-241110/herb.txt";
        ReadFile(L, originFilename);

        BiTreeDIS BT;
        InitTree(BT);

        createDecisionTreeDIS(BT, L);

        getchar();
        string herbName;
        cin >> herbName;

        FindClassDIS(BT, herbName);

        FreeList(L);
        createDecisionTree();
    }
    else {
        cout << "输入有误，请重新输入：" << endl;
        createDecisionTree();
    }
}

void HerbADM() {
    SqList L;
    OperationStack stack;

    // 初始化线性表和操作栈
    InitList(L);
    InitStack(stack);

    string originFilename = "D:/Data-241110/herb.txt";
    string newFilename = "D:/Data-241110/new_herb.txt";

    while (true) {
        cout << "输入选择：" << endl;
        cout << "1. 中草药信息增加" << endl;
        cout << "2. 中草药信息删除" << endl;
        cout << "3. 中草药信息修改" << endl;
        cout << "4. 撤销上次操作" << endl;
        cout << "0. 返回" << endl;

        char choice;
        cin >> choice;

        if (choice == '0') {
            system("cls");
            HerbManagement();
            break;
        }

        // 只需要在操作完成时保存到文件
        ReadFile(L, originFilename);
        switch (choice) {
        case '1':
            if (InsertHerb(L, stack)) {
                SaveFile(L, newFilename);
                Print(L);
            }
            else {
                cout << "增加失败" << endl;
            }
            break;
        case '2':
            char name[100];
            cout << "请输入要删除的中草药名称：";
            cin >> name;
            if (DeleteHerb(L, name, stack)) {
                SaveFile(L, newFilename);
                cout << "删除成功" << endl;
            }
            else {
                cout << "删除失败" << endl;
            }
            break;
        case '3': {
            char name_to_modi[100];
            int n;
            cout << "请输入要修改的药草名称：";
            cin >> name_to_modi;
            cout << "请输入归经数量：";
            cin >> n;

            // 限制输入归经数量
            if (n <= 0 || n > 6) {
                cout << "输入无效，请输入1-6之间的数字！" << endl;
                continue;
            }
            vector<string> lines(n);
            for (int i = 0; i < n; i++) {
                cout << "请输入第" << i + 1 << "个归经：" << endl;
                cin >> lines[i];
            }
            if (ModifyHerb(L, name_to_modi, lines.data(), n, stack)) {
                SaveFile(L, newFilename);
                cout << "修改成功" << endl;
            }
            else {
                cout << "修改失败" << endl;
            }
            break;
        }
        case '4':
            if (Undo(L, stack)) {
                SaveFile(L, newFilename);
            }
            else {
                cout << "没有可以撤销的操作！" << endl;
            }
            break;
        default:
            cout << "输入有误，请重新输入！" << endl;
        }
    }

    // 程序结束时释放资源
    FreeList(L);
}

void HerbSearch() {
    // 基于多种查找策略的中药材信息查找模块，调用对应的功能函数实现
    int totalLength = 50;
    int equalSignsOnEachSide = (totalLength - 42) / 2;


    for (int i = 0; i < totalLength; ++i) {
        cout << "=";
    }
    cout << endl;

    cout << string(equalSignsOnEachSide, '=') << "=  1. 基于顺序表的顺序查找             =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  2. 基于顺序表的折半查找             =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  3. 基于二叉排序树的查找             =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  4. 基于字典树的查找                 =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  5. 基于开放地址法的散列查找         =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  6. 基于链地址法的散列查找           =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  0. 返回                             =" << string(equalSignsOnEachSide, '=') << endl;

    for (int i = 0; i < totalLength; ++i) {
        cout << "=";
    }
    cout << endl;

    char choice;
    cout << "请输入你的选择：";
    cin >> choice;

    switch (choice) {
    case '1':
        system("cls");
        cout << string(equalSignsOnEachSide, '=') << "=     基于顺序表的顺序查找             =" << string(equalSignsOnEachSide, '=') << endl;
        SeqSearch();
        break;
    case '2':
        system("cls");
        cout << string(equalSignsOnEachSide, '=') << "=     基于顺序表的折半查找             =" << string(equalSignsOnEachSide, '=') << endl;
        BinarySearch();
        break;
    case '3':
        system("cls");
        cout << string(equalSignsOnEachSide, '=') << "=     基于二叉排序树的查找             =" << string(equalSignsOnEachSide, '=') << endl;
        SearchBST();
        break;
    case '4':
        system("cls");
        cout << string(equalSignsOnEachSide, '=') << "=       基于字典树的查找               =" << string(equalSignsOnEachSide, '=') << endl;
        TrieSearch();
        break;
    case '5':
        system("cls");
        cout << string(equalSignsOnEachSide, '=') << "=   基于开放地址法的散列查找           =" << string(equalSignsOnEachSide, '=') << endl;
        SearchHash();
        break;
    case '6':
        system("cls");
        cout << string(equalSignsOnEachSide, '=') << "=     基于链地址法的散列查找           =" << string(equalSignsOnEachSide, '=') << endl;
        SearchHL();
        break;
    case '0':
        system("cls");
        HerbManagement();
        break;
    default:
        cout << "输入错误，请重新输入：" << endl;
        HerbSearch();
        break;
    }
}

void HerbSort() {
    // 基于多种排序策略的中药材信息排序模块，调用对应的功能函数实现
    int totalLength = 50;
    int equalSignsOnEachSide = (totalLength - 42) / 2;


    for (int i = 0; i < totalLength; ++i) {
        cout << "=";
    }
    cout << endl;

    cout << string(equalSignsOnEachSide, '=') << "=  1. 直接插入排序                     =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  2. 折半插入排序                     =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  3. 冒泡排序                         =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  4. 归并排序                         =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  5. 快速排序                         =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  0. 返回                             =" << string(equalSignsOnEachSide, '=') << endl;

    for (int i = 0; i < totalLength; ++i) {
        cout << "=";
    }
    cout << endl;

    char choice;
    cout << "请输入你的选择：";
    cin >> choice;

    switch (choice) {
    case '1':
        system("cls");
        cout << string(equalSignsOnEachSide, '=') << "=            直接插入排序              =" << string(equalSignsOnEachSide, '=') << endl;
        InsertSort();
        break;
    case '2':
        system("cls");
        cout << string(equalSignsOnEachSide, '=') << "=            折半插入排序              =" << string(equalSignsOnEachSide, '=') << endl;
        BInsertSort();
        break;
    case '3':
        system("cls");
        cout << string(equalSignsOnEachSide, '=') << "=             冒泡排序                 =" << string(equalSignsOnEachSide, '=') << endl;
        cout << "冒泡排序" << endl;
        BubbleSort();
        break;
    case '4':
        system("cls");
        cout << string(equalSignsOnEachSide, '=') << "=             归并排序                 =" << string(equalSignsOnEachSide, '=') << endl;
        MergeSort();
        break;
    case '5':
        system("cls");
        cout << string(equalSignsOnEachSide, '=') << "=             快速排序                 =" << string(equalSignsOnEachSide, '=') << endl;
        QuickSort();
        break;
    case '0':
        system("cls");
        HerbManagement();
        break;
    default:
        cout << "输入错误，请重新输入：" << endl;
        HerbSort();
        break;
    }
}

void HerbManagement() {
    // 中药材基本信息管理模块
    int totalLength = 50;
    int equalSignsOnEachSide = (totalLength - 42) / 2;


    for (int i = 0; i < totalLength; ++i) {
        cout << "=";
    }
    cout << endl;

    cout << string(equalSignsOnEachSide, '=') << "=  1. 中药材基本信息的增加、删除与修改 =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  2. 基于多种查找策略的中药材信息查找 =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  3. 基于KMP算法的中药材关键信息查询  =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  4. 基于多种排序策略的中药材信息排序 =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  5. 基于散列表的相似中药材匹配       =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  0. 返回                             =" << string(equalSignsOnEachSide, '=') << endl;
    
    for (int i = 0; i < totalLength; ++i) {
        cout << "=";
    }
    cout << endl;

    char choice;
    cout << "请输入你的选择：";
    cin >> choice;
    switch (choice) {
    case '1':
        system("cls");
        cout << string(equalSignsOnEachSide, '=') << "=   中药材基本信息的增加、删除与修改   =" << string(equalSignsOnEachSide, '=') << endl;
        HerbADM();
        break;
    case '2':
        system("cls");
        cout << string(equalSignsOnEachSide, '=') << "=   基于多种查找策略的中药材信息查找   =" << string(equalSignsOnEachSide, '=') << endl;
        HerbSearch();
        break;
    case '3':
        system("cls");
        cout << string(equalSignsOnEachSide, '=') << "=   基于KMP算法的中药材关键信息查询    =" << string(equalSignsOnEachSide, '=') << endl;
        KMP();
        break;
    case '4':
        system("cls");
        cout << string(equalSignsOnEachSide, '=') << "=   基于多种排序策略的中药材信息排序   =" << string(equalSignsOnEachSide, '=') << endl;
        HerbSort();
        break;
    case '5':
        system("cls");
        cout << string(equalSignsOnEachSide, '=') << "=      基于散列表的相似中药材匹配      =" << string(equalSignsOnEachSide, '=') << endl;
        computeSimilarity();
        break;
    case '0':
        system("cls");
        SystemCall();
        break;
    default:
        cout << "输入错误，请重新输入：" << endl;
        HerbManagement();
        break;
    }
}

void CreateKG() {
    int totalLength = 50;
    int equalSignsOnEachSide = (totalLength - 42) / 2;


    for (int i = 0; i < totalLength; ++i) {
        cout << "=";
    }
    cout << endl;

    cout << string(equalSignsOnEachSide, '=') << "=  1. 基于规则的实体识别               =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  2. 基于规则的关系抽取               =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  3. 基于邻接表的知识图谱构建         =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  4. 基于路径推理的知识图谱多跳问答   =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  0. 返回                             =" << string(equalSignsOnEachSide, '=') << endl;

    for (int i = 0; i < totalLength; ++i) {
        cout << "=";
    }
    cout << endl;

    char choice;
    cout << "请输入你的选择：";
    cin >> choice;

    switch (choice) {
    case '1':
        system("cls");
        cout << string(equalSignsOnEachSide, '=') << "=          基于规则的实体识别          =" << string(equalSignsOnEachSide, '=') << endl;
        EntityRecognition();
        break;
    case '2':
        system("cls");
        cout << string(equalSignsOnEachSide, '=') << "=          基于规则的关系抽取          =" << string(equalSignsOnEachSide, '=') << endl;
        cout << "基于规则的关系抽取" << endl;
        RelationExtraction();
        break;
    case '3':
        system("cls");
        cout << string(equalSignsOnEachSide, '=') << "=        基于邻接表的知识图谱构建      =" << string(equalSignsOnEachSide, '=') << endl;
        CreateUDG();
        break;
    case '4':
        system("cls");
        cout << string(equalSignsOnEachSide, '=') << "=    基于路径推理的知识图谱多跳问答    =" << string(equalSignsOnEachSide, '=') << endl;
        QuestionAnswering();
        break;
    case '0':
        system("cls");
        SystemCall();
        break;
    default:
        cout << "输入错误，请重新输入：" << endl;
        CreateKG();
        break;
    }
}

void ClusterAndClassification() {
    // 林草中药材模块，调用对应的功能函数实现
    int totalLength = 50;
    int equalSignsOnEachSide = (totalLength - 42) / 2;


    for (int i = 0; i < totalLength; ++i) {
        cout << "=";
    }
    cout << endl;

    cout << string(equalSignsOnEachSide, '=') << "=  1. 基于树结构的层次聚类分析         =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  2. 基于图结构的社团检测聚类分析     =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  3. 基于最小生成树的变色龙聚类分析   =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  4. 基于决策树的分类分析             =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  0. 返回                             =" << string(equalSignsOnEachSide, '=') << endl;

    for (int i = 0; i < totalLength; ++i) {
        cout << "=";
    }
    cout << endl;

    char choice;
    cout << "请输入你的选择：";
    cin >> choice;

    switch (choice) {
    case '1':
        system("cls");
        cout << "基于树结构的层次聚类分析" << endl;
        hierarchicalClustering();
        break;
    case '2':
        system("cls");
        cout << "基于图结构的社团检测聚类分析" << endl;
        detectCommunities();
        break;
    case '3':
        system("cls");
        cout << "基于最小生成树的变色龙聚类分析" << endl;
        PrimMST();
        break;
    case '4':
        system("cls");
        cout << "基于决策树的分类分析" << endl;
        createDecisionTree();
        break;
    case '0':
        system("cls");
        SystemCall();
        break;
    default:
        cout << "输入错误，请重新输入：" << endl;
        ClusterAndClassification();
        break;
    }
}

void SystemCall() {
    string menuTitle = "基于知识图谱的林草中药材数据管理与应用系统";
    int titleLength = menuTitle.length();
    int totalLength = 50;

    // 计算左右两侧等号的数量，确保标题居中
    int equalSignsOnEachSide = (totalLength - titleLength) / 2;

    // 输出顶部装饰行
    for (int i = 0; i < totalLength; ++i) {
        cout << "=";
    }
    cout << endl;

    // 输出标题，居中显示
    cout << string(equalSignsOnEachSide, '=') << menuTitle << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  1. 林草中药材基本信息管理      =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  2. 林草中药材知识图谱构建及应用=" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  3. 林草中药材聚类与分类分析    =" << string(equalSignsOnEachSide, '=') << endl;
    cout << string(equalSignsOnEachSide, '=') << "=  0. 退出系统                    =" << string(equalSignsOnEachSide, '=') << endl;
    for (int i = 0; i < totalLength; ++i) {
        cout << "=";
    }
    cout << endl;
    char choice;
    cout << "请输入你的选择：";
    cin >> choice;

    switch (choice) {
    case '1':
        system("cls");
        cout << string(equalSignsOnEachSide, '=') << "=        林草中药材基本信息管理        =" << string(equalSignsOnEachSide, '=') << endl;
        HerbManagement();
        break;
    case '2':
        system("cls");
        cout << string(equalSignsOnEachSide, '=') << "=     林草中药材知识图谱构建及应用     =" << string(equalSignsOnEachSide, '=') << endl;
        CreateKG();
        break;
    case '3':
        system("cls");
        cout << string(equalSignsOnEachSide, '=') << "=       林草中药材聚类与分类分析       =" << string(equalSignsOnEachSide, '=') << endl;
        ClusterAndClassification();
        break;
    case '0':
        system("cls");
        cout << "退出系统" << endl;
        break;
    default:
        cout << "输入错误，请重新输入：" << endl;
        SystemCall();
        break;
    }
}
