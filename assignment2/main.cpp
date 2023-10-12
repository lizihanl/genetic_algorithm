//Name: Zihan Li
//Student# : A01282005
#include <iostream>
#include "SingletonFacade.hpp"
using namespace std;
unsigned seed=(unsigned)time(0);

int main() {
    srand(seed);
//    TSP citys;
    CityPosition CityPos[CITIES_IN_TOUR];
    SingletonFacade oS;
    double base,bestDistance,newElite,distanceBestNonElite;
    int iterationsNum;
    int baseRoute[CITIES_IN_TOUR+1];

    oS.shuffle_city(CityPos);
    oS.determine_fitness(CityPos);
    oS.arrCopy(oS.getBestRooting(),baseRoute,CITIES_IN_TOUR+1);
    cout<<"Original routing list: "<<endl;
    for(int i=0;i<POPULATION_SIZE;i++){
        oS.displayPopulation(i);
    }
    base=oS.getBestDistance();
    bestDistance=base;
    newElite=base;
    distanceBestNonElite=oS.getBestNonElite();
    cout<<"Elite:(At Team "<<oS.getBestNum()<<") "<<endl;
    cout<<"Best Route: ";
    oS.displayPopulation(oS.getBestNum());
    cout<<"Best Distance: "<<base<<endl;
    cout<<"Best non-elite distance: "<<distanceBestNonElite<<endl;
    int i=1;
    cout<<endl<<"Start iteration..."<<endl;
    while( (i<=ITERATIONS)&&((base/bestDistance)<IMPROVEMENT_FACTOR)) {
        iterationsNum=i;
        oS.select_parents();
        oS.crossover();
        oS.mutate();
        oS.determine_fitness(CityPos);
        bestDistance=oS.getBestDistance();
        distanceBestNonElite=oS.getBestNonElite();
        if(newElite!=bestDistance) {
            cout<<"Find a new Elite!(Iteration:"<<i<<"); Distance:"<<bestDistance<<endl;
            newElite = bestDistance;
        }
        else if(i%100==0&&i>0){
            cout<<"Iteration:"<<i<<";  Elite distance:"<<bestDistance<<";  Best non-elite distance: "<<distanceBestNonElite<<";  Improvement over base:"<<base/bestDistance<<endl;
        }
        i++;
    }
    cout<<"--- FINISHED ALGORITHM ---"<<endl;
    cout<<"Total iterations: "<<iterationsNum<<endl;
//    cout<<"Elite:(At Team "<<oS.getBestNum()<<"）"<<endl;
//    cout<<"Best Distance: "<<bestDistance<<"  improvement factor"<<bestDistance/base*100<<"%"<<endl;

    cout<<"Original elite: "<<endl<<"Distance: "<<base<<"  route: ";
    for(int j=0;j<CITIES_IN_TOUR;j++)
        cout<<baseRoute[j]<<"->";
    cout<<baseRoute[CITIES_IN_TOUR]<<endl;
    cout<<"Best elite:     "<<endl<<"Distance: "<<bestDistance<<"  route: ";
    oS.displayPopulation(oS.getBestNum());
    if(iterationsNum!=1000)
        cout<<"Improvement factor reached!"<<endl;
    cout<<"Improvement factor:"<<base/bestDistance<<endl;


    return 0;
}
