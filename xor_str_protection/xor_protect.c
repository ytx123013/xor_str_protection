//
//  xor_protect.c
//  xor_str_protection
//
//  Created by Macmini1 on 16/3/17.
//  Copyright © 2016年 ytx. All rights reserved.
//

#define X_KEY 0x1f

typedef enum {
    Language_ObjectC
}LanguageType;

#include "xor_protect.h"
#include <string.h>
#include <stdlib.h>

static LanguageType language_type = Language_ObjectC;

void xor_string(char *str){
    while (*str != '\0'){
        *str = (*str) ^ X_KEY;
        str++;
    }
}

void read_file(const char *file_path)
{
    FILE *f = fopen(file_path, "r+");
    
    const char* write_file_path = "./tmpString";
    FILE *wf = fopen(write_file_path,"w+");
    process_file(f,wf);

}

void process_file(FILE *f,FILE *wf)
{
    write_header_to_file(wf);
    while (!feof(f)) {
        char lineStr[1024];
        int i = 0;
        while (1){
            char tmpChar = fgetc(f);
            if (tmpChar == '\n'){
                lineStr[i] = '\0';
                break;
            }else if(feof(f)){
                lineStr[i] = '\0';
                break;
            }else{
                lineStr[i] = tmpChar;
            }
            i++;
        }
        xor_string(lineStr);
        write_wrapper_to_file(wf,lineStr);
    }
    write_footer_to_file(wf);
}

void write_string_to_file(FILE *file_handler,char *str)
{
    char *p = str;
    while(*p != '\0'){
        if (*p == '\\'){
            fputc('\\',file_handler);
        }
        fputc(*p,file_handler);
        p++;
    }
}

void write_wrapper_to_file(FILE *file_handler,char *unwrapper_str)
{
    char* (*fp)(char*);
    switch (language_type) {
        case Language_ObjectC:
            fp = get_OC_wrapper;
            break;
        default:
            break;
    }
    char *wrapper_str = fp(unwrapper_str);
    write_string_to_file(file_handler, wrapper_str);
    free(wrapper_str);
}

void write_footer_to_file(FILE *file_handler)
{
    char* (*fp)();
    switch (language_type) {
        case Language_ObjectC:
            fp = get_OC_footer;
            break;
        default:
            break;
    }
    char *footer_str = fp();
    write_string_to_file(file_handler, footer_str);
}

void write_header_to_file(FILE *file_handler)
{
    char* (*fp)();
    switch (language_type) {
        case Language_ObjectC:
            fp = get_OC_header;
            break;
        default:
            break;
    }
    char *header_str = fp();
    write_string_to_file(file_handler, header_str);
}


char* get_OC_header()
{
    static char *header = "[NSArray arrayWithObjects:";
    return header;
}

char* get_OC_footer()
{
    static char *footer = " nil]";
    return footer;
}

char* get_OC_wrapper(char *unwrapper_str)
{
    unsigned long len = strlen(unwrapper_str)+5;
    char *wrapper_str = (char *)malloc(len * sizeof(char));
    wrapper_str[0] = '@';
    wrapper_str[1] = '\"';
    int i = 2;
    while (*unwrapper_str != '\0'){
        wrapper_str[i] = *unwrapper_str;
        unwrapper_str++;
        i++;
    }
    wrapper_str[i] = '\"';
    wrapper_str[i+1] = ',';
    wrapper_str[i+2] = '\0';
    return wrapper_str;
}