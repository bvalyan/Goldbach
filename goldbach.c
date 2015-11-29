#include <stdio.h>
#include <stdlib.h>

/*
THIS CODE IS MY OWN WORK. IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS OR MATERIALS OTHER THAN THIS SEMESTER'S COURSE MATERIALS. Brandon Valyan-Clark
*/

typedef struct _seg{
	int bits[256];
	struct _seg *next, *prev;
} seg;

seg *head, *pt;
int numbers;
int numSegs;
int primecount;

seg* whichseg (int j){
	int segAmount = 0;	
	segAmount = (j-2)/16384;
	int count = 0;
	pt = head;
	while (count < segAmount && pt->next != NULL){
		pt = pt->next;
		count += 1;
}
	return pt;
} 

int whichint (int j){
	j = ((j-2)%16384)/64;

	return j;
}

int whichbit(int j){
	int i = (j-3)/2;
	int bitNum = i%32;

	return bitNum;	
} 

void clearAll(){
	seg *p = head;
	int k = 0;
	while(p != NULL){
		for( k = 0; k< 256; k++){
		p->bits[k] = 0;
		}
		p = p->next;
		}
	}

void setBit(int j) {
   seg* segNum =  whichseg(j);
   int rownum = whichint(j);
   int posinrow = whichbit(j);
   
   seg *p = segNum;
   unsigned int flag = 1;
   flag = flag << posinrow;
   p->bits[rownum] = p->bits[rownum] | flag;
}

int testBitIs0( int j ) {

   seg* segNum =  whichseg(j);
   int rownum = whichint(j);
   int posinrow = whichbit(j);

 
   int a = 0;
   seg *p = segNum;
   unsigned int flag = 1;
   flag = flag << posinrow;
   int r = p->bits[rownum] & flag; 

   if ( r == 0 )
      return 1;        
   else
      return 0;
}


int countPrimes( int N ) {
   // Loops to count primes for the Sieve
   int count, i;

   count = 1;

   for ( i = 3; i <= N; i = i+2 )
      if ( testBitIs0(i) )
         count++;

   return count;
}

void sieveOfE( int N )
{
   //Loops through marking multiples as composite, leaving only prime numbers
   int i, j, k;
   

   clearAll();
       

   k = 3;   

   while ( k <= N )   {
      for ( i = k; i <= N; i = i+2)
          if ( testBitIs0(i) )
             break;             

      for ( j = 3*i; j <= N; j = j + 2*i )
	  	setBit(j);

      k = i+2;    
   }
}

int checkLower(seg* p, int integer, int bita){
   //checks from 3  up, incrementing by bit.
   int a = 0;
   seg* segPoint1 = p;
   unsigned int flag = 1;
   flag = flag << bita;
   int r = segPoint1->bits[integer] & flag; 

   if ( r == 0 )
      return 1;        
   else
      return 0;
			
}

int checkHigher(seg* p, int integer, int bit){
   //checks from k-i down, incrementing by bit
   int a = 0;
   seg* segPoint2 = p;
   unsigned int flag = 1;
   flag = flag << bit;
   int r = segPoint2->bits[integer] & flag; 

   if ( r == 0 )
      return 1;        
   else
      return 0;
			
}
		

void goldbach(int n){
// finds the seg, int and bit for 3 and k-3 and passes them to methods that increment up and down in 2 different methods
int numCount = 0;
int k = 3;
int ktwo = n-3;
int goldCount = 0;
int targetNum1 = 0;
int targetNum2 = 0;
///////seg int and bit for 3
seg* segNum2 = whichseg(k);
int kintone = whichint(k);
int bit1 = whichbit(k);
///////seg in and bit for k-3
seg* segNum3 = whichseg(ktwo);
int kinttwo = whichint(ktwo);
int bit2 = whichbit(ktwo);

while (k <= n/2){
		
	if(checkLower(segNum2, kintone, bit1) && checkHigher(segNum3, kinttwo, bit2) == 1){
		goldCount += 1;
		targetNum1 = k;
		targetNum2 = ktwo;
		}

	//printf("%d %d\n", k, ktwo);

	//////////////////////////////////LOWER END LOGIC
	if(bit1 != 31){
		bit1 +=1;}
		
	else{
	bit1 = 0;
	kintone += 1;}

	if(kintone > 255 && segNum2->next !=NULL){
	kintone = 0;
	segNum2 = segNum2->next;}
	/////////////////////////////////////////////////
	//////////////////////////////////UPPER END LOGIC
	if(bit2 != 0){
		bit2 -=1;}

	else{
	bit2 = 31;
	kinttwo -= 1;}	
	
   	if( kinttwo < 0 && segNum3->prev != NULL){
	kinttwo = 255;
	segNum3 = segNum3->prev;
	}	
	/////////////////////////////////////////////////


	k += 2;
	ktwo -=2;

}
printf("\nThe last Goldbach decomposition is: %d + %d \n",  targetNum1, targetNum2 );
printf("The amount of decompositions is: %d \n", goldCount);	
	

}

int main(int argc, char const *argv[])
{

int i;

int N = atoi(argv[1]);

int nodesAlloc = ((N-2)/16384) + 2;

head= (  seg * ) malloc(sizeof(seg));
	pt=head;
	for (i=1;i<nodesAlloc;i++) { 
		pt->next = (  seg *) malloc(sizeof (seg)); //allocate forward nodes
		pt->prev = pt; 				   //allocate backward nodes
		pt=pt->next;
		}

	printf("Allocated %d nodes\n",i);
	
sieveOfE(N);
primecount = countPrimes(N)-1;
printf("Amount of primes = %d \n", primecount);

while(numbers != EOF){
printf("Enter your numbers or EOF:");
// if an odd integer is entered or eof is detected exit
if ( scanf("%d", &numbers) == EOF || numbers % 2 != 0 )
     {
        break;
     }
else{goldbach(numbers);}
}

   return 0;
}
