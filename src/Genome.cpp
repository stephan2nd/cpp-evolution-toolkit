#include "Genome.hpp"

#include <sstream>



Genome::Genome(void):
	m_genes(0),
	m_fitness(0),
	m_sigma_mutation(0.05)
{ }



Genome::Genome(const Genome& genome):
	m_genes(genome.m_genes),
	m_fitness(genome.m_fitness),
	m_sigma_mutation(genome.m_sigma_mutation)
{
	
}


Genome::Genome(unsigned int number_of_genes, default_random_engine& rnd):
	m_genes(number_of_genes),
	m_fitness(0),
	m_sigma_mutation(0.05)
{ 
    uniform_real_distribution<double> dist(0,1);
	for( auto it=m_genes.begin() ; it < m_genes.end(); it++ ) {
    	*it = dist(rnd);  
	}
}



Genome::~Genome()
{ }



string
Genome::toString(unsigned int indent) const
{
	string indention = "";
	for( unsigned int i=0; i<indent; i++ ){
		indention = indention + "\t";
	}
	
	stringstream ss;
	ss << indention << toLine();
	return ss.str();
}
	


string
Genome::toLine(void) const
{
	stringstream ss;
	ss.precision(5);
	ss << "Genome( fitness=" << m_fitness << ", sigma_mutation=" << m_sigma_mutation << ", genes=";
	for( auto it=m_genes.begin() ; it < m_genes.end(); it++ ) {
    	ss << "[" << *it << "]";
	}
	ss << " )";
	return ss.str();
}
	


ostream&
operator<<(ostream& os, const Genome& genome)
{
	return os << genome.toLine();
}



bool 
Genome::operator<(const Genome& other) const
{
	return (m_fitness < other.m_fitness);
}



Genome& 
Genome::operator=(const Genome& other)
{
	// START TODO: copy vector
	m_genes.clear(); 
	for( auto it=other.m_genes.begin() ; it < other.m_genes.end(); it++ ) {
    	m_genes.push_back(*it);
	}	
	// END TODO
	m_fitness = other.m_fitness;
	m_sigma_mutation = other.m_sigma_mutation;
	return *this;
}



void 
Genome::evaluate(double (*fitness_function)(const vector<double>& genes))
{
	m_fitness = fitness_function(m_genes);
}



void 
Genome::mutate(EvolutionParameters ep, default_random_engine& rnd)
{
    uniform_real_distribution<double> dist(0,1);
    normal_distribution<double> gauss(1, m_sigma_mutation);
    
	for( auto it=m_genes.begin() ; it < m_genes.end(); it++ ) {
    	if( dist(rnd) < ep.p_mutate_disturbe ) {
    		*it = (*it) * gauss(rnd);
    	} 
    	if( dist(rnd) < ep.p_mutate_replace ) {
    		*it = dist(rnd);
    	}
	}   
	
	if( ep.b_mutate_mutation_rate ){
	    normal_distribution<double> gauss2(1, 0.3);	

		double factor = -1;
		while( factor<0 or factor>2 ){
			factor = gauss2(rnd);
		}
		m_sigma_mutation = m_sigma_mutation * factor;
    }
}



Genome
Genome::crossover(const Genome& other, EvolutionParameters ep, default_random_engine& rnd) const
{
	Genome child;
	child.m_sigma_mutation = m_sigma_mutation;

	uniform_int_distribution<int> dist(ep.n_min_genes_till_cross, ep.n_max_genes_till_cross);
	
	int nof_genes_till_cross = dist(rnd);
	const Genome* active_genome = this;

	for( unsigned int i=0; i<m_genes.size(); i++){
		child.m_genes.push_back(active_genome->m_genes.at(i));
		if( nof_genes_till_cross > 0 ){
			nof_genes_till_cross -= 1;
		} else {
			nof_genes_till_cross = dist(rnd);
			if( active_genome == this ) { active_genome = &other; } 
		 	else						{ active_genome = this;   }
		}
	}

	return child;
}



Genome
Genome::non_homologous_crossover(const Genome& other, EvolutionParameters ep, default_random_engine& rnd) const
{
	uniform_int_distribution<int> dist_length(1, m_genes.size()/2);
	unsigned int length = dist_length(rnd);
    
	uniform_int_distribution<int> dist_start_index(0, m_genes.size()-1-length);
	unsigned int start_index = dist_start_index(rnd);
    
	uniform_int_distribution<int> dist_new_start(0, m_genes.size()-1);
	unsigned int new_start = dist_new_start(rnd);
	
	Genome child;
	child.m_sigma_mutation = m_sigma_mutation;
	
	bool shifting = false;

	for( unsigned int i=0; i<m_genes.size(); i++){
		
		if( i == new_start ){
			shifting = true;
		} else if ( i == new_start + length ){
			shifting = false;
		}
		
 		if( shifting ){
 			//cout << "A" << start_index << " " << i << " " << new_start << " " << length << endl;
 			
 			child.m_genes.push_back(other.m_genes.at(start_index + (i-new_start)));
 			//cout << "B" << endl;
		} else {
			child.m_genes.push_back(this->m_genes.at(i));
		}
	}
	
	return child;
}



vector<double> 
Genome::getGenes(void) const
{
	return m_genes;
}































