#include <iostream>

#include <random>

#include <climits>

#include "Population.h"

// Population settings
unsigned long int L = 100; // Size of population
double old_gen_pct = 0.3;
double mutation_pct = 0.55;

int main() {
    srand(time(NULL));

    unsigned long int N;
    std::cin >> N;

    Population* population = new Population(N, L, old_gen_pct, mutation_pct);

    // Generate genes for the population
    population->generate_genes();

    // Generate population
    population->generate_population();

    int itr = 0;
    while (itr < 1000) {
        population->new_generation();

        if (itr % 50 == 0) {
            std::cout << "Generation " << itr << ": ";
            population->print_total_eval();
        }
        ++itr;
    }

    delete population;

    return 0;
}
