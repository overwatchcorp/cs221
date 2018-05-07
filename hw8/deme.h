/*
 * Declarations for Deme class to evolve a genetic algorithm for the
 * travelling-salesperson problem.  A deme is a population of individuals.
 */

#ifndef _DEME_H_
#define _DEME_H_

#include "chromosome.h"
#include <random>
#include <vector>

class Deme {
  public:
    // Generate a Deme of the specified size with all-random chromosomes.
    // Also receives a mutation rate in the range [0-1].
    Deme(const cities_t* cities_ptr, unsigned pop_size, double mut_rate);

    // Clean up as necessary
    virtual ~Deme();

    // Evolve a single generation of new chromosomes, as follows:
    // We select pop_size/2 pairs of chromosomes (using the select() method below).
    // Each chromosome in the pair can be randomly selected for mutation, with
    // probability mut_rate, in which case it calls the chromosome mutate() method.
    // Then, the pair is recombined once (using the recombine() method) to generate
    // a new pair of chromosomes, which are stored in the Deme.
    // After we've generated pop_size new chromosomes, we delete all the old ones.
    virtual void compute_next_generation();

    // Return a copy of the chromosome with the highest fitness.
    Chromosome get_best() const;

    std::vector<Chromosome> create_pop(const cities_t* cities_ptr, unsigned pop_size);

  protected:
    // Randomly select a chromosome in the population based on fitness and
    // return a pointer to that chromosome.
    virtual Chromosome* select_parent();

  private:
    // list of all city coords
    const cities_t* my_cities_ptr; // Keep ptr to cities, no need for full copy
    // Store vector of Chromosomes that represent permutations for salesman
    std::vector<Chromosome> my_pop;
    // probability of a mutation occuring (0-1)
    const double my_mut_prob;
};

#endif
