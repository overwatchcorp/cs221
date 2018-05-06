/*
 * Implementation for Chromosome class
 */

#include <algorithm>
#include <cassert>
#include <random>
#include <iostream>
#include <fstream>
#include <random>

#include "chromosome.h"

// Generate a completely random permutation from a list of cities
Chromosome::Chromosome(const cities_t* cities_ptr)
  : my_cities_ptr(cities_ptr), my_order(random_permutation(cities_ptr->size()))
{
  assert(is_valid());
}

// Clean up as necessary
Chromosome::~Chromosome()
{
  //TBD
}

// Perform a single mutation on this chromosome
void
Chromosome::mutate()
{

  // create (truly, I think) random seed
  std::random_device dev;
  // create random number generator
  std::default_random_engine gen(dev());
  // create random distribution of unsinged ints
  std::uniform_int_distribution<unsigned int> dist(0, my_order.size() - 1);
  int p1, p2;
  p1 = dist(gen);
  // make sure p2 is differnt from p1
  do {
    p2 = dist(gen);
  } while (p1 == p2);
  // just a check to make sure they're not equal
  // (so we don't go on with a MISTAKE)
  assert(p1 != p2);

  // TODO: remove visual checks once behvaior is confirmed
  // visual check part 1
  std::cout << "Indexes " << p1 << " and " << p2 << " should swap!" << std::endl;
  for(auto it = my_cities_ptr->begin(); it != my_cities_ptr->end(); it++) {
    std::cout << it->first << " " << it->second;
  }
  std::cout << std::endl;

  // swap values
  cities_t cities = *my_cities_ptr;
  // copy value to temp
  coord_t temp = cities[p1];
  cities[p1] = cities[p2];
  cities[p2] =temp;

  // visual check part 2
  for(auto it = my_cities_ptr->begin(); it != my_cities_ptr->end(); it++) {
    std::cout << it->first << " " << it->second;
  }
  std::cout << std::endl;

  assert(is_valid());
}

// Return a pair of offsprings by recombining with another chromosome
// Note: this method allocates memory for the new offsprings
std::pair<Chromosome*, Chromosome*>
Chromosome::recombine(const Chromosome* other) const
{
  assert(is_valid());
  assert(other->is_valid());

  // generate bounds for swath to swap
  // create (truly, I think) random seed
  std::random_device dev;
  // create random number generator
  std::default_random_engine gen(dev());
  // create random distribution of unsinged ints
  std::uniform_int_distribution<unsigned int> dist(0, my_order.size() - 1);
  int p1, p2;
  p1 = dist(gen);
  // make sure p2 is differnt from p1
  do {
    p2 = dist(gen);
  } while (p1 == p2);
  // just a check to make sure they're not equal
  // (so we don't go on with a MISTAKE) (mistakes are bad, this is verified true info)
  assert(p1 != p2);
  // TODO: check to see if we need to add p1 < p2 check

  // create swaths
  const permutation_t
    swath1(my_order.begin() + p1, my_order.begin() + p2),
    swath2(other->my_order.begin() + p1, other->my_order.begin() + p2);

  // create permutation for child 1
  // -> derrived from parent 2 with swath from parent 1
  // first, create beginning (everything from index 0 to end of swatch) (gets put to right of swatch)
  permutation_t child2;
  // iterate over each index other my_order index 0 to p2
  for (permutation_t::const_iterator it = other->my_order.begin(); it != other->my_order.begin() + p2; it++) {
    // if *it NOT found in swath1, push_back to child1
    if(std::find(swath1.begin(), swath1.end(), *it) == swath1.end()) {
      child2.push_back(*it);
    }
  }
  // add swath1 to child2
  for(permutation_t::const_iterator it = swath1.begin(); it != swath1.end(); it++) {
    child2.push_back(*it);
  }
  // iterate over each index other my_order index p2 to end
  for (permutation_t::const_iterator it = other->my_order.begin() + p2; it != other->my_order.end(); it++) {
    // if *it NOT found in swath1, push_back to child1
    if(std::find(swath1.begin(), swath1.end(), *it) == swath1.end()) {
      child2.push_back(*it);
    }
  }
  // create permutation for child 2
  // -> derrived from parent 2 with swath from parent 1
  // first, create beginning (everything from index 0 to end of swatch) (gets put to right of swatch)
  permutation_t child1;
  // iterate over each index other my_order index 0 to p2
  for (permutation_t::const_iterator it = my_order.begin(); it != my_order.begin() + p2; it++) {
    // if *it NOT found in swath2, push_back to child1
    if(std::find(swath2.begin(), swath2.end(), *it) == swath2.end()) {
      child1.push_back(*it);
    }
  }
  // add swath2 to child1
  for(permutation_t::const_iterator it = swath2.begin(); it != swath2.end(); it++) {
    child1.push_back(*it);
  }
  // iterate over each index other my_order index p2 to end
  for (permutation_t::const_iterator it = my_order.begin() + p2; it != my_order.end(); it++) {
    // if *it NOT found in swath2, push_back to child1
    if(std::find(swath2.begin(), swath2.end(), *it) == swath2.end()) {
      child1.push_back(*it);
    }
  }
  // create and return pair of chromosomes
  Chromosome *ch1 = new Chromosome(my_cities_ptr);
  ch1->my_order = child1;
  Chromosome *ch2 = new Chromosome(my_cities_ptr);
  ch2->my_order = child2;
  return(std::pair<Chromosome*, Chromosome*>(ch1, ch2));
}

// For an ordered set of parents, return a child using the ordered crossover.
// The child will have the same values as p1 in the range [b,e),
// and all the other values in the same order as in p2.
Chromosome*
Chromosome::create_child_of(const Chromosome* p1, const Chromosome* p2,
                           unsigned b, unsigned e) const
{
  Chromosome* child = new Chromosome(*p1);

  // We iterate over both parents separately, copying from parent1 if the
  // value is within [b,e) and from parent2 otherwise
  unsigned i = 0, j = 0;

  for ( ; i < p1->my_order.size() && j < p2->my_order.size(); ++i) {
    if (i >= b and i < e) {
      child->my_order[i] = p1->my_order[i];
    }
    else { // Increment j as long as its value is in the [b,e) range of p1
      while (p1->is_in_range(p2->my_order[j], b, e)) {
        ++j;
      }
      assert(j < p2->my_order.size());
      child->my_order[i] = p2->my_order[j];
      j++;
    }
  }

  assert(child->is_valid());
  return child;
}

double calc_euclidian_dist(coord_t first, coord_t second) {
    double x1 = first.first, x2 = second.first, y1 = first.second, y2 = second.second;
    double x = x1 - x2;
    double y = y1 - y2;
    double distance = pow(x,2) + pow(y,2);
    distance = sqrt(distance);
    // std::cout << "hop "  << first.first << " " << first.second << ", " << second.first << " " << second.second<< std::endl;
    return distance;
}

// Return a positive fitness value, with higher numbers representing
// fitter solutions (shorter total-city traversal path).
double
Chromosome::calculate_fitness() const
{
  double totalDistance = 0.0;
  cities_t cities = *my_cities_ptr;
  coord_t firstCity = cities[*my_order.begin()];
  coord_t prevCity = firstCity;
  // add one to iterator so we start at 2nd index, with the first city stored in prevCity
  for (permutation_t::const_iterator it = my_order.begin() += 1; it != my_order.end(); it++) {
    int key = *it;
    coord_t city = cities[key];
    double distance = calc_euclidian_dist(prevCity, city);
    totalDistance += distance;
    prevCity = city;
  }
  // get last city coords
  coord_t lastCity = cities[*my_order.rbegin()];
  // add distance between last and first cities
  double returnDistance = calc_euclidian_dist(lastCity, firstCity);
  totalDistance += returnDistance;
  // distance subtracted from max distance (about?), so worst perfomer has fitness near 30000, best gets closer to 0
  const unsigned int fitness = 30000 - totalDistance;
  // check to make sure fitness is not negative
  assert(fitness > 0);
  // return total distance across permutation
  return fitness;
}

// Save city ordering to file.  Cities are represented with their coordinates
// and are saved in the same order as the chromosome's permutation.
void
Chromosome::save(std::string filename) const
{
  std::ofstream file;
  file.open(filename);
  if(file.fail()) {
    std::cout << "could not open file" << std::endl;
    return;
  }
  cities_t cities = *my_cities_ptr;
  for (permutation_t::const_iterator it = my_order.begin(); it != my_order.end(); it++) {
    coord_t city = cities[*it];
    file << city.first << " " << city.second << std::endl;
  }
  file.close();
  return;
}

// A chromsome is valid if it has no repeated values in its permutation,
// as well as no indices above the range (length) of the chromosome.
// We implement this check with a sort, which is a bit inefficient, but simple
bool
Chromosome::is_valid() const
{
  // go through every number from 0 to my_order.size() -1, check to see if my_order contains it
  for(unsigned int i = 0; i < my_order.size() - 1; i++) {
    if(std::find(my_order.begin(), my_order.end(), i) == my_order.end()) {
      return false;
    }
  }
  return true;
}

// Find whether a certain value appears in a given range of the chromosome.
// Returns true if value is within the specified the range specified
// [begin, end) and false otherwise.
bool
Chromosome::is_in_range(unsigned value, unsigned begin, unsigned end) const
{
  for (unsigned idx = begin; idx < end; ++idx) {
    if (value == my_order[idx]) {
      return true;
    }
  }
  return false;
}
