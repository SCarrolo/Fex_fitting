#include "FCtools.h"

vector<string> FCtools::ReadFile2String(string nof) //nof means name of file
{
  ifstream myfile;
  // int count = 0;
  string line;
  vector<string> filelines;
  myfile.open(nof);

  while(getline(myfile,line))
  {
    filelines.push_back(line);
  }
  myfile.close();
  return filelines;
}

vector<Vec> FCtools::ReadFile2Vec(string name) //file name, returns vectors of Vec’s
{
  vector<Vec> aux;
  vector<double> auxvec;
  ifstream myfile;

  stringstream ss;
  string line;
  myfile.open(name);
  double d1 = 0.0f;

  while(getline(myfile,line))
  {
    size_t found = line.find("//",0);
    if(found == string::npos && line.size() != 0){
      ss << line;
      while(ss >> d1)
      {
	       auxvec.push_back(d1);
      }
      Vec a(auxvec);
      aux.push_back(a);
      ss.clear();
      auxvec.clear();
    }
  }
  myfile.close();
  return aux;

}


Vec *FCtools::ReadFile(string name)
{
  vector<Vec> aux1 = ReadFile2Vec(name);
  Vec *a = new Vec[aux1.size()];
  for(int i = 0 ; i < (int)aux1.size() ; i++)
  {
    a[i] = aux1[i];
  }
  return a;
}
