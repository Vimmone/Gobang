#ifndef COMPUTER_H
#define COMPUTER_H
#include <QSet>
class computer
{
public:
    computer();
    int xy(int x,int y);
    int win();
    void init();
    void back(int x,int y);
    void insert(int x,int y);
private:
    QSet<int>hh,gg;
    int maxput(int n);
    int minput(int n);
    int countscore();
    int findscord(int n,int m);
    int p,q,qq,pp,c[5];
    char str, a[20][20];
    int find1(int n,int m),find2(int n,int m),find3(int n,int m),
    find6(int n,int m),find5(int n,int m),find4(int n,int m),
    find8(int n,int m),find7(int n,int m),find_d(int i);
    int ok(int i,int j);
    int i_1,j_1,b[400];
    void seet(int n,int m);
    void seet1(int n,int m);
};
#endif // COMPUTER_H
