#include <iostream>

#include <vector>

#include <iomanip>
#include <stdlib.h>
#include <time.h>

#include <random>
#include <algorithm>

#include "Gene.h"
#include "Chromosome.h"

#ifndef POPULATION_H
#define POPULATION_H

class Population {
private:
    unsigned long int N; // Genes count
    unsigned long int L; // Population count
    double old_gen_pct;
    double mutation_pct;
    double total_fitness;
    double total_eval;
    std::vector<Gene*> genes;
    std::vector<Chromosome*> population;

    void copy_genes(const Population&);
    void copy_population(const Population&);
    void copy_population_obj(const Population&);
    void clear();

public:
    Population();
    Population(unsigned long int, unsigned long int, double, double);
    Population(const Population&);
    Population& operator=(const Population&);
    ~Population();

    double calc_total_fitness() const;
    double calc_total_eval() const;

    void generate_genes();
    void generate_population();
    std::vector<double> calc_prob_of_selection();
    std::vector<std::pair<Chromosome*, Chromosome*>> select_couples();
    std::vector<Chromosome*> breed();
    std::vector<Chromosome*> mutate();
    void new_generation();

    unsigned long int get_N() const;
    unsigned long int get_L() const;
    double get_old_gen_pct() const;
    double get_mutation_pct() const;
    double get_total_fitness() const;
    double get_total_eval() const;
    std::vector<Gene*> get_genes() const;
    std::vector<Chromosome*> get_population() const;

    void print_genes() const;
    void print_total_fitness() const;
    void print_total_eval() const;
    void print_population() const;
};

#endif
