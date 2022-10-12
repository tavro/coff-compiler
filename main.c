#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "global.h"

/* probably would like to
*  convert headers below
*  to .c-files
*/
#include "error.h"
#include "emitter.h"
#include "symbol.h"
#include "lexer.h"
#include "init.h"
#include "parser.h"

int main(int argc, char **argv) {
	FILE *f = fopen(argv[1], "r");

	if(f == NULL) {
     		perror("Error in opening file");
      		return(-1);
   	}

	init();
	parse(f);
	return 0;
}
