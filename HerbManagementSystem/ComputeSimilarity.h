#pragma once
#include "herb_data_structure.h"

struct Herb_FV{
    char name[100];            		 	// 草药名
    char sname[100];            		// 英文名
    char growth_habits[5000];  		// 生长习性
    char reproductive[5000];   		// 繁殖方法
    char field_management[5000];  		// 田间管理
    char pest_control[5000];           // 病虫防治
    char harvesting[5000];          	// 采收加工
    char taste[5000];        			// 性味
    string channel_tropism[6];        	// 归经
    int channel_tropism_num = 0;		// 归经数量
    char effect[5000];       			// 功效
    char functional_indications[5000]; // 功能主治
    int feature_vector[6];              // 特征向量 
};

typedef struct {
    // 开放地址法散列表的存储表示
    Herb_FV* key;
    int length;
} HashTable_FV;

void InitHT(HashTable_FV& HT) {
    // 散列表初始化
    HT.key = new Herb_FV[m];
    for (int i = 0; i < m; i++) {
        // 初始化散列表每个单元为空
        HT.key[i].sname[0] = '\0';
    }
    HT.length = 0;
}

void generateFeatureVector(const string* herbChannels, int herbChannelsCount, int featureVector[]) {
    // 根据中药材的归经生成特征向量
        // 定义最大归经数量
    const int MAX_CHANNELS = 6;

    // 定义归经字符串数组
    const string channels[MAX_CHANNELS] = { "心", "肝", "脾", "肺", "肾", "胃" };

    // 初始化特征向量为全0
    for (int i = 0; i < MAX_CHANNELS; i++) {
        featureVector[i] = 0;
    }

    // 根据归经信息设置特征向量相应位置为1
    for (int i = 0; i < herbChannelsCount; i++) {
        for (int j = 0; j < MAX_CHANNELS; j++) {
            if (herbChannels[i] == channels[j]) {
                featureVector[j] = 1;
                break;
            }
        }
    }
}

void HTInsert(HashTable_FV& HT, Herb_FV h) {
    // 往散列表中插入新的中药材
        // 计算哈希值
    int hashValue = Hash(h.sname);
    int j = 0;

    while (j < m) {
        if (HT.key[hashValue].sname[0] == '\0') {
            // 如果当前位置为空，则插入
            HT.key[hashValue] = h;
            HT.length++;
            return;
        }
        else {
            hashValue = (hashValue + 1) % m;
            j++;
        }
    }

}

void ReadFile(HashTable_FV& HT, string filename) {
    // 从文件中读取中药材信息，将其存入散列表中
    ifstream infile(filename);
    char s[5000];
    int index = 1;
    while (infile.getline(s, sizeof(s), '#')) {
        stringstream streams(s);
        string ss;
        Herb_FV temp;
        int type = 0;

        while (getline(streams, ss, '\n')) {
            if (ss.empty()) continue;
            switch (type) {
            case 0: strcpy(temp.name, ss.substr(7).c_str()); break;//草药名
            case 1: strcpy(temp.sname, ss.substr(7).c_str()); break;//英文名
            case 2: strcpy(temp.growth_habits, ss.substr(9).c_str()); break;//生长习性
            case 3: strcpy(temp.reproductive, ss.substr(9).c_str()); break;//繁殖方式
            case 4: strcpy(temp.field_management, ss.substr(9).c_str()); break;//田间管理
            case 5: strcpy(temp.pest_control, ss.substr(9).c_str()); break;//病虫防治
            case 6: strcpy(temp.harvesting, ss.substr(9).c_str()); break;//采收加工
            case 7: strcpy(temp.taste, ss.substr(5).c_str()); break;//性味
            case 8: {//归经
                stringstream stream(ss.substr(5));
                string channel;
                while (getline(stream, channel, ',')) {
                    temp.channel_tropism[temp.channel_tropism_num++] = channel;
                }
                break;
            }
            case 9: strcpy(temp.effect, ss.substr(5).c_str()); break;//功效
            case 10: strcpy(temp.functional_indications, ss.substr(9).c_str()); break;//功能主治
            default: break;
            }
            type++;
        }
        // 生成特征向量并插入
        generateFeatureVector(temp.channel_tropism, temp.channel_tropism_num, temp.feature_vector);
        HTInsert(HT, temp);
    }
    infile.close();
}

void Print(HashTable_FV HT, int pos) {
    // 输出特征向量
    if (pos >= 0 && pos < HT.length) {
        cout << HT.key[pos].name << "的特征向量为:";
        for (int i = 0; i < 6; i++) {
            cout << HT.key[pos].feature_vector[i];
            if (i < 5) {
                cout << " ";
            }
        }
        cout << endl;
    }
}

int SearchHash(HashTable_FV HT, char* key) {
    // 在散列表HT中查找中药材英文名称等于key的元素
    // 若找到，则返回散列表的单元标号，否则返回-1
    int find = Hash(key);
    int j = 0;

    while (j < m && HT.key[find].sname[0] != '\0') {
        if (strcmp(HT.key[find].sname, key) == 0) {
            return find;
        }
        else {
            find = (find + 1) % m;
            j++;
        }
    }

    return -1;
}

int computeSimilarity(HashTable_FV HT, int p1, int p2) {
    int similarity = 0;
    for (int i = 0; i < 6; i++) {
        similarity += (HT.key[p1].feature_vector[i] ^ HT.key[p2].feature_vector[i]);
    }
    // 获取两种药材的英文名
    string name1 = HT.key[p1].name;
    string name2 = HT.key[p2].name;

    // 输出相似度结果
    cout << name1 << "和" << name2 << "的相似度为:" << similarity << endl;

    return similarity;
}