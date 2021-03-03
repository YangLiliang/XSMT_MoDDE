#include"Header.h"
#include"GenerateGraph.cpp"
#include"InitializeTree.cpp"
#include"Getfitness.cpp"
#include"InitializePop.cpp"
#include"GetMutation1.cpp"
#include"GetCrossover_self1.cpp"
#include"GetCrossover_global1.cpp"
#include"GetMutation.cpp"
#include"GetCrossover_self.cpp"
#include"GetCrossover_global.cpp"
#include"GetCrossover_rand.cpp"
#include"GetCrossover_rand1.cpp"
#include"GetCrossover.cpp"
#include"ImmuneCloneSelection.cpp"
struct edge
{
	int eg[3030];
	int point;
	double lenth;
	double share;
} e[1010];
int father[MAX];
bool compare(const edge e1, const edge e2)
{
	if (e1.share == e2.share) return degree[e1.point] > degree[e2.point];
	return e1.share > e2.share;
}
void Init(int num)
{
	for (int i = 1; i <= num; i++)
	{
		father[i] = i;
	}
}
int search(int x) //Find group 
{

	int temp;
	if (father[x] == x) return x;
	else
	{
		temp = father[x];
		father[x] = search(temp); //Compressed path 
		return father[x];
	}
}
void mergearray(int a, int b)
{
	int pa, pb;
	pa = search(a);
	pb = search(b);
	if (pa != pb) //If not merged into the same group, merge 
		father[pb] = pa;
}
int main1()
{
    int eval,i,j,k,kk,index,flag;
	double threshold=0.4;
//	int pp=1;1
	
    double min_fitness;
	w_now=w_start;
	c1_now=c1_start;
    GenerateGraph();//Initialize graph
    srand(time(NULL));
	InitializePop();  //Initialize population
	index=1;//The optimal individual index of the population is initialized to the number 1 particle 
	min_fitness=pop[1].fit_value;
	eval=1;
	clock_t start=clock();
	while(eval<=evaluations)
	{
        flag=0;
		differ = 0;
		if (eval > 1)
		{
			w_now = w_now - inerdec; //Update inertia weight 
			c1_now = c1_now - c1_dec;//Update acceleration factor 
		}
	//	c2_now=1-c1_now;
		if(eval==evaluations)//Set the coefficient of the last iteration 
		{
			 w_now=0.7;
//			 c1_now=0.6;
//		     c2_now=0.5;
		 }
		//flag_m=3;
		for(int now_=1;now_<=popsize;now_++) 
		{
			for (j = 1; j <= 3 * (vertice - 1); j++)
			{
				pop_tmp.edge[j] = pop[now_].edge[j];
			}
			pop_tmp.fit_value = pop[now_].fit_value;
			i = now_;
//			if (pop[i].fit_value<=fave)
//				c1_now = 0.5*(1+(fave-pop[i].fit_value)/(fave-fmin));
                //c1_now = 0.5;
//			else
//     			c1_now = 0.5*(fmax-pop[i].fit_value)/(fmax-fave);
               // c1_now = 0.5;
			c2_now = 1-c1_now;
//			printf("c1= %lf c2= %lf\n",c1_now, c2_now);
 //           printf("%d evaluation %d particle mu:\n",eval,i); //The mutation of the i-th particle in the eval iteration: £º
			  if(eval<threshold*evaluations)//Early iteration 
			  {
				  flag_m= (int)((rand() / (RAND_MAX + 1.0)) * 3) + 1;//Select mutation strategy 
				  if (flag_m==1) {
					  //cout << 'a';
					  GetMutation(); //Mutation
					  //cout << 'b';
//				  printf("%d evaluation %d particle cs:\n",eval,i); //Self-perception of the i-th particle in the eval iteration £º
					  GetCrossover_self(i); //Self-perception mutation
					  //cout << 'c';
//				  printf("%d evaluation %d particle cg:\n",eval,i); //Global-perception of the i-th particle in the eval iteration £º
					  GetCrossover_global(i); //Global-perception mutation
					  //cout << 'd';
					  GetCrossover(i);//crossover
					  //cout << 'e';
					  
				  }
				  if (flag_m==2) {
					  
					  i = (int)((rand() / (RAND_MAX + 1.0)) * (popsize - 1)) + 1;
					 // cout << 6;
					  GetMutation(); //Mutation
					  //cout << 7;
					  GetCrossover_self(i); //Self-perception mutation
					 // cout << 8;
					  GetCrossover_global(i); //Global-perception mutation
					  //cout << 9;
					  GetCrossover(now_);//crossover
					 // cout << 'x';
					  
				  }
				  if (flag_m == 3) {
					 // cout << 1;
					  GetMutation(); //Mutation
					 // cout << 2;
					  GetCrossover_rand(i); //Self-perception mutation
					  //cout << 3;
					  GetCrossover(i);//crossover
					 // cout << 4;
				  }
			  }
			  else//Late iteration 
			  {
		
				  if(eval==threshold*evaluations)
				  {
					  for(k=1;k<=popsize;k++) 
						  for(kk=1;kk<=(vertice-1);kk++)
						  {
                              pop[k].edge[kk*3-2]=gbest.edge[kk*3-2];
							  pop[k].edge[kk*3-1]=gbest.edge[kk*3-1];
						  }
 /*                     for(k=1;k<=popsize;k++) 
					  {
						  for(kk=1;kk<=(vertice-1);kk++)
						  {
                              pop[k].edge[kk*3-2]=gbest.edge[kk*3-2];
							  pop[k].edge[kk*3-1]=gbest.edge[kk*3-1];
							  printf("%d %d %d ",pop[k].edge[kk*3-2],pop[k].edge[kk*3-1],pop[k].edge[kk*3]);
						  }
						  printf("\n");
					  }
*/
				  }
					  GetMutation1(); //Mutation
	//			  printf("%d evaluation %d particle cs:\n",eval,i); //Self-perception of the i-th particle in the eval iteration £º£º
					  GetCrossover_self1(i); //Self-perception mutation
	//			  printf("%d evaluation %d particle cg:\n",eval,i); //Global-perception of the i-th particle in the eval iteration £º
					  GetCrossover_global1(i); //Global-perception mutation
					  GetCrossover(i);//crossover
				
			  }
			  if(pbest[i].fit_value>pop[i].fit_value) //Update the historical individual optimal solution of the particle 
			  {
				  for(j=1;j<=3*(vertice-1);j++)
					  pbest[i].edge[j]=pop[i].edge[j];
                  pbest[i].fit_value=pop[i].fit_value;
			  }
			  if(pop[i].fit_value<min_fitness)//Record the index and fitness value of the current optimal solution 
			  {
				  flag=1;
				  index=i;
//				  pp=eval;
				  min_fitness=pop[i].fit_value;
			  }
			  for (int j = 1; j <= (vertice - 1) * 3; j++)
			  {
				  pop_cpy[now_].edge[j] = pop[now_].edge[j];
			  }
			  pop_cpy[now_].fit_value = pop[now_].fit_value;
		}
//		cout <<"count"<< count11 << endl;

		int popsize_cpy = popsize;

		ImmuneCloneSelection();//Immune clone selection strategy

		for (i = popsize_cpy; i <= popsize; i++) {
			if (pop[i].fit_value < min_fitness)//Record the index and fitness value of the current optimal solution 
			{
				flag = 1;
				index = i;
				//				  pp=eval;
				min_fitness = pop[i].fit_value;
			}
		}
		if (flag)
		{
			for (j = 1; j <= 3 * (vertice - 1); j++)
				gbest.edge[j] = pop[index].edge[j];
			gbest.fit_value = min_fitness;
		}
		
		evalgbest[eval] = gbest.fit_value;

		eval++;
   //Adaptive learning factor
		fave=0; 
		ffmin=10000000;
		ffmax=0;
		for(i=1;i<=popsize;i++)
		{
			fave = fave + pop[i].fit_value;
			if(pop[i].fit_value<ffmin)
				ffmin = pop[i].fit_value;
    		if(pop[i].fit_value>ffmax)
				ffmax = pop[i].fit_value;
		}
		fave = fave/popsize;
	}
	
	//Refining process, as far as possible to find the smallest tree structure of the current topology 
	for (int kk = 1; kk <= popsize; kk++) {
		for (int ver = 1; ver <= vertice; ver++) {
			degree[ver] = 0;
			e[ver].lenth = DBL_MAX;
			e[ver].point = ver;
			e[ver].share = 0;
		}
		//Calculate the degree of each point
		for (int k = 1; k < vertice; k++) {
			degree[pop[kk].edge[3 * k - 2]]++;
			degree[pop[kk].edge[3 * k - 1]]++;
		}
		//Enumerate the connection method of each endpoint to find the optimal substructure 
		for (int k = 1; k <= vertice; k++)
		{
			int enums = pow(4, degree[k]);
			int l = 1;
			//Store the structure to be enumerated
			for (int ver = 1; ver < vertice; ver++) {
				if (pop[kk].edge[3 * ver - 1] == k || pop[kk].edge[3 * ver - 2] == k) {
					min_tree[l * 3 - 2] = pop[kk].edge[3 * ver - 2];
					min_tree[l * 3 - 1] = pop[kk].edge[3 * ver - 1];
					min_tree[l * 3] = 0;
					l += 1;
				}
			}
			for (int enumi = 0; enumi < enums; enumi++) {
				//Enumerate the results at one time 
				for (int pos = degree[k]; pos >= 2; pos--) {
					if (min_tree[3 * pos] == 4) {
						min_tree[3 * pos] %= 4;
						min_tree[3 * (pos - 1)]++;
					}
				}
				double test = Getfitness(degree[k] + 1);
				if (test < e[k].lenth)
				{
					for (int ver = 1; ver <= 3 * (vertice - 1); ver++) {
						e[k].eg[ver] = min_tree[ver];
					}
					e[k].lenth = test;
					e[k].share = Getsharelength(degree[k] + 1);
				}
				min_tree[degree[k] * 3]++;
			}
		}
		sort(e + 1, e + vertice + 1, compare);
		Init(vertice);
		int l = 1;
		for (int ver = 1; ver <= vertice; ver++) {
			int enumi = degree[e[ver].point];
			for (int k = 1; k <= enumi; k++) {
				if (search(e[ver].eg[3 * k - 2]) != search(e[ver].eg[3 * k - 1])) {
					min_tree[l * 3 - 2] = e[ver].eg[3 * k - 2];
					min_tree[l * 3 - 1] = e[ver].eg[3 * k - 1];
					min_tree[l * 3] = e[ver].eg[3 * k];
					mergearray(e[ver].eg[3 * k - 1], e[ver].eg[3 * k - 2]);
					l += 1;
				}
			}
			if (l == vertice) break;
		}


		for (int ver = 1; ver <= 3 * (vertice - 1); ver++) {
			pop[kk].edge[ver] = min_tree[ver];
		}
		pop[kk].fit_value = Getfitness(vertice);
		if (pop[kk].fit_value < gbest.fit_value) {
			for (j = 1; j <= 3 * (vertice - 1); j++)
				gbest.edge[j] = pop[kk].edge[j];
			gbest.fit_value = pop[kk].fit_value;
		}
	}
	//cout << 2;
	clock_t finish=clock();

	printf("%lf\n",gbest.fit_value);
	FILE *fout;
	fout=fopen("result.txt","w");
	for(j=1;j<=3*(vertice-1);j++)
		fprintf(fout,"%d ",gbest.edge[j]);
//	fprintf(fout," %d %d",pp,index);
	fprintf(fout,"\n%lf", gbest.fit_value);
	fprintf(fout,"\n%d", evaluations);
	for(j=1;j<=evaluations;j++)
		fprintf(fout,"\n%d %lf",j,evalgbest[j]);
	fclose(fout);
	return gbest.fit_value;
}
int main() {
	struct pop bestpop;
	double thebest = 999999999999;
	int bestcur;
	for (int k = 1; k <= 10; k++) {
		popsize = 50;
		double tmp = main1();
		if (thebest > tmp) {
			for (int j = 1; j <= 3 * (vertice - 1); j++)
				bestpop.edge[j] = gbest.edge[j];
			bestpop.fit_value = gbest.fit_value;
			thebest = tmp;
		}
	}
	cout << "Optimal result" << bestpop.fit_value<<endl;
	for (int j = 1; j <= 3 * (vertice - 1); j++)
		printf("%d ",bestpop.edge[j]);
}