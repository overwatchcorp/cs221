#include <iostream>
#include <fstream>
#include <string>
#include "tsp.cc"

// const int iters = 1;
const int iters = 100000;

void save_permuted_cities(std::string filename, permutation_t perm, cities_t cities) {
  std::ofstream file;
  file.open(filename);
  if(file.fail()) {
    std::cout << "could not open file" << std::endl;
    return;
  }
  for (permutation_t::iterator it = perm.begin(); it != perm.end(); it++) {
    coord_t city = cities[*it];
    file << city.first << " " << city.second << std::endl;
  }
  file.close();
  return;
}

int main() {
  cities_t cities = read_cities("challenge.tsv");
  permutation_t smallest = random_permutation(cities.size());
  double smallestDistance = total_path_distance(cities, smallest);

  for (int i = 0; i < iters - 1; i++) {
    permutation_t p = random_permutation(cities.size());
    double dist = total_path_distance(cities, p);
    if (dist < smallestDistance) {
      smallest = p;
      smallestDistance = dist;
      std::cout << i << " " << smallestDistance << std::endl;
    }
  }
  save_permuted_cities("out.tsv", smallest, cities);
  return 0;
}
