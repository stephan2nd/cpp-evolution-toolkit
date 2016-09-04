#ifndef POPULATION_HPP_
#define POPULATION_HPP_

#include <iostream>
#include <string>
#include <random>

#include "Genome.hpp"



using namespace std;

class Population
{
friend unsigned int test_population(bool verbose);

public:

	Population();

	Population(unsigned int number_of_genomes, unsigned int number_of_genes, default_random_engine& rnd);

	virtual
	~Population();

	string
	toString(unsigned int indent=0) const; 
	
	string
	toLine(void) const;
	
	friend ostream&
	operator<<(ostream& os, const Population& population);

	void addGenome(const Genome& genome);

	void evaluate(double (*fitness_function)(const vector<double>& genes));
	
	Population createOffspring(const EvolutionParameters& ep, default_random_engine& rnd);

	Population evaluateAndCreateOffspring(double (*fitness_function)(const vector<double>& genes), const EvolutionParameters& ep, default_random_engine& rnd);

	double fitness(void) const;
	
	Genome getBestGenome(void) const;

private:

	vector<Genome> m_genomes;
};

#endif /* POPULATION_HPP_ */
