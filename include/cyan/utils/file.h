#ifndef CYAN_FILES_H
#define CYAN_FILES_H

int folder_make( const char* path ) ;

int save_buffer(  unsigned char* filename, const char* extension, 
        unsigned char* buffer, size_t length, 
        unsigned char* path ) ;

int unzip_buffer( unsigned char*  buffer_in,  size_t  length_in,
                  unsigned char** buffer_out, size_t* length_out ) ;

#endif
