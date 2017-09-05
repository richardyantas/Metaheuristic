#include <bits/stdc++.h>

#define pb push_back

#if defined(__linux) || defined(__linux__)
	unsigned int seed = time(NULL);
	#define RND ((double)rand_r(&seed)/RAND_MAX)
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
	#define RND ((double)rand()/RAND_MAX) 
#endif

using namespace std;

int N;	
int spaper = 0;
double error;
vector<int> Answer(21);
vector< vector<int> > vv;
vector<int> v,w;	
int constraint_weight,limit;

struct chromo{
  bool* items;
	int f;	
	int dimc;
	chromo(int _dimc) { items = new bool[_dimc];dimc=_dimc; }
	~chromo() {	items = NULL; }
	void mutate(const int dimc, const int count){
		int mi;
		for(int i=0;i<count;i++){
			mi = (int)(round(RND*(dimc-1)));
			items[mi] = !items[mi];
		}
	}	
};

int fitness(bool*& x, const int dimc, const vector<int>& v, const vector<int>& w, vector< vector<int> > p, const int limit){
	int fit = 0, wsum = 0;
	for(int i=0;i<dimc;i++)
  {
      fit += x[i]*v[i];
      wsum += x[i]*w[i];
  }  
  for(int i=0;i<=dimc-2;i++)
      for(int j=i+1;j<=dimc-1;j++)
          fit += x[i]*x[j]*p[i][j-i-1];
	if(wsum>limit) fit=0;
	return fit;
}

void crossover1p(const chromo& c1, const chromo& c2, const chromo& c3, const int dimc, const int cp) {
	for(int i=0;i<dimc;i++){c3.items[i] = i<cp?c1.items[i]:c2.items[i];}
}


bool cfit(const chromo &c1,const chromo &c2) { return c1.f > c2.f; }
bool cmpfun(const std::pair<int,double> &r1, const std::pair<int,double> &r2) { return r1.second > r2.second; }
int coin(const double crp) {return RND<crp?1:0;} // 1 crossover, 0 Mutations

void initpopg(bool**& c, const std::vector<int> &w, const std::vector<int> &v,vector< vector<int> > &p, const int dimw, const int limit, const int pop){
	std::vector<std::pair<int,double> > rvals(dimw);
	std::vector<int> index(dimw,0);

	/*
	for(int i=0;i<dimw;i++) {
		rvals.push_back(std::pair<int,double>(std::make_pair(i,(double)v[i]/(double)w[i])));
	}*/
	
	vector<int> s;
	s.resize(dimw);
	for(int i=0;i<dimw-1;i++)
		for(int j=0;j<p[i].size();j++)
				s[i] += p[i][j];	

	s[dimw-1] = 0;	
	for(int i=0;i<dimw;i++){			      					     
		rvals.push_back(std::pair<int,double>(std::make_pair(i,(double)(v[i]+s[i])/(double)w[i])));
	}

	std::sort(rvals.begin(),rvals.end(),cmpfun);
	int currentw = 0, k;
	for(int i=0;i<dimw;i++){
		k = rvals[i].first;
		if(currentw + w[k] <= limit){ 
			currentw += w[k];
			index[k] = 1;
		}
	}
	
	
	for(int i=0;i<pop;i++){
		for(int j=0;j<dimw;j++){
			c[i][j] = index[j];
		}
	}
	

	// find solutions randomly
	/*
	int i = 0,s;
	vector<int> prueba(dimw);
	while( i < pop)
	{
		s = 0;
		for(int j=0;j<dimw;j++){
			prueba[j]=(RND<0.5)?0:1;
			s += w[j]*prueba[j];
		}
		if(s<limit)
		{
			for(int j=0;j<dimw;j++){
				c[i][j] = prueba[j];
			}
			i++;
		}
	}*/

	
	/*
	for(int i=0;i<pop;i++){
		for(int j=0;j<dimw;j++){
			//c[i][j] = index[j];
			cout << c[i][j];
		}
		cout << endl;
	}*/
	

}


void GA(int t)
{
	const int pop = N; // tamaño de la poblacion de cromosomas                             
	const int gens = 10*N;//INT_MAX; // maximo numero de generaciones
	const int disc = (int)(ceil(pop*0.8));// cromosomas descartados por elitismo
	const int dimw = w.size();
	int best = 0, ind = 0, ind2 = 0;
	int parc = 0;// indice del padre para el crossover
	double avg = 0, crp = 0.7;// probabilidad para realizar el crossover valir crp = 0.35 cambiado a 0.7	
	vector<chromo> ch(pop,chromo(dimw));
	bool **c = new bool*[pop];
	for(int i=0;i<pop;i++) c[i] = new bool[dimw];
	
	//printf("Initializing population with a greedy algorithm...");
	initpopg(c,w,v,vv,dimw,limit,pop);
	//printf("Done!");

	for(int i=0;i<pop;i++){	
				ch[i].items = c[i];
				ch[i].f = fitness(ch[i].items, dimw ,v, w, vv, limit);
	}
	/*
	cout << endl << endl;
	for(int i=0;i<pop;i++){
			cout << ch[i].f;
		cout << endl;
	}
	cout << endl;
	*/
	//printf("\n\n");
	//const int numElite = pop - disc;
	for(int p=0;p<gens;p++){
		std::sort(ch.begin(), ch.end(), cfit);
		for(int i=0;i<pop;i++){
			if(i>pop-disc){// ELitismo - solo se procesa los cromosomas descartados 
				if(coin(crp)==1) {
					ind = parc+round(dimw*RND);
					ind2 = parc+1+round(dimw*RND);
					crossover1p(ch[ind%pop],ch[ind2%pop],ch[i],dimw,RND*(dimw-1)); 
					ch[i].f = fitness(ch[i].items, dimw ,v ,w ,vv ,limit);
					parc += 1;
				}
				else {// seccion de la mutacion
					ch[i].mutate(dimw,1);
					ch[i].f = fitness(ch[i].items, dimw ,v, w,vv, limit);
				}
			}
			avg += ch[i].f;
			if(ch[i].f>best){
			    best=ch[i].f;
			}
		}
        
   		parc = 0;
		if(p%5==0){
			//printf("\n#%d\t",p);
			//printf("%d\n",best);
			//printf("best fitness: %d \t",best);
			//printf("avg fitness: %f",avg/pop);
		}		


   	if(p == gens-1)
   	{
   		//spaper++;

   		error = 100*(best-Answer[t])/best;
  		printf("best fitness: %d value: %d avg fitness: %f  Error: %lf% \t",best,Answer[t],avg/pop,error);
			//printf("best fitness: %d",best);
			//printf("avg fitness: %f",avg/pop); 		
   	}
		best = avg = 0;
	}   
	
	//printf("\n\n");

}


string nombre;
void readInput()
{
	cin >> nombre;
	scanf("%d",&N);		
	v.resize(N);
	for(int i=0;i<N;i++)scanf("%d",&v[i]);	
	vv.resize(N-1);
	for(int i=0;i<=N-2;i++)
	{
	    for(int j=0;j<N-1-i;j++)
	    {	        
	    		vv[i].resize(N-1-i);
	        scanf("%d",&vv[i][j]);    		
	    }	    
	}		
	scanf("%d",&constraint_weight);
	scanf("%d",&limit);						
	w.resize(N);
	for(int i=0;i<N;i++)scanf("%d",&w[i]);
}


int main() {	
	int numTest = 21;
	vector<char*> file;
	file.resize(numTest);
	
	file[1] = "jeu_100_25_1.txt";
	file[2] = "jeu_100_25_2.txt";
	file[3] = "jeu_100_25_3.txt";
	file[4] = "jeu_100_25_4.txt";
	file[5] = "jeu_100_25_5.txt";
	file[6] = "jeu_100_25_6.txt";
	file[7] = "jeu_100_25_7.txt";
	file[8] = "jeu_100_25_8.txt";
	file[9] = "jeu_100_25_9.txt";
	file[10] = "jeu_100_25_10.txt";

	file[11] = "jeu_200_100_1.txt";
	file[12] = "jeu_200_100_2.txt";
	file[13] = "jeu_200_100_3.txt";
	file[14] = "jeu_200_100_4.txt";
	file[15] = "jeu_200_100_5.txt";
	file[16] = "jeu_200_100_6.txt";
	file[17] = "jeu_200_100_7.txt";
	file[18] = "jeu_200_100_8.txt";
	file[19] = "jeu_200_100_9.txt";
	file[20] = "jeu_200_100_10.txt";

	Answer[1] = 18558;
	Answer[2] = 56525;
	Answer[3] = 3752;
	Answer[4] = 50382;
	Answer[5] = 61494;
	Answer[6] = 36360;
	Answer[7] = 14657;
	Answer[8] = 20452;
	Answer[9] = 35438;
	Answer[10] = 24630;
	Answer[11] = 937149;
	Answer[12] = 303058;
	Answer[13] = 29367;
	Answer[14] = 100838;
	Answer[15] = 786635;
	Answer[16] = 41171;
	Answer[17] = 701094;
	Answer[18] = 782398;	
	Answer[19] = 628992;
	Answer[20] = 378492;

	for(int test = 1;test<4;test++)
	{
		//int test = 1;		
		freopen(file[test],"r",stdin);
		//freopen("in_random.txt","w",stdout);
		readInput();				
		clock_t start = clock();
		printf("Test #%d  ",test);
		printf(" (N=%d) ",N);	
		GA(test);
		clock_t end = clock();
		double t = (double)(end-start)/CLOCKS_PER_SEC;
		printf(" Time: %fs.\n",t);	
	}
	printf("\n");
	
	return 0;
}

