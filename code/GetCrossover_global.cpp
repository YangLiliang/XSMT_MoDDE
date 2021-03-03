int parent1[MAX];
void initial1(int n) //The group of each node is initialized to itself 
{
	int i;
	for(i=1;i<=n;i++)
	   parent1[i]=i;
}
int find_set1(int x) //Find a group 
{
 int temp;
 if(parent1[x]==x) return x;
 else
 {
  temp=parent1[x];
  parent1[x]=find_set1(temp); //Compressed path
  return parent1[x];
 }
}
void union_set1(int a,int b)
{
  int pa,pb;
  pa=find_set1(a);
  pb=find_set1(b);
  if(pa!=pb) //If not merged into the same group, merge 
  parent1[pb]=pa;
}
struct tree 
{
	int s,e;
	int line_style;
}par[1010],par_best[1010],sur[2010],new_res[1010],sur_re[1010];//Store the current particles and the best particles in their own history, 
                                                               //and then sort them, sur stores non-common edges, and new_res stores new particles generated after crossing 
bool cmpp(struct tree a,struct tree b) //Arrange the particles in the order of starting point from small to large and ending point from small to large 
{
	if(a.s<b.s) return true;
	else if(a.s==b.s&&a.e<b.e) return true;
	else return false;
}
void GetCrossover_global(int cur)
{
    double c;
	int i,j,mid=0,sign1[1010],sign2[1010],count_new,count_sur,count_re,count_cur;
	c=rand()/(RAND_MAX+1.0); 


    if(c<c2_now)
	{ 
	  for(i=1;i<=(vertice-1);i++)
	  {
         par[i].s=pop_tmp.edge[i*3-2]; //Store the current particles in the structure 
		 par[i].e=pop_tmp.edge[i*3-1];
		 par[i].line_style=pop_tmp.edge[i*3];
		 if(par[i].s>par[i].e) //If the starting point number is greater than the ending point number, swap positions 
		 {
			 mid=par[i].s;
			 par[i].s=par[i].e;
			 par[i].e=mid;
			 if(par[i].line_style==0||par[i].line_style==1) //Interchange of connection methods 
                 par[i].line_style=!par[i].line_style;
			 else if(par[i].line_style==2)
			     par[i].line_style=3;
			 else if(par[i].line_style==3)
				 par[i].line_style=2;
		 }
	  }

	  

	  for(i=1;i<=(vertice-1);i++)//Store the historical optimal solution of the current particle in the structure 
	  {
         par_best[i].s=gbest.edge[i*3-2];
		 par_best[i].e=gbest.edge[i*3-1];
		 par_best[i].line_style=gbest.edge[i*3];
		 if(par_best[i].s>par_best[i].e)//If the starting point number is greater than the ending point number, swap positions 
		 {
			 mid=par_best[i].s;
			 par_best[i].s=par_best[i].e;
			 par_best[i].e=mid;
			 if(par_best[i].line_style==0||par_best[i].line_style==1)//Interchange of connection methods 
                 par_best[i].line_style=!par_best[i].line_style;
			 else if(par_best[i].line_style==2)
			     par_best[i].line_style=3;
			 else if(par_best[i].line_style==3)
				 par_best[i].line_style=2;
		 }
	  }

	  //The edges of the particles are arranged in the order of starting point from small to large, and ending point from small to large 
	  sort(par+1,par+vertice,cmpp); 
      sort(par_best+1,par_best+vertice,cmpp);


	  initial1(vertice);
	  //Initialize the marker array, mark which edge is the common edge 
	  for(i=1;i<=(vertice-1);i++)
	  {
		  sign1[i]=0;
		  sign2[i]=0;
	  }
	  count_new=1; //Record the current number of sides in the new particle 
      for(i=1;i<=(vertice-1);i++)//Find the same edge in two particles 
	  {
         for(j=1;j<=(vertice-1);j++)  //Find the same position as the starting point of the i-th edge of the current particle in the optimal particle in the individual history 
		 {
            if(par_best[j].s==par[i].s) 
				break;
		 }
		 for(;j<=(vertice-1);j++) //Find the edge that is the same as the end point of the i-th edge of the current particle in the optimal particle 
		 {
			 if(par_best[j].s!=par[i].s)  //If the starting point is different, the same edge does not exist, jump out; 
				 break;
			 if(par_best[j].e==par[i].e) //Find the same edge 
			 {
                sign1[i]=1; //The edge in the current particle is marked as 1 
				sign2[j]=1; //The edge marker position in the optimal particle in the individual history is 1 
				union_set1(par[i].s,par[i].e); //Combine the two endpoints of the edge into the same group 
                new_res[count_new].s=par_best[j].s; //Store the common edge in new_res 
				new_res[count_new].e=par_best[j].e;
				new_res[count_new++].line_style=par_best[j].line_style;
				break;//Jump out 
			 }
		 }
	  }

//	  printf("count_new:%d\n",count_new);
//	  for(i=1;i<count_new;i++)
//	    printf("%d %d %d\n",new_res[i].s,new_res[i].e,new_res[i].line_style);
//	  printf("\nsign1:\n");
  //    for(i=1;i<=(vertice-1);i++)
//	    printf("%d ",sign1[i]);
//	  printf("\nsign2:\n");
  //    for(i=1;i<=(vertice-1);i++)
//	    printf("%d ",sign2[i]);
//	  printf("\n");


	  count_sur=1; //Record the number of edges remaining after picking the common edge 
	  count_cur = 1;//Record the number of different edges in the current tree 
	  for(i=1;i<=(vertice-1);i++)
	  {
		  if(!sign1[i]) 
		  {
			  sur[count_sur].s=par[i].s;
			  sur[count_sur].e=par[i].e;
			  sur[count_sur++].line_style=par[i].line_style;
			  sur_re[count_cur].s = par[i].s;
			  sur_re[count_cur].e = par[i].e;
			  sur_re[count_cur++].line_style = par[i].line_style;
		  }
		  if(!sign2[i])
		  {
              sur[count_sur].s=par_best[i].s;
			  sur[count_sur].e=par_best[i].e;
			  sur[count_sur++].line_style=par_best[i].line_style;
		  }
	  }
	  
//	  printf("count_sur:%d\n",count_sur);
//	  for(i=1;i<count_sur;i++)
//	    printf("%d %d %d\n",sur[i].s,sur[i].e,sur[i].line_style);
//	  printf("\n");

	  int remain = count_new + count_cur * 0.3;
	 
	  while (1)
	  {
		  //cout << 3;
		  if (count_new == remain) break;
		  i = (int)((rand() / (RAND_MAX + 1.0)) * (count_cur-1))+1;
		  if (find_set1(sur_re[i].s) != find_set1(sur_re[i].e))
		  {
			  new_res[count_new].s = sur_re[i].s;
			  new_res[count_new].e = sur_re[i].e;
			  new_res[count_new++].line_style = sur_re[i].line_style;
			  union_set1(sur_re[i].s, sur_re[i].e);
		  }
	  }

	  while(1)
	  {
		  //cout << 6;
		  if(count_new==vertice) break;
		  i = (int)((rand() / (RAND_MAX + 1.0)) * (count_sur - 1)) + 1;
          if(find_set1(sur[i].s)!=find_set1(sur[i].e))
		  {
             new_res[count_new].s=sur[i].s; 
			 new_res[count_new].e=sur[i].e;
			 new_res[count_new++].line_style=sur[i].line_style;
			 union_set1(sur[i].s,sur[i].e);
		  }
	  }
	  for(i=1;i<=(vertice-1);i++)
	  {
		  pop_tmp.edge[i*3-2]=new_res[i].s;
          pop_tmp.edge[i*3-1]=new_res[i].e;
          pop_tmp.edge[i*3]=new_res[i].line_style;
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