// lecture3.cpp

#include <iostream>

using namespace std;

void listing_2_19()
{
    int i=100, m=100;
    cout<<i<<':'<<i++<<"+1="<<i<<endl;
    cout<<m<<':'<<m++<<"+1="; cout<<m<<endl;
    m=2; cout<<m<<endl; cout<<m<<':'<<m++*m++<<endl; cout<<m<<endl;
    m=2; cout<<m<<endl; cout<<m<<':'<<(++m)*(++m)<<endl; cout<<m<<endl;
}

void listing_2_20()
{
    int i=0, j=0, k=0;
    i=j=k++; cout<<i<<','<<j<<endl;
    i=k++; j=k++; cout<<i<<','<<j<<endl;
}

int main()
{
    listing_2_20();

    return 0;
}