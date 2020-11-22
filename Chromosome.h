#include <iostream>

#include <vector>

#include <cmath>

#include "Gene.h"

#ifndef CHROMOSOME_H
#define CHROMOSOME_H

class Chromosome {
private:
    std::vector<Gene*> genes;
    double eval;
    double fitness;

    void update_fitness_eval();

public:
    Chromosome();
    Chromosome(std::vector<Gene*>);
    Chromosome(Gene**, unsigned long int);
    bool operator<(const Chromosome&);

    double get_fitness() const;
    double get_eval() const;
    std::vector<Gene*> get_genes() const;

    std::pair<Gene**, Gene**> breed(Chromosome*);
    void mutate();

    void print_fitness() const;
    void print_eval() const;
    void print_chromosome();
};

struct compare_chromosomes_less
{
    inline bool operator() (const Chromosome* a, const Chromosome* b)
    {
        return a->get_fitness() < b->get_fitness();
    }
};

struct compare_chromosomes_more
{
    inline bool operator() (const Chromosome* a, const Chromosome* b)
    {
        return a->get_fitness() > b->get_fitness();
    }
};

#endif
