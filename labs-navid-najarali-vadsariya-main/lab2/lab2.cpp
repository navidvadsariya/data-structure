/**************************************************/
/*                                                */
/*  Lab 2 Starter file                            */
/*                                                */
/*  Name:   Navid Najarali Vadsariya              */
/*  Student number: 136-884-186                   */
/*                                                */
/**************************************************/

/* remember to code these in an iterative only manner*/


unsigned int factorial (unsigned int n){
    unsigned int rc = 1;
    if(n > 1){
        rc = n * factorial(n - 1);
    }
        return rc; 
}

double power (double base, unsigned int n){
    if(n != 0){
        return (base * power(base,(n - 1)));
    }
    else{
        return 1;
    } 
}
unsigned int fibonacci (unsigned int n){
	if(n > 1){
         return (fibonacci(n - 1) + fibonacci(n - 2));
    }
    else{
        return n;
    }
}
