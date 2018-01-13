#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#define  ACLR 90
#define  MAX 100
#define  Np  10e-10
#define  Ps  0.2
#define  IsameFreinterfere 10
#define  file1  "LTE"
//#define  file2  "WCDMA"

int main(int argc, char *argv[])
{
  
   srand(time(NULL));
  
   double Bvictim[MAX]; 
   double ACIR[MAX]; 
   double ACS[MAX],ACS1=0;
   double ACLR[MAX];
   double Baggressor[MAX];
   double ACLReff[MAX];  
      int  i,j;
   double s[MAX];
   double min,Max;
   double optACIR,toptACIR,optPower,toptPower,tmp=0;
   double avg,avgPower;
   double *mid,*top;
   double SINRvim[MAX];
   double ItoVimUE[MAX],ItoVimsys[MAX], NBIOTUE_BW[MAX];
   
   
   
   FILE *out1=fopen(file1,"w" );
   //FILE *out2=fopen(file2,"w" ); 
   for(i=0;i<MAX;i++)
   {
        Baggressor[i]=(rand()%2000000)+1;
        //printf("Baggressor[%d]=%lf\n",i,Baggressor[i]);
        ACS[i]=50;
    }    
    ACS1=ACS[0];
    for(i=0;i<MAX;i++)
   { 
      ACLR[i]=(rand()%100)+1;
     // printf("ACLR[%d]=%lf\n",i,ACLR[i]);
    } 
    printf("\n\n");
    
   //WCDMA
/* for(i=0;i<MAX;i++)
    {
       Bvictim[i]=(double)(i+915);
      }
   */
   
         
   /*    
   for(i=1;i<=MAX;i++)
   {
       Bvictim[i]=(double)(i+890);
	}
    */         
  // printf("===================排序前===================\n"); 
    
   for(i=0;i<MAX;i++)
   {  
        Bvictim[i]=(rand()%200000)+1;                      
    }
             
   for(i=0;i<MAX;i++)
   {     
        s[i]=10*(log10(Bvictim[i]/Baggressor[i]));           
        //printf("%lf\n",s[i]);              
        ACLReff[i]=ACLR[i]-s[i];            
        //printf("ACLReff[%3d]=%lf dB\n",i,ACLReff[i]);    
    }    
    
    for(i=MAX;i>=0;i--)
    {
        for(j=0;j<i;j++)
        {
            if(ACLReff[j]<ACLReff[j+1])
            { 
                tmp=ACLReff[j+1];                     
                ACLReff[j+1]=ACLReff[j];
                ACLReff[j]=tmp;                                  
                 // printf("\n");
            }                
        }
    }
     printf("\n\n");
     
    //printf("=====================ACLReff排序後======================\n");  
       
    for(i=0;i<MAX;i++)
    {
         //printf("ACLReff[%d]=%lf\n",i,ACLReff[i]);
    } 
      
     printf("\n\n");
     
    
	double sum1=0;
    for(i=0;i<MAX;i++)
    {
	    sum1=sum1+ACLReff[i];
	    avg=sum1/MAX;

     } 
     
    printf("平均ACLReff=%lf\n",avg); 
    
   for(i=0;i<MAX;i++) 
   {  
   
        if(ACLReff[i]<=ACS[i])
        {  
            ACIR[i]=(ACS[i]*ACLReff[i])/(ACLReff[i]+ACS[i]);
            //printf("ACIR[%3d]=%lf KdB\n",i,ACIR[i]);
           
               fprintf(out1,"%lf\n",ACIR[i]);
              //fprintf(out2,"%lf\n",ACIR[i]);
              //printf("ACIR[%d]=%lf\n",i,ACIR[i]);        
        }
        else 
        {
            ACIR[i]=ACLReff[i]; 
            //printf("ACIR[%3d]=%lf KdB\n",i,ACIR[i]);
            
               fprintf(out1,"%lf\n",ACIR[i]);      
            //fprintf(out2,"%lf\n",ACIR[i]);
            //printf("ACIR[%d]=%lf\n",i,ACIR[i]);
        }
    }
	printf("\n\n");
    
    min=Max=ACIR[0];
    for(i=0;i<MAX;i++)      
    {	 
        if(min>ACIR[i])     
            min=ACIR[i];    
                                    
        if(Max<ACIR[i])     
            Max=ACIR[i];               
    }
      
       printf("min ACIR=%lf\n",min);  
       printf("Max ACIR=%lf\n",Max);  
       
    double sum=0;  
    for(i=0;i<MAX;i++)      
    { 
       sum=sum+ACIR[i];
       avg=sum/MAX;          
    } 
    
	printf("平均ACIR=%lf\n",avg);

	/*   
    if(avg<ACS1)
	{  
       avgPower=(avg* ACS1)/(ACS1-avg);
       //avgPower=avgPower/MAX;
       printf("平均power=%lf dB\n",avgPower);   
     }
    else
	{
		avgPower=(avg* ACS1)/(-ACS1+avg);
		printf("平均power=%lf dB\n",avgPower); 
		
	 } 
     */
     
     
     /*
    printf("=====================ACIR排序後======================\n");  
      
    for(i=MAX;i>=0;i--)
    {
        for(j=0;j<i;j++)
        {
            if(ACIR[j]<ACIR[j+1])
            { 
                tmp=ACIR[j+1];                     
                ACIR[j+1]=ACIR[j];
                ACIR[j]=tmp;                                  
                 // printf("\n");
            }                
        }
    }
    for(i=0;i<MAX;i++)
    {
         printf("ACIR[%d]=%lf\n",i,ACIR[i]);
    }           
    mid=&(ACIR[MAX/2]);
    optACIR=*mid;   
    top=&(ACIR[0]);
    toptACIR=*top;
    */
    
    
     /*
    for(i=0;i<MAX;i++)      
    {
        if(abs(avg-ACIR[i])<=0.01)   
           optACIR=ACIR[i];
    }
    printf("中位數ACIR=%lf\n",optACIR);        
    optPower=(optACIR*ACS1)/(ACS1-optACIR);
      //optACIR=optACIR/MAX;
    printf("中位數power=%lf dB\n",optPower);        
    */     
    /*    
    printf("=================================================\n\n");                    
    printf("最大ACIR=%lf\n",toptACIR);        
    toptPower=(toptACIR*ACS1)/(-ACS1+toptACIR);
      //optACIR=optACIR/MAX;
    printf("最大power=%lf dB\n",toptPower);    
     

        
    printf("=================================================\n");                
      double Power=0;      
      Power=(avgPower+optPower)/2;
      printf("最佳Power=%lf\n",Power);                                           
    printf("=================================================\n\n");           
     double Lo;     
     Lo=abs(Power-avgPower)/2;       
     printf("最佳範圍 %lf~%lf dB\n",Power-Lo,Power+Lo);      
       */
      
            
    /*        
    if(avgPower<Power)        
        printf("最佳範圍 %lf~%lf dB\n",avgPower,Power);      
    else        
        printf("最佳範圍 %lf~%lf dB\n",Power,avgPower);     
            
     
	 double K1;            
      K1=(optPower-avgPower)/avgPower;      
      printf("調整前誤差=%lf\n",K1); 
	                    
     double K;            
     K=(avgPower-Power)/Power;      
     printf("調整後誤差=%lf\n",K);      
     */          
	
	
	/*
	double Nvim_User[MAX];
	for(i=0;i<MAX;i++)
    {
      NBIOTUE_BW[i]=(rand()%200000)+1;
      printf("NBIOTUE_BW[%2d]=%lfk\n",i,NBIOTUE_BW[i]);
      printf("Baggressor[%d]=%lfk\n",i,Baggressor[i]);
      
      Nvim_User[MAX]= NBIOTUE_BW[i]/Baggressor[i];
      printf("Nvim_User[%2d]=%lf\n",i,Nvim_User[i]);
	}  
	*/
	
	double DOACIR[MAX],Av_SINRvim=0,Tot_SINRvim[MAX];
	for(i=0;i<MAX;i++)
	{
	    DOACIR[i]=1/(ACIR[i]);
	    //printf("DOACIR[%2d]=%lf\n",i,DOACIR[i]);
    }
    for(i=0;i<MAX;i++)
	{
	    ItoVimsys[i]= 50;
	    //printf("ItoVimsys[%2d]=%lf\n",i,ItoVimsys[i]);
    }
    printf("--------------------------------------------");
	for(i=0;i<MAX;i++)
	{
	   ItoVimUE[i]= (ItoVimsys[i]/MAX)*(DOACIR[i]);
	   printf("ItoVimUE[%2d]=%lf\n",i,ItoVimUE[i]);
    }
    printf("--------------------------------------------\n");
	for(i=0;i<MAX;i++)
	{
	   SINRvim[i]= Ps/(ItoVimUE[i] + IsameFreinterfere + Np);
	   printf("SINRvim[%2d]=%lf\n",i,SINRvim[i]);
    }
    printf("--------------------------------------------\n");
   	/* 
	for(i=0;i<MAX;i++)
	{
	  Tot_SINRvim[MAX]=0;
    }
    printf("--------------------------------------------\n");
	for(i=0;i<MAX;i++)
	{
	   Tot_SINRvim[MAX]+= SINRvim[i];
	   Av_SINRvim=Tot_SINRvim[MAX]/MAX;
    }
	printf("Av_SINRvim=%lf\n",Av_SINRvim);
	*/
	
	double C[MAX];
	for(i=0;i<MAX;i++)
	{
	  C[MAX]=0;
    }
	for(i=0;i<MAX;i++)
	{   
	   C[i]=(180)*(log2(1+SINRvim[i]));
	   printf("C[%2d]=%lf\n",i,C[i]);
     }  

    printf("--------------------------------------------\n");
    double Average_C,Tot_C=0;
    for(i=0;i<MAX;i++)
	{
	  Average_C=0;
    }
	for(i=0;i<MAX;i++)
	{
	   Tot_C+= C[i];
	   Average_C=Tot_C/MAX;
    }
	printf("Average_C=%lfk (bps)\n",Average_C);
	
	
	
	
	
		
	 printf("\n\n");		   
			                  
     fclose(out1);
     //fclose(out2);
              
    system("PAUSE");	
    return 0;
}



































































































































































































































































































































