#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


double poisson(double mu, int k) {
    double poi_value  = pow(mu, k) * exp(-1 * mu) / tgamma(k+1);
    return poi_value;
}

int main() {
    using namespace std;


    ifstream input_file("datensumme.txt");

    //creating vector with 11 entries:
    vector<int> zaehler (11);


    int n_i;
    for(int i = 0 ; i < 234 ; i++) {
        input_file >> n_i;
        for (int zahl = 0; zahl < 11; zahl++){ //counting how often 0, 1, 2,... appears in the 234 entries
            (zahl == n_i)? zaehler[zahl] +=1 : false ;
        }
    }
    int i=0;
    for(int element : zaehler){
        std::cout << i++ << " : " << element << std::endl;

    }
    input_file.close();

    //writing goals in hist.txt

    ofstream histfile("hist.txt");

    int j = 0;
    for (int element: zaehler){
        histfile << j << " " << element << std::endl;
        j++;
    }
    histfile.close();



    //writing comparison to theory in histpoi.txt
    ofstream histpoi_file("histpoi.txt");
    int k = 0;
    double mean_value = 3.11538;
    for(int element : zaehler){
        histpoi_file << k << " " << element << " " << poisson(mean_value, k) * 234 << std::endl;
        k++;
    }
    histpoi_file.close();


}