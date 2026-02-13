#pragma once
#ifndef __COLORS__
#define __COLORS__

#include <iostream>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define INFO YELLOW << "[INFO] "
#define ERROR RED << "[ERROR] "
#define OK GREEN << "[OK] "

#ifndef DEBUG
#define DEBUG false
#endif // DEBUG

const int MAX_SIZE = 20;

#endif // __COLORS__