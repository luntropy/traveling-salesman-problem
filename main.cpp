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

    int gen = 0;
    double prev_eval = population->get_total_eval();
    std::cout << "Initial generation (" << gen << "): ";
    population->print_total_eval();
    ++gen;

    while (true) {
        population->new_generation();
        double current_eval = population->get_total_eval();

        if (prev_eval == current_eval) {
            std::cout << "Last generation (" << gen << "): ";
            population->print_total_eval();
            break;
        }
        prev_eval = current_eval;

        if (gen == 10 || gen % N == 0) {
            std::cout << "Generation (" << gen << "): ";
            population->print_total_eval();
        }
        ++gen;
    }

    delete population;

    return 0;
}
