// for debugging :)
#include <iostream>
#include "deme.h"

Deme::Deme(const cities_t* cities_ptr, unsigned pop_size, double mut_rate)
  : my_cities_ptr(cities_ptr), my_pop(create_pop(cities_ptr, pop_size)), my_mut_prob(mut_rate)
{

}

Deme::~Deme() {
}


std::vector<Chromosome *> create_pop(const cities_t* cities_ptr, unsigned pop_size) {
  std::vector<Chromosome *> population;
  for (unsigned i = 0; i < pop_size; i++) {
    Chromosome c = *new Chromosome(cities_ptr);
    population.push_back(&c);
  }
  return population;
}

// Return a copy of the chromosome with the highest fitness.
Chromosome Deme::get_best() const {
  // iterate over all Chromosomes, calculate fitness
  Chromosome* best = new Chromosome(my_cities_ptr);
  unsigned bestFitness = 30000;
  for(std::vector<Chromosome *>::const_iterator it = my_pop.begin(); it != my_pop.end(); it++) {
    const double thisFitness = (*it)->calculate_fitness();
    if (thisFitness > bestFitness) {
      best = *it;
      bestFitness = thisFitness;
    }
  }
  return *best;
}

Chromosome* Deme::select_parent() {
  // use roulette wheel sampling
  double fitnessSum = 0.0;
  for(std::vector<Chromosome* >::const_iterator it = my_pop.begin(); it != my_pop.end(); it++) {
    const double thisFitness = (*it)->calculate_fitness();
    fitnessSum += thisFitness;
  }
  double randomFitness = std::fmod(rand(), fitnessSum);
  Chromosome* out;
  std::cout << "is this randomFitness reasonable? " << randomFitness << std::endl;
  for(std::vector<Chromosome* >::const_iterator it = my_pop.begin(); it != my_pop.end(); it++) {
    const double thisFitness = (*it)->calculate_fitness();
    fitnessSum -= thisFitness;
    out = *it;
    if (fitnessSum <= randomFitness)
      break;
  }
  return out;
}

