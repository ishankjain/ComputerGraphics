#include<bits/stdc++.h>
using namespace std;
#define V vector<vector<float> >
struct point{
	float x,y,z;
};	
V compositeMatrix(4,vector<float>(4));
V translationMatrix(4,vector<float>(4));
V av(4,vector<float>(4));
V rotationMatrix(4,vector<float>(4));
// Function to get cofactor of A[p][q] in temp[][]. n is current 
// dimension of A[][] 
void getCofactor(V &A, V &temp, int p, int q, int n) 
{ 
	int i = 0, j = 0; 

	// Looping for each element of the matrix 
	for (int row = 0; row < n; row++) 
	{ 
		for (int col = 0; col < n; col++) 
		{ 
			// Copying into temporary matrix only those element 
			// which are not in given row and column 
			if (row != p && col != q) 
			{ 
				temp[i][j++] = A[row][col]; 

				// Row is filled, so increase row index and 
				// reset col index 
				if (j == n - 1) 
				{ 
					j = 0; 
					i++; 
				} 
			} 
		} 
	} 
} 

/* Recursive function for finding determinant of matrix. 
n is current dimension of A[][]. */
float determinant(V &A,  int n) 
{ 
	float D = 0; // Initialize result 

	// Base case : if matrix contains single element 
	if (n == 1) 
		return A[0][0]; 

	V temp(n,vector<float>(n)); // To store cofactors 

	float sign = 1; // To store sign multiplier 

	// Iterate for each element of first row 
	for (int f = 0; f < n; f++) 
	{ 
		// Getting Cofactor of A[0][f] 
		getCofactor(A, temp, 0, f, n); 
		D += sign * A[0][f] * determinant(temp, n - 1); 

		// terms are to be added with alternate sign 
		sign = -sign; 
	} 

	return D; 
} 

// Function to get adjoint of A[N][N] in adj[N][N]. 
void adjoint(V &A,V &adj) 
{ 
	int N=A.size();
	if (N == 1) 
	{ 
		adj[0][0] = 1; 
		return; 
	} 

	// temp is used to store cofactors of A[][] 
	float sign = 1;
	V temp(N,vector<float>(N)); 

	for (int i=0; i<N; i++) 
	{ 
		for (int j=0; j<N; j++) 
		{ 
			// Get cofactor of A[i][j] 
			getCofactor(A, temp, i, j, N); 

			// sign of adj[j][i] positive if sum of row 
			// and column indexes is even. 
			sign = ((i+j)%2==0)? 1: -1; 

			// Interchanging rows and columns to get the 
			// transpose of the cofactor matrix 
			adj[j][i] = (sign)*(determinant(temp, N-1)); 
		} 
	} 
} 

// Function to calculate and store inverse, returns false if 
// matrix is singular 
bool inverse(V &A,V &inv) 
{ 
	// Find determinant of A[][] 
	int N=A.size();
	float det = determinant(A, N); 
	if (det == 0) 
	{ 
		cout << "Singular matrix, can't find its inverse"; 
		return false; 
	} 

	// Find adjoint 
	V adj(N,vector<float>(N));
	adjoint(A, adj); 

	// Find Inverse using formula "inverse(A) = adj(A)/det(A)" 
	for (int i=0; i<N; i++) 
		for (int j=0; j<N; j++) 
			inv[i][j] = adj[i][j]/float(det); 

	return true; 
} 

void multiply(V mat1,V mat2,V &res) 
{  
    for (int i = 0; i < mat1.size(); i++) 
    { 
        for (int j = 0; j <mat2[0].size() ; j++) 
        { 
            res[i][j] = 0; 
            for (int k = 0; k < mat2.size(); k++) 
                res[i][j] += mat1[i][k] *  
                             mat2[k][j]; 
        } 
    } 
} 
void initialize(point o,float a,float b,float c,float angle)
{
	for(int i=0;i<4;++i)
	{
		compositeMatrix[i][i]=1;
	}

	translationMatrix=compositeMatrix;
	translationMatrix[0][3]-=o.x;
	translationMatrix[1][3]-=o.y;
	translationMatrix[2][3]-=o.z;

	rotationMatrix=compositeMatrix;
	rotationMatrix[0][0]=cos(angle);
	rotationMatrix[0][1]=-1*sin(angle);
	rotationMatrix[1][0]=sin(angle);
	rotationMatrix[1][1]=cos(angle);

	av=compositeMatrix;
	float lambda=sqrt(b*b+c*c),l=sqrt(a*a+b*b+c*c);
	av[0][0]=lambda/l,av[0][2]=a/l,av[1][0]=(-1.0*a*b)/(lambda*l),av[1][1]=c/lambda,av[1][2]=b/l;
	av[2][0]=(-1*a*c)/(lambda*l),av[2][1]=(-1*b)/lambda,av[2][2]=c/l;

}
int main()
{
	
	point o;
	cout<<"line passing through point:";
	cin>>o.x>>o.y>>o.z;
	float a,b,c;
	cout<<"enter direction cosines:";
	cin>>a>>b>>c;
	float angle;
	cin>>angle;
	initialize(o,a,b,c,angle);
	av[1][0]=0,av[2][0]=0;
	V res(4,vector<float>(4));
	multiply(compositeMatrix,translationMatrix,res);
	compositeMatrix=res;
	multiply(compositeMatrix,av,res);
	compositeMatrix=res;
	multiply(compositeMatrix,rotationMatrix,res);
	compositeMatrix=res;
	V inv(4,vector<float>(4));
	if(inverse(av,inv))
		multiply(compositeMatrix,inv,res);
	compositeMatrix=res;
	if(inverse(translationMatrix,inv))
		multiply(compositeMatrix,inv,res);
	compositeMatrix=res;
cout<<endl;
	for(int i=0;i<4;++i)
	{
		for(int j=0;j<4;++j)
		{
			cout<<compositeMatrix[i][j]<<" ";
		}
		cout<<endl;
	}
}