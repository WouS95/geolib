/*
**
** geo_lib
** copy left 2016 Hans Wessels
** This code is placed in public domain by Hans Wessels
**
** library for conversion of coordinate systems and pretty printing of coordinates
**
*/

/*
** conversion form WGS84 coordinates to dutch Rijksdriehoekscoordinaten
** based on "Transformatieformules.pdf" by
** ing. F.H. Schreutelkamp, Stichting ‘De Koepel’, sterrenwacht ‘Sonnenborgh’ te Utrecht
** ir. G.L. Strang van Hees, voormalig universitair docent van de afdeling Geodesie, TU Delft.
**/

#include <stdio.h>
#include <math.h>

int xy2ne(float* n, float* e, float x, float y); /* RD to WGS84 conversion */
int ne2xy(float *x, float *y, float n, float e); /* WGS84 to RD conversion */
char* nddd_str(char* str, float n);

#define X0 155000.00
#define Y0 463000.00
#define X_MIN -7000.00
#define X_MAX 300000.00
#define Y_MIN 289000.00
#define Y_MAX 629000.00
#define PHI_0 52.15517440
#define LABDA_0 5.38720621
#define PHI_MIN 50.56846
#define PHI_MAX 53.62702
#define LABDA_MIN 2.93875
#define LABDA_MAX 7.57893

int xy2ne(float* n, float* e, float x, float y)
{
  /* eerst boundary check, 
  **  -7000 <= x <= 300000
  ** 289000 <= y <= 629000
  ** buiten geldigheid gebied geeft error -1 voor x, error -2 voor y, error -3 voor beide
  ** de coordinaten worden wel berekend
  */
  int res=0;
  float dx1;
  float dx2;
  float dx3;
  float dx4;
  float dx5;
  float dy1;
  float dy2;
  float dy3;
  float dy4;
  float phi;
  float labda;
  if((x<X_MIN) || (x>X_MAX))
  { /* x buiten geldigheids gebied */
    res+=-1;
  }
  if((y<Y_MIN) || (y>Y_MAX))
  { /* y buiten geldigheids gebied */
    res+=-2;
  }
  dx1=(x-X0)*1e-5;
  dx2=dx1*dx1;
  dx3=dx2*dx1;
  dx4=dx3*dx1;
  dx5=dx4*dx1;
  dy1=(y-Y0)*1e-5;
  dy2=dy1*dy1;
  dy3=dy2*dy1;
  dy4=dy3*dy1;
  phi=PHI_0
      +(3235.65389*dy1-0.24750*dy2-0.06550*dy3
      +dx1*(-0.00738-0.00012*dy1)
      +dx2*(-32.58297-0.84978*dy1-0.01709*dy2-0.00039*dy3)
      +dx4*(0.00530+0.00033*dy1))/3600.00;
  labda=LABDA_0
        +(0.01199*dy1+0.00022*dy2
        +dx1*(5260.52916+105.94684*dy1+2.45656*dy2+0.05594*dy3+0.00128*dy4)
        +dx2*(-0.00022)
        +dx3*(-0.81885-0.05607*dy1-0.00256*dy2)
        +dx5*(0.00026))/3600.00;
  *n=phi;
  *e=labda;
  return res;
}

int ne2xy(float *x, float *y, float n, float e)
{
  /*
  ** eerst boundary check
  ** 50.00 < n < 53.62069
  **  3.00 < e <  7.37
  ** buiten geldigheids gebied error -1 voor e, -2 voor n, -3 voor beide
  ** de coordinaten worden wel berekend
  */
  int res=0;
  float dp1;
  float dp2;
  float dp3;
  float dl1;
  float dl2;
  float dl3;
  float dl4;
  float xx;
  float yy;
  if((n<PHI_MIN) || (n>PHI_MAX))
  { /* noord bound error */
    res+=-2;
  }
  if((e<LABDA_MIN) || (e>LABDA_MAX))
  { /* east bound error */
    res+=-1;
  }
  dp1=0.3600*(n-PHI_0);
  dp2=dp1*dp1;
  dp3=dp2*dp1;
  dl1=0.3600*(e-LABDA_0);
  dl2=dl1*dl1;
  dl3=dl2*dl1;
  dl4=dl3*dl1;
  xx=X0
     +(190094.945*dl1-0.008*dl2-32.391*dl3)
     +dp1*(-0.705-11832.228*dl1-0.608*dl3)
     +dp2*(-114.221*dl1+0.148*dl3)
     +dp3*(-2.340*dl1);
  yy=Y0
     +(0.433*dl1+3638.893*dl2+0.092*dl4)
     +dp1*(309056.544-0.032*dl1-157.984*dl2-0.054*dl4)
     +dp2*(73.077-6.439*dl2)
     +dp3*(59.788);
  *x=xx;
  *y=yy;
  return res;
}

char* nddd_str(char* str, float n)
{ /* 
  ** float n naar Ndd.ddddd string
  ** str is minstens 10 lang
  */
  if(n>=0)
  {
    str[0]='N';
  }
  else
  {
    str[0]='S';
    n=-n;
  }
  sprintf(str+1, "%08.5f", n);
  return str;
}

char* eddd_str(char* str, float e)
{ /* 
  ** float e naar Eddd.ddddd string
  ** str is minstens 11 lang
  */
  if(e>=0)
  {
    str[0]='E';
  }
  else
  {
    str[0]='W';
    e=-e;
  }
  sprintf(str+1, "%09.5f", e);
  return str;
}

char* ddd_str(char* str, float n, float e)
{ /* 
  ** float n, e naar Ndd.ddddd Eddd.ddddd string
  ** str is minstens 21 lang
  */
	nddd_str(str, n);
	str[9]=' ';
	eddd_str(str+10, e);
  return str;
}

char* ndmm_str(char* str, float n)
{ /* 
  ** float n naar Ndd mm.mmm string
  ** str is minstens 11 lang
  */
  int d;
  int m;
  int mm;
  if(n>=0)
  {
    str[0]='N';
  }
  else
  {
    str[0]='S';
    n=-n;
  }
  d=(int)floor(n);
  n-=floor(n);
  n*=60.00;
  m=(int)floor(n);
  n-=floor(n);
  n*=1000.00;
  mm=(int)round(n);
  sprintf(str+1, "%02i %02i.%03i", d, m, mm);
  return str;
}

char* edmm_str(char* str, float e)
{ /* 
  ** float e naar Eddd mm.mmm string
  ** str is minstens 12 lang
  */
  int d;
  int m;
  int mm;
  if(e>=0)
  {
    str[0]='E';
  }
  else
  {
    str[0]='W';
    e=-e;
  }
  d=(int)floor(e);
  e-=floor(e);
  e*=60.00;
  m=(int)floor(e);
  e-=floor(e);
  e*=1000.00;
  mm=(int)round(e);
  sprintf(str+1, "%03i %02i.%03i", d, m, mm);
  return str;
}

char* dmm_str(char* str, float n, float e)
{ /* 
  ** float n, e naar Ndd mm.mmm Eddd mm.mmm string
  ** str is minstens 23 lang
  */
	ndmm_str(str, n);
	str[10]=' ';
	edmm_str(str+11, e);
  return str;
}

char* ndms_str(char* str, float n)
{ /* 
  ** float n naar Ndd mm'ss.ss" string
  ** str is minstens 14 lang
  */
  int d;
  int m;
  int s;
  int ds;
  if(n>=0)
  {
    str[0]='N';
  }
  else
  {
    str[0]='S';
    n=-n;
  }
  d=(int)floor(n);
  n-=floor(n);
  n*=60.00;
  m=(int)floor(n);
  n-=floor(n);
  n*=60.00;
  s=(int)floor(n);
  n-=floor(n);
  n*=100;
  ds=(int)round(n);
  sprintf(str+1, "%02i %02i'%02i.%02i\"", d, m, s, ds);
  return str;
}

char* edms_str(char* str, float e)
{ /* 
  ** float e naar Eddd mm'ss.ss" string
  ** str is minstens 15 lang
  */
  int d;
  int m;
  int s;
  int ds;
  if(e>=0)
  {
    str[0]='E';
  }
  else
  {
    str[0]='W';
    e=-e;
  }
  d=(int)floor(e);
  e-=floor(e);
  e*=60.00;
  m=(int)floor(e);
  e-=floor(e);
  e*=60.00;
  s=(int)floor(e);
  e-=floor(e);
  e*=100;
  ds=(int)round(e);
  sprintf(str+1, "%03i %02i'%02i.%02i\"", d, m, s, ds);
  return str;
}

char* dms_str(char* str, float n, float e)
{ /* 
  ** float n, e naar Ndd mm'ss.ss" Eddd mm'ss.ss" string
  ** str is minstens 29 lang
  */
	ndms_str(str, n);
	str[13]=' ';
	edms_str(str+14, e);
  return str;
}

char* xxx_str(char* str, float x)
{ /*
	** x naar X:xxxxxxm
	** str is minstens 10 lang
	*/
	
	sprintf(str, "X:%06.0fm", round(x));
	return str;
}

char* yyy_str(char* str, float y)
{ /*
	** y naar Y:yyyyyym
	** str is minstens 10 lang
	*/
	
	sprintf(str, "Y:%06.0fm", round(y));
	return str;
}

char* xy_str(char* str, float x, float y)
{ /*
	** x, y naar X=xxxxxx m Y=yyyyyy m
	** str is minstens 20 lang
  */
  xxx_str(str, x);
  str[9]=' ';
  yyy_str(str+10, y);
  return str;
}

float pairs[]={
  141000.00, 629000.00,
  100000.00, 600000.00,
   80000.00, 500000.00,
   -7000.00, 392000.00,
       0.00, 392000.00,
   -7000.00, 336000.00,
       0.00, 336000.00,
  101000.00, 336000.00,
  161000.00, 289000.00,
  161000.00, 289000.00,
  219000.00, 289000.00,
  219000.00, 290000.00,
  300000.00, 451000.00,
  289999.00, 451000.00,
  300000.00, 614000.00,
  289999.00, 614000.00,
  259000.00, 629000.00,
  289985.00, 628000.00,
  289986.00, 628000.00,
  289987.00, 628000.00,
  289988.00, 628000.00,
  289989.00, 628000.00,
  289990.00, 628000.00,
  289991.00, 628000.00,
  289992.00, 628000.00,
  289993.00, 628000.00,
  289994.00, 628000.00,
  289995.00, 628000.00,
  289996.00, 628000.00,
  289997.00, 628000.00,
  289998.00, 628000.00,
  289999.00, 628000.00,
  289999.00, 627999.00,
  289999.00, 627998.00,
  289999.00, 627997.00,
  289999.00, 627996.00,
  289999.00, 627995.00,
  289999.00, 627994.00,
  289999.00, 627993.00,
  289999.00, 627992.00,
  289999.00, 627991.00,
  289999.00, 627990.00,
  289999.00, 627989.00,
  289999.00, 627988.00,
  289999.00, 627987.00,
  289999.00, 627986.00,
  289999.00, 627985.00,
  289999.00, 627984.00,
   -7000.00, 629000.00,
   -7000.00, 289000.00,
  300000.00, 289000.00,
  300000.00, 629000.00};

int main(void)
{
	int i;
	float *p=pairs;
	float n;
	float e;
	float x;
	float y;
	char string[128];
	char string2[128];
	FILE* f;
	f=fopen("pairs.txt","w");
	if(f==NULL)
	{
		printf("File open error!\n");
		return -1;
	}
	n=52.123456789;
	e=6.23456789;
	ne2xy(&x, &y, n, e);
	printf("%s\n", ddd_str(string, n, e));
	printf("%s\n", ddd_str(string, -n, -e));
	printf("%s\n", dmm_str(string, n, e));
	printf("%s\n", dmm_str(string, -n, -e));
	printf("%s\n", dms_str(string, n, e));
	printf("%s\n", dms_str(string, -n, -e));
	printf("%s\n", xy_str(string, x, y));
	for(i=0; i<52; i++)
	{
		x=*p++;
		y=*p++;
		xy2ne(&n, &e, x, y);
		fprintf(f, "%s = %s\n", xy_str(string, x, y), dmm_str(string2, n, e));
	}
	fclose(f);
	return 0;
}