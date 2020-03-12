#include "Vec.h"

//constructors e destructors
Vec::Vec()
{
  N = 0;
  entries = NULL;
}

Vec::~Vec()
{
  if(entries != NULL)
  {
    delete [] entries;
    N = 0;
  }else{
    N = 0;
    entries = NULL;
  }

}


Vec::Vec(int n)
{
  if(n!=0){
    entries = new double[n];
    for(int i = 0 ;i < n; i++)
    {
      entries[i] = 0.0f;
    }
    N = n;
  }else{
    entries = NULL;
    N = 0;
  }
}

Vec::Vec(int n, double *aux)
{
  entries = new double[n];
  N = n;
  for(int i = 0 ;  i < n ; i++)
  {
    entries[i] = aux[i];
  }

}

Vec::Vec(vector<double> aux)
{
  entries = new double[aux.size()];
  N = aux.size();
  for(int i = 0 ;  i < N; i++)
  {
    entries[i] = aux[i];
  }
}


//Operators
Vec::Vec(const Vec &aux)
{
  N = aux.N;
  entries = new double[N];
  for(int i = 0 ; i < N; i++)
  {
    entries[i] = aux.entries[i];
  }
}

Vec Vec::operator=(const Vec &aux)
{
  if(entries != NULL)
  {
    delete [] entries;
  }
  N = aux.N;
  entries = new double[N];
  for(int i = 0 ; i < N; i++)
  {
    entries[i] = aux.entries[i];
  }
  return Vec(N,entries);
}

void Vec::SetEntries(int n, double *aux)
{
  if(entries != NULL)
  {
    delete [] entries;
  }
  N = n;
  entries = new double [n];
  for(int i = 0 ; i < n;i++)
  {
    entries[i] = aux[i];
  }
}

double &Vec::operator[](int aux)
{
  return entries[aux];
}

double Vec::operator[](int aux) const
{
  return entries[aux];
}


Vec Vec::operator+(const Vec &op2) const //does this + op2
{
  if(op2.N == N)
  {
    Vec a(N,entries);
    for(int i = 0 ; i < N; i++)
    {
      a.entries[i] += op2.entries[i];
    }
    return a;
  }else{
    cout << "This sum is impossible to make" << endl;
    return Vec();
  }
}

Vec Vec::operator+=(const Vec &op2) //does this += op2
{

  if(op2.N == N)
  {
    for(int i = 0 ; i < N; i++)
    {
      entries[i] += op2.entries[i];
    }
    Vec a(N,entries);
    return a;
  }else{
    cout << "This sum is impossible to make" << endl;
    return Vec();
  }
}

Vec Vec::operator-(const Vec &op2) const //does this - op2
{

  if(op2.N == N)
  {
    Vec a(N,entries);
    for(int i = 0 ; i < N; i++)
    {
      a.entries[i] -= op2.entries[i];
    }
    return a;
  }else{
    cout << "This subtraction is impossible to make" << endl;
    return Vec();
  }
}

Vec Vec::operator-=(const Vec &op2) //does this -= op2
{

  if(op2.N == N)
  {
    for(int i = 0 ; i < N; i++)
    {
      entries[i] -= op2.entries[i];
    }
    Vec a(N,entries);
    return a;
  }else{
    cout << "This subtraction is impossible to make" << endl;
    return Vec();
  }
}

Vec Vec::operator*(const Vec &op2) const //does the product of ith component with ith component
{
  if(op2.N == N)
  {
    Vec a(N,entries);
    for(int i = 0 ; i < N; i++)
    {
      a.entries[i] *= op2.entries[i];
    }
    return a;
  }else{
    cout << "This multiplication is impossible to make" << endl;
    return Vec();
  }
}

Vec Vec::operator*(double lambda) const
{
  Vec a(N,entries);
  for(int i = 0 ; i < N; i++)
  {
    a.entries[i] = entries[i] * lambda;
  }
  return a;
}

//Other methods
int Vec::size() const
{
  return N;
}


void Vec::swap(int i1, int i2)
{
  double tmp  = 0.0f;
  tmp = entries[i1];
  entries[i1] = entries[i2];
  entries[i2] = tmp;
}

double Vec::dot(const Vec & op2) const //does the euclidean dot product
{
  double result = 0;
  if(op2.N == N)
  {
    for(int i = 0 ; i < N; i++)
    {
      result += entries[i]*op2.entries[i];
    }
    return result;
  }else{
    cout << "This dotproduct is impossible to make" << endl;
    return result;
  }
}

void Vec::Print() const
{
  cout << "[" ;
  for(int i = 0 ; i < N-1; i++)
  {
    cout << entries[i] << " , ";
  }
  cout << entries[N-1] << "]" << endl;

}
