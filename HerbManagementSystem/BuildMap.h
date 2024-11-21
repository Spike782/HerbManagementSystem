#pragma once
#include "herb_data_structure.h"
#define MVNum 10000


int BF(const char* S, const char* T, int& pos, int firstEntityStart, int firstEntityLen, int firstWildcardIndex, int wildcardCount) {
    // S: 主字符串，即要在其中进行匹配查找的非结构化文本
    // T: 模式字符串，即匹配规则
    // pos: 记录主字符串中的当前匹配位置
    // firstEntityStart: 第一个实体在模式字符串中的起始位置
    // firstEntityLen: 第一个实体在模式字符串中的长度
    // firstWildcardIndex: 模式字符串中第一个*出现的下标
    // wildcardCount: 模式字符串中*的个数
    int i = pos;  // 用于遍历主字符串S的指针，初始化为当前匹配位置pos
    int j = 0;    // 用于遍历模式字符串T的指针，初始化为0

    int mainLen = (int)strlen(S);  // 主字符串S的长度
    int patternLen = (int)strlen(T);  // 模式字符串T的长度

    while (i <= mainLen - 1 && j <= patternLen - 1) {
        if (S[i] == T[j]) {
            i++;
            j++;
        }
        else {
            i = i - j + firstEntityStart + 1;  // 若不匹配，主字符串指针i回溯到特定位置
            j = firstEntityStart;  // 模式字符串指针j设置为第一个实体的起始位置，重新开始匹配
        }

        // 处理模式字符串中除第一个实体和*部分外还有后续部分需要匹配的情况
        if ((wildcardCount + firstEntityLen) != patternLen && j == firstWildcardIndex) {
            j += wildcardCount;  // 模式字符串指针j跳过*部分，指向后续部分的起始位置
            i += 3 * wildcardCount;  // 主字符串指针i也要往后移动，因为主字符串里是汉字，每个汉字占3字节，所以要乘3
        }
        else if ((firstEntityStart == 0) && j == firstWildcardIndex) {
            // 当第一个实体起始位置为0且到达*部分起始位置时（情况1），表示第一个实体已匹配完
            j += wildcardCount;  // 模式字符串指针j跳过*部分，此时j会等于patternLen，即匹配成功
        }
    }

    if (j > patternLen - 1) {
        // 成功匹配了规则
        pos = (wildcardCount + firstEntityLen == patternLen) ? i - firstEntityLen : i - (patternLen + 2 * wildcardCount);
        return pos;
    }
    else {
        pos = -1;
        return pos;
    }
}

bool EntityRecognition(const char* S, const char* T) {
    // S为非结构化文本，T为规则
    // 如果匹配成功返回true，否则返回false
    // 输出所有匹配到的实体
    int patternLen = (int)strlen(T);  // 获取规则字符串T的长度

    int firstWildcardIndex = -1;  // 记录模式字符串中第一个*出现的下标，初始化为-1
    int wildcardCount = 0;  // 记录模式字符串中*的个数，即要匹配的中文字符数量，初始化为0

    // 遍历规则字符串T，找到第一个*出现的下标和*的个数
    for (int i = 0; i < patternLen; i++) {
        if (T[i] == '*' && firstWildcardIndex == -1) {
            firstWildcardIndex = i;
        }
        if (T[i] == '*') {
            wildcardCount++;
        }
    }

    // 确定第一个实体在模式字符串中的起始位置和长度
    int firstEntityStart, firstEntityLen;
    if (firstWildcardIndex + wildcardCount == patternLen) {
        // 情况1: 当*在模式字符串末尾时，第一个实体从开头到*之前
        firstEntityStart = 0;
        firstEntityLen = patternLen - wildcardCount;
    }
    else if (firstWildcardIndex == 0) {
        // 情况2: 当*在模式字符串开头时，第一个实体从*之后到末尾
        firstEntityStart = firstWildcardIndex + wildcardCount;
        firstEntityLen = patternLen - wildcardCount;
    }
    else {
        // 情况3: 其他情况，第一个实体从开头到第一个*之前
        firstEntityStart = 0;
        firstEntityLen = firstWildcardIndex;
    }

    int matchFlag = 1;  // 记录是否匹配成功，初始化为1（表示未匹配成功）
    int currentPos = 0;  // 记录主字符串中的当前位置，初始化为0

    // 循环进行匹配，直到找不到匹配的实体为止
    while (BF(S, T, currentPos, firstEntityStart, firstEntityLen, firstWildcardIndex, wildcardCount) != -1) {
        matchFlag = 0;  // 一旦找到匹配的实体，将匹配标志设为0，表示匹配成功

        char match[30];  // 临时数组，用于保存匹配到的字符

        if (firstEntityStart == 0) {
            // 情况1: 当第一个实体从开头开始时
            currentPos += firstEntityLen;  // 主字符串指针移动到目标字符起始位置

            // 从主字符串中提取匹配到的*所代表的中文字符
            int i;
            for (i = 0; i < 3 * wildcardCount; i++) {
                match[i] = S[currentPos++];
            }
            match[i] = '\0';

            // 主字符串指针移动到第二个实体后面的位置（如果存在第二个实体）
            currentPos += patternLen - (firstWildcardIndex + wildcardCount);
        }
        else {
            // 情况2: 当第一个实体不在开头时
            int frontPos = currentPos - 3 * wildcardCount;  // 计算往前找目标字符的起始位置

            // 从主字符串中提取匹配到的*所代表的中文字符
            int i;
            for (i = 0; i < 3 * wildcardCount; i++) {
                match[i] = S[frontPos++];
            }
            match[i] = '\0';

            currentPos++;  // 主字符串指针移动一位
        }
        cout << match << endl;  // 输出匹配到的实体
    }

    return matchFlag ? false : true;
}

typedef struct {
    string relation;    //关系名称
    string rule[10];    //规则数组
} Relation;

void InitRelation(Relation* r) {
    r[0].relation = "功效";
    r[0].rule[0] = "A具有B";
    r[0].rule[1] = "A功效为B";
    r[0].rule[2] = "A有利于B";
    r[0].rule[3] = "A有益于B";
    r[0].rule[4] = "A可以B";

    r[1].relation = "防治";
    r[1].rule[0] = "A可防治B";
    r[1].rule[1] = "A具备了防治B";
    r[1].rule[2] = "A可以治疗B";
    r[1].rule[3] = "A有利于预防B";

    r[2].relation = "性味";
    r[2].rule[0] = "A的性味是B";
    r[2].rule[1] = "A的性味为B";

    r[3].relation = "包含";
    r[3].rule[0] = "A包括B";
    r[3].rule[1] = "A主要有B";
    r[3].rule[2] = "A分解成B";
}

int BFMatch(const string& text, const string& pattern) {
    // 如果在text中找到了与pattern完全匹配的子串，返回该子串在text中的起始位置
    //未匹配到返回-1  
    int textLen = text.length();
    int patternLen = pattern.length();
    // 初始化两个指针，i用于遍历待匹配文本字符串text，j用于遍历模式字符串pattern
    int i = 0, j = 0;

    while (i < textLen && j < patternLen) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }
        else {
            i = i - j + 1;
            j = 0;
        }
    }

    if (j == patternLen) {
        return i - patternLen;
    }

    return -1;
}

bool RelationExtraction(char* text, char* entity1, char* entity2, Relation* r) {
    // 如果实体之间存在关系返回true，否则返回false
    // 输出所有存在的三元组
    string Text(text);
    string Entity1(entity1);
    string Entity2(entity2);

    // 先找到第一个实体在文本中的位置
    int entity1Pos = BFMatch(Text, Entity1);
    if (entity1Pos == -1) {
        return false;
    }

    // 再从第一个实体之后开始找第二个实体在文本中的位置
    int entity2Pos = BFMatch(Text.substr(entity1Pos + Entity1.length()), Entity2);
    if (entity2Pos == -1) {
        return false;
    }

    // 确定两个实体之间的内容
    string betweenContent = Text.substr(entity1Pos + Entity1.length(), entity2Pos);

    // 遍历所有关系类型及其规则数组，查找匹配的规则
    if (BFMatch(betweenContent, "具有") != -1) {
        cout << Entity1 << "-" << r[0].relation << "-" << Entity2 << endl;
        return true;
    }
    else if (BFMatch(betweenContent, "功效为") != -1) {
        cout << Entity1 << "-" << r[0].relation << "-" << Entity2 << endl;
        return true;
    }
    else if (BFMatch(betweenContent, "有利于") != -1) {
        cout << Entity1 << "-" << r[0].relation << "-" << Entity2 << endl;
        return true;
    }
    else if (BFMatch(betweenContent, "有益于") != -1) {
        cout << Entity1 << "-" << r[0].relation << "-" << Entity2 << endl;
        return true;
    }
    else if (BFMatch(betweenContent, "可以") != -1) {
        cout << Entity1 << "-" << r[0].relation << "-" << Entity2 << endl;
        return true;
    }

    else if (BFMatch(betweenContent, "可防治") != -1) {
        cout << Entity1 << "-" << r[1].relation << "-" << Entity2 << endl;
        return true;
    }
    else if (BFMatch(betweenContent, "具备了防治") != -1) {
        cout << Entity1 << "-" << r[1].relation << "-" << Entity2 << endl;
        return true;
    }
    else if (BFMatch(betweenContent, "可以治疗") != -1) {
        cout << Entity1 << "-" << r[1].relation << "-" << Entity2 << endl;
        return true;
    }
    else if (BFMatch(betweenContent, "有利于预防") != -1) {
        cout << Entity1 << "-" << r[1].relation << "-" << Entity2 << endl;
        return true;
    }

    else if (BFMatch(betweenContent, "的性味是") != -1) {
        cout << Entity1 << "-" << r[2].relation << "-" << Entity2 << endl;
        return true;
    }
    else if (BFMatch(betweenContent, "的性味为") != -1) {
        cout << Entity1 << "-" << r[2].relation << "-" << Entity2 << endl;
        return true;
    }

    else if (BFMatch(betweenContent, "包括") != -1) {
        cout << Entity1 << "-" << r[3].relation << "-" << Entity2 << endl;
        return true;
    }
    else if (BFMatch(betweenContent, "主要有") != -1) {
        cout << Entity1 << "-" << r[3].relation << "-" << Entity2 << endl;
        return true;
    }
    else if (BFMatch(betweenContent, "分解成") != -1) {
        cout << Entity1 << "-" << r[3].relation << "-" << Entity2 << endl;
        return true;
    }
    else return false;
}

typedef struct ArcNode {
    int adjvex;                     // 该边所指向顶点的位置
    int relationship;               // 表示边的类型，即关系的类型，对应为数组下标 
    struct ArcNode* nextarc;        // 下一条边
} ArcNode;                          // 边结点

typedef struct VNode {
    int entity;                     // 表示顶点的类型，即实体的类型，对应为数组下标
    string info;                    // 表示顶点的内容，即实体的内容
    ArcNode* firstarc;              // 指向第一条依附该顶点的边的指针
} VNode, AdjList[MVNum];

typedef struct {
    AdjList vertices;               // 邻接表
    int vexnum, arcnum;             // 图的当前顶点数和边数
} ALGraph;

// 定义关系数组，用于表示边的类型
string Relationship[] = { "类别","高度","叶","花","果","花期","果期","茎","药材" };

// 定义顶点数组，用于表示实体类型和内容
string Entity[] = { "草药","类别","高度","叶","花","果","花期","果期","茎","药材" };

int LocateVex(ALGraph& G, string str) {
    // 返回str在AdjList中的位置
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].info == str) {
            return i;
        }
    }
    return -1;
}

int LocateEntity(string str) {
    // 返回str在Entity数组中的位置
    for (int i = 0; i < 10; i++) {
        if (Entity[i] == str) {
            return i;
        }
    }
    return -1;
}

int LocateRelationship(string str) {
    // 返回str在Relationship数组中的位置
    for (int i = 0; i < 9; ++i) {
        if (Relationship[i] == str) {
            return i;
        }
    }
    return -1;
}

void InitALGraph(ALGraph& G) {
    // 初始化邻接表
    G.vexnum = 0;
    G.arcnum = 0;
    for (int i = 0; i < MVNum; ++i) {
        G.vertices[i].firstarc = nullptr;
        G.vertices[i].info = "";
    }
}

void CreateAdjList(ALGraph& G, string filename) {
    // 从filename中按顺序读取实体存入邻接表
    //若读取的元素word中含有换行符，可用word.erase(word.find_last_not_of(" \n\r\t") + 1)去掉 (word类型为string）
    ifstream infile(filename);
    string line;
    while (getline(infile, line)) {
        // 去掉换行符
        line.erase(line.find_last_not_of(" \n\r\t") + 1);
        // 使用 istringstream 解析每行数据
        istringstream iss(line);
        string entityName, entityType;

        iss >> entityName >> entityType;

        // 定位实体类型在 Entity 数组中的下标
        int entityIndex = LocateEntity(entityType);

        // 创建一个新的 VNode 结构体来表示该顶点
        VNode newVNode;
        newVNode.entity = LocateEntity(entityType);
        newVNode.info = entityName;
        newVNode.firstarc = nullptr;

        G.vertices[G.vexnum] = newVNode;
        G.vexnum++;
    }

    infile.close();
}

void CreateUDG(ALGraph& G, string filename) {
    // 从filename中按顺序三元组存入邻接表
    //若读取的元素word中含有换行符，可用word.erase(word.find_last_not_of(" \n\r\t") + 1)去掉 (word类型为string）
    ifstream infile(filename);
    string line;
    string source, relationshipStr, destination;

    while (getline(infile, line)) {
        // 去掉换行符等空白字符
        line.erase(line.find_last_not_of(" \n\r\t") + 1);

        // 用空格分割三元组
        istringstream iss(line);
        string source, relationshipStr, destination;
        iss >> source >> relationshipStr >> destination;


        int sourceIndex = LocateVex(G, source);
        int relationshipIndex = LocateRelationship(relationshipStr);
        int destinationIndex = LocateVex(G, destination);

        if (sourceIndex == -1 || relationshipIndex == -1 || destinationIndex == -1) {
            return;
        }
        // 正向添加边
        ArcNode* newArc = new ArcNode;
        newArc->adjvex = destinationIndex;
        newArc->relationship = relationshipIndex;
        newArc->nextarc = G.vertices[sourceIndex].firstarc;
        G.vertices[sourceIndex].firstarc = newArc;

        // 反向添加边
        newArc = new ArcNode;
        newArc->adjvex = sourceIndex;
        newArc->relationship = relationshipIndex;
        newArc->nextarc = G.vertices[destinationIndex].firstarc;
        G.vertices[destinationIndex].firstarc = newArc;

        G.arcnum += 2;
    }

    infile.close();

}

void PrintGraph(ALGraph& G) {
    //	按格式输出知识图谱
    for (int i = 0; i < G.vexnum; ++i) {
        VNode vertex = G.vertices[i];
        ArcNode* arc = vertex.firstarc;

        while (arc != nullptr) {
            cout << vertex.info << " " << arc->relationship << " " << G.vertices[arc->adjvex].info << endl;
            arc = arc->nextarc;
        }
    }
}

void SearchHerbsByEntity(ALGraph G, const string entityToSearch) {
    bool found = false;

    // 遍历图中的所有顶点，寻找符合条件的草药
    for (int i = 0; i < G.vexnum; i++) {
        ArcNode* p = G.vertices[i].firstarc;

        // 遍历每个与当前草药相关的边
        while (p) {
            // 获取当前信息
            string info = G.vertices[p->adjvex].info;

            // 判断是否匹配
            if (info == entityToSearch) {
                // 输出草药的所有信息，按照预期格式
                ArcNode* temp = G.vertices[i].firstarc;
                while (temp) {
                    cout << G.vertices[i].info << "->" << Relationship[temp->relationship] << "->" << G.vertices[temp->adjvex].info << endl;
                    temp = temp->nextarc;
                }
                found = true;
            }

            p = p->nextarc;
        }
    }

    if (!found) {
        cout << "未找到符合条件的草药" << endl;
    }
}