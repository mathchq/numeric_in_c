#include <iostream>
using namespace std;


#define TINY 1.0e-25

double fabs( double a)
{
	return ( a > 0) ? ( a) : ( -a);
}

// diagnol rational function
// v = u or v + 1 = u, v is the 
void ratint(  double xa[], double ya[], int n, double x, double *y, double *dy)
{
	double* c=( double*) malloc( sizeof( double) * n); 
	double* d=( double*) malloc( sizeof( double) * n);
	int ns = 0;
	double hh=fabs(x-xa[0]); 

	int i , m;
	double w, h, dd, t;
	for (i=0;i<n;i++) 
	{ 
		h=fabs(x-xa[i]); 
		//test the special case x equals to a
		if (h == 0.0)
		{ 
			*y=ya[i];
			*dy=0.0; 
			free( c); free(d); return; 
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
	//make up the element's reduction by index shifting 
	for (m=1;m<n;m++) //times to iteration
	{
		for ( i = 1; i <= n-m; i++)//calculate the value
		{ 
		//find the repeated pattern
		//use the simple pattern to form the complicated one
			w=c[i+1]-d[i]; //TINY to prevent over zero
			h=xa[i+m]-x; 
				//h will never be zero, since this was tested in the initializing loop.
			t=(xa[i]-x)*d[i]/h; 
			dd=t-c[i+1];
			if (dd == 0.0) 
			{
				printf( "error!");
				return;
			}
				//nrerror("Error in routine ratint"); 
				//???//This error condition indicates that the interpolating function has a pole at the requested value of x.
			dd=w/dd; 
			d[i]=c[i+1]*dd; c[i]=t*dd; //this is the eliminated behavior
		}
	
		//in a sequence uncertaining add we thought the error is the last step addition
		//*y += (*dy=(2*ns < (n-m) ? c[ns+1] : d[ns--])); // ns + 1 is determined by the shape of praymind
		
		cout << "( n - m) / 2 = " << ( n - m) / 2 << endl;
		cout << "ns = " << ns << endl;
		if( 2 * ns < ( n - m))
		{
			*dy = c[ns+1];
			cout << "c["<< ns + 1 << "]" << endl;
		}
		else
		{
			*dy = d[ns];
			cout << "d["<< ns << "]" << endl;
			ns--;
		}

		*y += (*dy);

		cout << endl;
		//point to the middle, 
		//equivalent with if else structure
	} 
	free( c); free(d); return; 

}

// not so accuracy when lack of enough data 
//special case : array length equals to four 
// 

const double pi = 3.141592653;
int main()
{
	const int n = 5;
	double xa[n] = { 0, pi / 8, pi / 4, pi * 3 / 8, pi / 2}; //, 6};
	double ya[n] = { 0, 0.3826834323, 0.707106781, 0.92387953, 1};//, //64};

	double x = pi * 3 / 32 ;
	double y = 0, dy;
	ratint( xa, ya, n, x, &y, &dy);
	//int ns = 0;
	//y += ( 2 * ns < n ? xa[ns+1] : ya[ns--]);
	//cout << ns << endl;


	//y += ( 2 * ns < n ? xa[ns+1] : ya[ns--]);
	//cout << ns << endl;


	//y += ( 2 * ns < n ? ns+1 : ns--);
	//cout << ns << endl;


	//y += ( 2 * ns < n ? ns+1 : ns--);
	//cout << ns << endl;
	cout << y << endl;
	cout << dy << endl;

	return 1;
}
