/*
 * The bounded parameters in 'optiNorms' [0 ; 1]
 * are de-bounded in 'optiParams'
 */

// 2014-3-11 16:43 (Date of file automatic generation)
#ifdef OPTI

void get_real_params_to_opt(double *optiNorms, double *optiParams) 
{
	int i;
      //***************************************************************************************************
      //			TEST OPTIMIZATION 
      //***************************************************************************************************
      // simple test for the optimization

      double test_opti_bounds[1][2]; // {min, max}

      test_opti_bounds[0][0]  = 0.010000;    test_opti_bounds[0][1]  = 0.020000;

	for(i=0; i<1; i++) 
	{ 
		optiParams[i+0] = optiNorms[i+0]*(test_opti_bounds[i][1] - test_opti_bounds[i][0]) + test_opti_bounds[i][0]; 
	} 

}

#endif
