/*****************************************************************************
 * Paul Alvarez
 * CSE 330 section 2
 * Plist.cpp
 * 3/12/2018
 * AAn implementation of a priority queue
 ***************************************************************************/
#include <time.h>
#include<cstdlib>
#include <iostream>
#include <assert.h>
using namespace std;

template <typename T>
class Lnode
{
  public :
  T data;
  Lnode *lptr;
  Lnode *rptr;
};

template <typename T>
class Plist
{ public :
  Plist();
  void add(T x);
  void add(int i, T x);
  void del();
  void del(int i);
  T getfront();
  T getback();
  T operator[] (unsigned int i);

  private :
  Lnode<T> *first;
  Lnode<T> *last;
  int lsize;
};

template <typename T>
Plist<T>::Plist()
{
 first=0;
 last=0;
 lsize=0;
}

template <typename T>
void Plist<T>:: add(T x)
{
	Lnode<T> *ptr=new Lnode<T>;
	ptr->data=x;
	if(lsize==0)
	{
	  ptr->lptr=0;
	  ptr->rptr=0;
	  first=ptr;
	  last=ptr;
	}
	else
	{
	  ptr->lptr=last;
	  ptr->rptr=0;
	  last->rptr=ptr;
	  last=ptr;
	}
	lsize++;
}

template<typename T>
void Plist<T>::add(int i,T x)
{
  Lnode<T> *nptr = new Lnode<T>;
  nptr->data=x;
  assert(i>=0 and i<=lsize);
  if (i==0 and lsize==0) //empty list
     {
       first=nptr;
       last=nptr;
       nptr->lptr=0;
       nptr->rptr=0;
       lsize++;
       return;
     }
   if (i==0) //add front
     {
       nptr->lptr=0;
       nptr->rptr=first;
       first=nptr;
       lsize++;
       return;
     }
   if (i==lsize) //add end
     {
       nptr->lptr=last;
       last->rptr=nptr;
       nptr->rptr=0;
       last=nptr;
       lsize++;
       return;
     }
     
  Lnode<T> *ptr=first;
  for (int j=0; j< i; j++)
      {
	ptr=ptr->rptr;
      }
  Lnode<T> *previous = ptr->lptr;
  nptr->rptr=ptr;
  nptr->lptr=previous;
  previous->rptr=nptr;
  ptr->lptr=nptr;
  lsize++;
  return;
}

template <typename T>
void Plist<T>::del()
{
	Lnode<T> *cur=first;
	first=first->rptr;
	delete cur;
	first->lptr=0;
	lsize--;
}

template <typename T>
void Plist<T>::del(int i)
{	
Lnode<T> *ptr=first;
  for (int j=0; j< i; j++)
      {
	ptr=ptr->rptr;
      }
  // now ptr points to [i]
     Lnode<T> *next = ptr->rptr;
     Lnode<T> *previous = ptr->lptr;
     if (previous==0 and next==0) // one element
        { delete first;
	  first=0;
	  last=0;
	  lsize--;
	  return;
	}
      if ( next==0) // last element
        { last=previous;
          last->rptr=0;
	  delete ptr;
	  lsize--;
	  return;
	}
     if (previous==0) //delete first element
	{ first=ptr->rptr;
	  first->lptr=0;
	  delete ptr;
	  lsize--;
	  ptr=first;
	}
      else // not the first and not the last 
        {
  	  previous->rptr=ptr->rptr;
	  next->lptr=ptr->lptr;
	  delete ptr;
	  lsize--;
	 }
}

template <typename T>
T Plist<T>::getfront()
{
   return first->data;
}

template <typename T>
T Plist<T>::getback()
{
   return last->data;
}

template <typename T>
T Plist<T>::operator[](unsigned int i)
{
	Lnode<T> *ptr=first;
     for(int j=0;j<i;j++)
     {
	  ptr=ptr->rptr;
	}
     return ptr->data;
}

int main()
{	
	srand(time(NULL));
	Plist<int> lis;
	cout<<"List of random numbers :"<<endl; 
	for(int i=0;i<5;i++)
	{
	lis.add(rand());
	}
	for(int i=0;i<5;i++)
	{
	 cout<<lis[i]<<endl;
	}
	cout<<"Adds numbers into 2nd and 5th index positions:"<<endl; 
	lis.add(2,rand());
	lis.add(5,rand());
	for(int i=0;i<7;i++)
	{
	 cout<<lis[i]<<endl;
	}
	cout<<"delete  fifth position "<<endl;
	lis.del(4);

	for(int i=0;i<6;i++)
	{
	 cout<<lis[i]<<endl;
	}
	cout<<"Use getback to return last element:"<<endl;
	cout<<lis.getback()<<endl;
	return 0;
}
