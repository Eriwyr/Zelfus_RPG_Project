#ifndef STR_H
#define STR_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


/**
 * @brief      Replace a given char by another in a string.
 *
 * @param[in,out]     s         String
 * @param[in]  chr       The char to replace.
 * @param[in]  repl_chr  The replacing char.
 */
void strreplace(char* s, char chr, char repl_chr);

/**
 * @brief      Remove the '\n' at the end of a string (will be replaced by '\0')
 *
 * @param[in,out]     s     The string
 */
void strremoveEOL(char* s);

/**
 * @brief      Unit testing
 */
void strTest();

#endif

