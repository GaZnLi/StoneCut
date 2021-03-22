#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#define num_SmallStone 200

using namespace std;
int LL;
int WW;
int s=0;
int n;//n��Сʯ��
vector<int> vl;//�泤��l
vector<int> vw;//����w
int flag;
int countNum[3];
struct
{
    int l;
    int w;
    int s;
    int t;//�ж��ܲ�����
}data[num_SmallStone];//��ÿ��Сʯ��ĳ��������

void sort_S()
{
    //̰���㷨�Ӵ�С�������д��
    int j,i,keyS,keyL,keyW;
    for(j=1;j<n;j++)
    {
        keyS=data[j].s;
        keyL=data[j].l;
        keyW=data[j].w;
        i=j-1;
        while(i>=0&&data[i].s<keyS)
        {
            data[i+1].s=data[i].s;
            data[i+1].l=data[i].l;
            data[i+1].w=data[i].w;
            i=i-1;
        }
        data[i+1].s=keyS;
        data[i+1].l=keyL;
        data[i+1].w=keyW;
    }

}
void sort_L()
{
    //̰���㷨�Ӵ�С�������д��
    int j,i,keyS,keyL,keyW;
    for(j=1;j<n;j++)
    {
        keyS=data[j].s;
        keyL=data[j].l;
        keyW=data[j].w;
        i=j-1;
        while(i>=0&&data[i].l<keyL)
        {
            data[i+1].s=data[i].s;
            data[i+1].l=data[i].l;
            data[i+1].w=data[i].w;
            i=i-1;
        }
        data[i+1].s=keyS;
        data[i+1].l=keyL;
        data[i+1].w=keyW;
    }

}
void sort_W()
{
    //̰���㷨�Ӵ�С�������д��
    int j,i,keyS,keyL,keyW;
    for(j=1;j<n;j++)
    {
        keyS=data[j].s;
        keyL=data[j].l;
        keyW=data[j].w;
        i=j-1;
        while(i>=0&&data[i].w<keyW)
        {
            data[i+1].s=data[i].s;
            data[i+1].l=data[i].l;
            data[i+1].w=data[i].w;
            i=i-1;
        }
        data[i+1].s=keyS;
        data[i+1].l=keyL;
        data[i+1].w=keyW;
    }

}

int  cutting(int s_l,int s_w,int t)
{
    t=0;
    int length = vl.size();
    for(int i = 0; i < length; ++i)
    {
        if(vl[i]>=s_l&&vw[i]>=s_w)
    {
        t=1;
        vl.push_back(vl[i]-s_l);
        vw.push_back(s_w);

        vl.push_back(vl[i]);
        vw.push_back(vw[i]-s_w);
        vl.erase(vl.begin()+i);//�Ƴ��Ѿ����еĴ�ש��
        vw.erase(vw.begin()+i);
        break;

    }

    }
    return t;
}
//����������
double cal_useRatio(int SS)
{
    int s=0;
    for(int i = 0; i < n; ++i)
    {
        if(data[i].t==1)
        {
            s=s+data[i].s;
        }
    }
    double useRatio;
    useRatio = s/(double)SS * 100;
    return useRatio;

}
int printStone(int temp)
{
    //��ӡ��������ߵ�����ʹ�õ�ʯ��
    for(int i = 0; i < n; ++i)
    {
        if(data[i].t==1)
        {
           cout << "l=" << data[i].l << ",w=" << data[i].w << endl;
           temp++;
        }
    }
    cout << "δ�����õ�ʯ��" << endl;
    for(int i = 0; i < n; ++i)
    {
        if(data[i].t==0)
        {
           cout << "l=" << data[i].l << ",w=" << data[i].w << endl;
        }
    }
    return temp;
}
int main()
{
    cout << "�����ʯ��ĳ�����:" ;
    cin >> LL;
    cin >> WW;
    int SS = LL * WW;
    cout << "����Сʯ��ĸ���:" ;
    cin >> n;
    cout <<"������" << n << "��Сʯ��ĳ�����" << endl;
    for(int i = 0; i < n; ++i)
    {
        cin >> data[i].l;
        cin >> data[i].w;
        data[i].s = data[i].l * data[i].w;
        data[i].t = 0;

    }

    //̰����������и�
    cout << "************Cutting************" << endl;
    double useRation[3];

    //̰����������и�
    sort_S();
    vl.push_back(LL);
    vw.push_back(WW);
    for(int i = 0; i < n; ++i)
    {
        data[i].t = cutting(data[i].l,data[i].w,data[i].t);
    }
    useRation[0]=cal_useRatio(SS);
    vl.clear();
    vw.clear();

    //̰�ĳ��������и�
    sort_L();
    vl.push_back(LL);
    vw.push_back(WW);
    for(int i = 0; i < n; ++i)
    {
        data[i].t = cutting(data[i].l,data[i].w,data[i].t);
    }
    useRation[1]=cal_useRatio(SS);
    vl.clear();
    vw.clear();

    //̰�Ŀ�������и�
    sort_W();
    vl.push_back(LL);
    vw.push_back(WW);
    for(int i = 0; i < n; ++i)
    {
        data[i].t = cutting(data[i].l,data[i].w,data[i].t);
    }
    useRation[2]=cal_useRatio(SS);
    vl.clear();
    vw.clear();

    double temp , maxUsing;
    temp=useRation[0]>useRation[1]?useRation[0]:useRation[1];
    maxUsing=temp>useRation[2]?temp:useRation[2];
    cout << "���������Ϊ��" << maxUsing << "%" << endl;
    for(int i = 0; i < 3; ++i)
    {
        if(maxUsing==useRation[i])
        {
            flag=i;
        }
    }
    if(flag==0)
    {
        cout << "�������̰���и�\n��ʹ�õ�Сש��Ϊ��" << endl;
        sort_S();
        vl.push_back(LL);
        vw.push_back(WW);
        for(int i = 0; i < n; ++i)
        {
            data[i].t = cutting(data[i].l,data[i].w,data[i].t);
        }
        countNum[0]=printStone(0);
        cout << "���õ���ʯ������" << countNum[0] << endl;
        vl.clear();
        vw.clear();

    }

    if(flag==1)
    {
        cout << "��������̰���и�\n��ʹ�õ�Сש��Ϊ��" << endl;
        sort_L();
        vl.push_back(LL);
        vw.push_back(WW);
        for(int i = 0; i < n; ++i)
        {
            data[i].t = cutting(data[i].l,data[i].w,data[i].t);
        }
        countNum[1]=printStone(0);
        cout << "���õ���ʯ������" << countNum[1] << endl;
        vl.clear();
        vw.clear();

    }

    if(flag==2)
    {
        cout << "�������̰���и�\n��ʹ�õ�Сש��Ϊ��" << endl;
        sort_W();
        vl.push_back(LL);
        vw.push_back(WW);
        for(int i = 0; i < n; ++i)
        {
            data[i].t = cutting(data[i].l,data[i].w,data[i].t);
        }
        countNum[2]=printStone(0);
        cout << "���õ���ʯ������" << countNum[2] << endl;
        vl.clear();
        vw.clear();
    }


    return 0;
}
