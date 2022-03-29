/**************************************************/
/*                                                */
/*  Lab 1 Starter file                            */
/*                                                */
/*  Name: Navid Najarali Vadsariya                */
/*  Student number: 136-884-186                   */
/*                                                */
/**************************************************/

/* remember to code these in an iterative only manner*/

unsigned int factorial (unsigned int n){
   unsigned int number = 1;
    for (unsigned int i = 2 ; i <= n ; i++){
        number = number * i;
    }
    return number;
}

double power (double base, unsigned int n){
    double number = 1.0;
    for (int i = 0 ; i < n ; i++){
        number = number * base;
    }
    return number;
}
unsigned int fibonacci (unsigned int n){
	 int n1 = 0;                         
     int n2 = 1;                         
     unsigned int number = n;            

    if(n >= 2){                          
        for(unsigned int i=2;i<=n;i++)   
        {
            number = n1 + n2;            
            n1 = n2;                     
            n2 = number;                 
        }
    }
    else {
        return number;                   
    }
    return number;                       
}