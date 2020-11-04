#include "merged_classes.h"

//~~~~ Condition Verifier ~~~~//

bool tools::is_continuous(double (*f)(double),double start, double end)
{
    // Verify the continuity of f within the interval [start,end]
    
    bool continuous = true; // f is considered continuous a priori
     
    vector<double> ifun;    // Vector for storing the values of 1/f(x)
    int points = 10000;     // Number of points used for testing continuity
    double delta = (end - start) / points;  // Step size
    
    for (double x = start; x < end; x += delta)
        {
            if (isinf(f(x)))
            {
                // If there is a inf value, f is not continuous
                continuous = false;
                break;
            }
            if (isnan(f(x)))
            {
                // If there is nan value, f is not continuous
                continuous = false;
                break;
            }
            // Fill a vector with the values of the function^-1
        
            ifun.push_back(1/f(x));
        }
    
    for (int i = 1; i < ifun.size() ; i++)
    {
        // If there is a change of sign in 1/f(x_o) there is a discontinuity of f(x) in x_o
        if ( abs(ifun[i]) < 50 &&  ifun[i] * ifun[i-1] < 0)
        {
            continuous = false;
            break;
        }
    }
    
    return continuous;
}

bool tools::is_defined_positive(double (*f)(double),double start, double end)
{

    int points = 10000;  // Number of points used for testing positiveness
    bool define_positive = true; // f is considered positive a priori
    double delta = (end - start) / points;  // Step size 
    
    for (double x = start; x < end; x += delta)
    {
        if (f(x) < 0)
        {
            // If there is a negative value within the interval is automatically not positive defined.
            define_positive = false;
        }
    }
    
    return define_positive;
}

bool tools::check_conditions(vector<double (*)(double)> funvec, double start, double end)
{
    // The input is an vector of three functions: {p(x),q(x),r(x)} and two numbers defining the interval [start,end]
    // The conditions for the linear shooting are the continuity of p(x),q(x),r(x) and q(x) must be positive defined.
    
    bool bp = is_continuous(funvec[0],start,end);  // Is p(x) continuous witih [start,end] ?
    bool bq = is_continuous(funvec[1],start,end);  // Is q(x) continuous witih [start,end] ?
    bool br = is_continuous(funvec[2],start,end);  // Is r(x) continuous witih [start,end] ?
    
    bool b = is_defined_positive(funvec[1],start,end);  // Is q(x) defined positive witih [start,end] ? 
    
    return bp && bq && br && b; // If all the conditions are satisfied, returns True, otherwise False
}


//~~~~ Equation Separator ~~~~//

s_diff_eq::s_diff_eq(vector <double> cond, vector <double> (*f)(double))
{
    boundary_c = cond;
    pfunc = f;
    
    // vector {y(a), y'(a), a} 
    init_cond_eq_1 = {boundary_c[0],0,boundary_c[2]};
    
    // vector {y, y', x}
    init_cond_eq_2 = {0,1,boundary_c[2]};
}

double s_diff_eq::y_prime (double x, vector <double> vect)
{
    double dy = vect[1];
    return dy;
}

//this function is equivalent to  u' = p(x)u+q(x)y+r(x)
double s_diff_eq::y_dprime_1 (double x, vector <double> vect)
{
    //v_funct contains [p(x),q(x),r(x)]
    vector <double> v_func = pfunc(x); 
    double du = v_func[0]*vect[1]+v_func[1]*vect[0]+v_func[2];
    return du;
}

//this function is equivalent to  u' = p(x)u+q(x)y
double s_diff_eq::y_dprime_2 (double x, vector <double> vect)
{
    //v_funct contains [p(x),q(x),r(x)]
    vector <double> v_func = pfunc(x); //v_funct contains [p(x),q(x),r(x)]
    double du = v_func[0]*vect[1]+v_func[1]*vect[0];
    return du;
}


//~~~~ RK4 INtegrator ~~~~//

vector<double> vec_sum(vector<double> vec, double sum)
{
	int vsize = vec.size();
    
	for (int i = 0; i < vsize; i++)
    {
		vec[i] += sum;
	}
	return vec;	
}


rk_int :: rk::rk()
{
	float t_step = 0.1;
}


double rk_int :: rk::rk4_step(double (*f)(double,vector<double>)  , double y_i, vector<double> y_n, double t_n)
{  
    double k1 = (*f)(t_n, y_n);
    double k2 =  (*f)(t_n + t_step*0.5, vec_sum(y_n, k1*0.5));
    double k3 =  (*f)(t_n + t_step*0.5, vec_sum(y_n, k2*0.5));
    double k4 =  (*f)(t_n + t_step    , vec_sum(y_n, k3));

	return y_i + t_step*(k1 + 2.*k2 + 2.*k3 + k4)/6.; 
}

vector<double> rk_int :: rk::eval_v_step(vector<double (*)(double,vector<double>)> f_syst, vector<double> y_n, double t_n)
{	
	vector<double> y_np1;
	int vsize = f_syst.size();
    
	for (int i=0; i < vsize; i++)
    {
	  y_np1.push_back(rk4_step(f_syst[i], y_n[i], y_n, t_n));
	}	

	y_np1.push_back(t_n);
	return y_np1;
}

vector<vector<double>> rk_int :: rk::odint_rk4(vector<double (*)(double,vector<double>)> f_syst, vector<double> c_0, double t_f)
{
	vector<vector<double>> syst_states = {c_0};
    
	for (double t = c_0.back()+t_step; t <= t_f+t_step; t += t_step)
    {
		vector<double> curr_state = syst_states.back();	
		vector<double> c_i = vector<double> (curr_state.begin(), curr_state.end() - 1);
		vector<double> next_state = eval_v_step(f_syst, c_i, t);
		syst_states.push_back(next_state);
	}
	return syst_states; 
}

void rk_int :: rk::set_tstep(double n_tstep)
{
	t_step = n_tstep;	
	cout << "Time step set to: " << t_step << endl;
}

void rk_int :: rk::print_tevol(vector<double> c_n)
{
	int vsize = c_n.size();
	for (int i = 0; i < (vsize - 1); i++)
    {
		cout << c_n[i] << ",";
	}
	cout << c_n.back() << endl;
}

//~~~~ Joint Solutions ~~~~//

void tools::joint_sol(vector<vector<double>>solution_1, vector<vector<double>>solution_2, double t_step, vector<double> boundary, ofstream *file)
{ 
    int N = (boundary[3]-boundary[2])/t_step;
    cout << "N_value: " << N << endl;
    double w20 =  (boundary[2] - solution_1[N][0])/solution_2[N][0];

    double W1;
    double W2;
    double x;

    if (file -> is_open())
    {
        for (int i=0; i<=N ; i++)
        {
			
            W1 = solution_1[i][0]+w20*solution_2[i][0];
	        W2 = solution_1[i][1]+w20*solution_2[i][1];
	        x =  solution_1[i][2];
	        *file << W1 << "," << W2 << "," << x << "\n";
        }
    }
}

