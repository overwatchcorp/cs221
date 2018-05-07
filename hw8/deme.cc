#include "deme.h"

Deme::Deme(const cities_t* cities_ptr, unsigned pop_size, double mut_rate)
  : my_cities_ptr(cities_ptr), my_pop(create_pop(cities_ptr, pop_size)), my_mut_prob(mut_rate)
{

}

Deme::~Deme() {
}


std::vector<Chromosome> create_pop(const cities_t* cities_ptr, unsigned pop_size) {
  std::vector<Chromosome> population;
  for (unsigned i = 0; i < pop_size; i++) {
    Chromosome c = *new Chromosome(cities_ptr);
    population.push_back(c);
  }
  return population;
}

// Return a copy of the chromosome with the highest fitness.
Chromosome Deme::get_best() const {
  // iterate over all Chromosomes, calculate fitness
  Chromosome* best;
  unsigned bestFitness = 30000;
  for (std::vector<Chromosome>::iterator it = my_pop.begin();
};
