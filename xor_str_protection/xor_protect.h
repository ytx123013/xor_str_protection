//
//  xor_protect.h
//  xor_str_protection
//
//  Created by Macmini1 on 16/3/17.
//  Copyright © 2016年 ytx. All rights reserved.
//

#ifndef xor_protect_h
#define xor_protect_h

#include <stdio.h>

void read_file(const char *file_path);
void process_file(FILE *source_file,FILE *des_file);

void write_string_to_file(FILE *file_handler,char *str);

void write_wrapper_to_file(FILE *file_handler,char *unwrapper_str);
void write_footer_to_file(FILE *file_handler);
void write_header_to_file(FILE *file_handler);

char* get_OC_header();
char* get_OC_footer();
char* get_OC_wrapper(char *unwrapper_str);

#endif /* xor_protect_h */
