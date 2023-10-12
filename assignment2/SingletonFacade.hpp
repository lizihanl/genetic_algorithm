//
// Created by zihan on 2022-11-21.
//

#ifndef LAB1TEMPLATE_SINGLETONFACADE_HPP
#define LAB1TEMPLATE_SINGLETONFACADE_HPP

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
using namespace std;

const int CITIES_IN_TOUR=32;
const int POPULATION_SIZE=32;
//const int SHUFFLES=64;
const int ITERATIONS=1000;
const int MAP_BOUNDARY=1000;
const int PARENT_POOL_SIZE=5;
const double MUTATION_RATE=0.15;
const int NUMBER_OF_PARENTS=2;
const int NUMBER_OF_ELITES=1;
const double IMPROVEMENT_FACTOR=1.6;

typedef struct CityPosition{
    int cityNum;
    int x;
    int y;
}CityPosition;

class SingletonFacade{
private:
    int colony[POPULATION_SIZE][CITIES_IN_TOUR+1];   //city colony,start city as 1
    double fitness[POPULATION_SIZE];           // 1/Distance[POPULATION_SIZE]
    double Distance[POPULATION_SIZE];
    int BestRooting[CITIES_IN_TOUR+1];
    int parent[NUMBER_OF_PARENTS][CITIES_IN_TOUR+1];
    double BestFitness;
    double BestValue;                  //best' distance
    double BestNonElite;                //non-elites' best distance
    int BestNum;                       //number of best cities


public:

    void shuffle_city(CityPosition CityPos[]);
    int get_distance_between_chities(CityPosition CityPos[],int first,int secend);
    double get_tour_distance(CityPosition CityPos[],int lineNum);
    void determine_fitness(CityPosition CityPos[]);
    void select_parents();
    void crossover();
    void mutate();
    bool contains_city(CityPosition CityPos[CITIES_IN_TOUR],int x,int y,int n);
    bool check(int pop,int num,int cityNum);
    bool checkArray(int arr[],int num,int data);
    void arrCopy(int src[],int dest[],int n);
    void displayPopulation(int lineNum);

    int getBestNum();
    double getBestDistance();
    double getBestNonElite();
    int *getBestRooting();
};



#endif //LAB1TEMPLATE_SINGLETONFACADE_HPP
