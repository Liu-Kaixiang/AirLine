#include "function.h"

void ReadFile(string str)
{
    //���ļ�
    ifstream inFile(str, ios::in);
    string lineStr;

    LineNum = -1;//����������ʼ��Ϊ-1����һ�����Ʋ�����
    while(getline(inFile, lineStr))
    {
        //��һ�����ڴ洢���е���Ϣ
        //��ɶ�ά��ṹ
        stringstream ss(lineStr);
        string str;
        vector<string> lineArray;
        // ���ն��ŷָ�
        while(getline(ss, str, ','))
            lineArray.push_back(str);

        if(LineNum == -1)
        {
            LineNum++;//��һ��Ϊ����
            continue;
        }
        airline[LineNum++] = {stoi(lineArray[0]), stoi(lineArray[3]), stoi(lineArray[4]), stoi(lineArray[5]),
                              DateToMin(StrToDate(lineArray[6])), DateToMin(StrToDate(lineArray[7])), stoi(lineArray[8]),
                              stoi(lineArray[9]), stoi(lineArray[10])};
    }
}

//��ʼ������strΪ��ʾ���ڵ��ַ���
//�����������str�е���Ϣת��Ϊ�ṹ�����ʹ洢�������ؽ��
Date StrToDate(string str)
{
    Date dt;
    string temp = "";//����Ϊ�մ�
    int len = str.length();
    int index = 0;//0��ʾ�洢�£�1��ʾ�洢�գ�2��ʾ�洢�꣬3��ʾ�洢Сʱ��4��ʾ�洢����
    for(int i = 0; i < len; i++)
    {
        while(str[i] != '/' && str[i] != ' ' && str[i] != ':' && i < len)//���ּ����
        {
            temp.push_back(str[i]);
            i++;
        }
        switch (index) {
        case 0:
            dt.month = stoi(temp);
            temp.clear();//����ַ���
            index++;
            break;
        case 1:
            dt.day = stoi(temp);
            temp.clear();//����ַ���
            index++;
            break;
        case 2:
            dt.year = stoi(temp);
            temp.clear();//����ַ���
            index++;
            break;
        case 3:
            dt.hour = stoi(temp);
            temp.clear();//����ַ���
            index++;
            break;
        case 4:
            dt.minute = stoi(temp);
            temp.clear();//����ַ���
            index++;
            break;
        default:
            break;
        }
    }
    return dt;
}

//��ʼ������dtΪ��ʾ���ڵĽṹ��
//�����������dt�е���Ϣת��Ϊ�Է���Ϊ��λ��ʱ�䣬������
int DateToMin(Date dt)
{
    //��ͳ�ƣ�����ĺ�����5�ų���
    return ((dt.day - 5) * 24 + dt.hour) * 60 + dt.minute;//����Ϊ��λת��������
}

//��ʼ������rΪ�յĽṹ�壬���Դ洢�û���������
//���������ͨ���û������뽫�û��������������r�У����õ���ֵ
void Request(Req &r)
{
    for(int i = 0; i < 10; i++)//��ʼ��Ϊ0
        r.AirplaneModel[i] = 0;

    r.FirstDepTime = 0;
    r.LastDepTime = INFINITY;//��ʼ��ʱĬ����Ҫ��
    r.FirstArrTime = 0;
    r.LastArrTime = INFINITY;

    cout << "�������������:" << endl;

    Date dt;
    cout << "��������ϣ�����������ʱ��(�����ա�Сʱ�����ӵĸ�ʽ˳������, ����������-1 -1 -1)" << endl;
    cin >> dt.day >> dt.hour >> dt.minute; //���з�����
    if(dt.day != -1)
        r.FirstDepTime = DateToMin(dt);

    cout << "��������ϣ�����������ʱ��(�����ա�Сʱ�����ӵĸ�ʽ˳������, ����������-1 -1 -1)" << endl;
    cin >> dt.day >> dt.hour >> dt.minute;
    if(dt.day != -1)
        r.LastDepTime = DateToMin(dt);

    cout << "��������ϣ��������ִ�ʱ��(�����ա�Сʱ�����ӵĸ�ʽ˳������, ����������-1 -1 -1)" << endl;
    cin >> dt.day >> dt.hour >> dt.minute;
    if(dt.day != -1)
        r.FirstArrTime = DateToMin(dt);

    cout << "��������ϣ��������ִ�ʱ��(�����ա�Сʱ�����ӵĸ�ʽ˳������, ����������-1 -1 -1)" << endl;
    cin >> dt.day >> dt.hour >> dt.minute;
    if(dt.day != -1)
        r.LastArrTime = DateToMin(dt);

    int ReqModelNum = 0;//Ҫ��Ļ�������
    cout << "��������Ҫ���ֻ��ͣ�������1-6������������6��ʾ�κλ��Ͷ����ԣ���";
    cin >> ReqModelNum;

    if(ReqModelNum >= 1 && ReqModelNum <= 5)
    {

        cout << "����������Ҫ�Ļ������ࣺ";
        for(int i = 0; i < ReqModelNum; i++)
        {
            int model;
            cin >> model;
            r.AirplaneModel[model] = 1;//���û�����5����ָ����5����ֵΪ1
        }
    }
    else if(ReqModelNum == 6)//���л��Ͷ���
    {
        for(int i = 0; i < ReqModelNum; i++)
            r.AirplaneModel[i] = 1;
    }
    else if(ReqModelNum >= 7)
        cout << "�������룡" << endl;
}

//��ʼ������r�洢���û��������������ReqTypeָ�û��������ࣨ0,1,2����Ҫ��֤�������ķɻ����ʹ��ڣ�0��ʾ�����ʱ����Ҫ��1��ʾ�Եִ�ʱ����Ҫ��2��ʾ���Ի�����Ҫ�󣩣�pΪ����ĵ�ǰ���߽��
//������������ݲ�ͬ��ReqType��ȷ���ú����Ƿ�����û������������򷵻�true�����򷵻�false
bool IsMatchReq(Req r, int ReqType, ArcCell* p)
{
    if(ReqType == 0)
    {
        if(r.FirstDepTime <= p->LineInfo.DepTime && r.LastDepTime >= p->LineInfo.DepTime)
        {
            if(r.AirplaneModel[p->LineInfo.AirplaneModel] == 1)//Ҫ��֤�˻��ʹ����ҿ��Գ���
                return true;
        }
    }

    if(ReqType == 1)
    {
        if(r.FirstArrTime <= p->LineInfo.ArrTime && r.LastArrTime >= p->LineInfo.ArrTime)
        {
            if(r.AirplaneModel[p->LineInfo.AirplaneModel] == 1)//Ҫ��֤�˻��ʹ����ҿ��Գ���
                return true;
        }
    }

    if(ReqType == 2)
    {
        if(r.AirplaneModel[p->LineInfo.AirplaneModel] == 1)
            return true;
    }

    return false;
}

//��ʼ������dt1,dt2Ϊ����ʱ�䣬�����ꡢ�¡��ա�Сʱ������
//�����������dt1��ʱ����dt2ʱ��֮���򷵻�1����������ͬ�򷵻�0�����򷵻�-1
int CompareDate(Date dt1, Date dt2)
{
    if(dt1.year > dt2.year)
        return 1;
    else if(dt1.year < dt2.year)
        return -1;

    if(dt1.month > dt2.month)
        return 1;
    else if(dt1.month < dt2.month)
        return -1;

    if(dt1.day > dt2.day)
        return 1;
    else if(dt1.day < dt2.day)
        return -1;

    if(dt1.hour > dt2.hour)
        return 1;
    else if(dt1.hour < dt2.hour)
        return -1;

    if(dt1.minute > dt2.minute)
        return 1;
    else if(dt1.minute < dt2.minute)
        return -1;
    else
        return 0;
}

void FreeGraph(MGraph &G)
{
    ArcCell *p, *q; //���Ա�����ÿ�����������ĵ�����
    for(int i = 0; i < G.vexnum; i++)
    {
        for(int j = 0; j < G.vexnum; j++)
        {
            p = G.arcs[i][j];
            if(p)
            {
                while(p)//����������
                {
                    q = p;
                    p = p->next;
                    free(q);
                    q = NULL;
                }
            }
        }
    }
    p = NULL;//��ֹ��ΪҰָ��
    G.arcnum = 0;
    G.vexnum = 0;
}

//��ʼ������ͼG���������ڽӱ�洢
//�����������ӡ�����������������ı���,����������ȱ����͹�����ȱ���
void Mission1(ALGraph &G)
{
    cout << "DFSTraverse:" << endl;
    int DepAirport;
    cout << "��������ʼ������";
    cin >> DepAirport;
    int DepPos = LocateVex(G, DepAirport);
    if(DepPos == -1)
    {
        cout << "�˻��������ڣ�" << endl;
        return;
    }

    DFSTraverse(G, DepPos);//ͷ�巨����
    /*
    for(int i = 0; i < G.vexnum; i++)
    {
        cout << "�Ի���" << G.vertices[i].data << "Ϊ��ʼ�㣬���Ϊ��";
        DFSTraverse(G, i);
        cout << endl << endl;
    }
    */
    cout << endl << endl;

    cout << "BFSTraverse:" << endl;

    cout << "��������ʼ������";
    cin >> DepAirport;
    DepPos = LocateVex(G, DepAirport);
    if(DepPos == -1)
    {
        cout << "�˻��������ڣ�" << endl;
        return;
    }
    BFSTraverse(G, DepPos); //ͷ�巨����
    cout << endl << endl;
    /*
    for(int i = 0; i < G.vexnum; i++)
    {
        cout << "�Ի���" << G.vertices[i].data << "Ϊ��ʼ�㣬���Ϊ��";
        BFSTraverse(G, i);
        cout << endl << endl;
    }
    */
}

//��ʼ������ͼG���������ڽӱ�洢
//���������ʹ���ڽӾ����������������������Ŀ���ͨ�ԣ������Ƿ����ֱ�ɡ�1����ת��2����ת��
void Mission2(MGraph &G)
{

    //�㷨˼�룺ÿ������ڶ�����·���о����Ļ����������ö��е����ԣ�ֻҪ�ѵ�ĳһ�����ĵ�ǰ����ΪĿ���������˽��洢��·������ת��������̵�·��

    cout << "��ֱ��������������Ŀ�Ļ����ı�ţ����ù�����ȱ�����������";
    int DepAirport, ArrAirport;
    cin >> DepAirport >> ArrAirport;

    if(DepAirport == ArrAirport)
    {
        cout << "�������룡����������Ŀ�Ļ�����ͬ��" << endl;
        return;
    }
    int StartPos = LocateVex(G, DepAirport); //���������ڶ��������е�λ���±�
    int TerminalPos = LocateVex(G, ArrAirport); //Ŀ�Ļ����ڶ��������е�λ���±�

    queue<Path*> PathNode;//·�����,�洢·���ϵ������Ϣ

    cout << "Loading..." << endl;

    for(int i = 0; i < G.vexnum; i++)//������ʼ�������ڵ��ڽӾ���һ�У���ջ�ĳ�ʼ��
    {
        if(G.arcs[StartPos][i])//��ǰλ���к���
        {
            ArcCell* p = G.arcs[StartPos][i];//���Ա����Դ˽��Ϊͷ�����к���
            while(p)//������˽����ص����к��ߣ����Դ˻���Ϊ�������������к���
            {
                if(i == TerminalPos)//��������ֱ��Ŀ�Ļ����ĺ����е����ʱ�䣬�˽�㲻��Ҫ����������У�ֻ��Ҫȷ�����ʱ�䣬��Ϊʱ����Ͻ�
                {
                    cout << "����ֱ�ɣ�����ת������Ϊ0�� " << endl;
                    return;
                }

                //�������к������ɽ�������
                Path *node = (Path*)malloc(sizeof(Path));
                node->TraceLen = 2;//��ǰ·����,��Ӧ��ת������Ϊ�˻����ϼ�2
                node->StartTime = p->LineInfo.DepTime;//��ʼʱ��Ϊ����ʱ��
                node->CurTime = p->LineInfo.ArrTime;//��ǰʱ��Ϊ�˺��ߵĵִ�ʱ��
                node->TraceAirport[0] = G.vexs[StartPos].data; //·�������Ļ���
                node->TraceAirport[1] = G.vexs[i].data;
                node->TraceID[0] = p->LineInfo.FlightID;
                PathNode.push(node);//�����

                p = p->next;
            }
        }
    }

    while(!PathNode.empty())//���зǿգ�����BFS,һ�����ѣ��ѵ�Ϊֹ
    {
        Path *pNode = PathNode.front();//ȡ����Ԫ��
        PathNode.pop();

        int CurAirport = pNode->TraceAirport[pNode->TraceLen - 1];//��ǰ���ڻ���

        if(CurAirport == ArrAirport)//�ö��У�ֻҪ�ѵ���ͣ
        {
            cout << "����ת������: " << pNode->TraceLen - 2 << endl;
            return;
        }

        int CurPos = LocateVex(G, CurAirport);//��ǰ�Ļ����ڶ��������е��±�

        for(int i = 0; i < G.vexnum; i++)//�����˽�㵱ǰ���ڻ������ڽӾ����һ��
        {
            if(G.arcs[CurPos][i] && i != StartPos)//��֤��λ���к�����·���ϲ�������ʼ����
            {
                ArcCell *p = G.arcs[CurPos][i];//���Ա������ߣ�ѡȡ���еĺ���S
                bool IsThrough = false;//���ڱ�ʾ��ǰ�����Ļ����Ƿ��Ѿ�������·���У���û�г�����Ϊfalse
                for(int j = 0; j < pNode->TraceLen; j++)//����·���������߹��Ļ���
                {
                    if(G.vexs[i].data == pNode->TraceAirport[j])//��ǰ�����Ѿ�������·���У����м�֦
                    {
                        IsThrough = true;
                        break;
                    }
                }

                if(!IsThrough)//ֻ��δ�����Ļ������б�Ҫ������
                {
                    while(p)//������˻�����ص����к���
                    {
                        if(p->LineInfo.DepTime > pNode->CurTime) //���˺�������ʱ���ڵ�ǰʱ�䣨���ִ�˻�����ʱ�䣩֮�󣬿���ͨ��
                        {
                            Path *newNode = (Path*)malloc(sizeof(Path));
                            newNode->TraceLen = pNode->TraceLen + 1;
                            newNode->CurTime = p->LineInfo.ArrTime;
                            newNode->StartTime = pNode->StartTime;
                            newNode->TraceID[pNode->TraceLen - 1] = p->LineInfo.FlightID;

                            for(int k = 0; k < pNode->TraceLen - 1; k++)//����·���ϵĺ���ID
                            {
                                newNode->TraceID[k] = pNode->TraceID[k];
                            }
                            for(int k = 0; k < pNode->TraceLen; k++)//����·���ϵĻ���
                            {
                                newNode->TraceAirport[k] = pNode->TraceAirport[k];
                            }
                            newNode->TraceAirport[newNode->TraceLen - 1] = G.vexs[i].data;
                            PathNode.push(newNode);
                        }
                        p = p->next;
                    }
                }
            }
        }
        delete pNode;
    }
    cout << "���ܵ���Ŀ�Ļ�����" << endl;//��������Ȼδ����ʱ˵���޿ɴ�·��
}

//ע���˴������ʱ��Ψһ����·����һ��Ψһ
//��ʼ������ͼG���������ڽӾ�����ʽ�洢
//���������ʹ���ڽӾ�����������������������֮�����̷���ʱ�䣨��ת��ͣ��ʱ�䣩
void Mission3(MGraph &G)
{
    /*�Ż�����֦��
     * 1.�������ʱ��ʱ����ÿ�����������к����ȡ�������ʱ�������һ�ࡣ(���Ա�֤����)
     * 2.�������ʱ��ʱ������ǰ·������ʱ���Ѿ����ڵ�ǰ��¼����Сֵ������ɾ��
     * 3.��������ʱ�������ڳ˿͵ִ�û�����ʱ��
     * 4.�����Ŀ�Ļ�����Ӧ��·���ϳ��ֹ�
     * 5.·����Ӧ���ֻ�·
     * 6.���оٺ���ʱ�������߹�����ֻ��ʾǰ2000���Լ����յ��������������߹�������ܼ���ʱ��ϳ�����
    */

    /*�����㷨˼�룺
     * 1.���ȱ�����ɻ������ڵ��ڽӾ����һ�У�
     *   ������ֱ���յ�ĺ������⴦����ʱ��Ҫ�޸�����ͳ�����ʱ��ı�����
     *   ��������������Ҫ������Ӧ�Ľ����ջ
     * 2.��ջ�ǿ�ʱ����DFS��ͬʱ�ڱ���ʱ������Ӧ���Ż��ͼ�֦����������ǰ·������ʱ���Ѿ����ڵ�ǰ��¼����Сֵ������ɾ����
     * 3.�ڱ���ʱ���ڵ�ǰ��㻹��Ҫ�����˽��Ŀǰ���ڵĻ������ڽӾ����һ�У��������������ĺ��ߣ��������µĽ����ջ��
     * 4.�Դ����Ƶ�����ջ��Ϊֹ��
    */

    cout << "���������������Ŀ�Ļ�������ţ�";
    int DepAirport, ArrAirport;
    cin >> DepAirport >> ArrAirport;

    if(DepAirport == ArrAirport)
    {
        cout << "�������룡����������Ŀ�Ļ�����ͬ��" << endl;
        return;
    }

    int StartPos = LocateVex(G, DepAirport); //���������ڶ��������е�λ���±�
    int TerminalPos = LocateVex(G, ArrAirport); //Ŀ�Ļ����ڶ��������е�λ���±�

    int MinTime = INFINITY;//���ͨ��ʱ�䣻ֻѡ����������ִ�ĺ��ߣ����ڵ���ĳ�������ص����к�����ֻѡ���һ������ĺ��ߣ������Ż���֦
    int MinAirportTrace[G.vexnum] = {G.vexs[StartPos].data, G.vexs[TerminalPos].data, 0}; //������飬�洢���·���Ļ�����Ϣ
    int MinIDtrace[G.vexnum] = {0}; //������飬�洢���·���ĺ���ID��Ϣ
    int TraceLen = 2; //·�����ȣ���¼����·���еĻ���������ʼֵΪ2����ʾ��������������

    stack<Path*> PathNode;//·�����,�洢·���ϵ������Ϣ

    cout << "Loading..." << endl;

    for(int i = 0; i < G.vexnum; i++)//������ʼ�������ڵ��ڽӾ���һ�У���ջ�ĳ�ʼ��
    {
        if(G.arcs[StartPos][i])//��ǰλ���к���
        {
            ArcCell* p = G.arcs[StartPos][i];//���Ա����Դ˽��Ϊͷ�����к���
            while(p)//������˽����ص����к��ߣ����Դ˻���Ϊ�������������к���
            {
                if(i == TerminalPos)//��������ֱ��Ŀ�Ļ����ĺ����е����ʱ�䣬�˽�㲻��Ҫ��������ջ��ֻ��Ҫȷ�����ʱ�䣬��Ϊʱ����Ͻ�
                {
                    if(p->LineInfo.ArrTime - p->LineInfo.DepTime < MinTime)//ֻȡʱ����̵ĺ���
                    {
                        MinTime = p->LineInfo.ArrTime - p->LineInfo.DepTime;
                        MinIDtrace[0] = p->LineInfo.FlightID;//��¼����ID
                    }
                    p = p->next;//������һ����صĺ���
                    continue;
                }

                //�������к������ɽ����ջ
                Path *node = (Path*)malloc(sizeof(Path));
                node->TraceLen = 2;//��ǰ·����
                node->StartTime = p->LineInfo.DepTime;//��ʼʱ��Ϊ����ʱ��
                node->CurTime = p->LineInfo.ArrTime;//��ǰʱ��Ϊ�˺��ߵĵִ�ʱ��
                node->SumTime = node->CurTime - node->StartTime; //�ܺ�ʱ
                node->TraceAirport[0] = G.vexs[StartPos].data; //·�������Ļ���
                node->TraceAirport[1] = G.vexs[i].data;
                node->TraceID[0] = p->LineInfo.FlightID;
                PathNode.push(node);//��ջ
                p = p->next;
            }
        }
    }

    while(!PathNode.empty())//ջ�ǿգ�����DFS��ͬʱ�ڱ��������н���һϵ�м�֦���������������ܵ��Ż�
    {
        Path *pNode = PathNode.top();//ȡջ��Ԫ��
        PathNode.pop();

        int CurAirport = pNode->TraceAirport[pNode->TraceLen - 1];//��ǰ���ڻ���
        if(pNode->SumTime > MinTime)//��ǰ·�����ѵ�ʱ���Ѿ�������̵�ʱ�䣬������������м�֦
        {
            continue;
        }

        if(CurAirport == ArrAirport)//����Ѿ�����Ŀ�Ļ�����������ж�
        {
            if(pNode->SumTime < MinTime)//�ܺ�ʱС�ڵ�ǰ���ʱ�䣬�������Ӧ�ĸ���
            {
                MinTime = pNode->SumTime; //������̺�ʱ

                TraceLen = pNode->TraceLen;//�޸ı��·����
                for(int i = 0; i < TraceLen; i++)//���˽��洢��·�����Ƹ�MinAirportTrace������ʱ�����·��
                    MinAirportTrace[i] = pNode->TraceAirport[i];//�޸ı��������Ϣ
                for(int i = 0; i < TraceLen - 1; i++)
                    MinIDtrace[i] = pNode->TraceID[i];//�޸ı��������Ϣ
            }
            continue;//���º�ǰ��������ٽ��к�������
        }

        int CurPos = LocateVex(G, CurAirport);//��ǰ�Ļ����ڶ��������е��±�

        for(int i = 0; i < G.vexnum; i++)//�����˽�㵱ǰ���ڻ������ڽӾ����һ��
        {
            if(G.arcs[CurPos][i] && i != StartPos)//��֤��λ���к�����·���ϲ�������ʼ����
            {
                ArcCell *p = G.arcs[CurPos][i];//���Ա������ߣ�ѡȡ���еĺ���
                ArcCell *q = NULL; //����ȥ����Щ���Ե����ĺ��࣬��ǰһ��ĵִ�ʱ���ں�һ�����ʱ��֮�󣬴������������Ҫ��
                int MinArr = INFINITY;//����ִ���һ��������ʱ��
                bool IsThrough = false;//���ڱ�ʾ��ǰ�����Ļ����Ƿ��Ѿ�������·���У���û�г�����Ϊfalse
                for(int j = 0; j < pNode->TraceLen; j++)//����·���������߹��Ļ���
                {
                    if(G.vexs[i].data == pNode->TraceAirport[j])//��ǰ�����Ѿ�������·���У����м�֦
                    {
                        IsThrough = true;
                        break;
                    }
                }

                if(!IsThrough)//ֻ��δ�����Ļ������б�Ҫ������
                {
                    while(p)//������˻�����ص����к���
                    {
                        if(p->LineInfo.DepTime > pNode->CurTime ) //���˺�������ʱ���ڵ�ǰʱ�䣨���ִ�˻�����ʱ�䣩֮�󣬿���ͨ��
                        {
                            if(p->LineInfo.ArrTime - pNode->CurTime < MinArr)//ѡ�񵽴���һ�����������һ�˺���
                            {
                                MinArr = p->LineInfo.ArrTime - pNode->CurTime;
                                q = p;
                            }
                        }
                        p = p->next;
                    }
                }

                if(q)//�ҵ�����ͨ�еĵ�ǰ���ź���
                {
                    p = q;
                    Path *newNode = (Path*)malloc(sizeof(Path));
                    newNode->TraceLen = pNode->TraceLen + 1;
                    newNode->CurTime = p->LineInfo.ArrTime;
                    newNode->StartTime = pNode->StartTime;
                    newNode->SumTime = newNode->CurTime - newNode->StartTime;//�ܺ�ʱ
                    newNode->TraceID[pNode->TraceLen - 1] = p->LineInfo.FlightID;

                    for(int k = 0; k < pNode->TraceLen - 1; k++)//����·���ϵĺ���ID
                    {
                        newNode->TraceID[k] = pNode->TraceID[k];
                    }
                    for(int k = 0; k < pNode->TraceLen; k++)//����·���ϵĻ���
                    {
                        newNode->TraceAirport[k] = pNode->TraceAirport[k];
                    }
                    newNode->TraceAirport[newNode->TraceLen - 1] = G.vexs[i].data;
                    PathNode.push(newNode);
                }

            }
        }
        delete pNode;
    }

    cout << "Done!" << endl;
    if(MinTime == INFINITY)
    {
        cout << "�޷��ִ" << endl;
        return;
    }

    cout << "���ʱ��Ϊ��" << MinTime << "min" << endl;
    cout << "·��Ϊ��" << endl << "����ID:";
    int i = 0;
    for(i = 0; i < TraceLen - 2; i++)
        cout << MinIDtrace[i] << "->";

    cout << MinIDtrace[i] << endl << "������";

    for(i = 0; i < TraceLen - 1; i++)
        cout << MinAirportTrace[i] << "->";

    cout << MinAirportTrace[i] << endl;
}

//��ʼ������ͼG���������ڽӾ�����ʽ�洢��start����ʼ�����ı�ţ�terminal��Ŀ������ı��
//�������������ֱ�ɻ�1����ת����ӡ����������������ĺ��ߣ�����ID˳���
void Mission4(MGraph G)
{
    int start, terminal;
    cout << "���������������Ŀ�Ļ�����";
    cin >> start >> terminal;

    if(start == terminal)
    {
        cout << "�������룡��ʼλ������ֹλ����ͬ" << endl;
        return;
    }
    int StartPos = LocateVex(G, start);
    int TerminalPos = LocateVex(G, terminal);
    if(StartPos == -1 || TerminalPos == -1)
    {
        cout << "�������룡�޴˻������" << endl;
        return;
    }

    int flag1 = 0;//�ܷ�ֱ�ɣ�����ʱΪ0����ʱΪ1
    if(G.arcs[StartPos][TerminalPos])
    {
        ArcCell* p = G.arcs[StartPos][TerminalPos];
        cout << "����ֱ�ɣ�" << endl;
        cout << "����IDΪ��" << p->LineInfo.FlightID;
        while(p->next)
        {
            p = p->next;
            cout << "��" << p->LineInfo.FlightID;
        }
        cout << endl << endl;
        flag1 = 1;
        return;
    }
    else
    {
        cout << "����ֱ�ɵִ" << endl;
    }


    int flag2 = 0;//�Ƿ���Ծ���һ��ת���ִ������Ϊ1,������Ϊ0

    int PrintNum = 0; //��ӡ�������
    for(int i = 0; i < G.vexnum; i++)
    {
        ArcCell* p = G.arcs[StartPos][i];
        while(p)
        {
            if(G.arcs[i][TerminalPos])//�ҵ���Ӧ��·��
            {
                ArcCell* q = G.arcs[i][TerminalPos];
                while(q)
                {
                    //�Ƚ�ʱ�䣬��֤ǰһ������ĵִ�ʱ���ں�һ���������ʱ��֮ǰ
                    if(p->LineInfo.ArrTime < q->LineInfo.DepTime)//�Ƚ�ÿ��·��
                    {
                        flag2 = 1;
                        if(PrintNum == 0)
                        {
                            cout << "���Ծ���һ��ת���ִ" << endl;
                            PrintNum++;
                        }
                        cout << "����IDΪ��" << p->LineInfo.FlightID << "->" << q->LineInfo.FlightID << endl;
                    }
                    q = q->next;
                }
            }
            p = p->next;
        }
    }
    if(flag1 == 0 && flag2 == 0)
    {
        cout << "����ֱ�ɻ�1����תʱ���޷��ִ" << endl;
    }
}

//��ʼ������ͼG���������ڽӾ�����ʽ�洢
//����������������ʱ�λ��߽���ʱ�λ��߻���Ҫ��, ��ӡ����������������Ķ����ѡ���ߣ�����ID˳���
void Mission5(MGraph G)
{
    //�㷨˼����Mission3����

    cout << "���������������Ŀ�Ļ�������ţ�";
    int DepAirport, ArrAirport;
    cin >> DepAirport >> ArrAirport;

    if(DepAirport == ArrAirport)
    {
        cout << "�������룡����������Ŀ�Ļ�����ͬ��" << endl;
        return;
    }

    int StartPos = LocateVex(G, DepAirport); //���������ڶ��������е�λ���±�
    int TerminalPos = LocateVex(G, ArrAirport); //Ŀ�Ļ����ڶ��������е�λ���±�

    Req r;//���Դ洢�û��ĸ�������
    cout << "!!�뾡���ܶ�ļ�Ҫ�󣬷������·����ܶࡣ�������·�����࣬������ǰ2000�����ߣ�ÿͳ�Ƴ�100000�������������Loading...��һ�Ρ�" << endl;
    Request(r);//�û���������

    stack<Path*> PathNode;//·�����,�洢·���ϵ������Ϣ

    int FlightNum = 0;//����ͳ�ƺ�������
    for(int i = 0; i < G.vexnum; i++)//����ʼ����Ϊ���Ľ����ջ
    {
        if(G.arcs[StartPos][i])//��ǰλ���к���
        {
            ArcCell* p = G.arcs[StartPos][i];//���Ա����Դ˽��Ϊͷ�����к���
            while(p)//������˽����ص����к���
            {
                if(!IsMatchReq(r, 0, p))//��ǰ��㲻�������ʱ��Ҫ��ֱ������
                {
                    p =p->next;
                    continue;
                }
                if(i == TerminalPos)//ֱ��Ŀ�Ļ���
                {
                    if(IsMatchReq(r, 1, p))//�ִ�ʱ����Ҫ��Χ��
                    {
                        FlightNum++;
                        cout << "·��" << FlightNum << ": " << p->LineInfo.FlightID << endl;
                    }
                    p = p->next;//������һ����صĺ���
                    continue;
                }

                //�������к������ɽ����ջ
                Path *node = (Path*)malloc(sizeof(Path));
                node->TraceLen = 2;//��ǰ·����
                node->StartTime = p->LineInfo.DepTime;//��ʼʱ��Ϊ����ʱ��
                node->CurTime = p->LineInfo.ArrTime;//��ǰʱ��Ϊ�˺��ߵĵִ�ʱ��
                node->SumTime = node->CurTime - node->StartTime; //�ܺ�ʱ
                node->TraceAirport[0] = G.vexs[StartPos].data; //·�������Ļ���
                node->TraceAirport[1] = G.vexs[i].data;
                node->TraceID[0] = p->LineInfo.FlightID;
                PathNode.push(node);//��ջ
                p = p->next;
            }
        }
    }

    while(!PathNode.empty())//ջ�ǿգ�����DFS���ڱ��������н��м򵥵ļ�֦����
    {
        Path *pNode = PathNode.top();//ȡջ��Ԫ��
        PathNode.pop();

        int CurAirport = pNode->TraceAirport[pNode->TraceLen - 1];//��ǰ���ڻ���

        //��һ�������ɵĽ���е����һ����������ΪĿ�Ļ���,
        //֮�����ɵĽ�����������һ�����Ҳ����ΪĿ�Ļ�������ΪֻҪ��Ŀ�Ļ����ҷ���Ҫ����ֱ�������
        //�˴�����һ���ж���Ϊ��׳�Ե����֡�
        if(CurAirport == ArrAirport)
        {
            cout << "��ջ�����ִ���" << endl;
            return;
        }

        int CurPos = LocateVex(G, CurAirport);//��ǰ�Ļ����ڶ��������е��±�

        for(int i = 0; i < G.vexnum; i++)
        {
            if(G.arcs[CurPos][i] && i != StartPos)//��֤·���ϲ�������ʼ����
            {
                ArcCell *p = G.arcs[CurPos][i];
                if(i == TerminalPos)//�ִ�Ŀ�����
                {
                    while(p)
                    {
                        if(IsMatchReq(r, 2, p) && p->LineInfo.DepTime > pNode->CurTime)//���ϵִ�ʱ��Ҫ���Ҵ��˺������ʱ���ڵ�ǰʱ��֮����ʵ�в����ܵ��ڣ�
                        {
                            FlightNum++;
                            if(FlightNum <= 2000)//����ӡ���ǰ2000��
                            {
                                cout << "·��" << FlightNum << ": ";
                                for(int j = 0; j < pNode->TraceLen - 1; j++)
                                    cout << pNode->TraceID[j] << "->";

                                cout << p->LineInfo.FlightID << endl;
                            }
                            else if(FlightNum % 100000 == 0)//��10��ı���
                            {
                                cout << "Loading..." << endl;
                            }
                        }
                        p = p->next;
                    }
                    continue;
                }

                bool IsThrough = false;//���ڱ�ʾ��ǰ�����Ļ����Ƿ��Ѿ�������·���У���û�г�����Ϊfalse
                for(int j = 0; j < pNode->TraceLen; j++)//����·���������߹��Ļ���
                {
                    if(G.vexs[i].data == pNode->TraceAirport[j])//��ǰ�����Ѿ�������·���У����м�֦
                    {
                        IsThrough = true;
                        break;
                    }
                }

                if(!IsThrough)//ֻ��δ�����Ļ������б�Ҫ������
                {
                    while(p)//������˻�����ص����к���
                    {
                        if(p->LineInfo.DepTime > pNode->CurTime) //���˺�������ʱ���ڵ�ǰʱ�䣨���ִ�˻�����ʱ�䣩֮�󣬿���ͨ��
                        {
                            if(IsMatchReq(r, 2, p))//���ϻ���Ҫ��
                            {
                                Path *newNode = (Path*)malloc(sizeof(Path));
                                newNode->TraceLen = pNode->TraceLen + 1;
                                newNode->CurTime = p->LineInfo.ArrTime;
                                newNode->StartTime = pNode->StartTime;
                                newNode->SumTime = newNode->CurTime - newNode->StartTime;
                                newNode->TraceID[pNode->TraceLen - 1] = p->LineInfo.FlightID;//����ǰ���ߵ�ID��Ϣ�����½���·����Ϣ��

                                for(int k = 0; k < pNode->TraceLen - 1; k++)
                                {
                                    newNode->TraceID[k] = pNode->TraceID[k];
                                }
                                for(int k = 0; k < pNode->TraceLen; k++)
                                {
                                    newNode->TraceAirport[k] = pNode->TraceAirport[k];
                                }
                                newNode->TraceAirport[newNode->TraceLen - 1] = G.vexs[i].data;
                                PathNode.push(newNode);
                            }
                        }
                        p = p->next;
                    }
                }
            }
        }
        delete pNode;
        pNode = NULL;
    }

    cout << "Done!" << endl;
    if(FlightNum == 0)
    {
        cout << "�޷��ִ" << endl;
        return;
    }
    else
    {
        cout << "���еĲ�ͬ·�������ܼ�Ϊ��" << FlightNum << endl;
    }
}

//��ʼ������ͼG���������ڽӾ�����ʽ�洢
//����������������ʱ�λ��߽���ʱ�λ��߻���Ҫ�󣬴�ӡ���������������֮��ĺ��ѣ���Ʊ�۸���͵�·��
void Mission6(MGraph G)
{
    //�㷨˼����Mission3����

    cout << "���������������Ŀ�Ļ�������ţ�";
    int DepAirport, ArrAirport;
    cin >> DepAirport >> ArrAirport;

    if(DepAirport == ArrAirport)
    {
        cout << "�������룡����������Ŀ�Ļ�����ͬ��" << endl;
        return;
    }

    int StartPos = LocateVex(G, DepAirport); //���������ڶ��������е�λ���±�
    int TerminalPos = LocateVex(G, ArrAirport); //Ŀ�Ļ����ڶ��������е�λ���±�

    Req r;
    cout << "!!�뾡���ܶ�ļ�Ҫ�󣬷������ʱ����ܻ�ܳ���" << endl;
    Request(r);//�û���������

    int MinFare = INFINITY;//���Լ�¼���п��Եִ�Ŀ�Ļ����ĺ����е���̺���
    int MinAirportTrace[G.vexnum] = {G.vexs[StartPos].data, G.vexs[TerminalPos].data, 0}; //������飬�洢�������ٵ�·���Ļ�����Ϣ
    int MinIDtrace[G.vexnum] = {0}; //������飬�洢�������ٵ�·���ĺ���ID
    int TraceLen = 2; //·�����ȣ���ʼֵΪ2����ʾ��������������

    stack<Path*> PathNode;//·�����,�洢·���ϵ������Ϣ

    cout << "Loading..." << endl;

    for(int i = 0; i < G.vexnum; i++)//����ʼ����Ϊ���Ľ����ջ
    {
        if(G.arcs[StartPos][i])//��ǰλ���к���
        {
            ArcCell* p = G.arcs[StartPos][i];//���Ա����Դ˽��Ϊͷ�����к���
            while(p)//������˽����ص����к���
            {
                if(!IsMatchReq(r, 0, p))//���������ʱ�ε�Ҫ��
                {
                    p = p->next;
                    continue;
                }

                if(i == TerminalPos)//��������ֱ��Ŀ�Ļ����ĺ����е����ʱ�䣬�˽�㲻��Ҫ��������ջ��ֻ��Ҫȷ�����ʱ�䣬��Ϊʱ����Ͻ�
                {
                    if(IsMatchReq(r, 1, p))//����ִ�ʱ��Ҫ�󣬴�ʱ������ת��������
                    {
                        if(p->LineInfo.AirFare < MinFare)//ֻȡʱ����̵ĺ���
                        {
                            MinFare = p->LineInfo.AirFare;
                            MinIDtrace[0] = p->LineInfo.FlightID;
                            TraceLen = 2;
                        }
                    }

                    p = p->next;//������һ����صĺ���
                    continue;
                }

                //�������к������ɽ����ջ
                Path *node = (Path*)malloc(sizeof(Path));
                node->TraceLen = 2;//��ǰ·����
                node->StartTime = p->LineInfo.DepTime;//��ʼʱ��Ϊ����ʱ��
                node->CurTime = p->LineInfo.ArrTime;//��ǰʱ��Ϊ�˺��ߵĵִ�ʱ��
                node->SumTime = node->CurTime - node->StartTime; //�ܺ�ʱ
                node->SumFare = p->LineInfo.AirFare;//��ǰ�ܷ���
                node->TraceAirport[0] = G.vexs[StartPos].data; //·�������Ļ���
                node->TraceAirport[1] = G.vexs[i].data;
                node->TraceID[0] = p->LineInfo.FlightID;
                PathNode.push(node);//��ջ
                p = p->next;
            }
        }
    }

    while(!PathNode.empty())//ջ�ǿգ�����DFS���ڱ��������н���һϵ�м�֦���������������ܵ��Ż�
    {
        Path *pNode = PathNode.top();//ȡջ��Ԫ��
        PathNode.pop();

        int CurAirport = pNode->TraceAirport[pNode->TraceLen - 1];//��ǰ���ڻ���

        if(CurAirport == ArrAirport)//����Ѿ�����Ŀ�Ļ���
        {
            delete pNode;
            continue;
        }
        int CurPos = LocateVex(G, CurAirport);//��ǰ�Ļ����ڶ��������е��±�

        for(int i = 0; i < G.vexnum; i++)
        {
            if(G.arcs[CurPos][i] && i != StartPos)//��֤·���ϲ�������ʼ����
            {
                ArcCell *p = G.arcs[CurPos][i];
                if(i == TerminalPos)//Ŀ�Ļ���
                {
                    while(p)
                    {
                        if(IsMatchReq(r, 1, p) && p->LineInfo.DepTime > pNode->CurTime)//���ϵִ�ʱ��Ҫ���Լ�ת��Ҫ��
                        {
                            int SumFare = pNode->SumFare + p->LineInfo.AirFare;
                            if(SumFare < MinFare)
                            {
                                MinFare = SumFare;
                                TraceLen = pNode->TraceLen + 1;
                                int j;
                                for(j = 0; j < TraceLen - 2; j++)//����ID��Ϣ
                                    MinIDtrace[j] = pNode->TraceID[j];
                                MinIDtrace[j] = p->LineInfo.FlightID;

                                for(j = 0; j < TraceLen - 1; j++)//���»�����Ϣ
                                    MinAirportTrace[j] = pNode->TraceAirport[j];
                                MinAirportTrace[j] = p->LineInfo.ArrAirport;
                            }
                        }
                        p = p->next;
                    }
                    continue;
                }

                bool IsThrough = false;//���ڱ�ʾ��ǰ�����Ļ����Ƿ��Ѿ�������·���У���û�г�����Ϊfalse
                for(int j = 0; j < pNode->TraceLen; j++)//����·���������߹��Ļ���
                {
                    if(G.vexs[i].data == pNode->TraceAirport[j])//��ǰ�����Ѿ�������·���У����м�֦
                    {
                        IsThrough = true;
                        break;
                    }
                }

                if(!IsThrough)//ֻ��δ�����Ļ������б�Ҫ������
                {
                    while(p)//������˻�����ص����к���
                    {
                        if(p->LineInfo.DepTime > pNode->CurTime) //���˺�������ʱ���ڵ�ǰʱ�䣨���ִ�˻�����ʱ�䣩֮�󣬿���ͨ��
                        {
                            if(IsMatchReq(r, 2, p) && (pNode->SumFare + p->LineInfo.AirFare) < MinFare)//���ϻ���Ҫ���Һ���ҪС�ڵ�ǰ�ִ�Ŀ�Ļ��������ٺ���
                            {
                                Path *newNode = (Path*)malloc(sizeof(Path));
                                newNode->TraceLen = pNode->TraceLen + 1;
                                newNode->CurTime = p->LineInfo.ArrTime;
                                newNode->StartTime = pNode->StartTime;
                                newNode->SumTime = newNode->CurTime - newNode->StartTime;
                                newNode->SumFare = pNode->SumFare + p->LineInfo.AirFare;

                                for(int k = 0; k < newNode->TraceLen - 2; k++)
                                {
                                    newNode->TraceID[k] = pNode->TraceID[k];
                                }
                                newNode->TraceID[newNode->TraceLen - 2] = p->LineInfo.FlightID;//TraceLen��¼·���еĻ�������������ID���Ȼ�������һ

                                for(int k = 0; k < newNode->TraceLen - 1; k++)
                                {
                                    newNode->TraceAirport[k] = pNode->TraceAirport[k];
                                }
                                newNode->TraceAirport[newNode->TraceLen - 1] = G.vexs[i].data;

                                newNode->SumFare = pNode->SumFare + p->LineInfo.AirFare;//�ܷ��õĸı�
                                PathNode.push(newNode);
                            }
                        }
                        p = p->next;
                    }
                }
            }
        }
        delete pNode;
    }

    cout << "Done!" << endl;
    if(MinFare == INFINITY)
    {
        cout << "�޷��ִ" << endl;
        return;
    }

    cout << "��̺���Ϊ��" << MinFare << endl;
    cout << "·��Ϊ��" << endl << "����ID:";
    int i = 0;
    for(i = 0; i < TraceLen - 2; i++)
        cout << MinIDtrace[i] << "->";

    cout << MinIDtrace[i] << endl << "������";

    for(i = 0; i < TraceLen - 1; i++)
        cout << MinAirportTrace[i] << "->";

    cout << MinAirportTrace[TraceLen - 1] << endl;
}

//��ʼ������ͼG���������ڽӾ�����ʽ�洢
//�����������������ʱ��������תʱ�����ƣ���ӡ����������������Ķ����ѡ���ߣ�����ID˳���
void Mission7(MGraph G)
{
    //�㷨˼����Mission3����

    cout << "���������������Ŀ�Ļ�������ţ�";
    int DepAirport, ArrAirport;
    cin >> DepAirport >> ArrAirport;

    if(DepAirport == ArrAirport)
    {
        cout << "�������룡����������Ŀ�Ļ�����ͬ��" << endl;
        return;
    }

    int TransUpLimit = INFINITY, TransDownLimit = 0;//�ֱ�Ϊת��ʱ������½�,Ĭ�Ϸֱ�Ϊ������0
    int FlightMaxTime = INFINITY, FlightMinTime = 0; //�ֱ�Ϊ���е��ʱ������ʱ�䣬Ĭ�Ϸֱ�Ϊ������0

    cout << "!!�����뾡���ܶ��Ҫ�󣬲�Ȼ�⼯��ܴ�" << endl;//���Լ��Ͻ�ǰ2000�����
    cout << "��ֱ��������ʱ�����½����Ͻ磨�Է���Ϊ��λ����������-1 -1����";
    cin >> FlightMinTime >> FlightMaxTime;
    if(FlightMinTime == -1)//��Ҫ��
    {
        FlightMaxTime = INFINITY;
        FlightMinTime = 0;
    }

    cout << "��ֱ�����ÿ��ת��ʱ�����½����Ͻ磨�Է���Ϊ��λ����������-1 -1����";
    cin >> TransDownLimit >> TransUpLimit;
    if(TransDownLimit == -1)
    {
        TransUpLimit = INFINITY;
        TransDownLimit = 0;
    }
    int StartPos = LocateVex(G, DepAirport); //���������ڶ��������е�λ���±�
    int TerminalPos = LocateVex(G, ArrAirport); //Ŀ�Ļ����ڶ��������е�λ���±�

    stack<Path*> PathNode;//·�����,�洢·���ϵ������Ϣ

    cout << "Loading..." << endl;

    int FlightNum = 0;//����ͳ�ƺ�������
    for(int i = 0; i < G.vexnum; i++)//����ʼ����Ϊ���Ľ����ջ
    {
        if(G.arcs[StartPos][i])//��ǰλ���к���
        {
            ArcCell* p = G.arcs[StartPos][i];//���Ա����Դ˽��Ϊͷ�����к���
            while(p)//������˽����ص����к���
            {
                if(p->LineInfo.ArrTime - p->LineInfo.DepTime < FlightMinTime ||
                        p->LineInfo.ArrTime - p->LineInfo.DepTime > FlightMaxTime)//��ǰ��㲻�������ʱ��Ҫ��ֱ������
                {
                    p = p->next;
                    continue;
                }
                if(i == TerminalPos)//ֱ��Ŀ�Ļ�����������ת
                {

                    FlightNum++;
                    cout << "·��" << FlightNum << ": " << p->LineInfo.FlightID << endl;

                    p = p->next;//������һ����صĺ���
                    continue;
                }

                //�������к������ɽ����ջ
                Path *node = (Path*)malloc(sizeof(Path));
                node->TraceLen = 2;//��ǰ·����
                node->StartTime = p->LineInfo.DepTime;//��ʼʱ��Ϊ����ʱ��
                node->CurTime = p->LineInfo.ArrTime;//��ǰʱ��Ϊ�˺��ߵĵִ�ʱ��
                node->SumTime = node->CurTime - node->StartTime; //�ܺ�ʱ
                node->TraceAirport[0] = G.vexs[StartPos].data; //·�������Ļ���
                node->TraceAirport[1] = G.vexs[i].data;
                node->TraceID[0] = p->LineInfo.FlightID;
                PathNode.push(node);//��ջ
                p = p->next;
            }
        }
    }

    while(!PathNode.empty())//ջ�ǿգ�����DFS���ڱ��������н��м򵥵ļ�֦����
    {
        Path *pNode = PathNode.top();//ȡջ��Ԫ��
        PathNode.pop();

        int CurAirport = pNode->TraceAirport[pNode->TraceLen - 1];//��ǰ���ڻ���

        if(pNode->SumTime > FlightMaxTime)//����ǰ���������ʱ���Ѿ�����ʱ������,�������ж�
            continue;

        if(CurAirport == ArrAirport)//���ջ��Ԫ�صĻ���ΪĿ�Ļ�������˽�������Ҫ����
        {
            cout << "��ǰ������" << endl;
            return;
        }

        int CurPos = LocateVex(G, CurAirport);//��ǰ�Ļ����ڶ��������е��±�

        for(int i = 0; i < G.vexnum; i++)
        {
            if(G.arcs[CurPos][i] && i != StartPos)//��֤·���ϲ�������ʼ����
            {
                ArcCell *p = G.arcs[CurPos][i];//���Ա���������

                if(i == TerminalPos)//�ִ�Ŀ�����
                {
                    while(p)
                    {
                        int SumTime = p->LineInfo.ArrTime - pNode->StartTime;//��������˺�����ܺ�ʱ
                        int TransTime = p->LineInfo.DepTime - pNode->CurTime;//��������˺����ת��ʱ�������޷�ת�������ʱ����Ϊ��ֵ
                        if((TransTime >= TransDownLimit && TransTime <= TransUpLimit)
                                && (SumTime >= FlightMinTime && SumTime <= FlightMaxTime))//����ת��Ҫ���Լ��ܺ���ʱ���Ҫ��
                        {
                            FlightNum++;
                            if(FlightNum <= 2000)
                            {
                                cout << "·��" << FlightNum << ": ";
                                for(int j = 0; j < pNode->TraceLen - 1; j++)
                                    cout << pNode->TraceID[j] << "->";

                                cout << p->LineInfo.FlightID << endl;
                            }
                            else if(FlightNum % 100000 == 0)//��10��ı���
                            {
                                cout << "Loading..." << endl;
                            }
                        }
                        p = p->next;
                    }
                    continue;
                }

                bool IsThrough = false;//���ڱ�ʾ��ǰ�����Ļ����Ƿ��Ѿ�������·���У���û�г�����Ϊfalse
                for(int j = 0; j < pNode->TraceLen; j++)//����·���������߹��Ļ���
                {
                    if(G.vexs[i].data == pNode->TraceAirport[j])//��ǰ�����Ѿ�������·���У����м�֦
                    {
                        IsThrough = true;
                        break;
                    }
                }

                if(!IsThrough)//ֻ��δ�����Ļ������б�Ҫ������
                {
                    while(p)//������˻�����ص����к���
                    {
                        int SumTime = p->LineInfo.ArrTime - pNode->StartTime;//��������˺�����ܺ�ʱ
                        int TransTime = p->LineInfo.DepTime - pNode->CurTime;//��������˺����ת��ʱ�������޷�ת�������ʱ����Ϊ��ֵ
                        if(TransTime >= TransDownLimit && TransTime <= TransUpLimit) //���˺����ת��ʱ����Ҫ��Χ��
                        {
                            if(SumTime <= FlightMaxTime)//��ǰ����ʱ�仹δ��������ʱ�����޵ĺ����������
                            {
                                Path *newNode = (Path*)malloc(sizeof(Path));
                                newNode->TraceLen = pNode->TraceLen + 1;
                                newNode->CurTime = p->LineInfo.ArrTime;
                                newNode->StartTime = pNode->StartTime;
                                newNode->SumTime = newNode->CurTime - newNode->StartTime;

                                for(int k = 0; k < pNode->TraceLen - 1; k++)
                                {
                                    newNode->TraceID[k] = pNode->TraceID[k];
                                }
                                newNode->TraceID[pNode->TraceLen - 1] = p->LineInfo.FlightID;

                                for(int k = 0; k < pNode->TraceLen; k++)
                                {
                                    newNode->TraceAirport[k] = pNode->TraceAirport[k];
                                }
                                newNode->TraceAirport[newNode->TraceLen - 1] = G.vexs[i].data;
                                PathNode.push(newNode);
                            }
                        }
                        p = p->next;
                    }
                }
            }
        }
        delete pNode;
    }

    cout << "Done!" << endl;
    if(FlightNum == 0)
    {
        cout << "�޷��ִ" << endl;
        return;
    }
    else
    {
        cout << "���еĲ�ͬ·�������ܼ�Ϊ��" << FlightNum << endl;
    }
}
