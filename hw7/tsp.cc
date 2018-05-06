// we need fstream to read in files
#include <fstream>
// used to log on file opening err
#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>
#include "tsp.h"

// reads in file of city coords from csv, returns vector of coords
cities_t read_cities(std::string filename) {
  std::ifstream file;
  file.open(filename);
  // create empty array, will be returned immediately if file fails to open
  cities_t output;
  if(file.fail()) {
    std::cout << "file could not be opened" << std::endl;
    return output;
  }
  // read in file by coord
  // presumes each line cottains only 2 ints, seperated by whitespace
  int x, y;
  while (file >> x >> y) {
    const coord_t this_coord = { x, y };
    output.push_back(this_coord);
  }

  // close file, flush any changes still in buffer
  file.close();
  // return array of city coordinates
  return output;
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

double total_path_distance(cities_t cities, permutation_t ordering) {
  double totalDistance = 0.0;
  coord_t firstCity = cities[*ordering.begin()];
  coord_t prevCity = firstCity;
  // add one to iterator so we start at 2nd index, with the first city stored in prevCity
  for (permutation_t::iterator it = ordering.begin() += 1; it != ordering.end(); it++) {
    int key = *it;
    coord_t city = cities[key];
    double distance = calc_euclidian_dist(prevCity, city);
    totalDistance += distance;
    prevCity = city;
  }
  // get last city coords
  coord_t lastCity = cities[*ordering.rbegin()];
  // add distance between last and first cities
  double returnDistance = calc_euclidian_dist(lastCity, firstCity);
  totalDistance += returnDistance;
  // return total distance across permutation
  return totalDistance;
}

permutation_t random_permutation(unsigned size) {
  // create (truly, I think) random seed
  std::random_device dev;
  // create random number generator
  std::default_random_engine gen(dev());
  // create random distribution of unsinged ints
  std::uniform_int_distribution<unsigned int> dist(0, size - 1);
  // create permutation to return
  permutation_t out;
  // loop until permutation is filled
  // only add numbers if they are not in the array,
  // so we search through the array each time
  // probably not the most efficient thing
  while (out.size() < size) {
    unsigned int val = dist(gen);
    // only add val to permutation if it isn't already in out
    if(std::find(out.begin(), out.end(), val) == out.end()) {
      out.push_back(val);
    }
  }
  // return permutation
  return out;
}

