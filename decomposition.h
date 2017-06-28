#include<iostream>
#include<vector>
#include<algorithm>
#include "tree.hh"

using namespace std;

class decomposition
{
public:
  decomposition(){size=0; sumdegre=0; degre.resize(0); next.resize(0); prec.resize(0);}

  decomposition(const int n)
  {
    size=n; 
    sumdegre=2*n;
    degre.resize(n);
    next.resize(n);
    prec.resize(n);
    for(int i=0; i<size; i++) 
      {
	degre[i]=2;
	next[i]=(i+1)%size;
	prec[i]=(i+size-1)%size;
      }
  }

  decomposition(const decomposition &d)
  {
    size=d.size;
    sumdegre=d.sumdegre;
    degre.resize(size);
    next.resize(size);
    prec.resize(size);
    for(int i=0; i<size; i++) 
      {
	degre[i]=d.degre[i];
	next[i]=d.next[i];
	prec[i]=d.prec[i];
      }
  }

  int getsize() const {return size;}
  int getdegre(const int i) const {return degre[i];}
  int getsumdegre() const {return sumdegre;}

  int operator==(const decomposition d)
  {
    if (size!=d.size) return 0;
    int res=1;
    for(int shift=0; shift<size; shift++)
      {
	int i=0;
	res=1;
	while(i<size && res)
	  {
	    if (degre[i]!=d.degre[(i+shift)%d.size]) res=0;
	    i++;
	  }
	if(res) return 1;
      }
    return res;
  }

  decomposition cut(const int index)
  {
    decomposition d(*this);
    int ind;
    if(index<0) ind=index%size+size;
    else ind=index%size;
   
    if(d.prec[ind]==ind || 
       d.next[ind]==ind) return *this;
    if(d.next[ind] - d.prec[ind]==1) return *this;
    if(d.next[ind] - d.prec[ind]==-1) return *this;
    if(d.next[ind] == d.prec[prec[ind]]) return *this;

    int prec_ind, next_ind;
    prec_ind=d.prec[ind];
    next_ind=d.next[ind];
    
    d.prec[next_ind]=prec_ind; d.prec[ind]=ind;
    d.next[prec_ind]=next_ind; d.next[ind]=ind;
    
    d.degre[prec_ind]+=1;
    d.degre[next_ind]+=1;
    d.sumdegre+=2;
    return d;
  }

  void print()
  {
    cout << "[";
    for(int i=0; i<size-1; i++) cout << degre[i] << ", ";
    cout << degre[size-1] << "] " << endl;
  }

private:
  int size;
  int sumdegre;
  vector<int> degre;
  vector<int> next;
  vector<int> prec;
};

void make_dec_tree(tree<decomposition> &t,
		   tree<decomposition>::iterator iter,
		   vector<decomposition> &l)
{
  int s=iter->getsize();
  for(int i=0; i<s; i++)
    {
      decomposition d=iter->cut(i);
      vector<decomposition>::iterator find_iter = find(l.begin(), l.end(), d);
      if(find_iter==l.end())
	{
	  if(d.getsumdegre()==4*d.getsize() - 6)
	    cout << "[" << l.size() << "]" << flush;
	  tree<decomposition>::iterator iter_fils=t.append_child(iter, d);
	  l.push_back(d);
	  make_dec_tree(t, iter_fils, l);
	} 
    }
}

vector<decomposition> select_triangulation(vector<decomposition> l)
{
  vector<decomposition> vt;
  for(int i=0; i<l.size(); i++)
    {
      if((l[i].getsumdegre())==(4*(l[i].getsize())-6))
	vt.push_back(l[i]);
    }
  return vt;
}
