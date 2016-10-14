#include "str.h"

void strreplace(char* s, char chr, char repl_chr){
     int i=0;
     while(s[i] != '\0')
     {
           if(s[i]==chr)
           {
               s[i]=repl_chr;
           }  
           i++; 
     }
}

void strremoveEOL(char* s){
	int i = 0;	
	while(s[i] != '\0'){
		if(s[i] == '\n')
			s[i] = '\0';
		i++;
	}
}

void strTest(){
	char* test;
	test = strdup("test");

	strreplace(test, 'e', 'd');
	assert(test[1] == 'd');
	char* test2 = strdup("this/is/a/path/to/Linux");
	printf("Test of replacement of / by \\ : \n");
	printf("Before :\n");
	printf("%s\n", test2);
	strreplace(test2, '/', '\\');
	printf("After :\n");
	printf("%s\n", test2);
	printf("Ok.\n");
	free (test2);
	free(test);
}