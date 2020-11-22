#include "Gene.h"

Gene::Gene() {
    this->id = -1;
    this->x = -1;
    this->y = -1;
}

Gene::Gene(int id, int x, int y) {
    this->id = id;
    this->x = x;
    this->y = y;
}

int Gene::get_x() const {
    return this->x;
}

int Gene::get_y() const {
    return this->y;
}

double Gene::get_eval(Gene* gene) const {
    double x_dist = abs(this->x - gene->get_x());
    double y_dist = abs(this->y - gene->get_y());

    double distance = sqrt(pow(x_dist, 2) + pow(y_dist, 2));

    return distance;
}

void Gene::print_gene_id() const {
    std::cout << this->id;
}

void Gene::print_gene() const {
    std::cout << "Gene id: " << this->id << std::endl;
    std::cout << "Position: " << this->x << ':' << this->y << std::endl;
    std::cout << std::endl;
}
