#include <iostream>
#include <fstream>
#include <vector>


double poisson(double mu, int k) {
    double p = (std::pow(mu, k)*std::exp(-mu))/tgamma(k + 1);

    return p;
}

int main() {
    using namespace std;

    vector<int> zaehler(11);

    ifstream fin("datensumme.txt");
    int n_i;
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> n_i;
        zaehler[n_i] += 1;
    }
    fin.close();
    for(unsigned int k = 0 ; k < zaehler.size() ; ++k) { std::cout << k << ":" << zaehler[k] << std::endl;
    }
    std::ofstream fout("hist.txt");
    for(unsigned int k = 0 ; k < zaehler.size() ; ++k) {
        fout << k << " " << zaehler[k] << " " << std::endl;
    }
    
    std::ofstream fout1("histpoi.txt");
    for(unsigned int k = 0 ; k < zaehler.size() ; ++k) {
        double NP = 234 * poisson(3.11538, k);
        fout1 << k << " " << zaehler[k] << " " << NP << std::endl;
    }
}