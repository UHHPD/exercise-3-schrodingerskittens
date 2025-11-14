#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

double poisson(double mu, int k) {
    double poi_value  = pow(mu, k) * exp(-1 * mu) / tgamma(k+1);
    return poi_value;
}

double prob(std::vector<int> values, double mean){
    
    double prob_value{1};
    for (auto element : values ){
        
        prob_value *= poisson(mean, element);
    }
    return prob_value;


}

//writing saturated_prob for e)
double saturated_prob(std::vector<int> values){
    double sat_prob_value{1};
    for (auto element: values)
    {
        sat_prob_value *=poisson(element, element);
    }
    return sat_prob_value;

}

int main() {
    using namespace std;

    ifstream input_file("datensumme.txt");

    

    //creating vector with all datentext.txt numbers in
    std::vector<int> daten;
    int n_i;
    for(int i = 0 ; i < 234 ; i++) {
        input_file >> n_i;
        daten.push_back(n_i);
    }
    
    input_file.close();

    //take daten_mean out of old calculations: m = 3.11538
    double daten_mean = 3.11538;
    double likelihood{1};
    likelihood = prob(daten, daten_mean);
    
    std::cout << "likelihood : " << likelihood << std::endl;



    //b) letting mu range from 0 to 6 and calculating L for it
    ofstream like_file("likelihood.txt");

    //create array of means and array of likelihoods
    std::vector<double> mean_values;
    std::vector<double> poi_variable_mu;
    for (double x = 0; x < 6; x += 0.1){
        mean_values.push_back(x) ;
        poi_variable_mu.push_back(prob(daten, x));
        like_file << x << " " << prob(daten,x) << std::endl;
        
    }
    like_file.close();

    //check what exact value the maximum of the likelihood distribution is
    double max =  *max_element(poi_variable_mu.begin(), poi_variable_mu.end());

    cout << " max value of likelihood : " <<  max << endl;

    //used to find out that index of this maximum likelihood value is 31
    //auto it = find(poi_variable_mu.begin(), poi_variable_mu.end(), max);
    //cout << "index position of this maximum: " << it - poi_variable_mu.begin() << endl;;

    cout << "mu value of this maximum likelihood value: " << mean_values[31] << endl;


    cout << "-------------------" << endl;

    //c) write out negative log likelihood

    ofstream loglike("nll.txt");
    std::vector<double> lnlikelihood;
    double x {};

    for (double element : poi_variable_mu){
        x = -2 * log(element);
        lnlikelihood.push_back(x);
    }

    //now the vectors of interest are mean_values and lnlikelihood
    //if we want to include the first 10 elements which are infinity, start from i = 11

    for (size_t i = 0; i < mean_values.size(); ++i) {
        loglike << mean_values[i] << " " << lnlikelihood[i] << "\n";
    }

    loglike.close();


    //d) write file deltanll.txt and plot again the difference of L and L(true mean)
    //find minimum of the function

    ofstream deltanll("deltanll.txt");
    double true_L = -2 * log(likelihood);
    std::vector<double> delta_loglike;

    for (auto element : lnlikelihood){
        delta_loglike.push_back(element - true_L);
    }

    for (size_t i = 0; i < mean_values.size(); ++i) {
        deltanll << mean_values[i] << " " << delta_loglike[i] << "\n";
    }

    deltanll.close();


    double minimum =  *min_element(delta_loglike.begin(), delta_loglike.end());

    cout << "min value of delta log likelihoods : " <<  minimum << endl;

    auto k = find(delta_loglike.begin(), delta_loglike.end(), minimum);
    auto index_min = k - delta_loglike.begin();

    //cout << "index position of this maximum: " << it - poi_variable_mu.begin() << endl;;

    cout << "mu value of this minimum in delta likelihood: " << mean_values[index_min] << endl;


    //find an interval of mu that fulfills -2 ln(L(mu)/ L(mu true)) < 1 and compare to uncertainty of sample mean
    //if we just took our 60 generated mu values, only 3.1 and 3.2 fulfill condition --> do i have to crank up 
    //the resolution??

    //uncertainty of the sample mean: we already did that in stichprobe.cc 
    //variance is 2.73455, standard deviation 1.65365




    //e) saturated model

    auto sat_value = saturated_prob(daten);
    //comute likelihood ratio by deviding likelihood by sat_value and taking log and so on...
    double sat_model_value = -2 * log(likelihood / sat_value);

    std::cout << "-----------exercise e) ------------" << endl;
    std::cout << "For saturated model, the log likelihood ratio is " << sat_model_value << std::endl;


    //relative deviation of likelihood from mean:

    double rel_dev = (sat_model_value - 233)/sqrt(2* 233);

    std::cout << "Standard deviation of likelihood ratio from mean: " << rel_dev << std::endl;

    



}