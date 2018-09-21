#ifndef HSLAPixel_H_
#define HSLAPixel_H_

namespace cs221util {

class HSLAPixel {

public:

	HSLAPixel();
	HSLAPixel(double hue, double sat, double lum);
	HSLAPixel(double hue, double sat, double lum, double alp);

	double h;
	double s;
	double l;
	double a;
 
 };
 
}

#endif