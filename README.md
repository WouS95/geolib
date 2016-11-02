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

`int xy2ne(float* n, float* e, float x, float y);`


## `ne2xy`: WGS84 to RD conversion

`int ne2xy(float *x, float *y, float n, float e);`




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

