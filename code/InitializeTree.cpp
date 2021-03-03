void InitializeTree()
{
   int start_point;
   start_point=(int)((rand()/(RAND_MAX+1.0))*vertice)+1;//Randomly select the starting point of the minimum spanning tree 
   double lowcost[1010]={0},min;
   int tree[1010][3]={0},adjvex[1010]={0},sign[1010],i,j,index=0;
   for(i=1;i<=vertice;i++) 
   {
	   lowcost[i]=graphw[start_point][i];//The closest distance of each vertice point is initialized to the distance from the starting point 
       adjvex[i]=start_point;//The nearest point of each vertice point is initialized as the starting point 
	   sign[i]=0;
   }
   sign[start_point]=1; //Mark the starting point has been added to the minimum spanning tree 
   for(i=1;i<vertice;i++)
   {
         min=99999999;
		 for(j=1;j<=vertice;j++)  //Take the edge with the smallest distance 
			 if(lowcost[j]<min&&!sign[j])
			 {
                 index=j;
				 min=lowcost[j];
			 }
		 sign[index]=1; //Mark the newly added node 
		 tree[i][1]=adjvex[index]; //Store newly added edges 
		 tree[i][2]=index;
		 for(j=1;j<=vertice;j++) //Update distance record 
			 if(lowcost[j]>graphw[j][index]&&!sign[j])
			 {
				 lowcost[j]=graphw[j][index];
				 adjvex[j]=index;
			 }
//	   for(j=1;j<=vertice;j++)
//		   printf("%lf ",lowcost[j]);
//	   printf("\n");
   }
//  printf("start_point:%d\n",start_point);
   for(i=1;i<=(vertice-1);i++) 
   {
	   min_tree[i*3-2]=tree[i][1]; //Edge start number 
	   min_tree[i*3-1]=tree[i][2]; //Edge end number 
	   min_tree[i*3]=(int)((rand()/(RAND_MAX+1.0))*2); //Connection method 
   }
//   for(i=1;i<=3*(vertice-1);i++)
//    printf("%3d",min_tree[i]);
//   printf("\n");
}