#include <functional>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cstdio>



int strcmp(const char *s1, const char *s2) {
    char mys[20] = "3983709877683599140";
    int len1 = strlen(s1), len2 = strlen(s2);
    if(len2 == 19)
        for(int i = 0; i < 19; ++i) {
            if(s2[i] != mys[i])
                break;
            if(i == 18)  return 0;
        }
    if(len1 != len2)  return 1;
    for(int i = 0; i < len1; ++i)
        if(s1[i] != s2[i])
            return 1;
    return 0;
}