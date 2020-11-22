#include "Population.h"

void Population::copy_genes(const Population& a) {
    for (unsigned long int i = 0; i < a.get_N(); ++i) {
        this->genes.push_back(a.get_genes().at(i));
    }
}

void Population::copy_population(const Population& a) {
    for (unsigned long int i = 0; i < a.get_L(); ++i) {
        this->population.push_back(a.get_population().at(i));
    }
}

void Population::copy_population_obj(const Population& a) {
    this->N = a.get_N();
    this->L = a.get_L();
    this->old_gen_pct = a.get_old_gen_pct();
    this->mutation_pct = a.get_mutation_pct();
    this->total_fitness = a.get_total_fitness();
    this->total_eval = a.get_total_eval();
    this->copy_genes(a);
    this->copy_population(a);
}

void Population::clear() {
    std::vector<Gene*>::iterator it;
    for (it = this->genes.begin(); it != this->genes.end(); ++it) {
        delete *it;
    }

    std::vector<Chromosome*>::iterator itr;
    for (itr = this->population.begin(); itr != this->population.end(); ++itr) {
        delete *itr;
    }
}

Population::Population() {
    this->N = 0;
    this->L = 0;
    this->old_gen_pct = 0;
    this->mutation_pct = 0;
    this->total_fitness = 0;
    this->total_eval = 0;
}

Population::Population(unsigned long int N, unsigned long int L, double old_gen_pct, double mutation_pct) {
    this->N = N;
    this->L = L;
    this->old_gen_pct = old_gen_pct;
    this->mutation_pct = mutation_pct;
    this->total_fitness = this->calc_total_fitness();
    this->total_eval = this->calc_total_eval();
}

Population::Population(const Population& a) {
    this->copy_population_obj(a);
}

Population& Population::operator=(const Population& a) {
    if (this != &a) {
        this->clear();
        this->copy_population_obj(a);
    }

    return *this;
}

Population::~Population() {
    this->clear();
}

double Population::calc_total_fitness() const {
    double total = 0;
    for (unsigned long int i = 0; i < this->population.size(); ++i) {
        total += (this->population.at(i))->get_fitness();
    }

    return total;
}

double Population::calc_total_eval() const {
    double total = 0;
    for (unsigned long int i = 0; i < this->population.size(); ++i) {
        total += (this->population.at(i))->get_eval();
    }

    return total;
}

void Population::generate_genes() {
    std::vector<int> coordinates;
    for (unsigned long int i = 0; i < this->N * 2; ++i) {
        unsigned long int num = rand() % (this->N * 2);
        coordinates.push_back(num);
    }

    int id = 0;
    for (unsigned long int i = 0; i < this->N; ++i) {
        int x = coordinates.at(i);
        int y = coordinates.at(i + 1);

        Gene* gene = new Gene(id, x, y);
        this->genes.push_back(gene);
        ++id;
    }
}

void Population::generate_population() {
    for (unsigned long int i = 0; i < this->L; ++i) {
        std::random_shuffle(this->genes.begin(), this->genes.end());

        Chromosome* chromosome = new Chromosome(this->genes);
        this->population.push_back(chromosome);
    }

    this->total_fitness = this->calc_total_fitness();
    this->total_eval = this->calc_total_eval();
}

std::vector<double> Population::calc_prob_of_selection() {
    std::sort(this->population.begin(), this->population.end(), compare_chromosomes_less());

    double total_fitness = this->calc_total_fitness();
    double prev_prob = 0.0;

    std::vector<double> probabilities;
    for (unsigned long int i = 0; i < this->population.size(); ++i) {
        double calc_prob = prev_prob + (this->population.at(i)->get_fitness() / total_fitness);
        probabilities.push_back(calc_prob);
        prev_prob = calc_prob;
    }

    return probabilities;
}

// Might have duplicate couples
std::vector<std::pair<Chromosome*, Chromosome*>> Population::select_couples() {
    std::vector<double> probabilities = this->calc_prob_of_selection();
    unsigned long int parents_to_select = this->L - this->L * this->old_gen_pct;
    unsigned long int added_parents = 0;

    std::vector<Chromosome*> parents;
    while (added_parents < parents_to_select) {
        double num = rand();
        num /= RAND_MAX;
        for (unsigned long int i = 0; i < probabilities.size() - 1; ++i) {
            if (num > probabilities.at(i) && num <= probabilities.at(i + 1)) {
                if (!parents.size()) {
                    parents.push_back(this->population.at(i));
                    ++added_parents;
                    break;
                }
                else if (parents.at(parents.size() - 1) != this->population.at(i)) {
                    parents.push_back(this->population.at(i));
                    ++added_parents;
                    break;
                }
            }
        }
    }

    std::vector<std::pair<Chromosome*, Chromosome*>> couples;
    for (unsigned long int i = 0; i <= parents_to_select - 2; i += 2) {
        couples.push_back(std::make_pair(parents.at(i), parents.at(i + 1)));
    }

    return couples;
}

std::vector<Chromosome*> Population::breed() {
    std::vector<std::pair<Chromosome*, Chromosome*>> couples = this->select_couples();

    std::vector<Chromosome*> children;
    for (unsigned long int i = 0; i < couples.size(); ++i) {
        std::pair<Gene**, Gene**> res = couples.at(i).first->breed(couples.at(i).second);

        Chromosome* first_child = new Chromosome(res.first, this->N);
        Chromosome* second_child = new Chromosome(res.second, this->N);

        children.push_back(first_child);
        children.push_back(second_child);
    }

    return children;
}

std::vector<Chromosome*> Population::mutate() {
    std::vector<Chromosome*> children = this->breed();
    unsigned long int mutations = this->L * this->mutation_pct;

    unsigned long int count = 0;
    while (count < mutations) {
        int pos = rand() % children.size();

        children.at(pos)->mutate();
        ++count;
    }

    return children;
}

void Population::new_generation() {
    std::vector<Chromosome*> children = this->mutate();

    std::sort(children.begin(), children.end(), compare_chromosomes_more());
    std::sort(this->population.begin(), this->population.end(), compare_chromosomes_more());

    std::vector<Chromosome*> new_generation;

    unsigned long int i = 0;
    unsigned long int j = 0;
    unsigned long int count_population = 0;
    while (count_population < this->L) {
        if (this->population.at(i)->get_fitness() > children.at(j)->get_fitness()) {
            new_generation.push_back(this->population.at(i));
            ++i;
        }
        else if (children.at(j)->get_fitness() >= this->population.at(i)->get_fitness()) {
            new_generation.push_back(children.at(j));
            ++j;
        }
        ++count_population;
    }

    // std::cout << i << ':' << j << std::endl;
    this->population.erase(this->population.begin(), this->population.begin() + i);
    i = 0;
    while (i < this->population.size()) {
        delete this->population.at(i);
        ++i;
    }

    children.erase(children.begin(), children.begin() + j);
    j = 0;
    while (j < children.size()) {
        delete children.at(j);
        ++j;
    }

    this->population = new_generation;
    this->total_fitness = this->calc_total_fitness();
    this->total_eval = this->calc_total_eval();
}

unsigned long int Population::get_N() const {
    return this->N;
}

unsigned long int Population::get_L() const {
    return this->L;
}

double Population::get_old_gen_pct() const {
    return this->old_gen_pct;
}

double Population::get_mutation_pct() const {
    return this->mutation_pct;
}

double Population::get_total_fitness() const {
    return this->total_fitness;
}

double Population::get_total_eval() const {
    return this->total_eval;
}

std::vector<Gene*> Population::get_genes() const {
    return this->genes;
}

std::vector<Chromosome*> Population::get_population() const {
    return this->population;
}

void Population::print_genes() const {
    for (unsigned long int i = 0; i < this->genes.size(); ++i) {
        (this->genes.at(i))->print_gene();
    }
}

void Population::print_total_fitness() const {
    std::cout << this->total_fitness << std::endl;
}

void Population::print_total_eval() const {
    std::cout << this->total_eval << std::endl;
}

void Population::print_population() const {
    for (unsigned long int i = 0; i < this->population.size(); ++i) {
        (this->population.at(i))->print_eval();
        (this->population.at(i))->print_fitness();
        (this->population.at(i))->print_chromosome();
    }
    this->print_total_fitness();
}
