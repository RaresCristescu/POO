#include <iostream>
#include<string.h>
using namespace std;
class vec_mari;

class nr_int_mari
{
char semn;
char *nr;
public:
    nr_int_mari(){semn='+';}
    friend istream &operator >>(istream&,nr_int_mari&);
    friend ostream &operator <<(ostream&,nr_int_mari&);
    friend nr_int_mari operator +(nr_int_mari ,nr_int_mari );
    friend nr_int_mari operator +(nr_int_mari ,int);
    friend nr_int_mari operator -(nr_int_mari ,nr_int_mari );
    friend nr_int_mari operator *(nr_int_mari ,nr_int_mari );
    friend nr_int_mari operator *(nr_int_mari ,int);
    friend int operator >(nr_int_mari n1,nr_int_mari n2);
    nr_int_mari maxim( const nr_int_mari &b);
    friend void transf(char*,int,int*);
    friend class vec_mari;
};
istream &operator>>(istream & in, nr_int_mari& p)
{
    char v[1000];
    in>>v;
    p.nr=new char[strlen(v)+1];
    if(v[0]=='-'||v[0]=='+'){
    p.semn=v[0];
    strcpy(p.nr,v+1);}
    else strcpy(p.nr,v);
    return in;
}
ostream &operator <<(ostream&out,nr_int_mari&p)
{
    out<<p.semn<<p.nr;
    return out;
}
int operator >(nr_int_mari n1,nr_int_mari n2)
{
    int i=0,a,b,m;
    a=strlen(n1.nr);
    b=strlen(n2.nr);
    if(a>b){m=a;return 1;}//Verifica care e mai lung
    else if(a<b){m=b;return 0;}
    else{m=a;
    while((n1.nr[i]-'0')==(n2.nr[i]-'0'))i++;
    if(i>=m)return 1;
    else if((n1.nr[i]-'0')>(n2.nr[i]-'0'))return 1;
    else return 0;}
}
nr_int_mari operator *(nr_int_mari n1,int n)
{
    int i,a,j,c=0,b=0,A[1000]={0},C[1000]={0};
    nr_int_mari p;
    a=strlen(n1.nr);
    p.nr=new char [a+b+1];
    if(n==-1&&n1.semn=='+'){p=n1;p.semn='-';return p;}
    else if(n==-1&&n1.semn=='-'){p=n1;p.semn='+';return p;}
    p.semn=n1.semn;
    for(i=a-1;i>=0;i--)
    {
        if(i>=a)A[i]=0;
        else A[i]=n1.nr[i]-'0';
    }
    if(A[0]*n<9)b--;//pt casul 3*x
    for(i=a+b,j=a-1;i>=0;i--,j--)//i merge normal cu j daca b=-1 sau i merge cu un pass in urma daca d=0
    {
        C[i]=C[i]+A[j]*n+c;
        if(C[i]>9)
        {
            c=C[i]/10;
            C[i]=C[i]%10;
        }
        else c=0;
        if(i==0&&c==1)C[i-1]=1;
    }
    for(i=a+b;i>=-1;i--)p.nr[i]=C[i]+'0';
    if(n==0)p.nr[1]='\0';
    else p.nr[a+b+1]='\0';
    return p;
}
nr_int_mari operator *(nr_int_mari n1,nr_int_mari n2)
{
    int i,a,b,B[1000]={0},A[1000]={0},ok=0,cp=0;
    nr_int_mari p,s;
    b=strlen(n2.nr);
    a=strlen(n1.nr);
    p.nr=new char[b+a+2];
    s.nr=new char[b+a+2];
    s=s*0;
    p=p*0;
    if(n1>n2)
    {
        for(i=a-1;i>=0;i--)//transformare 1 nr din sir in cifre
        {
            A[i]=n1.nr[i]-'0';
        }
        for(i=a-1;i>=0;i--)
        {
            s=n2*A[i];
            cp=ok;
            while(cp!=0){s=s*10;cp--;}
            p=s+p;
            ok++;
        }
    }
    else
    {
        for(i=b-1;i>=0;i--)//transformare 1 nr din sir in cifre
        {
            B[i]=n2.nr[i]-'0';
        }
        for(i=b-1;i>=0;i--)
        {
            s=n1*B[i];
            cp=ok;
            while(cp!=0){s=s*10;cp--;}//inmultirea cu 10 pnetru marirea numarului la adunare
            p=s+p;
            ok++;
        }
    }
    if(n1.semn=='-'&&n2.semn=='-')p.semn='+';//Hotararea semnului pentru inmultire
    else if(n1.semn=='+'&&n2.semn=='+')p.semn='+';
    else p.semn='-';
    return p;
}
nr_int_mari operator -(nr_int_mari n1,nr_int_mari n2)
{
    int i,j,a,b,m,d,A[1000]={0},B[1000]={0},C[1000]={0},c=0;
    nr_int_mari p,q;
    if(n1.semn=='+'&&n2.semn=='-'){n2=n2*(-1);p=n1+n2;return p;}
    else if (n1.semn=='-'&&n2.semn=='+'){n1=n1*(-1);p=n1+n2;p.semn='-'; return p;}//hotarari in functie de semn

    else if(n1.semn=='-'&&n2.semn=='-'){n2=n2*(-1);n1=n1*(-1);p=n2-n1;p.semn='-';
    return p;}
    else{//pentru forma generala de scadere a-b
    a=strlen(n1.nr);
    b=strlen(n2.nr);
    if(n1>n2){p.nr=new char[a+1];m=a;p.semn='+';}
    else {p.nr=new char[b+1];m=b;p=n1*1;n1=n2*1;n2=p*1;p.semn='-';d=a;a=b;b=d;}
    for(i=a-1;i>=0;i--)
    {
        A[i]=n1.nr[i]-'0';

    }
    for(i=a-1,j=b-1;i>=0&&j>=-(a-b);j--,i--)
    {
        B[i]=n2.nr[j]-'0';
        if(j<0)B[i]=0;

    }
    d=0;
    for(i=a-d-1,j=a-1;i>=0;j--,i--)
    {
        C[i]=A[j]-B[j];
        if(B[j]>A[j])//cazul 2-7
        {
            C[i]=C[i]+10;
            c=1;
            A[j-1]-=c;
            c=0;
        }
        else //cazul 7-2
        {
            if(C[i]<0)
            {
                if(A[j]+B[j]==A[j]||A[j]+B[j]==B[j])c=0;
                C[i]=A[j]-B[j];
                c=1;
                A[j-1]-=c;
                c=0;

            }
        }

    }
    for(i=0;i<a;i++)if(C[i]!=0)break;
    else d++;
    for(i=a-d-1;i>=0;i--)p.nr[i]=C[i+d]+'0';
    p.nr[m-d]='\0';
    return p;
    }
}
nr_int_mari operator +(nr_int_mari n1,nr_int_mari n2)
{
    int i,j,a,b,m,A[1000]={0},B[1000]={0},C[1000]={0},c=0,d=0;
    nr_int_mari p,r;
    a=strlen(n1.nr);
    b=strlen(n2.nr);
    if(n1>n2){p.nr=new char[a+2];r.nr=new char[a+2];m=a;}
    else{p.nr=new char[b+2];r.nr=new char[a+2]; m=b;}
    if(n1.semn=='-'&&n2.semn=='+')
    {
        n1=n1*(-1);p=n2-n1;
        if(n1>n2)p.semn='-';
        else p.semn='+';
        return p;
    }
    else if(n1.semn=='+'&&n2.semn=='-')
    {
        n2=n2*(-1);cout<<n2<<" ";p=n1-n2;cout<<p<<" "<<endl;
        if(n1>n2)p.semn='+';
        else p.semn='-';
        return p;
    }
    else
    {//cazul in care ambele semne sunt la fel
        for(i=m-1;i>=0;i--)//Transformare primu sir in cifre
        {
            if(i>=a)A[i]=0;
            else A[i+m-a]=n1.nr[i]-'0';
        }
        for(i=m-1;i>=0;i--)//Transformare al doilea sir in cifre
        {
            if(i>=b)B[i]=0;
            else B[i+m-b]=n2.nr[i]-'0';
        }
        if((A[0]+B[0])>9)d=1;//conditie pentru marirea numarului de cifre in numar
        for(i=m+d-1,j=m-1;i>=0;i--,j--)
        {
            C[i]=c+A[j]+B[j];
            if(C[i]>9)
            {
                C[i]=C[i]%10;
                c=1;
            }
            else c=0;
            p.nr[i]=C[i]+'0';
        }

        p.semn=n1.semn;
        p.nr[m+d]='\0';
        return p;
    }
}
nr_int_mari operator +(nr_int_mari n1,int x)
{
    nr_int_mari p;
    int a,i,A[1000]={0},c=0;
    a=strlen(n1.nr);
    p.nr=new char[a];
    for(i=a-1;i>=0;i--)
    {
        A[i]=n1.nr[i]-'0';
    }
    i=a-1;
    while(x!=0)
    {
        A[i]=A[i]+x%10;
        if(A[i]>9){c=1;A[i]=A[i]%10;}
        else c=0;
        x=x/10;
        A[i-1]+=c;
        i--;
    }
    for(i=a-1;i>=0;i--)
    {
        p.nr[i]=A[i]+'0';
    }
    p.semn=n1.semn;
    p.nr[a]='\0';
    return p;
}
class vec_mari{
int n;
nr_int_mari *v;
public:
    vec_mari(){n=0;v=NULL;}
    vec_mari(int x){n=x;v=new nr_int_mari[x];}
    friend istream &operator >>(istream&,vec_mari&);
    friend ostream &operator <<(ostream&,vec_mari&);
    friend nr_int_mari operator *(vec_mari,vec_mari);
    friend int operator >(nr_int_mari n1,nr_int_mari n2);
    nr_int_mari maxim( const nr_int_mari &b);
    friend nr_int_mari maximul(vec_mari);
};
istream &operator >>(istream& in,vec_mari& ob)
{
    in>>ob.n;
    ob.v=new nr_int_mari[ob.n];
    for(int i=0;i<ob.n;i++)
        in>>ob.v[i];
    return in;
}
ostream &operator <<(ostream& out,vec_mari& ob)
{
    out<<"Cele "<<ob.n<<" elemente sunt: ";
    for(int i=0;i<ob.n;i++)out<<ob.v[i]<<" ";
    return out;
}
nr_int_mari operator *(vec_mari v1,vec_mari v2)
{
    int i,a;
    nr_int_mari p,q,r;
    if(v1.n!=v2.n){cout<<"Nu au o lungime la fel de mare";p=p*0;return p;}
    else
    {
        a=v1.n;
        r=r*0;
        p=r;
        for(i=0;i<a;i++)
            {
                cout<<v1.v[i]<<" "<<v2.v[i]<<" ";
                r=(v1.v[i]*v2.v[i]);
                cout<<r<<" ";
                p=r+p;


                cout<<p<<endl;
            }
        return p;
    }
}
nr_int_mari maximul(vec_mari v) //aflarea maximului dintr-un vector de numere mari61
{
    nr_int_mari p;
    p=v.v[0];
    for(int i=1;i<v.n;i++)
        if((p>v.v[i])==0)p=v.v[i];
    return p;
}
int main()
{

    nr_int_mari p,q,r;
    vec_mari v,w;
    //int a;
    cin>>v>>w;
    //cin>>p>>a;
    r=v*w;
    //r=maximul(v);
    //r=p+a;
    cout<<r;
    //r=p-q;
    //cout<<endl<<r;
    //cout<<p<<" "<<" "<<q<<" "<<r;
    return 0;
}
