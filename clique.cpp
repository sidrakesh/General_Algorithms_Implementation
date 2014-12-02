#include <iostream> 
#include <fstream> 
#include <string> 
#include <vector> 
using namespace std;
bool removable(vector<int> neighbor, vector<int> cover); 
int max_removable(vector<vector<int> > neighbors, vector<int> cover); 
vector<int> procedure_1(vector<vector<int> > neighbors, vector<int> cover); 
vector<int> procedure_2(vector<vector<int> > neighbors, vector<int> cover, int k); 
int cover_size(vector<int> cover); 

int P[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127};

bool coprime(int a,int b) {
    vector<int> fact;
    for(int i=0;i<=30;i++) {
        if(a%P[i]==0) {
            fact.push_back(P[i]);
            while(a%P[i]==0)
                a=a/P[i];
        }
    }
    fact.push_back(a);
    for(int i=0;i<fact.size();i++)
        if(b%fact[i]==0)
            return true;
    return false;
}

int main() 
{ 
 int n, t,i, j, k, K, p, q, r, s, min, edge, counter=0; 


  n = 777;

  vector<vector<int> > neighbors;
  for(i=2;i<=n;i++)
  {
    vector<int> temp;
    for(j=2;j<=n;j++) {
      if(coprime(i,j)) {
        temp.push_back(j);
      }
    }
    neighbors.push_back(temp);
  }
  


  cout<<"Graph has n = "<<n<<" vertices."<<endl; 
  //Read maximum size of Clique wanted 
  cout<<"Find a Clique of size at least k = "; 
  cin>>K; k=n-K; 
  //Find Cliques 
  bool found=false; 
  cout<<"Finding Cliques..."<<endl; 
 min=n+1; 
 vector<vector<int> > covers; 
 vector<int> allcover; 
 for(i=0; i<n; i++) 
 allcover.push_back(1); 
 for(i=0; i<allcover.size(); i++) 
 { 
  if(found) break; 
  counter++; cout<<counter<<". ";
  vector<int> cover=allcover; 
  cover[i]=0; 
  cover=procedure_1(neighbors,cover); 
  s=cover_size(cover); 
  if(s<min) min=s; 
  if(s<=k) 
  { 
   cout<<"Clique ("<<n-s<<"): "; 
   for(j=0; j<cover.size(); j++) if(cover[j]==0) cout<<j+1<<" "; 
   cout<<endl; 
   cout<<"Clique Size: "<<n-s<<endl; 
   covers.push_back(cover); 
   found=true; 
   break; 
  } 
  for(j=0; j<n-k; j++) 
  cover=procedure_2(neighbors,cover,j); 
  s=cover_size(cover); 
  if(s<min) min=s; 
  cout<<"Clique ("<<n-s<<"): "; 
  for(j=0; j<cover.size(); j++) if(cover[j]==0) cout<<j+1<<" "; 
  cout<<endl; 
  cout<<"Clique Size: "<<n-s<<endl; 
  covers.push_back(cover); 
  if(s<=k){ found=true; break; } 
 } 
//Pairwise Intersections 
 for(p=0; p<covers.size(); p++) 
 { 
  if(found) break; 
  for(q=p+1; q<covers.size(); q++) 
  { 
   if(found) break; 
   counter++; cout<<counter<<". "; 
   vector<int> cover=allcover; 
   for(r=0; r<cover.size(); r++) 
   if(covers[p][r]==0 && covers[q][r]==0) cover[r]=0; 
   cover=procedure_1(neighbors,cover); 
   s=cover_size(cover); 
   if(s<min) min=s; 
   if(s<=k) 
   { 
    cout<<"Clique ("<<n-s<<"): "; 
    for(j=0; j<cover.size(); j++) if(cover[j]==0) cout<<j+1<<" "; 
    cout<<endl; 
    cout<<"Clique Size: "<<n-s<<endl; 
    found=true; 
    break; 
   } 
   for(j=0; j<k; j++) 
   cover=procedure_2(neighbors,cover,j); 
   s=cover_size(cover); 
   if(s<min) min=s; 
   cout<<"Clique ("<<n-s<<"): "; 
   for(j=0; j<cover.size(); j++) if(cover[j]==0) cout<<j+1<<" "; 
   cout<<endl; 
   cout<<"Clique Size: "<<n-s<<endl; 
   if(s<=k){ found=true; break; } 
   } 
 } 
 if(found) cout<<"Found Clique of size at least "<<K<<"."<<endl; 
 else cout<<"Could not find Clique of size at least "<<K<<"."<<endl 
 <<"Maximum Clique size found is "<<n-min<<"."<<endl; 
 cout<<"See cliques.txt for results."<<endl; 
  
 return 0; 
}

bool removable(vector<int> neighbor, vector<int> cover) 
{ 
 bool check=true; 
 for(int i=0; i<neighbor.size(); i++) 
 if(cover[neighbor[i]]==0) 
 { 
  check=false; 
  break; 
 } 
 return check; 
}

int max_removable(vector<vector<int> > neighbors, vector<int> cover) 
{ 
 int r=-1, max=-1; 
 for(int i=0; i<cover.size(); i++) 
 { 
  if(cover[i]==1 && removable(neighbors[i],cover)==true) 
  { 
   vector<int> temp_cover=cover; 
   temp_cover[i]=0; 
   int sum=0; 
   for(int j=0; j<temp_cover.size(); j++) 
   if(temp_cover[j]==1 && removable(neighbors[j], temp_cover)==true) 
   sum++; 
   if(sum>max) 
   { 
    max=sum; 
    r=i; 
   } 
  } 
 } 
 return r; 
}

vector<int> procedure_1(vector<vector<int> > neighbors, vector<int> cover) 
{ 
 vector<int> temp_cover=cover; 
 int r=0; 
 while(r!=-1) 
 { 
  r= max_removable(neighbors,temp_cover); 
  if(r!=-1) temp_cover[r]=0; 
 } 
 return temp_cover; 
}

vector<int> procedure_2(vector<vector<int> > neighbors, vector<int> cover, int k) 
{ 
 int count=0; 
 vector<int> temp_cover=cover; 
 int i=0; 
 for(int i=0; i<temp_cover.size(); i++) 
 { 
  if(temp_cover[i]==1) 
  { 
   int sum=0, index; 
   for(int j=0; j<neighbors[i].size(); j++) 
   if(temp_cover[neighbors[i][j]]==0) {index=j; sum++;} 
   if(sum==1 && cover[neighbors[i][index]]==0) 
   { 
    temp_cover[neighbors[i][index]]=1; 
    temp_cover[i]=0; 
    temp_cover=procedure_1(neighbors,temp_cover); 
    count++; 
   } 
   if(count>k) break; 
  } 
 } 
 return temp_cover; 
}

int cover_size(vector<int> cover) 
{ 
 int count=0; 
 for(int i=0; i<cover.size(); i++) 
 if(cover[i]==1) count++; 
 return count; 
}