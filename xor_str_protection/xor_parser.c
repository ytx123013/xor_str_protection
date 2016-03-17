//
//  xor_parser.c
//  xor_str_protection
//
//  Created by Macmini1 on 16/3/17.
//  Copyright © 2016年 ytx. All rights reserved.
//

#define X_KEY 0x1f

#include "xor_parser.h"

void xor_string(char *str){
    while (*str != '\0'){
        *str = (*str) ^ X_KEY;
        str++;
    }
}

void xor_parser(char *str)
{
    xor_string(str);
}