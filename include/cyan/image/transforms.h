#ifndef TRANSFORMS_H
#define TRANSFORMS_H

typedef struct s_complex_polar_t{
	double power;
	double phase;
}complex_polar_t;

typedef struct s_complex_cart_t{
	double real;
	double im;
}complex_cart_t;

static complex_polar_t * FFT_1D( complex_polar_t *, complex_polar_t *, int);
static complex_polar_t * FFT_1D_reverse( complex_polar_t * fourier_polar, int n);

complex_cart_t * FFT_1D_cart_to_cart( complex_cart_t * f, int n);
complex_cart_t * FFT_1D_reverse_cart_to_cart( complex_cart_t * fft, int n);

complex_cart_t ** FFT_2D(complex_cart_t ** array_cart, int n, int m);
complex_cart_t ** FFT_2D_reverse(complex_cart_t ** ft_array_cart, int n, int m);

image_t * FT_image_Y(image_t * image, complex_cart_t ** (*transform)(complex_cart_t **, int, int) );

complex_cart_t ** image_to_cart(image_t * image, complex_cart_t (*xyz_to_cart)( double, double, double) );
image_t * cart_to_image(complex_cart_t ** array, int n, int m );

complex_cart_t Y_to_cart(double X, double Y, double Z);

complex_polar_t * cart_array_to_polar( complex_cart_t * cart_array, int n);
complex_cart_t * polar_array_to_cart( complex_polar_t * polar_array, int n);

void * unitary_ft_polar(complex_polar_t * polar_array, int N);
void * unitary_ft_cart(complex_cart_t * cart_array, int N);

image_t * color2grey(image_t *);

float norm_2_sq_4_f( float, float , float , float );
float dot_product_4_f(	float, float, float, float, float, float, float, float );

void * assign_complex_polar( complex_polar_t *, complex_polar_t);

complex_cart_t * add_complex_cart(complex_cart_t * result, complex_cart_t z1, complex_cart_t z2);
complex_cart_t * substract_complex_cart(complex_cart_t * result, complex_cart_t z1, complex_cart_t z2);	

void * flip_cart(complex_cart_t * z);
void * flip_polar(complex_polar_t * z);
	
double mult_complex_polar( complex_polar_t *, complex_polar_t, complex_polar_t);
void * mult_complex_cart_t( complex_cart_t *, complex_cart_t, complex_cart_t);

double norm_complex_cart( complex_cart_t );
double phase_complex_cart( complex_cart_t);

void * polar_to_cart( complex_cart_t *, complex_polar_t);
void * cart_to_polar( complex_polar_t *, complex_cart_t);
#endif
