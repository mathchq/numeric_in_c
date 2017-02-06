#define TINY 1.0e-25
#define FREE_RETURN{ free( c); free(d); return; }

void ratint(  float xa[], float ya[], int n, float x, float *y, float *dy)
{
	float * c=( float *) malloc( sizeof( float) * n); 
	float * d=( float *) malloc( sizeof( float) * n);
	int ns = 1;
	float hh=fabs(x-xa[1]); 
	float h;
	for (i=0;i<n;i++) 
	{ 
		h=fabs(x-xa[i]); 
		//test the special case x equals to a
		if (h == 0.0)
		{ 
			*y=ya[i];
			*dy=0.0; 
			FREERETURN
		}
		else if (h < hh) 
		{ 
			ns=i;
			hh=h; 
		} 
		//initialization
		//prevent the extreme condition happens
		// zero can be overlooked 
		c[i]=ya[i]; 
		d[i]=ya[i]+TINY;
		//The TINY part is needed to prevent a rare zero-over-zero condition.
	} 
	*y=ya[ns--];

	//length has been reduce by one after the second for loop executed once
	//ns - 1, the coordinate has been minus one , use the coordinate 
	for (m=1;m<n;m++) //times to iteration
	{
		for ( i = 0; i < n-m; i++)//calculate the value
		{ 
		//find the repeated pattern
		//use the simple pattern to form the complicated one
			w=c[i+1]-d[i];
			h=xa[i+m]-x; 
				//h will never be zero, since this was tested in the initializing loop.
			t=(xa[i]-x)*d[i]/h; 
			dd=t-c[i+1];
			if (dd == 0.0) 
				nrerror("Error in routine ratint"); 
				???//This error condition indicates that the interpolating function has a pole at the requested value of x.
			dd=w/dd; 
			d[i]=c[i+1]*dd; c[i]=t*dd; //this is the eliminated behavior
		}
		//in a sequence uncertaining add we thought the error is the last step addition
		*y += (*dy=(2*ns < (n-m) ? c[ns+1] : d[ns--])); // ns + 1 is determined by the shape of praymind
	} 
	FREERETURN
}
}
