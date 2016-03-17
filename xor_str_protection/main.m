//
//  main.m
//  xor_str_protection
//
//  Created by Macmini1 on 16/3/17.
//  Copyright © 2016年 ytx. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "xor_protect.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...        
        const char *file_path = argv[1];
        read_file(file_path);
    }
    return 0;
}
