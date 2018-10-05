#include <stdio.h>
#include <image/image.h>
#include <color/color.h>
#include <io/image_io.h>


int main( int argc, char** argv, char* envv ) {

    int result ;
    image_t* image ;
    
    if ( argc != 3 ) {
        fprintf(stderr, "Usage : %s input_file output_file.ppm \n", argv[0] ) ;
        return -1 ;
    }

    image = image_load_ppm( argv[1], &result ) ;
    if ( image == NULL ) {
        fprintf(stderr, "Image could not be loaded\n") ;
        return -2 ;
    }

    image_save_ppm( image, argv[2]) ;

    image_free( image) ;

    return 0 ;
}
