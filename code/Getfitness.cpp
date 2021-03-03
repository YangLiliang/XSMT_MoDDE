struct node1
{
	double pos;
	double s;
	double e;
}xsegment[1010],ysegment[1010],r_x[1010],r_y[1010]; //Horizontal line segment
struct node2
{
	double sx;
	double sy;
	double ex;
	double ey;
}x45[1010],x135[1010];//Slash 
bool cmp1(struct node1 a,struct node1 b)
{
	if(a.pos<b.pos) return true;
	else return false;
}
bool cmp2(struct node1 a,struct node1 b)
{
	if(a.s<b.s) return true;
	else return false;
}
double Getfitness(int num)
{
    int i,k,sp,xt=0,yt=0,x45t=0,x135t=0,rxt=0,ryt=0;
	double x1,x2,y1,y2,fx,fy,fitness=0,midx,midy;
//	printf("%d\n",vertice);
//	for(i=1;i<=3*(vertice-1);i++)
//		printf("%d ",min_tree[i]);
//	printf("\n");
	for(i=1;i<num;i++)
	{
        x1=graph[min_tree[i*3-2]][0]; //Starting point x 
		y1=graph[min_tree[i*3-2]][1]; //Starting point y
		x2=graph[min_tree[i*3-1]][0]; //Ending point x 
		y2=graph[min_tree[i*3-1]][1]; //Ending point y
		sp=min_tree[i*3]; //Connection method 
		fx=fabs(x1-x2);  //Horizontal distance 
		fy=fabs(y1-y2);  //vertical distance 
//		printf("%lf %lf %lf %lf %d %lf %lf\n",x1,y1,x2,y2,sp,fx,fy);
        if(sp==2||sp==3)  //When the line segment is connected by Manhattan
		{
			if(sp==2)
			{
				xsegment[xt].pos=y2; //Ordinate of horizontal line 
				ysegment[yt].pos=x1; //Ordinate of vertical line 
			}
			else 
			{
			    xsegment[xt].pos=y1;
				ysegment[yt].pos=x2;
			}
			if(x1>x2)
			{
				xsegment[xt].s=x2; //The abscissa of the left starting point of the horizontal line 
				xsegment[xt++].e=x1; //The abscissa of the right end point of the horizontal line 
			}
			else
			{
                xsegment[xt].s=x1;
				xsegment[xt++].e=x2;
			}
			if(y1>y2)
			{
				ysegment[yt].s=y2; //The ordinate of the bottom starting point of the vertical line 
				ysegment[yt++].e=y1; //The ordinate of the upper end point of the vertical line 
			}
			else 
			{
                ysegment[yt].s=y1;
				ysegment[yt++].e=y2;
			}
		}
		if(sp==0||sp==1) //When the connection method of the line segment is a non-Manhattan structure 
		{
           if(fx==0||fy==0) //When two points are collinear
		   {
			   if(sp==0)
			   {
                  xsegment[xt].pos=y1; 
				  ysegment[yt].pos=x1;
			   }
			   else
			   {
				   xsegment[xt].pos=y2;
				   ysegment[yt].pos=x2;
			   }
			   	if(x1>x2)
				{
				   xsegment[xt].s=x2; //The abscissa of the left starting point of the horizontal line 
				   xsegment[xt++].e=x1; //The abscissa of the right end point of the horizontal line 
				}
			    else
				{
                   xsegment[xt].s=x1;
				   xsegment[xt++].e=x2;
				}
			    if(y1>y2)
				{
				   ysegment[yt].s=y2; //The ordinate of the bottom starting point of the vertical line 
				   ysegment[yt++].e=y1; //The ordinate of the upper end point of the vertical line 
				}
			    else 
				{
                   ysegment[yt].s=y1;
			  	   ysegment[yt++].e=y2;
				}
		   }
		   else //Two points are not collinear 
		   {
                if(x1>x2) //If the starting point is at the right end of the end point 
				{
					midx=x1;
					midy=y1;
					x1=x2;
					y1=y2;
					x2=midx;
                    y2=midy;
					sp=!sp;
				}
                if(fx>fy) //When the horizontal spacing is greater than the vertical spacing 
				{
				  if(sp==0) //0 connection method 
				  {
					xsegment[xt].pos=y1;
					xsegment[xt].s=x1;
					xsegment[xt++].e=x2-fy;
					if(y1<y2) //Record the start and end coordinates of the 45 degree line segment 
					{
						x45[x45t].sx=x2-fy;
						x45[x45t].sy=y1;
						x45[x45t].ex=x2;
						x45[x45t++].ey=y2;
					}
					else  //Record the start and end coordinates of the 135 degree line segment
					{
                        x135[x135t].sx=x2-fy;
						x135[x135t].sy=y1;
						x135[x135t].ex=x2;
						x135[x135t++].ey=y2;
					}
				  }
				  else //1 connection method
				  {
					xsegment[xt].pos=y2;
					xsegment[xt].s=x1+fy;
					xsegment[xt++].e=x2;
					if(y1<y2)
					{
                      	x45[x45t].sx=x1;
						x45[x45t].sy=y1;
						x45[x45t].ex=x1+fy;
						x45[x45t++].ey=y2;
					}
					else
					{
                        x135[x135t].sx=x1;
						x135[x135t].sy=y1;
						x135[x135t].ex=x1+fy;
						x135[x135t++].ey=y2;
					}
				  }
				}
				else //When the vertical spacing is greater than or equal to the horizontal spacing 
				{
                  if(sp==0) 
				  {
					ysegment[yt].pos=x1;
					if(y1<y2)
					{
						x45[x45t].sx=x1;
						x45[x45t].sy=y2-fx;
						x45[x45t].ex=x2;
						x45[x45t++].ey=y2;
						ysegment[yt].s=y1;
					    ysegment[yt++].e=y2-fx;
					}
					else
					{
                        x135[x135t].sx=x1;
						x135[x135t].sy=y2+fx;
						x135[x135t].ex=x2;
						x135[x135t++].ey=y2;
					 	ysegment[yt].s=y1;
					    ysegment[yt++].e=y2+fx;
					}
				  }
				  else
				  {
					ysegment[yt].pos=x2;
					if(y1<y2)
					{
                      	x45[x45t].sx=x1;
						x45[x45t].sy=y1;
						x45[x45t].ex=x2;
						x45[x45t++].ey=y1+fx;
						ysegment[yt].s=y1+fx;
				   	    ysegment[yt++].e=y2;
					}
					else
					{
                        x135[x135t].sx=x1;
						x135[x135t].sy=y1;
						x135[x135t].ex=x2;
						x135[x135t++].ey=y1-fx;
						ysegment[yt].s=y1-fx;
					    ysegment[yt++].e=y2;
					}
				  }
				}
		   }
		} 
//		printf("%d %d %d %d\n",xt,yt,x45t,x135t);
	}
	for(i=0;i<x45t;i++) //Rotate the 45 degree line counterclockwise by 45 degrees to become horizontal, and add it to the xsegment 
	{
		r_x[rxt].pos=P*(x45[i].sy-x45[i].sx); //Vertical coordinate after rotation
		r_x[rxt].s=P*(x45[i].sx+x45[i].sy);   //Starting point after rotation
		r_x[rxt++].e=P*(x45[i].ex+x45[i].ey); //End point after rotation 
	}
	for(i=0;i<x135t;i++)//Rotate the 135 degree line counterclockwise by 45 degrees to become vertical, and add it to the ysegment 
	{
        r_y[ryt].pos=P*(x135[i].sx+x135[i].sy); 
		r_y[ryt].s=P*(x135[i].sy-x135[i].sx);
		r_y[ryt++].e=P*(x135[i].ey-x135[i].ex);
	}
	for(i=0;i<xt;i++) //Adjust the horizontal line segment so that the start point is on the left and the end point is on the right 
	{
		if(xsegment[i].s>xsegment[i].e)
		{
			midx=xsegment[i].s;
			xsegment[i].s=xsegment[i].e;
			xsegment[i].e=midx;
		}
	}
	for(i=0;i<yt;i++)
	{
       if(ysegment[i].s>ysegment[i].e)
	   {
		   midy=ysegment[i].s;
		   ysegment[i].s=ysegment[i].e;
		   ysegment[i].e=midy;
	   }
	}
	for(i=0;i<rxt;i++)
	{
		if(r_x[i].s>r_x[i].e)
		{
			midx=r_x[i].s;
			r_x[i].s=r_x[i].e;
			r_x[i].e=midx;
		}
	}
	for(i=0;i<ryt;i++)
	{
		if(r_y[i].s>r_y[i].e)
		{
			midx=r_y[i].s;
			r_y[i].s=r_y[i].e;
			r_y[i].e=midx;
		}
	}
	sort(xsegment,xsegment+xt,cmp1);  //Sort in ascending order of the first column 
	sort(ysegment,ysegment+yt,cmp1);
	sort(r_x,r_x+rxt,cmp1);
	sort(r_y,r_y+ryt,cmp1);
	//The horizontal line is arranged in the ascending order of the first column and then arranged in the ascending order of the second column 
	for(i=1;i<xt;i++)
	{
        k=i-1;
		while(i<xt&&xsegment[i].pos==xsegment[i-1].pos)
			i++;
		sort(xsegment+k,xsegment+i,cmp2);
	}
	//The horizontal line is arranged in the ascending order of the first column and then arranged in the ascending order of the second column 
	for(i=1;i<yt;i++)
	{
        k=i-1;
		while(i<yt&&ysegment[i].pos==ysegment[i-1].pos)
			i++;
		sort(ysegment+k,ysegment+i,cmp2);
	}
	//The rotated horizontal lines are arranged in the ascending order of the first column and then arranged in the ascending order of the second column 
	for(i=1;i<rxt;i++)
	{
        k=i-1;
		while(i<rxt&&r_x[i].pos==r_x[i-1].pos)
			i++;
		sort(r_x+k,r_x+i,cmp2);
	}
	//The rotated vertical lines are arranged in the ascending order of the first column and then arranged in the ascending order of the second column 
    for(i=1;i<ryt;i++)
	{
        k=i-1;
		while(i<ryt&&r_y[i].pos==r_y[i-1].pos)
			i++;
		sort(r_y+k,r_y+i,cmp2);
	}
	for(i=1;i<xt;i++) //Merge overlapping horizontal lines 
	{
		if(xsegment[i].pos==xsegment[i-1].pos)
			if(xsegment[i].s==xsegment[i-1].s)
			{
				if(xsegment[i].e<xsegment[i-1].e)
					xsegment[i].e=xsegment[i-1].e;
				xsegment[i-1].pos=0;
				xsegment[i-1].s=0;
				xsegment[i-1].e=0;
			}
			else 
			{
				if(xsegment[i].s<xsegment[i-1].e)
				{
				   xsegment[i].s=xsegment[i-1].s;
			   	   if(xsegment[i].e<xsegment[i-1].e)
				  	 xsegment[i].e=xsegment[i-1].e;
				   xsegment[i-1].pos=0;
			 	   xsegment[i-1].s=0;
				   xsegment[i-1].e=0;
				}
			}
	}
	for(i=1;i<yt;i++) //Merge overlapping vertical lines 
	{
		if(ysegment[i].pos==ysegment[i-1].pos)
			if(ysegment[i].s==ysegment[i-1].s)
			{
				if(ysegment[i].e<ysegment[i-1].e)
					ysegment[i].e=ysegment[i-1].e;
				ysegment[i-1].pos=0;
				ysegment[i-1].s=0;
				ysegment[i-1].e=0;
			}
			else 
			{
				if(ysegment[i].s<ysegment[i-1].e)
				{
					ysegment[i].s=ysegment[i-1].s;
			    	if(ysegment[i].e<ysegment[i-1].e)
					  ysegment[i].e=ysegment[i-1].e;
				    ysegment[i-1].pos=0;
				    ysegment[i-1].s=0;
				    ysegment[i-1].e=0;
				}
			}
	}
	for(i=1;i<rxt;i++) //Merge the overlapping horizontal lines after rotation 
	{
		if(r_x[i].pos==r_x[i-1].pos)
			if(r_x[i].s==r_x[i-1].s)
			{
				if(r_x[i].e<r_x[i-1].e)
					r_x[i].e=r_x[i-1].e;
				r_x[i-1].pos=0;
				r_x[i-1].s=0;
				r_x[i-1].e=0;
			}
			else 
			{
				if(r_x[i].s<r_x[i-1].e)
				{
					r_x[i].s=r_x[i-1].s;
				    if(r_x[i].e<r_x[i-1].e)
					  r_x[i].e=r_x[i-1].e;
				    r_x[i-1].pos=0;
				    r_x[i-1].s=0;
				    r_x[i-1].e=0;
				}
			}
	}
	for(i=1;i<ryt;i++) //Merge and rotate overlapping vertical lines 
	{
		if(r_y[i].pos==r_y[i-1].pos)
			if(r_y[i].s==r_y[i-1].s)
			{
				if(r_y[i].e<r_y[i-1].e)
					r_y[i].e=r_y[i-1].e;
				r_y[i-1].pos=0;
				r_y[i-1].s=0;
				r_y[i-1].e=0;
			}
			else 
			{
				if(r_y[i].s<r_y[i-1].e)
				{
					r_y[i].s=r_y[i-1].s;
				    if(r_y[i].e<r_y[i-1].e)
				  	  r_y[i].e=r_y[i-1].e;
			    	r_y[i-1].pos=0;
			    	r_y[i-1].s=0;
				    r_y[i-1].e=0;
				}
			}
	}

//		printf("\nx:\n");
//	for(i=0;i<xt;i++)
//		printf("%.0lf %.0lf %.0lf\n",xsegment[i].pos,xsegment[i].s,xsegment[i].e);
//	printf("\ny:\n");
// 	for(i=0;i<yt;i++)
//	printf("%.0lf %.0lf %.0lf\n",ysegment[i].pos,ysegment[i].s,ysegment[i].e);
//	printf("\nrx:\n");
// 	for(i=0;i<rxt;i++)
//	printf("%lf %lf %lf\n",r_x[i].pos,r_x[i].s,r_x[i].e);
//	printf("\nry:\n");
//  for(i=0;i<ryt;i++)
//	printf("%lf %lf %lf\n",r_y[i].pos,r_y[i].s,r_y[i].e);
	for(i=0;i<xt;i++)
	  fitness+=(xsegment[i].e-xsegment[i].s);
	for(i=0;i<yt;i++)
	  fitness+=(ysegment[i].e-ysegment[i].s);
	for(i=0;i<rxt;i++)
	  fitness+=(r_x[i].e-r_x[i].s);
	for(i=0;i<ryt;i++)
	  fitness+=(r_y[i].e-r_y[i].s);
//	printf("%lf\n",fitness);
	return fitness;
}                 
double Getsharelength(int num)
{
	int i, k, sp, xt = 0, yt = 0, x45t = 0, x135t = 0, rxt = 0, ryt = 0;
	double x1, x2, y1, y2, fx, fy, share = 0, midx, midy;
	//	printf("%d\n",vertice);
	//	for(i=1;i<=3*(vertice-1);i++)
	//		printf("%d ",min_tree[i]);
	//	printf("\n");
	for (i = 1; i < num; i++)
	{
		x1 = graph[min_tree[i * 3 - 2]][0]; 
		y1 = graph[min_tree[i * 3 - 2]][1]; 
		x2 = graph[min_tree[i * 3 - 1]][0]; 
		y2 = graph[min_tree[i * 3 - 1]][1]; 
		sp = min_tree[i * 3]; 
		fx = fabs(x1 - x2);  
		fy = fabs(y1 - y2);  
//		printf("%lf %lf %lf %lf %d %lf %lf\n",x1,y1,x2,y2,sp,fx,fy);
		if (sp == 2 || sp == 3)  
		{
			if (sp == 2)
			{
				xsegment[xt].pos = y2; 
				ysegment[yt].pos = x1; 
			}
			else
			{
				xsegment[xt].pos = y1;
				ysegment[yt].pos = x2;
			}
			if (x1 > x2)
			{
				xsegment[xt].s = x2; 
				xsegment[xt++].e = x1; 
			}
			else
			{
				xsegment[xt].s = x1;
				xsegment[xt++].e = x2;
			}
			if (y1 > y2)
			{
				ysegment[yt].s = y2; 
				ysegment[yt++].e = y1; 
			}
			else
			{
				ysegment[yt].s = y1;
				ysegment[yt++].e = y2;
			}
		}
		if (sp == 0 || sp == 1) 
		{
			if (fx == 0 || fy == 0) 
			{
				if (sp == 0)
				{
					xsegment[xt].pos = y1;
					ysegment[yt].pos = x1;
				}
				else
				{
					xsegment[xt].pos = y2;
					ysegment[yt].pos = x2;
				}
				if (x1 > x2)
				{
					xsegment[xt].s = x2; 
					xsegment[xt++].e = x1; 
				}
				else
				{
					xsegment[xt].s = x1;
					xsegment[xt++].e = x2;
				}
				if (y1 > y2)
				{
					ysegment[yt].s = y2; 
					ysegment[yt++].e = y1; 
				}
				else
				{
					ysegment[yt].s = y1;
					ysegment[yt++].e = y2;
				}
			}
			else 
			{
				if (x1 > x2) 
				{
					midx = x1;
					midy = y1;
					x1 = x2;
					y1 = y2;
					x2 = midx;
					y2 = midy;
					sp = !sp;
				}
				if (fx > fy) 
				{
					if (sp == 0) 
					{
						xsegment[xt].pos = y1;
						xsegment[xt].s = x1;
						xsegment[xt++].e = x2 - fy;
						if (y1 < y2) 
						{
							x45[x45t].sx = x2 - fy;
							x45[x45t].sy = y1;
							x45[x45t].ex = x2;
							x45[x45t++].ey = y2;
						}
						else  
						{
							x135[x135t].sx = x2 - fy;
							x135[x135t].sy = y1;
							x135[x135t].ex = x2;
							x135[x135t++].ey = y2;
						}
					}
					else 
					{
						xsegment[xt].pos = y2;
						xsegment[xt].s = x1 + fy;
						xsegment[xt++].e = x2;
						if (y1 < y2)
						{
							x45[x45t].sx = x1;
							x45[x45t].sy = y1;
							x45[x45t].ex = x1 + fy;
							x45[x45t++].ey = y2;
						}
						else
						{
							x135[x135t].sx = x1;
							x135[x135t].sy = y1;
							x135[x135t].ex = x1 + fy;
							x135[x135t++].ey = y2;
						}
					}
				}
				else 
				{
					if (sp == 0)
					{
						ysegment[yt].pos = x1;
						if (y1 < y2)
						{
							x45[x45t].sx = x1;
							x45[x45t].sy = y2 - fx;
							x45[x45t].ex = x2;
							x45[x45t++].ey = y2;
							ysegment[yt].s = y1;
							ysegment[yt++].e = y2 - fx;
						}
						else
						{
							x135[x135t].sx = x1;
							x135[x135t].sy = y2 + fx;
							x135[x135t].ex = x2;
							x135[x135t++].ey = y2;
							ysegment[yt].s = y1;
							ysegment[yt++].e = y2 + fx;
						}
					}
					else
					{
						ysegment[yt].pos = x2;
						if (y1 < y2)
						{
							x45[x45t].sx = x1;
							x45[x45t].sy = y1;
							x45[x45t].ex = x2;
							x45[x45t++].ey = y1 + fx;
							ysegment[yt].s = y1 + fx;
							ysegment[yt++].e = y2;
						}
						else
						{
							x135[x135t].sx = x1;
							x135[x135t].sy = y1;
							x135[x135t].ex = x2;
							x135[x135t++].ey = y1 - fx;
							ysegment[yt].s = y1 - fx;
							ysegment[yt++].e = y2;
						}
					}
				}
			}
		}
		
	}
	for (i = 0; i < x45t; i++) 
	{
		r_x[rxt].pos = P * (x45[i].sy - x45[i].sx); 
		r_x[rxt].s = P * (x45[i].sx + x45[i].sy);   
		r_x[rxt++].e = P * (x45[i].ex + x45[i].ey); 
	}
	for (i = 0; i < x135t; i++) 
	{
		r_y[ryt].pos = P * (x135[i].sx + x135[i].sy);
		r_y[ryt].s = P * (x135[i].sy - x135[i].sx);
		r_y[ryt++].e = P * (x135[i].ey - x135[i].ex);
	}
	for (i = 0; i < xt; i++)
	{
		if (xsegment[i].s > xsegment[i].e)
		{
			midx = xsegment[i].s;
			xsegment[i].s = xsegment[i].e;
			xsegment[i].e = midx;
		}
	}
	for (i = 0; i < yt; i++)
	{
		if (ysegment[i].s > ysegment[i].e)
		{
			midy = ysegment[i].s;
			ysegment[i].s = ysegment[i].e;
			ysegment[i].e = midy;
		}
	}
	for (i = 0; i < rxt; i++)
	{
		if (r_x[i].s > r_x[i].e)
		{
			midx = r_x[i].s;
			r_x[i].s = r_x[i].e;
			r_x[i].e = midx;
		}
	}
	for (i = 0; i < ryt; i++)
	{
		if (r_y[i].s > r_y[i].e)
		{
			midx = r_y[i].s;
			r_y[i].s = r_y[i].e;
			r_y[i].e = midx;
		}
	}
	sort(xsegment, xsegment + xt, cmp1); 
	sort(ysegment, ysegment + yt, cmp1);
	sort(r_x, r_x + rxt, cmp1);
	sort(r_y, r_y + ryt, cmp1);
	for (i = 1; i < xt; i++) 
	{
		k = i - 1;
		while (i < xt && xsegment[i].pos == xsegment[i - 1].pos)
			i++;
		sort(xsegment + k, xsegment + i, cmp2);
	}
	for (i = 1; i < yt; i++) 
	{
		k = i - 1;
		while (i < yt && ysegment[i].pos == ysegment[i - 1].pos)
			i++;
		sort(ysegment + k, ysegment + i, cmp2);
	}
	for (i = 1; i < rxt; i++) 
	{
		k = i - 1;
		while (i < rxt && r_x[i].pos == r_x[i - 1].pos)
			i++;
		sort(r_x + k, r_x + i, cmp2);
	}
	for (i = 1; i < ryt; i++) 
	{
		k = i - 1;
		while (i < ryt && r_y[i].pos == r_y[i - 1].pos)
			i++;
		sort(r_y + k, r_y + i, cmp2);
	}
	for (i = 1; i < xt; i++) 
	{
		if (xsegment[i].pos == xsegment[i - 1].pos)
			if (xsegment[i].s == xsegment[i - 1].s)
			{
				if (xsegment[i].e < xsegment[i - 1].e)
				{
					xsegment[i].e = xsegment[i - 1].e;
					share += xsegment[i].e - xsegment[i].s;
				}
				else share += xsegment[i - 1].e - xsegment[i - 1].s;
				xsegment[i - 1].pos = 0;
				xsegment[i - 1].s = 0;
				xsegment[i - 1].e = 0;
			}
			else
			{
				if (xsegment[i].s < xsegment[i - 1].e)
				{
					xsegment[i].s = xsegment[i - 1].s;
					if (xsegment[i].e < xsegment[i - 1].e)
					{
						xsegment[i].e = xsegment[i - 1].e;
						share += xsegment[i].e - xsegment[i].s;
					}
					else share += xsegment[i - 1].e - xsegment[i].s;
					xsegment[i - 1].pos = 0;
					xsegment[i - 1].s = 0;
					xsegment[i - 1].e = 0;
				}
			}
	}
	for (i = 1; i < yt; i++) 
	{
		if (ysegment[i].pos == ysegment[i - 1].pos)
			if (ysegment[i].s == ysegment[i - 1].s)
			{
				if (ysegment[i].e < ysegment[i - 1].e)
				{
					ysegment[i].e = ysegment[i - 1].e;
					share += ysegment[i].e - ysegment[i].s;
				}
				else share += ysegment[i - 1].e - ysegment[i - 1].s;
				ysegment[i - 1].pos = 0;
				ysegment[i - 1].s = 0;
				ysegment[i - 1].e = 0;
			}
			else
			{
				if (ysegment[i].s < ysegment[i - 1].e)
				{
					ysegment[i].s = ysegment[i - 1].s;
					if (ysegment[i].e < ysegment[i - 1].e)
					{
						ysegment[i].e = ysegment[i - 1].e;
						share += ysegment[i].e - ysegment[i].s;
					}
					else share += ysegment[i - 1].e - ysegment[i].s;
					ysegment[i - 1].pos = 0;
					ysegment[i - 1].s = 0;
					ysegment[i - 1].e = 0;
				}
			}
	}
	for (i = 1; i < rxt; i++) 
	{
		if (r_x[i].pos == r_x[i - 1].pos)
			if (r_x[i].s == r_x[i - 1].s)
			{
				if (r_x[i].e < r_x[i - 1].e)
				{
					r_x[i].e = r_x[i - 1].e;
					share += r_x[i].e - r_x[i].s;
				}
				else share += r_x[i - 1].e - r_x[i - 1].s;
				r_x[i - 1].pos = 0;
				r_x[i - 1].s = 0;
				r_x[i - 1].e = 0;
			}
			else
			{
				if (r_x[i].s < r_x[i - 1].e)
				{
					r_x[i].s = r_x[i - 1].s;
					if (r_x[i].e < r_x[i - 1].e)
					{
						r_x[i].e = r_x[i - 1].e;
						share += r_x[i].e - r_x[i].s;
					}
					else share += r_x[i - 1].e - r_x[i].s;
					r_x[i - 1].pos = 0;
					r_x[i - 1].s = 0;
					r_x[i - 1].e = 0;
				}
			}
	}
	for (i = 1; i < ryt; i++)
	{
		if (r_y[i].pos == r_y[i - 1].pos)
			if (r_y[i].s == r_y[i - 1].s)
			{
				if (r_y[i].e < r_y[i - 1].e)
				{
					r_y[i].e = r_y[i - 1].e;
					share += r_y[i].e - r_y[i].s;
				}
				else share += r_y[i - 1].e - r_y[i - 1].s;
				r_y[i - 1].pos = 0;
				r_y[i - 1].s = 0;
				r_y[i - 1].e = 0;
			}
			else
			{
				if (r_y[i].s < r_y[i - 1].e)
				{
					r_y[i].s = r_y[i - 1].s;
					if (r_y[i].e < r_y[i - 1].e)
					{
						r_y[i].e = r_y[i - 1].e;
						share += r_y[i].e - r_y[i].s;
					}
					else share += r_y[i - 1].e - r_y[i].s;
					r_y[i - 1].pos = 0;
					r_y[i - 1].s = 0;
					r_y[i - 1].e = 0;
				}
			}
	}
	return share;
}