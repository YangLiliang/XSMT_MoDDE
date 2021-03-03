#pragma once
bool cmp4(struct pop a, struct pop b)
{
	if (a.fit_value < b.fit_value)
		return true;
	else
		return false;
}
int parentt[MAX];
void initial11l(int n) //The group of each node is initialized to itself 
{
	int i;
	for (i = 1; i <= n; i++)
		parentt[i] = i;
}
int find_sett(int x) //Find a group 
{
	int temp;
	if (parentt[x] == x) return x;
	else
	{
		temp = parentt[x];
		parentt[x] = find_sett(temp); //Compressed path
		return parentt[x];
	}
}
void union_sett(int a, int b)
{
	int pa, pb;
	pa = find_sett(a);
	pb = find_sett(b);
	if (pa != pb) //If not merged into the same group, merge 
		parentt[pb] = pa;
}
void ImmuneCloneSelection() {
	int clone[100],cur_mid=1;//clone represents the number of clones of particle i, and cur_mid represents the current position of the intermediate population 

	sort(pop_cpy + 1, pop_cpy + popsize + 1, cmp4);


	for (int i = 1; i <= 20; i++) {//Generate the corresponding number of clones for each particle 
		int k = popsize,b=1;
		double m = rand() % (RAND_MAX + 1) / (double)(RAND_MAX + 1.0);//The value of m is 0 to 1 
		clone[i] = (int)(k * m / i + 1);//Assign the number of clones for each particle 
		double min_fit = 99999999;
		int min_cur=0;
		for (int j = 1; j <= clone[i]; j++) {//Variant screening of clone samples of each particle 
			for (int k = 1; k <= (vertice - 1) * 3; k++)//Copy to pop_mid 
				pop_mid[cur_mid].edge[k] = pop_cpy[i].edge[k];

			//Mutation topology 
			int arr1[1010], arr2[1010];
			int times = vertice * 0.01;
			if (times == 0) times = 1;
			for (int iii = 1; iii <= times; iii++) {
				int p1 = (int)((rand() / (RAND_MAX + 1.0)) * (vertice - 1)) + 1;//Randomly select the edge to be mutated 
				int m1 = pop_mid[cur_mid].edge[3 * p1];//Take out the current connection mode of the two edges 
				int t = m1;

				initial11l(vertice);
				int p, q;
				for (int jj = 1; jj <= (vertice - 1); jj++) //Merge the connected endpoints 
				{
					if (jj == p1) continue; //The broken edges of the selected mutation are not merged 
					p = pop_mid[cur_mid].edge[3 * jj - 2];
					q = pop_mid[cur_mid].edge[3 * jj - 1];
					union_sett(p, q);
				}

				//	  for(i=1;i<=vertice;i++)
				//	   printf("%d ",find_set(i));
				//	  printf("\n");

				for (int jj = 1; jj <= vertice; jj++)
				{
					if (parentt[jj] == jj) //Because there are only two groups, you only need to find one group 
					{
						p = jj;
						break;
					}
				}

				//	  printf("%d\n",p);
				int sum1 = 1; int sum2 = 1;
				for (int jj = 1; jj <= vertice; jj++) //Divide points into two groups 
				{
					if (find_sett(jj) == p)
						arr1[sum1++] = jj;
					else arr2[sum2++] = jj;
				}
				//	  for(i=1;i<sum1;i++)
				//		  printf("%d ",arr1[i]);
				//	  printf("\n");
				//	  for(i=1;i<sum2;i++)
				//		  printf("%d ",arr2[i]);
				//	  printf("\n");

				p = (int)((rand() / (RAND_MAX + 1.0)) * (sum1 - 1)) + 1;
				q = (int)((rand() / (RAND_MAX + 1.0)) * (sum2 - 1)) + 1;

				//  printf("%d %d\n",p,q);

				pop_mid[cur_mid].edge[p1 * 3 - 2] = arr1[p];
				pop_mid[cur_mid].edge[p1 * 3 - 1] = arr2[q];

			}
			
			

			for (k = 1; k <= 3 * (vertice - 1); k++)//Calculate fitness
				min_tree[k] = pop_mid[cur_mid].edge[k];
			pop_mid[cur_mid].fit_value = Getfitness(vertice);
			if (min_fit > pop_mid[cur_mid].fit_value) {
				min_fit = pop_mid[cur_mid].fit_value;
				min_cur = cur_mid;
			}
			cur_mid++;
		}
		//If the optimal particle in the mutant population is better than the copy, then the particle is added to the population 
		if (min_fit < pop_cpy[i].fit_value) {
			popsize++;
			//tag = 1;
			for (k = 1; k <= 3 * (vertice - 1); k++)
			{
				pop[popsize].edge[k] = pop_mid[min_cur].edge[k];
				pbest[popsize].edge[k]= pop_mid[min_cur].edge[k];
			}
			pop[popsize].fit_value = min_fit;
			pbest[popsize].fit_value = min_fit;
			F[popsize] = 0.8;
			F_self[popsize] = 0.8;
		}
	}

}