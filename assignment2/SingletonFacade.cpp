//
// Created by zihan on 2022-11-21.
//
#include "SingletonFacade.hpp"

int round1(double number)
{
    return (number>0.0)?(number+0.5):(number-0.5);
}
void SingletonFacade::shuffle_city(CityPosition CityPos[]){
//    TSP citys;
//    CityPosition CityPos[CITIES_IN_TOUR];
    int x,y;
    cout<<"City list:"<<endl<<"Name:(x,y)"<<endl;
    for(int i=0;i<CITIES_IN_TOUR;i++) {
        CityPos[i].cityNum = i +1;
        CityPos[i].x = 0;
        CityPos[i].y = 0;
        x = rand() % MAP_BOUNDARY + 1;
        y = rand() % MAP_BOUNDARY + 1;
        while (contains_city(CityPos, x, y, i)) {
            x = rand() % MAP_BOUNDARY + 1;
            y = rand() % MAP_BOUNDARY + 1;
        }
        CityPos[i].x = x;
        CityPos[i].y = y;
        cout << CityPos[i].cityNum << ": (" << CityPos[i].x << " , " << CityPos[i].y << ")" << endl;
    }
    int cityNum;
    for(int i=0;i<POPULATION_SIZE;i++){
        colony[i][0]=NUMBER_OF_ELITES;
        colony[i][CITIES_IN_TOUR]=NUMBER_OF_ELITES;
        BestValue=0;
        BestFitness=0;
        BestNum=99;
        BestNonElite=65535;
    }
    for(int i=0;i<POPULATION_SIZE;i++)
    {
//            cout<<"1->";
        for(int j=1;j<CITIES_IN_TOUR;j++)       //not counting 0,32
        {
            cityNum=rand()%(CITIES_IN_TOUR-1)+1+1;      //random number in 2-32)
            while(check(i,j,cityNum))      //city.colony[i][j]
            {
                cityNum=rand()%(CITIES_IN_TOUR-1)+1+1;
            }

            colony[i][j]=cityNum;
//                cout<<cityNum<<"->";
        }
//            cout<<1<<"    "<<colony[i][0]<<"   "<<colony[i][1]<<" : "
//            <<get_distance_between_chities(CityPos,colony[i][0]-1,colony[i][1]-1)<<endl;
    }
    cout<<endl;
//    get_tour_distance(citys,CityPos);
}
bool SingletonFacade::contains_city(CityPosition CityPos[CITIES_IN_TOUR],int x,int y,int n){
    bool flag= false;
    for(int i=0;i<n;i++){
//        cout<<x<<","<<y<<endl;
        if(x==CityPos[i].x&&y==CityPos[i].y){
//            cout<<x<<","<<y<<endl;
            return true;
        }
    }
    return flag;
}
//check if new city is in the colony
bool SingletonFacade::check(int pop,int num,int cityNum){
    for(int i=0;i<=num;i++){
        if(cityNum==colony[pop][i])
            return true;    //yes
    }
    return false;
}
//check if the random number is repeated in the array
bool SingletonFacade::checkArray(int arr[],int num,int data){
    for(int i=0;i<num;i++){
        if(data==arr[i])
            return true;    //yes
    }
    return false;
}
int SingletonFacade::get_distance_between_chities(CityPosition CityPos[],int first,int secend){
//    cout<<"x1:"<<CityPos[first-1].x<<"x2"<<CityPos[secend-1].x<<" ";
    return round1(sqrt(pow(CityPos[first].x-CityPos[secend].x,2)+pow(CityPos[first].y-CityPos[secend].y,2)));
}
double SingletonFacade::get_tour_distance(CityPosition CityPos[],int lineNum){
    int start,end;
    double tourDistance=0;
//    for(int i=0;i<POPULATION_SIZE;i++){
//        Distance[i]=0;
    for(int j=1;j<=CITIES_IN_TOUR;j++){
        start=colony[lineNum][j-1]-1;
        end=colony[lineNum][j]-1;
        tourDistance=tourDistance + get_distance_between_chities(CityPos,start,end);   //city.Distance[i]每个个体的总路径
//            cout<<colony[i][j-1]<<"->";
    }
//        cout<<colony[i][CITIES_IN_TOUR];
//        cout<<"   "<<get_distance_between_chities(CityPos,start,end)<<" : ";
//        cout<<"   Distance: "<<Distance[i]<<endl;

//    }
    return tourDistance;
}
void SingletonFacade::determine_fitness(CityPosition CityPos[]){
    int Best=0;
    for(int i=0;i<POPULATION_SIZE;i++){
        Distance[i]= get_tour_distance(CityPos,i);
        fitness[i]=1/Distance[i];
        if(fitness[i]>fitness[Best])  //find the largest fitness
            Best=i;
//        displayPopulation(i);
    }
    arrCopy(colony[Best],BestRooting,CITIES_IN_TOUR+1);
    BestFitness=fitness[Best];
    BestValue=Distance[Best];
    BestNum=Best;
//    cout<<"Elite:"<<BestNum<<" Fitness:"<<BestFitness<<"  Distance:"<<BestValue
//    <<"  best three routes:"<<BestRooting[0]<<"->"<<BestRooting[1]<<"->"<<BestRooting[2]<<endl;
}

void SingletonFacade::arrCopy(int src[],int dest[],int n){
    for(int i=0;i<n;i++)
    {
        dest[i]=src[i];
    }
}
void SingletonFacade::displayPopulation(int lineNum){
    for(int i=0;i<CITIES_IN_TOUR;i++){
        cout<<colony[lineNum][i]<<"->";
    }
    cout<<colony[lineNum][CITIES_IN_TOUR]<<endl;//"     Distance: "<<Distance[lineNum]<<endl;
}
void SingletonFacade::select_parents(){
    int drawLots[PARENT_POOL_SIZE*2];
    int selectDistance=65535;
    int one;
//    int parent[2][CITIES_IN_TOUR+1];
//    cout<<BestNum<<endl;
//    int secendDistance=0;
    for(int k=0;k<2;k++) {
        for (int i = 0; i < 5; i++) {
            drawLots[i+5*k] = rand() % (CITIES_IN_TOUR);
            while (drawLots[i+5*k] == BestNum) {
                drawLots[i+5*k] = rand() % (CITIES_IN_TOUR);
            }
            for (int j = 0; j < i+5*k; j++) {
                while (drawLots[i+5*k] == drawLots[j]) {
                    drawLots[i + 5 * k] = rand() % (CITIES_IN_TOUR);
                }
            }
//            cout << "Randomly selected" << i + 1 << "Team--" << drawLots[i+5*k] << " : ";
            if (selectDistance > Distance[drawLots[i+5*k]]) {
                selectDistance = Distance[drawLots[i+5*k]];
                one = i+5*k;
            }
//            displayPopulation(drawLots[i+5*k]);
        }
//        cout << "Parent"<<k<<" select ："<< drawLots[one] << endl;
        arrCopy(colony[drawLots[one]],parent[k],CITIES_IN_TOUR+1);
//        displayPopulation(drawLots[one]);
        selectDistance=65535;
    }
}
void SingletonFacade::crossover(){
    int index=0;
    arrCopy(BestRooting,colony[0],CITIES_IN_TOUR+1);
    for(int i=1;i<POPULATION_SIZE;i++){
        index=rand()%(CITIES_IN_TOUR-1)+1;
//        index++;
        arrCopy(parent[0],colony[i],index+1);
        int j=1;                              //from index+1 to 31，loop 32-(index+1) times
        int k=index+1;
        while(j<CITIES_IN_TOUR-index){
            if(k==CITIES_IN_TOUR)
                k=1;
            if(!check(i,index,parent[1][k]))
            {
                colony[i][j+index]=parent[1][k];
                j++;
            }
//            else cout<<parent[1][k]<<"==k"<<k<<"  ";
            k++;

        }
//      cout<<endl;
//        displayPopulation(i);
    }
}
void SingletonFacade::mutate() {
    double index;
    int tmp;
    int mutateNum=(int)(POPULATION_SIZE*0.6);
    int subMutate[mutateNum];
    for(int i=0;i<mutateNum;i++){
        subMutate[i]=rand()%(CITIES_IN_TOUR-1)+1;
        while (checkArray(subMutate,i,subMutate[i])){
            subMutate[i]=rand()%(CITIES_IN_TOUR-1)+1;
        }
//        cout<<subMutate[i]<<"  ";
        for (int j = 1; j < CITIES_IN_TOUR; j++) {
            index=((double)(rand() % RAND_MAX)) / RAND_MAX;            //0-1 random number
//            cout<<index<<"  ";
            if(index<MUTATION_RATE){
                if(j!=CITIES_IN_TOUR-1) {
                    tmp = colony[subMutate[i]][j + 1];
                    colony[subMutate[i]][j + 1] = colony[subMutate[i]][j];
                    colony[subMutate[i]][j] = tmp;
                }
                else{
                    tmp = colony[subMutate[i]][1];
                    colony[subMutate[i]][1] = colony[subMutate[i]][j];
                    colony[subMutate[i]][j] = tmp;
                }
            }
        }
//        displayPopulation(subMutate[i]);
    }

}
int SingletonFacade::getBestNum(){
    return BestNum;
}
double SingletonFacade::getBestDistance(){
    return BestValue;
}
int *SingletonFacade::getBestRooting(){
    return BestRooting;
}
double SingletonFacade::getBestNonElite(){
    for(int i=0;i<POPULATION_SIZE;i++){
        if(BestNonElite>Distance[i]&&Distance[i]!=BestValue)
            BestNonElite=Distance[i];
    }
    return BestNonElite;
}
