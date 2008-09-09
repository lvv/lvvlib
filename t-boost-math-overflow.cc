
#undef dMODEL
#define dMODEL
#define dMODEL_FILTER 1

#include <stats/stats.h>
#include <nf/nf.h>

 #include <cstring>
 using std::memset;

 using namespace std;
 using namespace lvv;


int main() { 

	//ofstream out("clog");
	//clog.rdbuf(out.rdbuf());


	{
		
		#if MODEL_POINTS == 5
			ModelPointT_t Y = {{ 0.0259 , 0.0693, 0.1966, 0.4537, 0.8006 }}; 
			
			//double Y[] = { 0.0645 , 0.1649, 0.2814, 0.4427, 0.7616} ; 
			//double Y[] = {+0.0662 , 0.2824, 0.6288, 0.8986, 0.9861} ; 
			//double Y[] = {0       , 0     , 0     , 0.2   , 0.9}    ; 
			//double Y[] = {0.1     , 0.3   , 0.4   , 0.7   , 0.9}    ; 
		#endif
			
		#if MODEL_POINTS == 5+2
			ModelPointT_t Y = {{ -0.01  , +0.1259, 0.43, 0.5, 0.53, 0.7006, 1.01 }}; 		// with horizontal shelf in the middle
			//ModelPointT_t Y = {{ -0.01, +0.0259, 0.0693, 0.1966, 0.4537, 0.8006, 1.01 }}; 
			
			//double Y[] = { 0    , 0.0645 , 0.1649, 0.2814, 0.4427, 0.7616, 1}    ; 
			//double Y[] = {0     , +0.0662, 0.2824, 0.6288, 0.8986, 0.9861, 1 }   ; 
			//double Y[] = {0     , 0      , 0     , 0     , 0.2   , 0.9   , 1}    ; 
			//double Y[] = {0     , 0.1    , 0.3   , 0.4   , 0.7   , 0.9   , 1}    ; 
		#endif
		
		/*
		Model  m;
		double mse = m.C_finder(R, Y);

		// print data points
		FMT("#########  Model   type=%s    order=%d    points=%d    part_size=%d    \n")   %m.name()  %model_order  %model_points  %part_size;
		format		table(" % 9f    %20t % 9f   %40t % 9f   %60t % 9f\n");
		string		_("\" \"");
		for (int i=R.ibegin();  i<R.iend(); ++i              	)	cout << table	% R[i] 	% Y[i] 		% _    		% _ ;

		cout << format("# C_model  RMSE=%f\n") % sqrt(mse);
		m.print("t-model.cc");
		return 0;
		*/

	}

	{
		cout << "##########  ModelMaker\n";
		part_t	part=1;
		u_t	u=2;
		m_t	m=3;

		Model		model;
		ModelMaker	mm;

		//{ mm.BIN[1] = 9   ; mm.BIN[2] = 29 ; mm.BIN[3] = 28 ; mm.BIN[4] = 32 ; mm.BIN[5] = 187 ; double mse = mm.make(model) ;}
		//{ mm.BIN[1] = 3   ; mm.BIN[2] = 0  ; mm.BIN[3] = 0  ; mm.BIN[4] = 0  ; mm.BIN[5] = 3   ; double mse = mm.make(model) ;}
		//{ mm.BIN[1] = 3333; mm.BIN[2] = 0  ; mm.BIN[3] = 0  ; mm.BIN[4] = 0  ; mm.BIN[5] = 3333; double mse = mm.make(model) ;}
		//{ mm.BIN[1] = 0   ; mm.BIN[2] = 0  ; mm.BIN[3] = 0  ; mm.BIN[4] = 0  ; mm.BIN[5] = 3333; double mse = mm.make(model) ;}
		//{ mm.BIN[1] = 333 ; mm.BIN[2] = 333; mm.BIN[3] = 333; mm.BIN[4] = 333; mm.BIN[5] = 333 ; double mse = mm.make(model) ;}

	// test infinity
		{
			mm.BIN[1] = 0   ; mm.BIN[2] = 333; mm.BIN[3] = 0  ; mm.BIN[4] = 333; mm.BIN[5] = 0   ;
			double mse = mm.make(model) ;
			cout << model.r2z(5)<< endl;
		}
//		double mse = mm.make(model); 

	}

	cerr << Model::name() << endl;

    exit(0);
}
