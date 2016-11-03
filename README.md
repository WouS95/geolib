# geolib

convert geo coordinates between various systems (WGS84, RD coords (dutch: RijksDriehoek Coordinaten), ...)


# Mathematical background

For reference see the PDF article in the `documentation/` directory:

> Benaderingsformules voor de transformatie tussen RD- en WGS84-kaartcoördinaten
>
> ing. F.H. Schreutelkamp,
>
> Stichting ‘De Koepel’, sterrenwacht
> ‘Sonnenborgh’ te Utrecht, en
>
> ir. G.L. Strang van Hees,
>
> voormalig universitair docent van de
> afdeling Geodesie, TU Delft.
>


# API (C library)

## `xy2ne`: RD to WGS84 conversion

`int xy2ne(double* n, double* e, double x, double y);`


## `ne2xy`: WGS84 to RD conversion

`int ne2xy(double* x, double* y, double n, double e);`


## `nddd_str`: n to Ndd.ddddd string, length of str is at least 10

`char* nddd_str(char* str, double n);`


## `eddd_str`: e to Eddd.ddddd string, length of str is at least 11

`char* eddd_str(char* str, double e);`


## `ddd_str`: n, e to Ndd.ddddd Eddd.ddddd string, length of str is at least 21

`char* ddd_str(char* str, double n, double e);`


## `ndmm_str`: n to Ndd mm.mmm string, length of str is at least 11

`char* ndmm_str(char* str, double n);`


## `edmm_str`: e to Eddd mm.mmm string, length of str is at least 12

`char* edmm_str(char* str, double e);`


## `dmm_str`: n, e to Ndd mm.mmm Eddd mm.mmm string, length of str is at least 23

`char* dmm_str(char* str, double n, double e);`


## `ndms_str`: n to Ndd mm'ss.ss" string, length of str is at least 14

`char* ndms_str(char* str, double n);`


## `edms_str`: e to Eddd mm'ss.ss" string, length of str is at least 15

`char* edms_str(char* str, double e);`


## `dms_str`: n, e to Ndd mm'ss.ss" Eddd mm'ss.ss" string, length of str is at least 29

`char* dms_str(char* str, double n, double e);`


## `xxx_str`: x to X:xxxxxxm, length of str is at least 10

`char* xxx_str(char* str, double x);`


## `yyy_str`: y to Y:yyyyyym, length of str is at least 10

`char* yyy_str(char* str, double y);`


## `xy_str`: x, y to X:xxxxxxm Y:yyyyyym, length of str is at least 20

`char* xy_str(char* str, double x, double y);`


## `fopen_kml`: opens filename and initializes it for kml ponits

`FILE* fopen_kml(char* filename);`


## `fprint_placemark`: print coordinates with name and description in kml file

`int fprint_placemark(FILE* f, double n, double e, char* name, char* description);`


## `fclose_kml`: closes kml file

`int fclose_kml(FILE* f);`



# Design goals / TODO

The intent of this library / code is to develop a geocaching tool for analyzing coordinate-based puzzles where bulk processing / visualizing of coordinates is helpful in finding the desired solutuion.


## Example

Find the geocache location which is positioned on the coordinate which matches the Pyuthagorean triplet `x^2 + y^2 = z^2` where `x`, `y` and `z` are integer.


## TODO

* conversion to JavaScript so this code can run in a web page

* visualize results in Google Maps

* ... unit tests? 

* ... etc.




# Testing

Test output is currently stored in the file PAIRS.TXT.

Test output is oproduced by running `main()` in the geolib.c source file.

