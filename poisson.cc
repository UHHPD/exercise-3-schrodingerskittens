#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>

using namespace std;


double poisson(double mu, int k)
{
    double p;
    p = (exp(-mu) * pow(mu, k))/tgamma(k+1);
    return p;
}

int main() {
    
    vector<int> zaehler(11, 0);
    ifstream fin("datensumme.txt");
    ofstream fout("hist.txt");
    ofstream fout2("histpoi.txt");

    int a, N=234;
    while(fin>>a)
    {
        zaehler[a]+=1;
    }

    for(unsigned int k=0; k<zaehler.size(); ++k)
    {
        cout << k <<": "<< zaehler[k]<<endl;
        fout << k <<" "<<zaehler[k] << endl;
    }
    fin.close();
    fout.close();
    double mu = 3.11538, p;

    for(unsigned int k=0; k<zaehler.size(); ++k)
    {
        p = N * poisson(mu, k);
        fout2 << k <<" "<<zaehler[k] << " " << p << endl;
    }

    fout2.close();

    return 0;
}