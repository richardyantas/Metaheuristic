#include<iostream>
#include<cstdio>
#include<vector>
#define pb push_back
using namespace std;
int main(){
    // 4123 19382 23581 23040 1743 18362 
    
    /*
    int* items;
    int i=0;
    items = new int;
    while( scanf("%d",items) ){
        items=new int;        
        i++;
    }
    */
    /*
    int size = sizeof(items)/sizeof(bool);
    printf("%d",size);
    */
    
    int items[100];
    int n=0;
    vector<int> w, v; // items weights and values
    int var,vv[1000][1000];
    
    while(cin>>items[n]){
        n++;
    }
    
    for(int i=0;i<100;i++)
	{
	    scanf("%d",&var);
	    v.pb(var);
	}
	
	for(int i=0;i<100-1;i++)
	{
	    for(int j=i+1;j<100;j++)
	    {	        
	        //printf(".");
	        scanf("%d",&vv[i][j]);
	    }
	}
	
	for(int i=0;i<100;i++)
	{
	    scanf("%d",&var);
	    w.pb(var);
	}
		
		
		
    //cout << "n: "<< n<<endl;
    for(int i=0;i<100;i++)
    {
        cout << items[i] << " ";
    }
    cout << endl;
    
    int fit = 0, wsum = 0;
    
    for(int i=0;i<100;i++)
	{
	    fit += items[i]*v[i];
	    wsum += items[i]*w[i];
	    for(int j=i+1;j<=100;j++)
	    {    		
	    	fit += items[i]*items[j]*vv[i][j];
	    }
	}
        
    
    cout << "fit is: "<< fit << endl;
    //cout << s << endl;
    return 0;
}
