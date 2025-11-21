#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;


double poisson(double mu, int k) {
    double p;
    p = (exp(-mu) * pow(mu, k))/tgamma(k+1);
    return p;
}

long double probe(vector<int> daten, double mu){
    long double L=1;

    for (int k: daten){
        L*=poisson(mu, k);
        
    
    }
    return L;
}

long double saturated_probe(vector<int> daten)
{
    long double L=1;
    for (int k: daten){
        L*=poisson(k, k);
    }
    return L;
}

int main() {
    using namespace std;

    vector<int> daten;

    ifstream fin("datensumme.txt");
    int n_i;
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> n_i;
        daten.push_back(n_i);
        
    }

    fin.close();

    long double L = probe(daten, 3.11538);
    double lnL, delta_lnL, s;
    s = -2*log(L);
    cout<<"likelihood: "<<L<<endl;

     vector<double> mu_val, nll_val, delta_nll_val;


    ofstream fout("likelihood.txt");
    ofstream fout2("nll.txt");
    ofstream fout3("deltanll.txt");
    for (double mu=0; mu<=6; mu+=0.01){
        L = probe(daten, mu);

            lnL = -2*log(L);
            delta_lnL = lnL - s;
        fout<< mu<<" "<<L<<endl;
        fout2<<mu<<" "<<lnL<<endl;
        fout3<<mu<<" "<<delta_lnL<<endl;

        mu_val.push_back(mu);
        nll_val.push_back(lnL);
        delta_nll_val.push_back(delta_lnL);
    }
    fout.close();
    fout2.close();
    fout3.close();

    
    auto min_nll = min_element(delta_nll_val.begin(), delta_nll_val.end());
    int index = distance(delta_nll_val.begin(), min_nll);
    double mu_hat = mu_val[index];
    cout<<"Mu_hat: "<<mu_hat<<endl;

    double lambda;
    lambda = probe(daten, 3.11538)/saturated_probe(daten);
    cout<<"Likelihood ratio Lambda: "<<lambda<<endl;

    double lLambda = -2*log(lambda);
    double ndof = daten.size() - 1;
    double z = (lLambda - ndof)/sqrt(2*ndof);
    cout<<"-2Ln(Lambda): : "<<lLambda<<endl;
    cout<<"z "<<z<<endl;
    return 0;


}