#include <iostream>
#include <random>
#include <chrono>

#include "Genome.hpp"
#include "Population.hpp"
//#include "DriftTube.hpp"

using namespace std;
 
double fitness_function(const vector<double>& genes)
{
	double sum_off_diff = 0;
	for( auto it=genes.begin() ; it < genes.end(); it++ ) {
		sum_off_diff += 1-abs(0.12345 - *it);
	}
	return sum_off_diff;
}


double fitness_2_max(const vector<double>& genes)
{
	double sum_off_diff = 0;
	for( auto it=genes.begin() ; it < genes.end(); it++ ) {
		double x = *it * 6 - 3;
		sum_off_diff += -0.25*x*x*x*x + 2*x*x + 0.01*x - 1;
	}
	return sum_off_diff;
	//x = x*3;
//-0.25 * x^4 + 2 * x^2 + 0.01x- 1
	// f(-1.99875) = 2.98001 (1/3x = 0.166875)
	// f(2.00125) = 3.02001  (1/3x = 0.83354167)
	return 0;
}
 
 
int main(int argc , char *argv[])
{
	cout << "BRIENCHEN!!!" << endl;
 
	default_random_engine rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

	EvolutionParameters ep;
	ep.n_keep                     = 2;
	ep.sigma_survive              = 0.3; // 0.3 scheint ein guter Wert zu sein // 0.1 wirft 60% weg, 0.2 wirft 40% weg
	ep.p_mutate_disturbe          = 0.5;
	ep.p_mutate_replace           = 0.01;
	ep.p_non_homologous_crossover = 0.2;
	ep.b_crossing_over            = true;
	ep.b_mutate_mutation_rate     = true;
	ep.n_min_genes_till_cross     = 1;
	ep.n_max_genes_till_cross     = 10;	
	     
	int number_of_genomes     = 50;
	int number_of_genes       = 10;
	int number_of_generations = 200;
	
    Population p(number_of_genomes, number_of_genes, rnd);
    
    for( int i=0; i<number_of_generations; i++ ) {
    
		p = p.createOffspring(fitness_2_max, ep, rnd);
    	p.evaluate(fitness_2_max);
	    cout << "Generation " << i << ":\t" << p.toLine() << endl;     
    }
    
    cout << p.toString() << endl; 
    
    /*
    int max__ = 20;
    int a[20];
	for( int i=0; i< max__; i++ ){	
		a[i] = 0;
	}
    normal_distribution<double> rdist(0, ep.sigma_survive * max__);
	for( int i=0; i< 10000; i++ ){
		int mother_index = min(floor(abs(rdist(rnd))), max__-1.);
		a[mother_index] ++;
	}
	
	for( int i=0; i< max__; i++ ){	
		cout << i << " -> " << a[i] << endl;
	}*/

    return 0;
}
