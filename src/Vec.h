#ifndef VEC_H
#define VEC_H

#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
class Vec {
  public:
    Vec();
    ~Vec(); //destructor
    Vec(int);
    Vec(int,double*);
    Vec(vector<double>);
    Vec(const Vec &); //copy constructor

    //operators
    Vec operator=(const Vec &); //copy assignment
    double &operator[](int); //aceder ao elemento [i] quando nao existe, retorna RAND_MAX
    double operator[](int) const; //aceder ao elemento [i] quando nao existe, retorna RAND_MAX

    Vec operator+(const Vec &) const;
    Vec operator-(const Vec &) const;
    Vec operator+=(const Vec &);
    Vec operator-=(const Vec &);
    Vec operator*(const Vec &) const;
    Vec operator*(double) const;

    //other methods
    double dot(const Vec &) const;
    void Print() const; //print do vetor todo
    void SetEntries(int, double *);
    void swap(int,int);
    int size() const;

  private:
    int N; //number of elements
    double *entries; //pointer to array of doubles
};


#endif
