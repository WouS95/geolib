function convertRDtoWGS84() {

var x = 195994;
var y = 447683;


var X0 = 155000.00;
var Y0 = 463000.00;
var X_MIN = -7000.00;
var X_MAX = 300000.00;
var Y_MIN = 289000.00;
var Y_MAX = 629000.00;
var PHI_0 = 52.15517440;
var LABDA_0 = 5.38720621;
var PHI_MIN = 50.56846;
var PHI_MAX = 53.62702;
var LABDA_MIN = 2.93875;
var LABDA_MAX = 7.57893;
var res=0;
if((x<X_MIN) || (x>X_MAX))
  { /* x buiten geldigheids gebied */
    res+=-1;
  }
  if((y<Y_MIN) || (y>Y_MAX))
  { /* y buiten geldigheids gebied */
    res+=-2;
  }

  var dx1=(x-X0)*1e-5;
  var dx2=dx1*dx1;
  var dx3=dx2*dx1;
  var dx4=dx3*dx1;
  var dx5=dx4*dx1;
  var dy1=(y-Y0)*1e-5;
  var dy2=dy1*dy1;
  var dy3=dy2*dy1;
  var dy4=dy3*dy1;
  var phi=PHI_0+(3235.65389*dy1-0.24750*dy2-0.06550*dy3+dx1*(-0.00738-0.00012*dy1)+dx2*(-32.58297-0.84978*dy1-0.01709*dy2-0.00039*dy3)+dx4*(0.00530+0.00033*dy1))/3600.00;

  labda=LABDA_0+(0.01199*dy1+0.00022*dy2+dx1*(5260.52916+105.94684*dy1+2.45656*dy2+0.05594*dy3+0.00128*dy4)+dx2*(-0.00022)+dx3*(-0.81885-0.05607*dy1-0.00256*dy2)+dx5*(0.00026))/3600.00;
  //*n=phi;
  //*e=labda;
  //return res;
console.log(x);
console.log(y);
console.log('Error code '+res);
console.log(phi);
console.log(labda);

}

convertRDtoWGS84();
