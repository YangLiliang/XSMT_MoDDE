int parent2[MAX];
void initial2(int n) // The group of each node is initialized to itself
{
	int i;
	for(i=1;i<=n;i++)
	   parent2[i]=i;
}
int find_set2(int x) //Find a group 
{
 int temp;
 if(parent2[x]==x) return x;
 else
 {
  temp=parent2[x];
  parent2[x]=find_set2(temp); //Compressed path 
  return parent2[x];
 }
}
void union_set2(int a,int b)
{
  int pa,pb;
  pa=find_set2(a);
  pb=find_set2(b);
  if(pa!=pb) //If not merged into the same group, merge 
  parent2[pb]=pa;
}

//Store the current particles and the best particles in their own history, and then sort them, sur1 stores non-common edges, and new_res1 stores new particles generated after crossover 
struct tree1 
{
	int s,e;
	int line_style;
}par1[1010],par1_best[1010],sur1[2010],new_res1[1010],sur1_re[1010];

//Arrange the particles in the order of starting point from small to large and ending point from small to large 
bool cmpp1(struct tree1 a,struct tree1 b) 
{
	if(a.s<b.s) return true;
	else if(a.s==b.s&&a.e<b.e) return true;
	else return false;
}
void GetCrossover_self(int a)
{
    double c;
	int i,j,mid=0,sign1[1010],sign2[1010],count_new,count_sur1,count_cur1;
	c=rand()/(RAND_MAX+1.0); 

    if(c<c1_now)
	{ 
	  for(i=1;i<=(vertice-1);i++)
	  {
         par1[i].s=pop_tmp.edge[i*3-2]; //Store the current particles in the structure 
		 par1[i].e=pop_tmp.edge[i*3-1];
		 par1[i].line_style=pop_tmp.edge[i*3];
		 if(par1[i].s>par1[i].e) //If the starting point number is greater than the ending point number, swap positions 
		 {
			 mid=par1[i].s;
			 par1[i].s=par1[i].e;
			 par1[i].e=mid;
			 if(par1[i].line_style==0||par1[i].line_style==1) //Interchange of connection methods 
                 par1[i].line_style=!par1[i].line_style;
			 else if(par1[i].line_style==2)
			     par1[i].line_style=3;
			 else if(par1[i].line_style==3)
				 par1[i].line_style=2;
		 }
	  }

	  

	  //Store the historical optimal solution of the current particle in the structure 
	  for(i=1;i<=(vertice-1);i++)
	  {
         par1_best[i].s=pbest[a].edge[i*3-2];
		 par1_best[i].e=pbest[a].edge[i*3-1];
		 par1_best[i].line_style=pbest[a].edge[i*3];
		 if(par1_best[i].s>par1_best[i].e)//If the starting point number is greater than the ending point number, swap positions 
		 {
			 mid=par1_best[i].s;
			 par1_best[i].s=par1_best[i].e;
			 par1_best[i].e=mid;
			 if(par1_best[i].line_style==0||par1_best[i].line_style==1)//Interchange of connection methods 
                 par1_best[i].line_style=!par1_best[i].line_style;
			 else if(par1_best[i].line_style==2)
			     par1_best[i].line_style=3;
			 else if(par1_best[i].line_style==3)
				 par1_best[i].line_style=2;
		 }
	  }

	  //The edges of the particles are arranged in the order of starting point from small to large, and ending point from small to large 
	  sort(par1+1,par1+vertice,cmpp1);
      sort(par1_best+1,par1_best+vertice,cmpp1);

	  initial2(vertice);
	  for(i=1;i<=(vertice-1);i++)//Initialize the marker array, mark which edge is the common edge 
	  {
		  sign1[i]=0;
		  sign2[i]=0;
	  }
	  count_new=1; 
      for(i=1;i<=(vertice-1);i++)//Find the same edge in two particles 
	  {
		  //Find the same position as the starting point of the i-th edge of the current particle in the optimal particle in the individual history
         for(j=1;j<=(vertice-1);j++)   
		 {
            if(par1_best[j].s==par1[i].s) //Jump out 
				break;
		 }
		 //Find the edge that is the same as the end point of the i-th edge of the current particle in the optimal particle 
		 for(;j<=(vertice-1);j++) 
		 {
			 if(par1_best[j].s!=par1[i].s)  //If the starting point is different, the same edge does not exist, jump out; 
				 break;
			 if(par1_best[j].e==par1[i].e) //Find the same edge 
			 {
                sign1[i]=1; //The edge in the current particle is marked as 1 
				sign2[j]=1; //The edge marker position in the optimal particle in the individual history is 1 
				union_set2(par1[i].s,par1[i].e); //Combine the two endpoints of the edge into the same group 
                new_res1[count_new].s=par1_best[j].s; //Store the common edge in new_res1 
				new_res1[count_new].e=par1_best[j].e;
				new_res1[count_new++].line_style=par1_best[j].line_style;
				break;//Jump out 
			 }
		 }
	  }

	  count_sur1=1; //Record the number of edges remaining after picking the common edge 
	  count_cur1 = 1;//Record the number of different edges in the current tree 
	  for(i=1;i<=(vertice-1);i++)
	  {
		  if(!sign1[i]) 
		  {
			  sur1[count_sur1].s=par1[i].s;
			  sur1[count_sur1].e=par1[i].e;
			  sur1[count_sur1++].line_style=par1[i].line_style;
			  sur1_re[count_cur1].s = par1[i].s;
			  sur1_re[count_cur1].e = par1[i].e;
			  sur1_re[count_cur1++].line_style = par1[i].line_style;
		  }
		  if(!sign2[i])
		  {
              sur1[count_sur1].s=par1_best[i].s;
			  sur1[count_sur1].e=par1_best[i].e;
			  sur1[count_sur1++].line_style=par1_best[i].line_style;
		  }
	  }
	  

	  int remain = count_new + count_cur1 * 0.3;

	  while (1)
	  {
		 // cout << 1;
		  //cout << count_new<<" "<<remain;
		  if (count_new == remain) break;
		  i = (int)((rand() / (RAND_MAX + 1.0)) * (count_cur1 - 1)) + 1;
		  if (find_set2(sur1_re[i].s) != find_set2(sur1_re[i].e))
		  {
			  new_res1[count_new].s = sur1_re[i].s;
			  new_res1[count_new].e = sur1_re[i].e;
			  new_res1[count_new++].line_style = sur1_re[i].line_style;
			  union_set2(sur1_re[i].s, sur1_re[i].e);
		  }
	  }

	  while(1)
	  {
		//  cout << 5;
		  if(count_new==vertice) break;
		  i=(int)((rand()/(RAND_MAX+1.0))*(count_sur1-1))+1;
          if(find_set2(sur1[i].s)!=find_set2(sur1[i].e))
		  {
             new_res1[count_new].s=sur1[i].s; 
			 new_res1[count_new].e=sur1[i].e;
			 new_res1[count_new++].line_style=sur1[i].line_style;
			 union_set2(sur1[i].s,sur1[i].e);
		  }
	  }
	  for(i=1;i<=(vertice-1);i++)
	  {
		  pop_tmp.edge[i*3-2]=new_res1[i].s;
          pop_tmp.edge[i*3-1]=new_res1[i].e;
          pop_tmp.edge[i*3]=new_res1[i].line_style;
	  }


	  for(i=1;i<=3*(vertice-1);i++)
		  min_tree[i]=pop_tmp.edge[i];

	}
	double fit_v = Getfitness(vertice);
	if (fit_v < pop_tmp.fit_value) {
		count11++;
	}
	pop_tmp.fit_value = fit_v;
}