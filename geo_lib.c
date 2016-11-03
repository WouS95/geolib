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
#include "geo_lib.h"

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



int xy2ne(double* n, double* e, double x, double y)
{
  /* eerst boundary check, 
  **  -7000 <= x <= 300000
  ** 289000 <= y <= 629000
  ** buiten geldigheid gebied geeft error -1 voor x, error -2 voor y, error -3 voor beide
  ** de coordinaten worden wel berekend
  */
  int res=0;
  double dx1;
  double dx2;
  double dx3;
  double dx4;
  double dx5;
  double dy1;
  double dy2;
  double dy3;
  double dy4;
  double phi;
  double labda;
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

int ne2xy(double *x, double *y, double n, double e)
{
  /*
  ** eerst boundary check
  ** 50.00 < n < 53.62069
  **  3.00 < e <  7.37
  ** buiten geldigheids gebied error -1 voor e, -2 voor n, -3 voor beide
  ** de coordinaten worden wel berekend
  */
  int res=0;
  double dp1;
  double dp2;
  double dp3;
  double dl1;
  double dl2;
  double dl3;
  double dl4;
  double xx;
  double yy;
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

char* nddd_str(char* str, double n)
{ /* 
  ** double n naar Ndd.ddddd string
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

char* eddd_str(char* str, double e)
{ /* 
  ** double e naar Eddd.ddddd string
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

char* ddd_str(char* str, double n, double e)
{ /* 
  ** double n, e naar Ndd.ddddd Eddd.ddddd string
  ** str is minstens 21 lang
  */
	nddd_str(str, n);
	str[9]=' ';
	eddd_str(str+10, e);
  return str;
}

char* ndmm_str(char* str, double n)
{ /* 
  ** double n naar Ndd mm.mmm string
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
  n*=60000.00;
  n=round(n);
  mm=(int)fmod(n,1000);
  n/=1000;
  n=floor(n);
  m=(int)fmod(n, 60);
  n/=60;
  n=floor(n);
  d=(int)floor(n);
  sprintf(str+1, "%02i %02i.%03i", d, m, mm);
  return str;
}

char* edmm_str(char* str, double e)
{ /* 
  ** double e naar Eddd mm.mmm string
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
  e*=60000.00;
  e=round(e);
  mm=(int)fmod(e,1000);
  e/=1000;
  e=floor(e);
  m=(int)fmod(e, 60);
  e/=60;
  e=floor(e);
  d=(int)floor(e);
  sprintf(str+1, "%03i %02i.%03i", d, m, mm);
  return str;
}

char* dmm_str(char* str, double n, double e)
{ /* 
  ** double n, e naar Ndd mm.mmm Eddd mm.mmm string
  ** str is minstens 23 lang
  */
	ndmm_str(str, n);
	str[10]=' ';
	edmm_str(str+11, e);
  return str;
}

char* ndms_str(char* str, double n)
{ /* 
  ** double n naar Ndd mm'ss.ss" string
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
  n*=360000.00;
  n=round(n);
  ds=fmod(n,100);
  n/=100;
  n=floor(n);
  s=fmod(n,60);
  n/=60;
  n=floor(n);
  m=fmod(n,60);
  n/=60;
  d=(int)floor(n);
  sprintf(str+1, "%02i %02i'%02i.%02i\"", d, m, s, ds);
  return str;
}

char* edms_str(char* str, double e)
{ /* 
  ** double e naar Eddd mm'ss.ss" string
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
  e*=360000.00;
  e=round(e);
  ds=fmod(e,100);
  e/=100;
  e=floor(e);
  s=fmod(e,60);
  e/=60;
  e=floor(e);
  m=fmod(e,60);
  e/=60;
  d=(int)floor(e);
  sprintf(str+1, "%03i %02i'%02i.%02i\"", d, m, s, ds);
  return str;
}

char* dms_str(char* str, double n, double e)
{ /* 
  ** double n, e naar Ndd mm'ss.ss" Eddd mm'ss.ss" string
  ** str is minstens 29 lang
  */
	ndms_str(str, n);
	str[13]=' ';
	edms_str(str+14, e);
  return str;
}

char* xxx_str(char* str, double x)
{ /*
	** x naar X:xxxxxxm
	** str is minstens 10 lang
	*/
	sprintf(str, "X:%06.0fm", round(x));
	return str;
}

char* yyy_str(char* str, double y)
{ /*
	** y naar Y:yyyyyym
	** str is minstens 10 lang
	*/
	sprintf(str, "Y:%06.0fm", round(y));
	return str;
}

char* xy_str(char* str, double x, double y)
{ /*
	** x, y naar X:xxxxxxm Y:yyyyyym
	** str is minstens 20 lang
  */
  xxx_str(str, x);
  str[9]=' ';
  yyy_str(str+10, y);
  return str;
}

FILE* fopen_kml(char* filename)
{
	FILE* f;
	f=fopen(filename,"w");
  if(f==NULL)
  {
  	return f;
  }
  fprintf(f, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
             "<kml xmlns=\"http://earth.google.com/kml/2.2\">\n"
             "  <Document>\n");
  return f;
}

int fprint_placemark(FILE* f, double n, double e, char* name, char* description)
{
  return fprintf(f, "    <Placemark>\n"
                    "      <name>%s</name>\n"
                    "      <description>%s</description>\n"
                    "      <Point>\n"
                    "        <coordinates>\n"
                    "          %f,%f\n"
                    "        </coordinates>\n"
                    "      </Point>\n"
                    "    </Placemark>\n", name, description, e, n);
}

int fclose_kml(FILE* f)
{
  fprintf(f, "</Document>\n</kml>\n");
	return fclose(f);
}


