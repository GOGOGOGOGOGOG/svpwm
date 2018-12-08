#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PWM_MAX_COUNT 290
#define M_PI 3.14159265358979323846
int i=0;

void svpwm(double Umax,double Vdc,double angle,double* u,double* v,double* w){
        double Ua,Ub;
     double Usalfa,Usbeta;
     char sector;
     double X,Y,Z;
     double t1,t2;
      double ta,tb,tc;
      //  double p1,p2,p3;      
        
        Ua=sin(angle);// sin(0)
        Ub=sin(angle-M_PI*2/3); // -sin(2/3pi)
       // Uc=sin(angle+M_PI*2/3);
        //Clarke
        Usalfa=Ua;
        Usbeta=(2*Ub+Ua)*0.57735026918963; //3^(-1/3)=0.57735026918963
        
        sector=0;  
        if(Usbeta>0)
            sector+=1;
       
        if(-Usbeta+1.732*Usalfa>0)
            sector+=2;
       
        if(Usbeta+1.732*Usalfa<0)
            sector+=4;
 
        X=1.732*Usbeta*PWM_MAX_COUNT;
        Y=(1.732*Usbeta+3*Usalfa)*PWM_MAX_COUNT/2;
        Z=(1.732*Usbeta-3*Usalfa)*PWM_MAX_COUNT/2;
        switch(sector){
            case 1:t1=Z;t2=Y;break;
            case 2:t1=Y;t2=-X;break;
            case 3:t1=-Z;t2=X;break;
            case 4:t1=-X;t2=Z;break;
            case 5:t1=X;t2=-Y;break;
            case 6:t1=-Y;t2=-Z;break;
        }
       
        t1=t1*Umax/Vdc;
        t2=t2*Umax/Vdc;
       
        if(t1+t2>PWM_MAX_COUNT){
            t1=PWM_MAX_COUNT*t1/(t1+t2);
            t2=PWM_MAX_COUNT*t2/(t1+t2);
        }
       
        ta=(PWM_MAX_COUNT-t1-t2)/2;
        tb=ta+t1;
        tc=tb+t2;
       
        switch(sector){
            case 1:*u=tb;*v=ta;*w=tc;break; // section 1
            case 2:*u=ta;*v=tc;*w=tb;break; // section 2
            case 3:*u=ta;*v=tb;*w=tc;break; // section 3
            case 4:*u=tc;*v=tb;*w=ta;break; // section 4
            case 5:*u=tc;*v=ta;*w=tb;break; // section 5
            case 6:*u=tb;*v=tc;*w=ta;break; // section 6
        }
}

int main (){
    double angle=0;
    double u,v,w;
   FILE *fp;  
   fp=fopen("output.txt","w"); 
   if (fp!=NULL){

    while(angle<4*M_PI){
        i++;
        svpwm(310,550,angle,&u,&v,&w);
    
        fprintf(fp,"%d   %d   %d   %d\n",(int)i,(int)u,(int)v,(int)w); //move to the output.txt
        angle+=1*M_PI*0.01; //increase each test angle
    }
    fclose(fp);
    
   }
   else
        printf("open file error\n");

    system("Pause");
}
