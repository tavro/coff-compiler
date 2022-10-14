int lexical_analyzer(FILE* f) {
        int t;

        while(1) {
                t = getc(f);//getchar();
		if (t == ' ' || t == '\t');             /* strip white space */
                else if (t == '\n')
                        line_number = line_number + 1;  /* new line */
                else if (isdigit(t)) {                  /* is digit */
                        ungetc(t, f);//stdin);
                        fscanf(f, "%d", &token_value);
                        return NUM;
                }
                else if (isalpha(t)) {                  /* is letter */
                        int p, buffer_index = 0;

                        while(isalnum(t)) {             /* is alphanumeric */
                                lex_buffer[buffer_index] = t;
                                t = getc(f);//getchar();
                                buffer_index = buffer_index + 1;

                                if (buffer_index >= BUFFER_SIZE) {
					char error_msg[] = "compiler error: buffer index out of range";
                                        error(error_msg);
				}
                        }

                        lex_buffer[buffer_index] = EOS;
                        if (t != EOF)
                                ungetc(t, f);//stdin);

                        p = lookup(lex_buffer);
                        if (p == 0)
                                p = insert(lex_buffer, ID);

                        token_value = p;
                        return symbol_table[p].token;
                }
                else if (t == EOF)
                        return DONE;
                else {
                        token_value = NONE;
                        return t;
                }
        }
}
