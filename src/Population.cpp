#include "Population.hpp"

#include <sstream>



Population::Population():
	m_genomes(0)
{

}



Population::Population(unsigned int number_of_individuals, unsigned int number_of_genes, default_random_engine& rnd):
	m_genomes(number_of_individuals)
{ 
	for( auto it=m_genomes.begin() ; it < m_genomes.end(); it++ ) {
    	*it = Genome(number_of_genes, rnd);
	}	
}



Population::~Population()
{ }



string
Population::toString(unsigned int indent) const
{
	string indention = "";
	for( unsigned int i=0; i<indent; i++ ){
		indention = indention + "\t";
	}
	
	stringstream ss;
	ss << indention << toLine() << " {\n";
	for( auto it=m_genomes.begin() ; it < m_genomes.end(); it++ ) {
    	ss << it->toString(indent+1) << "\n";
	}
	ss << indention << "}";	
	
	return ss.str();
}
	


string
Population::toLine(void) const
{
	stringstream ss;
	ss << "Population( size=" << m_genomes.size() << ", fitness=" << fitness() << ", best=" << m_genomes.at(0).fitness() << " )";
	return ss.str();
}
	


ostream&
operator<<(ostream& os, const Population& population)
{
	return os << population.toLine();
}



void 
Population::addGenome(const Genome& genome)
{
	m_genomes.push_back(genome);
}



void 
Population::evaluate(double (*fitness_function)(const vector<double>& genes))
{
	for( auto it=m_genomes.begin() ; it < m_genomes.end(); it++ ) {
    	it->evaluate(fitness_function);
	}
	sort(m_genomes.rbegin(), m_genomes.rend());
}



Population 
Population::createOffspring(double (*fitness_function)(const vector<double>& genes), const EvolutionParameters& ep, default_random_engine& rnd)
{
	Population offspring;
	
	evaluate(fitness_function);
	
	for( int i=0; i<ep.n_keep; i++ ){
		offspring.addGenome(m_genomes.at(i));
	}
	
	if( !ep.b_crossing_over ){
		normal_distribution<double> rdist(0, ep.sigma_survive * m_genomes.size());
		while( offspring.m_genomes.size() < m_genomes.size() ){
	
			int mother_index = floor(abs(rdist(rnd)));
			while( mother_index >= m_genomes.size() ){
				mother_index = floor(abs(rdist(rnd)));
			}

			Genome mother = m_genomes.at(mother_index);		
			mother.mutate(ep, rnd);		
			offspring.addGenome(mother);
		}	
		return offspring;
	} else {	
		normal_distribution<double> rdist(0, ep.sigma_survive * m_genomes.size());
	    uniform_real_distribution<double> dist(0,1);

		while( offspring.m_genomes.size() < m_genomes.size() ){
	
			int mother_index = floor(abs(rdist(rnd)));
			while( mother_index >= m_genomes.size() ){
				mother_index = floor(abs(rdist(rnd)));
			}
	
			int father_index = floor(abs(rdist(rnd)));
			while( father_index >= m_genomes.size() ){
				father_index = floor(abs(rdist(rnd)));
			}		

			Genome mother = m_genomes.at(mother_index);
			Genome father = m_genomes.at(father_index);
		
			mother.mutate(ep, rnd);
			father.mutate(ep, rnd);
		
			if( dist(rnd) < ep.p_non_homologous_crossover ){
				offspring.addGenome(mother.non_homologous_crossover(father, ep, rnd)); 
			} else {
				offspring.addGenome(mother.crossover(father, ep, rnd)); 
			}
		}	
		return offspring;
	}
}



double 
Population::fitness(void) const
{
	double fitness = 0;
	
	for( auto it=m_genomes.begin() ; it < m_genomes.end(); it++ ) {
    	fitness += it->fitness();
	}
	
	return fitness;
}



Genome 
Population::getBestGenome(void) const
{
	return m_genomes.at(0);
}











