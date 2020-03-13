//CPP standard includes
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
//my classes includes
#include "FCtools.h"
#include "Vec.h"

//Root includes
#include "TGraph.h"
#include "TApplication.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TF1.h"

vector<double *> ReadFileGeneral(string,int&);
TGraphErrors* SetGraphStuff(int, double*,double*,double*,double*,string,string,string);
void DrawEverything(TGraphErrors*,TGraphErrors*,TF1*, string);
pair<double,double> GetExtremes(double*,int n);

using namespace std;

int main (void)
{
  cout << "Nome do ficheiro:" << endl;
  string a = "20-LiF-1";
  // cin >> a;
  cout << "o nome que inseriu é: " << a << endl;
  //General stuff about the graph - title && axis, etc
  string titulograf ="LiF - 2^{a} ordem K_{#beta}";
  string xtitulo = "#theta(^{o})";
  string ytitulo = "R(s^{-1})";


  int n=0;
  vector<double*> FileShit = ReadFileGeneral("Text/"+a+".txt",n);
  TGraphErrors *results = SetGraphStuff(n,FileShit[0],FileShit[1],NULL,FileShit[3],titulograf,xtitulo ,ytitulo );

  TF1 *fitfunction = new TF1("fitting function", "[b]+[a]*x");
  results->Fit("fitting function", "V");
  cout << "chi square/ndf = " << fitfunction->GetChisquare()/fitfunction->GetNDF() << endl;

  vector<double> sigma;
  for(int i = 0; i < n;i++)
  {
    sigma.push_back(FileShit[1][i]-fitfunction->Eval(FileShit[0][i]));
  }
  TGraphErrors *resultsSigma = SetGraphStuff(n,FileShit[0],sigma.data(),NULL,FileShit[3],"Residuos",xtitulo ,"Exp-Teo" );
  pair<double, double> extremes = GetExtremes(FileShit[0],n);
  TF1 *fNull = new TF1("null func", "0",extremes.first,extremes.second);
  fNull->SetLineColor(kBlack);
  DrawEverything(results,resultsSigma,fNull,a);
}

pair<double,double> GetExtremes(double*v,int n)
{
  pair<double,double> pExt;
  pExt.first = v[0]; //Minimum
  pExt.second = v[0]; //maximum
  for(int i = 0;i < n;i++)
  {
    if(v[i] <= pExt.second)
    {
      pExt.second = v[i];
    }
    if(v[i] >= pExt.first)
    {
      pExt.first = v[i];
    }
  }
  return pExt;
}

//
// void DrawEverything(TGraphErrors* graph,TGraphErrors* graph2,TF1*func,string name)
// {
//   TApplication * MyRootApp;
//   MyRootApp = new TApplication("", NULL, NULL);
//   MyRootApp->SetReturnFromRun(true);
//   TCanvas *c1 = new TCanvas("c1","",1280,720);
//
//   c1->Divide(1,2);
//   c1->cd(1);
//   gPad->Clear();
//   graph->Draw("AP");
//
//   c1->cd(2);
//   c1->SetGrid(1,1);
//   graph2->Draw("AP");
//   func->Draw("SAME");
//   c1->SaveAs(("imagens/"+name + ".png").c_str());
//   c1->Update();
//   gPad->WaitPrimitive();
//   delete c1;
// }

void DrawEverything(TGraphErrors* graph,TGraphErrors* graph2,TF1*func,string name)
{
  TApplication * MyRootApp;
  MyRootApp = new TApplication("", NULL, NULL);
  MyRootApp->SetReturnFromRun(true);
  TCanvas *c1 = new TCanvas("c1","",1280,720);
  gPad->Clear();
  TPad* P = new TPad("PadFit","",0,0.33,1,1);
  TPad* PRes = new TPad("PadRes","",0,0,1,0.33);
  P->SetBorderMode(0);
  PRes->SetBorderMode(0);

  c1->cd();
  P->Draw();
  PRes->Draw();
  P->cd();
  graph->Draw("AP");
  PRes->cd();
  graph2->Draw("AP");
  func->Draw("SAME");


  c1->SaveAs(("imagens/"+name + ".png").c_str());
  c1->Update();
  gPad->WaitPrimitive();
  delete c1;
}



TGraphErrors* SetGraphStuff(int n, double*x ,double*y,double*ex,double*ey,string title,string xtitle,string ytitle)
{
  TGraphErrors *results = new TGraphErrors(n,x,y,ex,ey);
  results->SetMarkerStyle(6);
  results->SetMarkerSize(1);
  results->SetMarkerColor(kRed+2);
  results->SetTitle(title.c_str());
  results->GetXaxis()->SetTitle(xtitle.c_str());
  results->GetYaxis()->SetTitle(ytitle.c_str());
  return results;

}

vector<double *> ReadFileGeneral(string a,int &n)
{
  FCtools reader;
  vector<Vec> values = reader.ReadFile2Vec(a);
  n = (int)values.size();
  double *x = new double [n];
  double *y = new double [n];
  double *ex = new double [n];
  double *ey = new double [n];
  if(values[0].size() == 3)
  {
    delete [] ex;
    double *ex = NULL;
  }


  for(int i = 0 ; i < n;i++)
  {
    x[i] = values[i][0];
    y[i] = values[i][1];

    if(values[0].size() == 3)
    {
      ey[i] =values[i][2];

    }else{
      ey[i] =values[i][3];
      ex[i] =values[i][2];
    }
  }

  vector<double*> ret;
  ret.push_back(x);
  ret.push_back(y);
  ret.push_back(ex);
  ret.push_back(ey);
  return ret;
}
