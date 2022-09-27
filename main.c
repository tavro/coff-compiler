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

int main() {
	init();
	parse();
	return 0;
}
