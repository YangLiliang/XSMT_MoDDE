#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
using namespace std;
int popsize= 50; //Population size
const int evaluations= 500; //Maximum evolution algebra
const int endeval=evaluations;
const double w_start=0.95;
const double w_end=0.4;
const int w_varyfor=evaluations;
double w_now;
const double inerdec=(w_start-w_end)/w_varyfor;
const double c1_start=0.9;
const double c1_end=0.45;
const int c1_varyfor=evaluations;
double c1_now;
double c2_now;
const double c1_dec=(c1_start-c1_end)/c1_varyfor;
const int MAX=1010;
const double P=0.7071;//Store the value of sqrt(2)/2, which is convenient for rotating straight lines 
int vertice;// vertice number
double graph[MAX][2]={0},graphw[MAX][MAX]={0}; //Point coordinates, network diagram of the distance between points 
int min_tree[3010]={0}; //Store every temporarily generated particle 
struct pop
{
	int edge[3010];
	double fit_value;
}pop[1000+1],pbest[1000+1],gbest,pop_cpy[1200+1],pop_mid[1000+1],pop_tmp; //Population, individual optimal, global optimal 
 double evalgbest[100010];
 double fave=0, ffmin=10000000, ffmax=0;
 int count11;
 double count_ave;
 int flag_m;
 double fi, fm;//Adaptive variable 
 double differ_avg, differ,F[1000],F_self[1000];
 int  degree[MAX];
