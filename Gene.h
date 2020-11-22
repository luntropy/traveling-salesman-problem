#include <iostream>

#include <utility>

#include <cmath>

#ifndef GENE_H
#define GENE_H

class Gene {
private:
    int id;
    int x;
    int y;

public:
    Gene();
    Gene(int, int, int);

    int get_x() const;
    int get_y() const;
    double get_eval(Gene*) const;

    void print_gene_id() const;
    void print_gene() const;
};

#endif
