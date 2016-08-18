#ifndef GENOME_HPP_
#define GENOME_HPP_

#include <iostream>
#include <string>
#include <random>


using namespace std;	


class EvolutionParameters
{
public:
	int n_keep;
	double sigma_survive;
	double p_mutate_disturbe;
	double p_mutate_replace;
	double p_non_homologous_crossover;
	bool b_crossing_over;
	bool b_mutate_mutation_rate;
	int n_min_genes_till_cross;
	int n_max_genes_till_cross;
};

class Genome
{
friend unsigned int test_genome(bool verbose);

public:

	Genome(void);
	
	Genome(const Genome& genome);

	Genome(unsigned int number_of_genes, default_random_engine& rnd);

	virtual
	~Genome();

	string
	toString(unsigned int indent=0) const; 
	
	string
	toLine(void) const;
	
	friend ostream&
	operator<<(ostream& os, const Genome& genome);
	
	bool 
	operator<(const Genome& other) const;
	
	Genome& 
	operator=(const Genome& other);
	
	void 
	evaluate(double (*fitness_function)(const vector<double>& genes));
	
	void 
	mutate(EvolutionParameters ep, default_random_engine& rnd);
	
	Genome
	crossover(const Genome& other, EvolutionParameters ep, default_random_engine& rnd) const;
	
	Genome
	non_homologous_crossover(const Genome& other, EvolutionParameters ep, default_random_engine& rnd) const;

	double fitness(void) const { return m_fitness; }
	
	vector<double> getGenes(void) const;

private:

	vector<double> m_genes;
	
	double m_fitness;
	
	double m_sigma_mutation;
};



#endif /* GENOME_HPP_ */
