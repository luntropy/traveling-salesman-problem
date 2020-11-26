#include <iostream>

#include <random>

#include <climits>

#include "Population.h"

// Population settings
unsigned long int L = 200; // Size of population - 2 * N
double old_gen_pct = 1 / 200; // How many individuals to keep from old generation - 1 / pop_size
double mutation_pct = 0.25;

int main() {
    srand(time(NULL));

    unsigned long int N;
    std::cin >> N;

    L = 2 * N;
    old_gen_pct = 1 / L;

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
            // population->print_total_eval();
            population->print_best_path();
            break;
        }
        prev_eval = current_eval;

        if (gen == 10 || gen % N == 0) {
            std::cout << "Generation (" << gen << "): ";
            // population->print_total_eval();
            population->print_best_path();
        }
        ++gen;
    }

    delete population;

    return 0;
}
