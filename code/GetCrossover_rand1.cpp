#pragma once
void GetCrossover_rand1(int tmp)
{
	double c;
	int i, r1, r2, mid = 0;
	int m;
	c = rand() / (RAND_MAX + 1.0);
	int r = (int)((rand() / (RAND_MAX + 1.0)) * (popsize - 1)) + 1;//Randomly select a particle from the population 
	//	printf("%lf %lf\n",c,c2_now);
	if (c < c1_now)
	{

		r1 = (int)((rand() / (RAND_MAX + 1.0)) * (vertice - 1)) + 1;//Randomly select two edges
		r2 = (int)((rand() / (RAND_MAX + 1.0)) * (vertice - 1)) + 1;
		while (r1 == r2)
			r2 = (int)((rand() / (RAND_MAX + 1.0)) * vertice) + 1;
		if (r1 > r2)
		{
			mid = r1;
			r1 = r2;
			r2 = mid;
		}
		//	  printf("%d %d\n",r1,r2);
		int p_count = 0;
		for (i = r1; i <= r2; i++) {
			double pp = (rand() / (RAND_MAX + 1.0));
			if (pp < 0.5) pop_tmp.edge[i * 3] = pbest[r].edge[i * 3], p_count++;
		}

		for (i = 1; i <= 3 * (vertice - 1); i++)
			min_tree[i] = pop_tmp.edge[i];
		//pop[cur].fit_value = Getfitness();
	}

	double fit_v = Getfitness(vertice);
	if (fit_v < pop_tmp.fit_value) {
		count11++;
	}
	pop_tmp.fit_value = fit_v;
}
