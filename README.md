# genetic_algorithm

Examine the traveling salesman problem. Suppose we have an unordered container of cities to visit. 
We want to sort and visit the cities in a sequence that minimizes the distance traveled. 
With a small number of cities this is trivial, but with a large number of cities this can take a very, 
very long time (what is the big O of this type of problem)? A genetic algorithm is one approach that makes this easier.

A genetic algorithm is an algorithm that draws inspiration from theories of natural selection. 
Start with a ‘population’ of sample candidates, evaluate their fitness, 
perform some sort of cross-over and mutation, 
and continue until we have a solution that most closely meets our needs or meets our termination criteria.

