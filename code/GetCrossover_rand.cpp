#pragma once
int parent3[MAX];
void initial3(int n) //The group of each node is initialized to itself
{
	int i;
	for (i = 1; i <= n; i++)
		parent3[i] = i;
}
int find_set3(int x) //Find a group 
{
	int temp;
	if (parent3[x] == x) return x;
	else
	{
		temp = parent3[x];
		parent3[x] = find_set3(temp); //Compressed path 
		return parent3[x];
	}
}
void union_set3(int a, int b)
{
	int pa, pb;
	pa = find_set3(a);
	pb = find_set3(b);
	if (pa != pb) //If not merged into the same group, merge
		parent3[pb] = pa;
}
struct tree2
{
	int s, e;
	int line_style;
}par2[1010], par_rand[1010], sur2[2010], new_res2[1010],sur2_re[1010];
bool cmppp(struct tree2 a, struct tree2 b) 
{
	if (a.s < b.s) return true;
	else if (a.s == b.s && a.e < b.e) return true;
	else return false;
}
void GetCrossover_rand(int cur)
{
	double c;
	int i, j, mid = 0, sign1[1010], sign2[1010], count_new, count_sur,count_cur2;
	c = rand() / (RAND_MAX + 1.0);
	int r= (int)((rand() / (RAND_MAX + 1.0)) * (popsize - 1)) + 1;//Randomly select a particle from the population 


	if (c < c1_now)
	{
		//flag_c = 1;
		for (i = 1; i <= (vertice - 1); i++)
		{
			par2[i].s = pop_tmp.edge[i * 3 - 2]; //Store the current particles in the structure
			par2[i].e = pop_tmp.edge[i * 3 - 1];
			par2[i].line_style = pop_tmp.edge[i * 3];
			if (par2[i].s > par2[i].e) //If the starting point number is greater than the ending point number, swap positions 
			{
				mid = par2[i].s;
				par2[i].s = par2[i].e;
				par2[i].e = mid;
				if (par2[i].line_style == 0 || par2[i].line_style == 1) //Interchange of connection methods 
					par2[i].line_style = !par2[i].line_style;
				else if (par2[i].line_style == 2)
					par2[i].line_style = 3;
				else if (par2[i].line_style == 3)
					par2[i].line_style = 2;
			}
		}


		for (i = 1; i <= (vertice - 1); i++)//Store the historical optimal solution of the current particle in the structure 
		{
			par_rand[i].s = pop[r].edge[i * 3 - 2];
			par_rand[i].e = pop[r].edge[i * 3 - 1];
			par_rand[i].line_style = pop[r].edge[i * 3];
			if (par_rand[i].s > par_rand[i].e)//If the starting point number is greater than the ending point number, swap positions
			{
				mid = par_rand[i].s;
				par_rand[i].s = par_rand[i].e;
				par_rand[i].e = mid;
				if (par_rand[i].line_style == 0 || par_rand[i].line_style == 1)// Interchange of connection methods
					par_rand[i].line_style = !par_rand[i].line_style;
				else if (par_rand[i].line_style == 2)
					par_rand[i].line_style = 3;
				else if (par_rand[i].line_style == 3)
					par_rand[i].line_style = 2;
			}
		}

		//The edges of the particles are arranged in the order of starting point from small to large, and ending point from small to large 
		sort(par2 + 1, par2 + vertice, cmppp); 
		sort(par_rand + 1, par_rand + vertice, cmppp);


		initial3(vertice);
		for (i = 1; i <= (vertice - 1); i++)//Initialize the marker array, mark which edge is the common edge 
		{
			sign1[i] = 0;
			sign2[i] = 0;
		}
		count_new = 1; //Record the current number of sides in the new particle 
		for (i = 1; i <= (vertice - 1); i++)//Find the same edge in two particles 
		{
			//Find the same position as the starting point of the i-th edge of the current particle in the optimal particle in the individual history 
			for (j = 1; j <= (vertice - 1); j++) 
			{
				if (par_rand[j].s == par2[i].s) 
					break;
			}
			//Find the edge that is the same as the end point of the i-th edge of the current particle in the optimal particle 
			for (; j <= (vertice - 1); j++) 
			{
				if (par_rand[j].s != par2[i].s)  //If the starting point is different, the same edge does not exist, jump out 
					break;
				if (par_rand[j].e == par2[i].e) //Find the same edge 
				{
					sign1[i] = 1; //The edge in the current particle is marked as 1
					sign2[j] = 1; //The edge marker position in the optimal particle in the individual history is 1 
					union_set3(par2[i].s, par2[i].e); //Combine the two endpoints of the edge into the same group 
					new_res2[count_new].s = par_rand[j].s; //Store the common edge in new_res 
					new_res2[count_new].e = par_rand[j].e;
					new_res2[count_new++].line_style = par_rand[j].line_style;
					break;//Jump out
				}
			}
		}


		count_sur = 1; //Record the number of edges remaining after picking the common edge 
		count_cur2 = 1;
		for (i = 1; i <= (vertice - 1); i++)
		{
			if (!sign1[i])
			{
				sur2[count_sur].s = par2[i].s;
				sur2[count_sur].e = par2[i].e;
				sur2[count_sur++].line_style = par2[i].line_style;
				sur2_re[count_cur2].s= par2[i].s;
				sur2_re[count_cur2].e = par2[i].e;
				sur2_re[count_cur2++].line_style = par2[i].line_style;
			}
			if (!sign2[i])
			{
				sur2[count_sur].s = par_rand[i].s;
				sur2[count_sur].e = par_rand[i].e;
				sur2[count_sur++].line_style = par_rand[i].line_style;
			}
		}


		int remain = count_new + count_cur2 * 0.3;
		while (1)
		{
			//cout << 2;
			if (count_new == remain) break;
			i = (int)((rand() / (RAND_MAX + 1.0)) * (count_cur2 - 1)) + 1;
			if (find_set3(sur2_re[i].s) != find_set3(sur2_re[i].e))
			{
				new_res2[count_new].s = sur2_re[i].s;
				new_res2[count_new].e = sur2_re[i].e;
				new_res2[count_new++].line_style = sur2_re[i].line_style;
				union_set3(sur2_re[i].s, sur2_re[i].e);
			}
		}

		while (1)
		{
			if (count_new == vertice) break;
			i = (int)((rand() / (RAND_MAX + 1.0)) * (count_sur - 1)) + 1;
			if (find_set3(sur2[i].s) != find_set3(sur2[i].e))
			{
				new_res2[count_new].s = sur2[i].s;
				new_res2[count_new].e = sur2[i].e;
				new_res2[count_new++].line_style = sur2[i].line_style;
				union_set3(sur2[i].s, sur2[i].e);
			}
		}
		for (i = 1; i <= (vertice - 1); i++)
		{
			pop_tmp.edge[i * 3 - 2] = new_res2[i].s;
			pop_tmp.edge[i * 3 - 1] = new_res2[i].e;
			pop_tmp.edge[i * 3] = new_res2[i].line_style;
		}


		for (i = 1; i <= 3 * (vertice - 1); i++)
			min_tree[i] = pop_tmp.edge[i];
	}
	double fit_v = Getfitness(vertice);
	if (fit_v < pop_tmp.fit_value) {
		count11++;
	}
	pop_tmp.fit_value = fit_v;
}