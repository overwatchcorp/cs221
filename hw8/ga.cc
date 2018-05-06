#include "tsp.h"
#include "deme.h"
#include "chromosome.h"

#include <iostream>

/* This program uses a genetic algorithm to solve the traveling salesperson
 * problem.  The user supplies a command line argument to the program
 * when it is executed. That command line argument is the name of a file
 * containing information about the cities to be visited in the form of
 * the x and y coordinates (whole numbers) for each city, one city per line.
 * The program then creates a randomly generated population of permutations
 * for traveling to those cities.  A mutation rate is also specified and which
 * indicates how aggressively the population's individuals mutate.  The
 * program then repeatedly evolves the population to generate increasingly
 * better (i.e. shorter total distances) city permutations.
 */

int main(int argc, char* argv[])  // These parameters are command line args
{
  const long pop_size = 20;
  const double mutation_rate = 0.1;

  // Check that the user specified an input file and exit if they didn't.
  if (argc != 2) {
    std::cerr << "Required parameter: TSV filename\n";
    return -1;
  }

  // Read in the cities from the specified file.
  cities_t cities = read_cities(argv[1]);

  double mindist = 1e100;   // shortest distance found so far

  // Create initial random population
  Deme deme(&cities, pop_size, mutation_rate);

  // Evolve the population to make it fitter and keep track of 
  // the shortest distance generated  
  for (long i = 1; i <= 10000/pop_size; ++i) {
    deme.compute_next_generation();    // generate next generation

    // Find best individual in this population
    const Chromosome best = deme.get_best();
    const double dist = best.calculate_total_distance();

    // If current best individual is fitter than previous individuals,
    // keep track of this distance as best city permutation found so far.
    if (mindist > dist) {
      mindist = dist;
      std::cout << (i*pop_size) << "\t" << mindist << std::endl;
      best.save("shortest.tsv");
    }
  }
}

