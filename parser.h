void match(int t, FILE* f)
{
        if (lookahead == t)
                lookahead = lexical_analyzer(f);
        else error("compiler error: syntax error");
}

void expression(FILE* f);
void factor(FILE* f) {
        switch(lookahead) {
                case '(':
                        match('(', f);
                        expression(f);
                        match(')', f);
                        break;
                case NUM:
                        emit(NUM, token_value);
                        match(NUM, f);
                        break;
                case ID:
                        emit(ID, token_value);
                        match(ID, f);
                        break;
                default:
                        error("compiler error: syntax error");
        }
}

void term(FILE* f) {
        int t;

        factor(f);
        while(1) {
                switch(lookahead) {
                        case '*': case '/': case DIV: case MOD:
                                t = lookahead;
                                match(lookahead, f);
                                factor(f);
                                emit(t, NONE);
                                continue;
                        default:
                                return;
                }
        }
}

void expression(FILE* f) {
        int t;

        term(f);
        while(1) {
                switch(lookahead) {
                        case '+': case '-':
                                t = lookahead;
                                match(lookahead, f);
                                term(f);
                                emit(t, NONE);
                        default:
                                return;
                }
        }
}

/* parses & translates expression list */
void parse(FILE* f) {
        lookahead = lexical_analyzer(f);
        while(lookahead != DONE) {
                expression(f);
                match(';', f);
        }
}
