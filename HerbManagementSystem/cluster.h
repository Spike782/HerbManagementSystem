#pragma once
#include "herb_data_structure.h"
#define MAX_WORDS 300
#define OK 1
#define MAX_DIST 8 

typedef struct BiTNodeHEIGHT {
    string data;
    struct BiTNodeHEIGHT* lchild, * rchild;
    int height; //  表示结点合并时的距离，叶子结点无需合并，新建时可设为0
} BiTNodeHEIGHT, * BiTreeHEIGHT;

typedef struct ArcNodeC {
    int adjvex;
    struct ArcNodeC* nextarc;
} ArcNodeC;

typedef struct VNodeC {
    string word;
    ArcNodeC* firstarc;
} VNodeC, AdjListC[MAX_WORDS];

typedef struct {
    AdjListC vertices;
    int vexnum, arcnum;
} ALGraphC;

// 计算编辑距离
int editDistance(string s1, string s2) {
    int k = s1.length();
    int n = s2.length();
    vector<vector<int>> dp(k + 1, vector<int>(n + 1));
    for (int i = 0; i <= k; i++)
        dp[i][0] = i;
    for (int j = 0; j <= n; j++)
        dp[0][j] = j;
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;
        }
    }
    return dp[k][n];
}

BiTreeHEIGHT newTreeNode(string data, int height) {
    // 新建一个树结点，两个结点A、B合并成一个新结点C，height是合并时A、B两个结点间的距离
    BiTreeHEIGHT node = new BiTNodeHEIGHT;
    node->data = data;
    node->lchild = nullptr;
    node->rchild = nullptr;
    node->height = height;
    return node;
}

void findClosestPair(int distMatrix[MAX_WORDS][MAX_WORDS], int wordCount, int* minDist, int* a, int* b) {
    // 找出距离矩阵中距离最近的两个结点位置，分别赋值给a、b （如果距离相同，则取相对位置靠前的）
    *minDist = INT_MAX;
    for (int i = 0; i < wordCount; i++) {
        for (int j = i + 1; j < wordCount; j++) {
            if (distMatrix[i][j] < *minDist) {
                *minDist = distMatrix[i][j];
                *a = i;
                *b = j;
            }
        }
    }
}

void updateDistanceMatrix(int distMatrix[MAX_WORDS][MAX_WORDS], int wordCount, int a, int b) {
    // 更新距离矩阵
        // 遍历距离矩阵的每一行
    for (int i = 0; i < wordCount; i++) {
        // 如果当前行与节点a对应的列的距离为INT_MAX，说明该节点i已经被合并过了，跳过本次循环，继续下一个节点的处理
        if (distMatrix[i][a] == INT_MAX) {
            continue;
        }

        // 计算节点a与节点i的新距离，取节点a与节点i的原距离和节点b与节点i的原距离的平均值
        distMatrix[a][i] = (distMatrix[a][i] + distMatrix[b][i]) / 2;

        // 由于距离矩阵是对称的，所以也要更新节点i与节点a的距离，使其与节点a与节点i的距离相等
        distMatrix[i][a] = distMatrix[a][i];
    }

    // 将节点a到自身的距离设置为INT_MAX，表示该节点已经被合并，自身到自身的距离在当前情境下可视为无穷大
    distMatrix[a][a] = INT_MAX;

    // 遍历距离矩阵的每一行，将节点b与其他所有节点（包括自身）的距离都设置为INT_MAX
    // 这表示节点b已经被合并，与其他节点的距离不再具有实际意义，可视为无穷大
    for (int i = 0; i < wordCount; i++) {
        distMatrix[b][i] = INT_MAX;
        distMatrix[i][b] = INT_MAX;
    }
}

void printCluster(BiTreeHEIGHT tree) {
    // 先序遍历输出树
    if (tree) {
        cout << tree->data << " ";
        printCluster(tree->lchild);
        printCluster(tree->rchild);
    }
}

void cutTree(BiTreeHEIGHT tree, int threshold) {
    //先序遍历切割树，threshold是预设的距离阈值
    //可参考如下方法：“切割”并不是要将tree切割成多棵二叉树。而是要根据结点的height与threshold比较，确定聚类群组的根节点，得到对应的聚类结果
    if (tree) {
        if (tree->height <= threshold) {
            cout << "Cluster: ";
            printCluster(tree);
            cout << endl;
        }
        else {
            cutTree(tree->lchild, threshold);
            cutTree(tree->rchild, threshold);
        }
    }
}

void hierarchicalClustering(string words[MAX_WORDS], int wordCount, int threshold) {
    // 层次聚类，wordCount是结点的总个数
    // 合并两个结点时，将距离矩阵中相对位置靠前的结点作为新结点的左孩子，靠后的结点作为新结点的右孩子
    int distMatrix[MAX_WORDS][MAX_WORDS];
    BiTreeHEIGHT trees[MAX_WORDS];

    for (int i = 0; i < wordCount; i++) {
        trees[i] = newTreeNode(words[i], 0);
        for (int j = 0; j < wordCount; j++) {
            if (i == j) {
                distMatrix[i][j] = INT_MAX;
            }
            else {
                distMatrix[i][j] = editDistance(words[i], words[j]);
            }
        }
    }

    //迭代合并，直至所有结点合并成一颗树
    //结点两两合并，共进行wordCount - 1次合并
    int count = wordCount - 1;
    int minDist, a, b;
    for (int i = 0; i < count; i++) {
        findClosestPair(distMatrix, wordCount, &minDist, &a, &b);
        //找到距离最近的两个节点a和b后，合并成新节点c，并更新距离矩阵
        //生成合并节点，在wordcount 位置暂时储存
        trees[wordCount] = newTreeNode("", minDist);
        trees[wordCount]->lchild = trees[a];
        trees[wordCount]->rchild = trees[b];
        updateDistanceMatrix(distMatrix, wordCount, a, b);
        trees[a] = trees[wordCount];
    }
    //聚类树构建完成后，进行切割，得到聚类结果
    cutTree(trees[0], threshold);

}

void readWordsFromFile(const string& filename, string words[MAX_WORDS], int& wordCount) {
    //读取文本文件，将所有结点存入words数组，计算wordCount为结点的总个数
    //若读取的元素word中含有换行符，可用word.erase(word.find_last_not_of(" \n\r\t") + 1)去掉 (word类型为string）
    wordCount = 0;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line) && wordCount < MAX_WORDS) {
            // 去除行首尾的空白字符（包括换行符、空格等）
            line.erase(line.find_last_not_of(" \n\r\t") + 1);
            line.erase(0, line.find_first_not_of(" \n\r\t"));

            // 跳过空行
            if (line.empty()) {
                continue;
            }

            words[wordCount++] = line;
        }
        file.close();
    }
}

void insertArcNode(VNodeC* vnode, int adjvex) {
    // 插入边
    ArcNodeC* newArc = new ArcNodeC;
    newArc->adjvex = adjvex;
    newArc->nextarc = vnode->firstarc;
    vnode->firstarc = newArc;
}

int createGraph(ALGraphC* graph, string words[MAX_WORDS], int wordCount) {
    // 创建图
    graph->vexnum = wordCount;
    graph->arcnum = 0;
    for (int i = 0; i < wordCount; i++) {
        graph->vertices[i].word = words[i];
        graph->vertices[i].firstarc = nullptr;
    }

    int distMatrix[MAX_WORDS][MAX_WORDS]; //定义距离矩阵
    for (int i = 0; i < wordCount; i++) {
        for (int j = 0; j < wordCount; j++) {
            if (i == j) distMatrix[i][j] = INT_MAX;
            else distMatrix[i][j] = editDistance(words[i], words[j]);
        }
    }

    //遍历矩阵，若两个结点间的距离小于预设的阈值，则判定这两个结点属于同一社团，并在图中为这两个结点添加一条边
    //因为是对称矩阵，只需遍历矩阵上半部分，就可以创建所有边
    for (int i = 0; i < wordCount; i++) {
        for (int j = i + 1; j < wordCount; j++) {
            if (distMatrix[i][j] < MAX_DIST) { //小于预设阈值，则给两个节点加边
                insertArcNode(&(graph->vertices[i]), j);
                insertArcNode(&(graph->vertices[j]), i);
                graph->arcnum++;
            }
        }
    }
    return OK;
}

void DFS(ALGraphC* graph, int v, int visited[], int component[], int compID) {
    // 深度优先搜索，v是结点在顶点表中的下标，component用来标记结点所属的社团，compID表示社团的编号
    visited[v] = 1;
    component[v] = compID;

    ArcNodeC* p = graph->vertices[v].firstarc;
    while (p != nullptr) {
        if (!visited[p->adjvex]) {
            DFS(graph, p->adjvex, visited, component, compID);
        }
        p = p->nextarc;
    }
}

void detectCommunities(ALGraphC* graph) {
    // 检测社团
    int visited[MAX_WORDS];
    int component[MAX_WORDS];
    int compID = 0;

    memset(visited, 0, sizeof(visited));
    memset(component, 0, sizeof(component));

    for (int i = 0; i < graph->vexnum; i++) {
        if (!visited[i]) {
            DFS(graph, i, visited, component, compID);
            compID++;
        }
    }

    // 输出社团信息
    for (int i = 0; i < compID; i++) {
        cout << "Community " << i << ": ";
        for (int j = 0; j < graph->vexnum; j++) {
            if (component[j] == i) {
                cout << graph->vertices[j].word << " ";
            }
        }
        cout << endl;
    }
}

// 图的邻接矩阵存储表示
typedef struct {
    string vexs[MAX_WORDS];    // 顶点表
    int arcs[MAX_WORDS][MAX_WORDS];    // 邻接矩阵
    int vexnum, arcnum;     // 图的当前点数和边数
} AMGraph;
// 边的存储表示
struct Edge {
    int u, v, weight;
};


void buildDistanceMatrix(AMGraph& G, const string words[], int wordCount) {
    // 构建距离矩阵（完全图）
    G.vexnum = wordCount;
    for (int i = 0; i < wordCount; i++) {
        G.vexs[i] = words[i];
        for (int j = 0; j < wordCount; j++) {
            if (i == j)
                G.arcs[i][j] = 0;
            else
                G.arcs[i][j] = editDistance(words[i], words[j]);
        }
    }
    G.arcnum = wordCount * (wordCount - 1) / 2;
}

void PrimMST(AMGraph& G) {
    // 使用Prim算法构建最小生成树，起始结点为顶点表中的第一个结点
    int n = G.vexnum;
    int parent[MAX_WORDS];
    int key[MAX_WORDS];
    bool mstSet[MAX_WORDS];

    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < n - 1; count++) {
        int minKey = INT_MAX;
        int minIndex = 0;

        for (int v = 0; v < n; v++) {
            if (!mstSet[v] && key[v] < minKey) {
                minKey = key[v];
                minIndex = v;
            }
        }

        mstSet[minIndex] = true;

        for (int v = 0; v < n; v++) {
            if (!mstSet[v] && G.arcs[minIndex][v] && G.arcs[minIndex][v] < key[v]) {
                parent[v] = minIndex;
                key[v] = G.arcs[minIndex][v];
            }
        }
    }

    // 更新图的邻接矩阵为最小生成树的邻接矩阵
    G.arcnum = n - 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (parent[i] == j || parent[j] == i)
                G.arcs[i][j] = G.arcs[j][i] = editDistance(G.vexs[i], G.vexs[j]);
            else
                G.arcs[i][j] = G.arcs[j][i] = 0;
        }
    }
}

int calculateEdges(AMGraph& G, Edge edges[]) {
    // 计算所有边距离并存储
    int edgeCount = 0;
    for (int i = 0; i < G.vexnum; i++) {
        for (int j = i + 1; j < G.vexnum; j++) {
            if (G.arcs[i][j]) {
                edges[edgeCount].u = i;
                edges[edgeCount].v = j;
                edges[edgeCount].weight = G.arcs[i][j];
                edgeCount++;
            }
        }
    }
    return edgeCount;
}

void sortEdgesDescending(Edge edges[], int edgeCount) {
    // 对边按距离进行降序排序
    sort(edges, edges + edgeCount, [](const Edge& a, const Edge& b) {
        return a.weight > b.weight;
        });
}

void removeLargestEdges(AMGraph& G, Edge edges[], int k) {
    // 删除最大距离的k-1条边
    int edgeCount = calculateEdges(G, edges);
    sortEdgesDescending(edges, edgeCount);

    for (int i = 0; i < k - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        G.arcs[u][v] = G.arcs[v][u] = 0;
    }

    G.arcnum -= k - 1;
}

void DFS(AMGraph& G, int v, bool visited[]) {
    // DFS遍历图，v是顶点在顶点表中的下标
    visited[v] = true;
    cout << G.vexs[v] << " ";

    for (int i = 0; i < G.vexnum; i++) {
        if (G.arcs[v][i] && !visited[i])
            DFS(G, i, visited);
    }
}

void outputClusters(AMGraph& G) {
    // 调用DFS函数输出聚类结果
    bool visited[MAX_WORDS];
    memset(visited, false, sizeof(visited));

    for (int i = 0; i < G.vexnum; i++) {
        if (!visited[i]) {
            cout << "cluster: ";
            DFS(G, i, visited);
            cout << endl;
        }
    }
}

typedef struct BiTNodeDIS {
    Herb data;
    struct BiTNodeDIS* lchild, * rchild;
    string disition; //决策条件，只有决策条件结点有内容,中草药结点可设置为""
} BiTNodeDIS, * BiTreeDIS;

void InitTree(BiTreeDIS& BT)
{// 初始化二叉树
    BT = new BiTNodeDIS; BT->lchild = NULL; BT->rchild = NULL;
    BiTreeDIS b1 = new BiTNodeDIS; b1->disition = "采收加工不为暂无"; b1->lchild = NULL; b1->rchild = NULL;
    BiTreeDIS b2 = new BiTNodeDIS; b2->disition = "采收加工为暂无"; b2->lchild = NULL; b2->rchild = NULL;
    BiTreeDIS b3 = new BiTNodeDIS; b3->disition = "归经数量大于等于3"; b3->lchild = NULL; b3->rchild = NULL;
    BiTreeDIS b4 = new BiTNodeDIS; b4->disition = "归经数量小于3"; b4->lchild = NULL; b4->rchild = NULL;
    BiTreeDIS b5 = new BiTNodeDIS; b5->disition = "归经含有胃"; b5->lchild = NULL; b5->rchild = NULL;
    BiTreeDIS b6 = new BiTNodeDIS; b6->disition = "归经不含有胃"; b6->lchild = NULL; b6->rchild = NULL;
    BT->lchild = b1;
    BT->rchild = b2;
    b1->lchild = b3;
    b1->rchild = b4;
    b3->lchild = b5;
    b3->rchild = b6;
}

void insertNodeToTreeDIS(BiTreeDIS& root, BiTreeDIS& node) {
    // 结点插入二叉树
    while (root->lchild != NULL && root->rchild != NULL) root = root->lchild;

    //右子树存herb,左子树存temp
    root->rchild = node;
    BiTNodeDIS* temp = new BiTNodeDIS;
    temp->disition = "";
    temp->lchild = temp->rchild = NULL;
    root->lchild = temp;
}

void createDecisionTreeDIS(BiTreeDIS& BT, SqList L) {
    //构建决策树，并使用二叉树结构存储
    for (int i = 1; i <= L.length; i++) {
        BiTNodeDIS* node = new BiTNodeDIS; // 创建新草药结点
        node->data = L.elem[i];
        node->disition = "";
        node->lchild = node->rchild = NULL;

        BiTreeDIS current = BT; // 从根结点开始遍历

        // 判断“采收加工不为暂无”
        if (strcmp(node->data.harvesting, "暂无。") != 0) {
            current = current->lchild; // 采收加工不为暂无 -> 左孩子
        }
        else {
            current = current->rchild; // 采收加工为暂无 -> 右孩子
            insertNodeToTreeDIS(current, node); // 插入到右子树
            continue;
        }

        // 判断“归经数量大于等于3”
        if (node->data.channel_tropism_num >= 3) {
            current = current->lchild; // 归经数量>=3 -> 左孩子
        }
        else {
            current = current->rchild; // 归经数量<3 -> 右孩子
            insertNodeToTreeDIS(current, node); // 插入到右子树
            continue;
        }

        // 判断“归经是否含有胃”
        bool containsWei = false;
        for (int j = 0; j < node->data.channel_tropism_num; j++) {
            if (node->data.channel_tropism[j] == "胃") {
                containsWei = true;
                break;
            }
        }
        if (containsWei) {
            current = current->lchild; // 归经含有胃 -> 左孩子
            insertNodeToTreeDIS(current, node); // 插入到左子树
        }
        else {
            current = current->rchild; // 归经不含有胃 -> 右孩子
            insertNodeToTreeDIS(current, node); // 插入到右子树
        }
    }
}

BiTreeDIS FindNodeByName(BiTreeDIS BT, string name) {
    //根据植物名递归找到对应结点，若不存在则返回NULL
    if (BT == NULL) {
        return NULL;
    }
    if (BT->data.name == name) {
        return BT;
    }
    //递归查找
    BiTreeDIS find = FindNodeByName(BT->lchild, name);
    if (find) return find; // 在左子树中找到
    return FindNodeByName(BT->rchild, name); // 在右子树中找
}

BiTreeDIS FindOriginalFather(BiTreeDIS BT, BiTreeDIS t) {
    //查找二叉树中一个节点在决策树结构中的父结点
        //也是递归查找
    if (!BT || !t) return NULL;
    if (BT->lchild == t || BT->rchild == t) return BT; // 当前结点是目标结点的父结点
    BiTreeDIS find = FindOriginalFather(BT->lchild, t);
    if (find) return find; // 在左子树中找到
    return FindOriginalFather(BT->rchild, t); // 在右子树中找
}

void FindClassDIS(BiTreeDIS& BT, string name) {
    //根据中药材草药名，输出其所经历的所有决策条件
    BiTreeDIS node = FindNodeByName(BT, name);
    if (!node) {
        return;
    }

    while (node) {
        BiTreeDIS parent = FindOriginalFather(BT, node);
        if (!parent) break; // 已到达根结点
        if (parent->disition != "")
            cout << parent->disition << endl;
        node = parent; // 向上回溯
    }
}
