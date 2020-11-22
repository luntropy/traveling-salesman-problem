#include "Chromosome.h"

void Chromosome::update_fitness_eval() {
    double evaluation = 0;
    std::vector<Gene*>::iterator it;
    for (it = this->genes.begin(); it != this->genes.end() - 1; ++it) {
        evaluation += (*it)->get_eval(*(it + 1));
    }

    this->eval = evaluation;
    this->fitness = 1 / evaluation;
}

Chromosome::Chromosome() {
    this->eval = 0.0;
    this->fitness = 0.0;
}

Chromosome::Chromosome(std::vector<Gene*> genes) {
    this->genes = genes;
    this->update_fitness_eval();
}

Chromosome::Chromosome(Gene** genes, unsigned long int N) {
    for (unsigned long int i = 0; i < N; ++i) {
        this->genes.push_back(genes[i]);
    }
    this->update_fitness_eval();
}

bool Chromosome::operator<(const Chromosome& a) {
    return this->get_fitness() < a.get_fitness();
}

double Chromosome::get_fitness() const {
    return this->fitness;
}

double Chromosome::get_eval() const {
    return this->eval;
}

std::vector<Gene*> Chromosome::get_genes() const {
    return this->genes;
}

std::pair<Gene**, Gene**> Chromosome::breed(Chromosome* second_parent) {
    unsigned long int point_one = rand() % this->genes.size();
    unsigned long int point_two = rand() % this->genes.size();

    if (point_two < point_one) {
        unsigned long int num = point_one;
        point_one = point_two;
        point_two = num;
    }

    // Tries to avoid generating the parents
    if ((point_one == 0 && (point_two == this->genes.size() - 1 || point_two == this->genes.size() - 2)) || (point_one = 1 && point_two == this->genes.size() - 1)) {
        point_two = rand() % this->genes.size();

        if (point_two < point_one) {
            unsigned long int num = point_one;
            point_one = point_two;
            point_two = num;
        }
    }

    Gene** first_child = new Gene*[this->genes.size()];
    Gene** second_child = new Gene*[this->genes.size()];
    Gene empty = Gene();

    for (unsigned long int t = 0; t < this->genes.size(); ++t) {
        first_child[t] = &empty;
        second_child[t] = &empty;
    }

    for (unsigned long int i = point_one; i <= point_two; ++i) {
        first_child[i] = this->genes.at(i);
        second_child[i] = second_parent->get_genes().at(i);
    }

    bool has_num = false;
    unsigned long int index = point_two + 1;
    for (unsigned long int i = 0; i < second_parent->get_genes().size(); ++i) {
        for (unsigned long int j = 0; j < second_parent->get_genes().size(); ++j) {
            if (second_parent->get_genes().at(i) == first_child[j]) {
                has_num = true;
                break;
            }
        }

        if (!has_num) {
            if (index > second_parent->get_genes().size() - 1) {
                index = 0;
            }
            if (index == point_one) {
                break;
            }
            first_child[index] = second_parent->get_genes().at(i);
            ++index;
        }
        has_num = false;
    }

    has_num = false;
    index = point_two + 1;
    for (unsigned long int i = 0; i < this->genes.size(); ++i) {
        for (unsigned long int j = 0; j < this->genes.size(); ++j) {
            if (this->genes.at(i) == second_child[j]) {
                has_num = true;
                break;
            }
        }

        if (!has_num) {
            if (index > this->genes.size() - 1) {
                index = 0;
            }
            if (index == point_one) {
                break;
            }
            second_child[index] = this->genes.at(i);
            ++index;
        }
        has_num = false;
    }

    std::pair<Gene**, Gene**> res = std::make_pair(first_child, second_child);

    // delete[] first_child;
    // delete[] second_child;

    return res;
}

void Chromosome::mutate() {
    unsigned long int position_one = rand() % this->genes.size();
    unsigned long int position_two = rand() % this->genes.size();

    if (position_one == position_two) {
        position_one = rand() % this->genes.size();
    }

    std::swap(this->genes.at(position_one), this->genes.at(position_two));
    this->update_fitness_eval();
}

void Chromosome::print_fitness() const {
    std::cout << this->fitness << std::endl;
}

void Chromosome::print_eval() const {
    std::cout << this->eval << std::endl;
}

void Chromosome::print_chromosome() {
    std::vector<Gene*>::iterator it;
    for (it = this->genes.begin(); it != this->genes.end(); ++it) {
        (*it)->print_gene_id();
    }
    std::cout << std::endl;
}
