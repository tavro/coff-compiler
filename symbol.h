/* returns position of entry for s */
int lookup(char s[]) {
        int p;
        for(p = last_entry; p > 0; p = p - 1)
                if (strcmp(symbol_table[p].lexptr, s) == 0)
                        return p;
        return 0;
}

/* returns position of entry for s */
int insert(char s[], int tok) {
        int len;
        len = strlen(s);

        if (last_entry + 1 >= SYM_MAX) {
		char error_msg[] = "compiler error: symbol table is full";
                error(error_msg);
	}

        if (last_char + len + 1 >= STR_MAX) {
                char error_msg[] = "compiler error: lexemes array is full";
		error(error_msg);
	}

        last_entry = last_entry + 1;
        symbol_table[last_entry].token = tok;
        symbol_table[last_entry].lexptr = &lexemes[last_char + 1];

        last_char = last_char + len + 1;
        strcpy(symbol_table[last_entry].lexptr, s);

        return last_entry;
}
