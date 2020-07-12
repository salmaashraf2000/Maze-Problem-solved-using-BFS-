#include <iostream>
#include <bits/stdc++.h>
#define X first.first
#define Y first.second
#define direction second
using namespace std;

const int oo=0x3f3f3f3f,N=1005;
int M,destinationX,destinationY,index1,index2;
int dis[N][N][4];
string grid[N];
pair<pair<int,int>,int> parent[N][N][4];
int x[]={-1,0,1,0};
int y[]={0,1,0,-1};

void GetState(int state)
{
     if(state==0)
     {
         index1=0;
         index2=1;

     }else if(state==1)
     {
         index1=1;
         index2=2;

     }else if(state==2)
     {
         index1=2;
         index2=3;

     }else if(state==3)
     {
         index1=3;
         index2=0;

     }
     return;

}

bool check(int nexti,int nextj,int n,int m,int index)
{
    if(nexti>=0 && nexti<n && nextj>=0 && nextj<m && dis[nexti][nextj][index]==oo && (grid[nexti][nextj]=='.' || grid[nexti][nextj]=='e'))
    {
        return true;
    }
    return false;
}

int BFS(int startX,int startY,int n,int m)
{
    int state=0;
    memset(dis,oo,sizeof(dis));
    dis[startX][startY][0]=0;
    queue<pair<pair<int,int>,int>> q;
    q.push({{startX,startY},0});
    parent[startX][startY][0]={{-1,-1},-1};

    while(!q.empty())
    {
     pair<pair<int,int>,int> p=q.front();
     q.pop();
     state=p.direction;
     if(p.X==destinationX && p.Y==destinationY)
     {
         return state;
     }
     int nexti,nextj,Nexti,Nextj;

     GetState(state);
     nexti=p.X+x[index1];
     nextj=p.Y+y[index1];
     Nexti=p.X+x[index2];
     Nextj=p.Y+y[index2];

    if(check(nexti,nextj,n,m,index1))
    {

       dis[nexti][nextj][index1]=dis[p.X][p.Y][p.direction]+1;
       q.push({{nexti,nextj},index1});
       parent[nexti][nextj][index1]={{p.X,p.Y},p.direction};

    }

   if(check(Nexti,Nextj,n,m,index2))
   {

      dis[Nexti][Nextj][index2]=dis[p.X][p.Y][p.direction]+1;
      q.push({{Nexti,Nextj},index2});
      parent[Nexti][Nextj][index2]={{p.X,p.Y},p.direction};

     }


    }
    return oo;
}

vector<string> GetPath(int state)
{
     pair<pair<int,int>,int> p=parent[destinationX][destinationY][state];
        vector<string> path;

         if(state==0)
         {
            path.push_back("north");
         }else if(state==1)
         {
             path.push_back("east");
         }else if(state==2)
         {
             path.push_back("south");
         }else if(state==3)
         {
             path.push_back("west");
         }

        while(1)
        {
           if(p.X==-1 && p.Y==-1 && p.direction==-1)
            {
             break;
           }

           if(p.direction==0)
           {
             path.push_back("north");
           }else if(p.direction==1)
           {
             path.push_back("east");
           }else if(p.direction==2)
           {
             path.push_back("south");
           }else if(p.direction==3)
           {
             path.push_back("west");
           }
           p=parent[p.X][p.Y][p.direction];
        }

    reverse(path.begin(),path.end());
    return path;
}

void printPath(vector<string> path)
{
     int cnt=1,total=0;
     string Direction="";
     Direction=path[1];
     cout<<"Directions\n";
     for(int i=2;i<path.size();i++)
     {
        if(path[i]==path[i-1])
        {
            Direction=path[i];
            cnt++;

        }else
        {
            cout<<cnt<<" "<<Direction<<endl;
            cnt=1;
            Direction=path[i];
        }

     }
     cout<<cnt<<" "<<Direction<<endl;
}

int main()
{
    freopen("testCase6.txt","r",stdin);
    int startX,startY,n,m;
    cin>>n>>m;
    string s;
    for(int i=0;i<n;i++)
    {
        cin>>s;
        grid[i]=s;
        for(int j=0;j<m;j++)
        {
           if(grid[i][j]=='c')
            {
              startX=i;
              startY=j;
           }else if(grid[i][j]=='e')
           {
               destinationX=i;
               destinationY=j;
           }
        }
    }
    int state=BFS(startX,startY,n,m);
    if(state==oo){
        cout<<"Can not reach destination";
    }else{
        cout<<"Number of steps: "<<dis[destinationX][destinationY][state]<<endl;

        vector<string> path=GetPath(state);
        printPath(path);

    }
    return 0;
}

/*
7 6
******
***..*
e....*
*.*.**
*....*
*c*..*
******
16

2 2
e.
.c
no

5 5
*....
e...c
**..*
*****
*****
no

4 3
*e*
..*
..*
*c*
3

5 4
*..*
*..*
c...
...e
**.*
4

8 8
.......e
*****.**
****..**
****.***
***...**
*.....**
c.....**
****..**

3 5
c....
...**
.e...
*/
