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
int n;//n个小石块
vector<int> vl;//存长度l
vector<int> vw;//存宽度w
int flag;
int countNum[3];
struct
{
    int l;
    int w;
    int s;
    int t;//判断能不能切
}data[num_SmallStone];//存每个小石块的长、宽、面积

void sort_S()
{
    //贪心算法从大到小排序，先切大的
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
    //贪心算法从大到小排序，先切大的
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
    //贪心算法从大到小排序，先切大的
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
        vl.erase(vl.begin()+i);//移除已经被切的大砖块
        vw.erase(vw.begin()+i);
        break;

    }

    }
    return t;
}
//计算利用率
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
    //打印利用率最高的排序使用的石块
    for(int i = 0; i < n; ++i)
    {
        if(data[i].t==1)
        {
           cout << "l=" << data[i].l << ",w=" << data[i].w << endl;
           temp++;
        }
    }
    cout << "未被利用的石块" << endl;
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
    cout << "输入大石块的长，宽:" ;
    cin >> LL;
    cin >> WW;
    int SS = LL * WW;
    cout << "输入小石块的个数:" ;
    cin >> n;
    cout <<"请输入" << n << "个小石块的长，宽" << endl;
    for(int i = 0; i < n; ++i)
    {
        cin >> data[i].l;
        cin >> data[i].w;
        data[i].s = data[i].l * data[i].w;
        data[i].t = 0;

    }

    //贪心面积优先切割
    cout << "************Cutting************" << endl;
    double useRation[3];

    //贪心面积优先切割
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

    //贪心长度优先切割
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

    //贪心宽度优先切割
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
    cout << "最高利用率为：" << maxUsing << "%" << endl;
    for(int i = 0; i < 3; ++i)
    {
        if(maxUsing==useRation[i])
        {
            flag=i;
        }
    }
    if(flag==0)
    {
        cout << "面积排序贪心切割\n被使用的小砖块为：" << endl;
        sort_S();
        vl.push_back(LL);
        vw.push_back(WW);
        for(int i = 0; i < n; ++i)
        {
            data[i].t = cutting(data[i].l,data[i].w,data[i].t);
        }
        countNum[0]=printStone(0);
        cout << "共用到的石块数：" << countNum[0] << endl;
        vl.clear();
        vw.clear();

    }

    if(flag==1)
    {
        cout << "长度排序贪心切割\n被使用的小砖块为：" << endl;
        sort_L();
        vl.push_back(LL);
        vw.push_back(WW);
        for(int i = 0; i < n; ++i)
        {
            data[i].t = cutting(data[i].l,data[i].w,data[i].t);
        }
        countNum[1]=printStone(0);
        cout << "共用到的石块数：" << countNum[1] << endl;
        vl.clear();
        vw.clear();

    }

    if(flag==2)
    {
        cout << "宽度排序贪心切割\n被使用的小砖块为：" << endl;
        sort_W();
        vl.push_back(LL);
        vw.push_back(WW);
        for(int i = 0; i < n; ++i)
        {
            data[i].t = cutting(data[i].l,data[i].w,data[i].t);
        }
        countNum[2]=printStone(0);
        cout << "共用到的石块数：" << countNum[2] << endl;
        vl.clear();
        vw.clear();
    }


    return 0;
}
