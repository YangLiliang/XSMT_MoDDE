int parent[MAX];
void initial(int n) //The group of each node is initialized to itself 
{
	int i;
	for(i=1;i<=n;i++)
		parent[i]=i;
}
int find_set(int x) //Find group 
{
 int temp;
 if(parent[x]==x) return x;
 else
 {
  temp=parent[x];
  parent[x]=find_set(temp); //Compressed path 
  return parent[x];
 }
}
void union_set(int a,int b)
{
 int pa,pb;
 pa=find_set(a);
 pb=find_set(b);
 if(pa!=pb) //If not merged into the same group, merge 
  parent[pb]=pa;
}
void GetMutation()
{
    double w=rand()/(RAND_MAX+1.0); //Generate random numbers, mutate if less than w_now 
	int p1,p2,m1,j,t,p,q,arr1[1010],arr2[1010],sum1,sum2;
	double f1=0;

//	printf("%lf %lf\n",w,w_now);
	
	if(w<w_now)
	{
	  

	  p1=(int)((rand()/(RAND_MAX+1.0))*(vertice-1))+1;//Randomly select the edge to be mutated 
	  p2=(int)((rand()/(RAND_MAX+1.0))*(vertice-1))+1;
	  while(p1==p2)
         p2=(int)((rand()/(RAND_MAX+1.0))*(vertice-1))+1;
	  m1=pop_tmp.edge[3*p1];//Take out the current connection mode of the two edges 
      t=m1;
//	  printf("p1,m1:%d %d\n\n",p1,m1);
	  while(t==m1) //mutate the connection method of the first edge. 
	  {
          f1=rand()/(RAND_MAX+1.0);
//		  printf("%lf\n",f1);
		  if(f1<0.2)
			  m1=2;
		  else if(f1>=0.2&&f1<0.5)
			  m1=0;
		  else if(f1>=0.5&&f1<=0.8)
			  m1=1;
		  else m1=3;
	  }
	  pop_tmp.edge[3*p1]=m1;


	  initial(vertice);
      for(j=1;j<=(vertice-1);j++) //Merge the connected endpoints 
	  {
            if(j==p1) continue; //The broken edges of the selected mutation are not merged 
		    p=pop_tmp.edge[3*j-2];
			q=pop_tmp.edge[3*j-1];
			union_set(p,q);
	  }

//	  for(i=1;i<=vertice;i++)
//	   printf("%d ",find_set(i));
//	  printf("\n");

	  for(j=1;j<=vertice;j++)
	  {
		  if(parent[j]==j) //Because there are only two groups, you only need to find one group 
		  {
			  p=j;
			  break;
		  }
	  }

//	  printf("%d\n",p);

	  sum1=1;sum2=1;
	  for(j=1;j<=vertice;j++) //Divide points into two groups
	  {
		  if(find_set(j)==p)
			  arr1[sum1++]=j;
		  else arr2[sum2++]=j;
	  }
//	  for(i=1;i<sum1;i++)
//		  printf("%d ",arr1[i]);
//	  printf("\n");
//	  for(i=1;i<sum2;i++)
//		  printf("%d ",arr2[i]);
//	  printf("\n");

      p=(int)((rand()/(RAND_MAX+1.0))*(sum1-1))+1;
	  q=(int)((rand()/(RAND_MAX+1.0))*(sum2-1))+1;

	//  printf("%d %d\n",p,q);

	  pop_tmp.edge[p1*3-2]=arr1[p];
	  pop_tmp.edge[p1*3-1]=arr2[q];

//	  for(j=1;j<=3*(vertice-1);j++)
//		  printf("%d ",pop[cur].edge[j]);
//	  printf("\n");
	  m1=pop_tmp.edge[3*p2];//Take out the current connection method of the two edges 
      t=m1;
//	  printf("p1,m1:%d %d\n\n",p1,m1);
	  while(t==m1) //mutate the connection method of the first edge. 
	  {
          f1=rand()/(RAND_MAX+1.0);
//		  printf("%lf\n",f1);
		  if(f1<0.2)
			  m1=2;
		  else if(f1>=0.2&&f1<0.5)
			  m1=0;
		  else if(f1>=0.5&&f1<=0.8)
			  m1=1;
		  else m1=3;
	  }
	  pop_tmp.edge[3*p2]=m1;
  

	  initial(vertice);
      for(j=1;j<=(vertice-1);j++) //Merge the connected endpoints 
	  {
            if(j==p2) continue; //The selected mutated edges are disconnectedand the edges are not merged
		    p=pop_tmp.edge[3*j-2];
			q=pop_tmp.edge[3*j-1];
			union_set(p,q);
	  }
      for(j=1;j<=vertice;j++)
	  {
		  if(parent[j]==j) //Because there are only two groups, you only need to find one group 
		  {
			  p=j;
			  break;
		  }
	  }
	  sum1=1;sum2=1;
	  for(j=1;j<=vertice;j++) //Divide points into two groups 
	  {
		  if(find_set(j)==p)
			  arr1[sum1++]=j;
		  else arr2[sum2++]=j;
	  }
	  p=(int)((rand()/(RAND_MAX+1.0))*(sum1-1))+1;
	  q=(int)((rand()/(RAND_MAX+1.0))*(sum2-1))+1;
	  pop_tmp.edge[p2*3-2]=arr1[p];
	  pop_tmp.edge[p2*3-1]=arr2[q];
      for(j=1;j<=3*(vertice-1);j++)
		  min_tree[j]=pop_tmp.edge[j];
	  pop_tmp.fit_value=Getfitness(vertice); 
	}
//	 for(j=1;j<=3*(vertice-1);j++)
//		 printf("%3d",pop[cur].edge[j]);
//	 printf("\n");
//	 printf("%lf\n",pop[cur].fit_value);
}