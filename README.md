# Traveling Salesman Problem
## Purpose
The objective of the program is to solve the Traveling Salesman Problem using genetic algorithm.

[Traveling Salesman Problem Wikipedia](https://en.wikipedia.org/wiki/Travelling_salesman_problem)

## Rules
- The cities are represented as points.
- The points are randomly generated in the euclidean space.
- No return to the initial city.

## About the program
The program uses genetic algorithm to find the best route. A gene represents a city and a chromosome represents a route. Every chromosome is a valid solution. At least the best individual of each generation should be kept in the population. The program stops when no improvement is detected.

### To run the program
- Build it using `make`
- Run `./main`
- Input the number of cities (N <= 100)

### Output
- The cost of the best current route in the population.

![Output](https://github.com/luntropy/traveling-salesman-problem/blob/main/images/output-example-100-cities.png)
