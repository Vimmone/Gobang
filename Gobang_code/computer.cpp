#include "computer.h"

computer::computer()
{
    init();
}
void computer::init()                                               //初始化
{
    hh.clear();
    gg.clear();
    memset(a,'-',sizeof(a));
    memset(b,0,sizeof(b));
}
void computer::back(int x,int y)                                    //悔棋
{
    int i= y/30-1;
    int j=x/30-1;
    a[i][j]='-';
    seet1(i,j);
    gg.clear();
    hh.erase(hh.find(i*19+j));
    for(QSet<int>::iterator it=hh.begin();it!=hh.end();it++)
    {
            int k=*it;
            i=k/19,j=k%19;
            seet(i,j);
    }
}
void computer::insert(int x,int y)                                  //插入已经下的棋的位置
{
    seet(x,y);
    hh.insert(x*19+y);
    a[x][y]='$';
}

int computer::win()                                                 //判断输赢
{
    int k,i,j,t=0;
    for(QSet<int>::iterator it=hh.begin();it!=hh.end();it++)
    {
            k=*it;
            i=k/19,j=k%19;
            if(a[i][j]=='$'&&findscord(i,j)>=100000) t=1;
            else if(a[i][j]=='@'&&findscord(i,j)>=100000) return 2;
     }
    return t;
}
void computer::seet1(int n,int m)                                   //把附近没有棋子的空白位置移除出待选集合
{
    int y;
    if(ok(n-1,m-1)&&a[n-1][m-1]=='-')
    {
        int k=(n-1)*19+m-1;
      b[k]--;
      if(!b[k]) gg.erase(gg.find(k));
    }
    if(ok(n-1,m)&&a[n-1][m]=='-')
    {
        int k=(n-1)*19+m;
       b[k]--;
      if(!b[k]) gg.erase(gg.find(k));
    }
    if(ok(n-1,m+1)&&a[n-1][m+1]=='-')
    {
        int k=(n-1)*19+m+1;
       b[k]--;
      if(!b[k]) gg.erase(gg.find(k));
    }

    if(ok(n,m-1)&&a[n][m-1]=='-')
    {
        int k=(n)*19+m-1;
        b[k]--;
      if(!b[k]) gg.erase(gg.find(k));
    }
    if(ok(n,m+1)&&a[n][m+1]=='-')
    {
        int k=(n)*19+m+1;
      b[k]--;
      if(!b[k]) gg.erase(gg.find(k));
    }
    if(ok(n+1,m-1)&&a[n+1][m-1]=='-')
    {
        int k=(n+1)*19+m-1;
      b[k]--;
      if(!b[k]) gg.erase(gg.find(k));
    }
    if(ok(n+1,m)&&a[n+1][m]=='-')
    {
        int k=(n+1)*19+m;
        b[k]--;
      if(!b[k]) gg.erase(gg.find(k));

    }
    if(ok(n+1,m+1)&&a[n+1][m+1]=='-')
    {

        int k=(n+1)*19+m+1;
     b[k]--;
      if(!b[k]) gg.erase(gg.find(k));
    }
}
void computer:: seet(int n,int m)                                   //把已经下的棋的附近空白位置加入待选集合
{
    int y;
    if(ok(n-1,m-1)&&a[n-1][m-1]=='-')
    {
        int k=(n-1)*19+m-1;
        gg.insert(k);
        b[k]++;
    }
    if(ok(n-1,m)&&a[n-1][m]=='-')
    {
        int k=(n-1)*19+m;
        gg.insert(k);b[k]++;

    }
    if(ok(n-1,m+1)&&a[n-1][m+1]=='-')
    {
        int k=(n-1)*19+m+1;
        gg.insert(k);b[k]++;

    }

    if(ok(n,m-1)&&a[n][m-1]=='-')
    {
        int k=(n)*19+m-1;
        gg.insert(k);b[k]++;
    }
    if(ok(n,m+1)&&a[n][m+1]=='-')
    {
        int k=(n)*19+m+1;
        gg.insert(k);b[k]++;
    }
    if(ok(n+1,m-1)&&a[n+1][m-1]=='-')
    {
        int k=(n+1)*19+m-1;
        gg.insert(k);b[k]++;
    }
    if(ok(n+1,m)&&a[n+1][m]=='-')
    {
        int k=(n+1)*19+m;
        gg.insert(k);b[k]++;
    }
    if(ok(n+1,m+1)&&a[n+1][m+1]=='-')
    {

        int k=(n+1)*19+m+1;
      gg.insert(k);b[k]++;
    }
}
int  computer::xy(int x,int y)                                          //把Gobang下的棋子传递给computer
{
    int i= y/30-1;
    int j=x/30-1;
    if(a[i][j]!='-') return -1;
    a[i][j]='@';
    hh.insert((i)*19+j);
    seet(i,j);
    i_1=0,j_1=0;
    maxput(3);
    seet(i_1,j_1);
    hh.insert(i_1*19+j_1);
    gg.erase(gg.find(i_1*19+j_1));
    a[i_1][j_1]='$';
    return i_1*19+j_1;                                                  //返回电脑下的位置

}
int computer:: maxput(int n)                                            //极大极小算法的max函数
{
        if(n==1) return countscore();
        int t=-100000000,w=0,k,i,j;
            for(QSet<int>::iterator it2=gg.begin();it2!=gg.end();it2++)
            {

               i=*it2/19;j=*it2% 19;
                if(a[i][j]=='-')
                {
                    a[i][j]='$';

                    seet(i,j);
                    hh.insert(*it2);

                    k=minput(n-1);

                    seet1(i,j);
                    if(t<k)
                    {
                        t=k;
                        if(n==3) i_1=i,j_1=j;
                    }
                     a[i][j]='-';
                     hh.erase(hh.find(*it2));
                }
            }

        return t;
}

int computer::minput(int n)                                             //极大极小算法的min函数
{
    if(n==1) return countscore();
    int t=100000000,w=0,k,i,j;

        for(QSet<int>::iterator it2=gg.begin();it2!=gg.end();it2++)
        {
           i=*it2/19;j=*it2% 19;
            if(a[i][j]=='-')
            {
                a[i][j]='@';
                seet(i,j);
                hh.insert(*it2);
                k=maxput(n-1);
                seet1(i,j);
                if(t>k)
                {
                    t=k;
                }
                 a[i][j]='-';
                hh.erase(hh.find(*it2));
            }
        }
    return t;
}
int computer::countscore()                                              //进行棋盘评分
{
    int cs=0,ps=0,t,i,j,k;
    for(QSet<int>::iterator it=hh.begin();it!=hh.end();it++)
    {
            k=*it;
            i=k/19,j=k%19;
            if(a[i][j]=='$')
            {
                t=findscord(i,j);
                if(t>=10000)
                {
                    t+=10000;
                }
                cs+=t;
             }
            else if(a[i][j]=='@') ps+=findscord(i,j);
     }
       return cs-ps;
}
int computer::findscord(int n,int m)                                   //进行棋子评分
{
    p=0,q=0;
        int t=0,k,g,ppp,qqq;
        if(a[n][m]=='@') str='@';
        else if(a[n][m]=='$') str='$';
      qq=0;pp=0;
        c[1]=find1(n,m)+1;
        ppp=pp,qqq=qq;
        c[1]+=find5(n,m);
        k=0,g=0;
        if(p&&(!q)) c[1]+=find1(ppp,qqq);
        else if(!p&&q) c[1]+=find5(pp,qq);
        else if(p&&q)
        {
            k=find1(ppp,qqq);
            g=find5(pp,qq);
            if(k+p>=g+q) c[1]+=k,q=1;
            else c[1]+=g,p=1;
        }
        t=t+find_d(1);p=0,q=0;qq=0;pp=0;
        c[2]=find2(n,m)+1;
        ppp=pp,qqq=qq;
        c[2]+=find6(n,m);
        k=0,g=0;
        if(p&&(!q)) c[2]+=find2(ppp,qqq);
        else if(!p&&q) c[2]+=find6(pp,qq);
        else if(p&&q)
        {
            k=find2(ppp,qqq);
            g=find6(pp,qq);
            if(k+p>=g+q) c[2]+=k,q=1;
            else c[2]+=g,p=1;
        }
        t=t+find_d(2);p=0,q=0;qq=0;pp=0;
        c[3]=find3(n,m)+1;
        ppp=pp,qqq=qq;
        c[3]+=find7(n,m);
        k=0,g=0;
        if(p&&(!q)) c[3]+=find3(ppp,qqq);
        else if(!p&&q) c[3]+=find7(pp,qq);
        else if(p&&q)
        {
            k=find3(ppp,qqq);
            g=find7(pp,qq);
            if(k+p>=g+q) c[3]+=k,q=1;
            else c[3]+=g,p=1;
        }
        t=t+find_d(3);p=0,q=0;qq=0;pp=0;
        c[4]=find4(n,m)+1;
        ppp=pp,qqq=qq;
        c[4]+=find8(n,m);
        k=0,g=0;
        if(p&&(!q)) c[4]+=find4(ppp,qqq);
        else if(!p&&q) c[4]+=find8(pp,qq);
        else if(p&&q)
        {
            k=find4(ppp,qqq);
            g=find8(pp,qq);
            if(k+p>=g+q) c[4]+=k,q=1;
            else c[4]+=g,p=1;
        }
        t=t+find_d(4);p=0,q=0;
        if(t>=2000&&t<=10000) t+=8000;

        return t;
}
int computer:: ok(int i,int j)                                      //判断位置是否合法
{
    if(i>=0&&j>=0&&i<19&&j<19) return 1;
    return 0;
}

int computer:: find1(int n,int m)
{
    if(ok(n-1,m-1)&&a[n-1][m-1]==str)  return 1+find1(n-1,m-1);

       if(ok(n-1,m-1)&&a[n-1][m-1]=='-')
       {
           p=1;pp=n-1;qq=m-1;
       }
       return 0;
}
int computer:: find2(int n,int m)
{
    if(ok(n-1,m)&&a[n-1][m]==str) return 1+find2(n-1,m);

       if(ok(n-1,m)&&a[n-1][m]=='-')
       {
           p=1;pp=n-1;qq=m;
       }
       return 0;
}
int computer:: find3(int n,int m)
{
    if(ok(n-1,m+1)&&a[n-1][m+1]==str) return 1+find3(n-1,m+1);

       if(ok(n-1,m+1)&&a[n-1][m+1]=='-')
       {
           p=1;pp=n-1;qq=m+1;
       }
       return 0;
}
int computer:: find4(int n,int m)
{
    if(ok(n,m+1)&&a[n][m+1]==str) return 1+find4(n,m+1);

        if(ok(n,m+1)&&a[n][m+1]=='-')
        {
            p=1;pp=n;qq=m+1;
        }
        return 0;
}
int computer:: find5(int n,int m)
{
    if(ok(n+1,m+1)&&a[n+1][m+1]==str) return 1+find5(n+1,m+1);

       if(ok(n+1,m+1)&&a[n+1][m+1]=='-')
       {
           q=1;pp=n+1;qq=m+1;
       }
       return 0;
}
int computer:: find6(int n,int m)
{
    if(ok(n+1,m)&&a[n+1][m]==str) return 1+find6(n+1,m);

       if(ok(n+1,m)&&a[n+1][m]=='-')
       {
           q=1;pp=n+1;qq=m;
       }
       return 0;
}
int computer:: find7(int n,int m)
{
    if(ok(n+1,m-1)&&a[n+1][m-1]==str) return 1+find7(n+1,m-1);

        if(ok(n+1,m-1)&&a[n+1][m-1]=='-')
        {
            q=1;pp=n+1;qq=m-1;
        }
        return 0;
}
int computer:: find8(int n,int m)
{
    if(ok(n,m-1)&&a[n][m-1]==str) return 1+find8(n,m-1);

        if(ok(n,m-1)&&a[n][m-1]=='-')
        {
            q=1;pp=n;qq=m-1;
        }
        return 0;
}
int computer::find_d(int i)
{
     if(c[i]>=5) return 100000;
     if(c[i]==4)
     {
         if(p&&q) return 10000;
         if(p^q) return 1000;
         return 0;
     }
     if(c[i]==3)
     {
         if(p&&q) return 1000;
         if(p^q) return 100;
         return 0;
     }
      if(c[i]==2)
     {
         if(p&&q) return 100;
         if(p^q) return 10;
         return 0;
     }
     if(c[i]==1)
     {

         if(p&&q)
         {
             return 10;
         }
         if(p^q) return 1;
         return 0;
     }
}
