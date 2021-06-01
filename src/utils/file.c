#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <zip.h>

#include <cyan/utils/file.h>
#include <cyan/common/error.h>

int folder_make( const char* path ) {
    char tmp[PATH_MAX];
    char *p = NULL;
    size_t len;
    struct stat st = {0};
    snprintf(tmp, sizeof(tmp),"%s",path);
    len = strlen(tmp);
    if(tmp[len - 1] == '/')
        tmp[len - 1] = 0;
    for(p = tmp + 1; *p; p++)
        if(*p == '/') {
            *p = 0;
            if (stat(tmp, &st) == -1 )
            if (mkdir(tmp, 0755)) {
                fprintf(stderr,"[folder_make] Cannot create folder %s\n", tmp);
                return ERR_NOPE ;
            }
            *p = '/';
        }
    if (stat(tmp, &st) == -1 )
    if (mkdir(tmp, 0755)) {
                fprintf(stderr,"[folder_make] Cannot create folder %s\n", tmp);
                return ERR_NOPE ;
    }
    return ERR_OK ;
}

int save_buffer(  unsigned char* filename, const char* extension, 
        unsigned char* buffer, size_t length, 
        unsigned char* path ) {

    unsigned char filepath[PATH_MAX] ;
    FILE* fd ;
    snprintf( filepath, sizeof(filepath),"%s/%s.%s", path, filename, extension );
    fd = fopen(filepath,"w+") ;
    fwrite( buffer, 1, length, fd ) ;
    fclose(fd) ;
    return ERR_OK ;

}

int unzip_buffer( unsigned char*  buffer_in,  size_t  length_in,
                  unsigned char** buffer_out, size_t* length_out ) {

    zip_error_t error;
    zip_source_t *src;
    zip_t *za;
    zip_file_t * zipfile ;
    struct zip_stat zipstat ;
    int size ;
    zip_error_init(&error);
    if ((src = zip_source_buffer_create(buffer_in, length_in, 1, &error)) == NULL) {
        fprintf(stderr, "can't create source: %s\n", zip_error_strerror(&error));
        zip_error_fini(&error);
        return ERR_NOPE;
    }
    if ((za = zip_open_from_source(src, 0, &error)) == NULL) {
        fprintf(stderr, "can't open zip from source: %s\n", zip_error_strerror(&error));
        zip_source_free(src);
        zip_error_fini(&error);
        return ERR_NOPE;
    }
    if ( zip_stat_index( za, 0, 0, &zipstat) != 0 ) {
        fprintf(stderr, "zip_stat_index error\n");
        return ERR_NOPE;
    }
    if ((zipfile = zip_fopen_index( za, 0, 0)) == NULL ) {
        fprintf(stderr, "zip_fopen_index error\n");
        return ERR_NOPE;

    }
    *length_out = zipstat.size ;
    *buffer_out = malloc( *length_out ) ;
    size =zip_fread( zipfile, *buffer_out, zipstat.size);
    zip_close(za) ;
    return ERR_OK ;
}
