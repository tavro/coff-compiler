void match(int t)
{
        if (lookahead == t)
                lookahead = lexical_analyzer();
        else error("compiler error: syntax error");
}

void expression();
void factor() {
        switch(lookahead) {
                case '(':
                        match('(');
                        expression();
                        match(')');
                        break;
                case NUM:
                        emit(NUM, token_value);
                        match(NUM);
                        break;
                case ID:
                        emit(ID, token_value);
                        match(ID);
                        break;
                default:
                        error("compiler error: syntax error");
        }
}

void term() {
        int t;

        factor();
        while(1) {
                switch(lookahead) {
                        case '*': case '/': case DIV: case MOD:
                                t = lookahead;
                                match(lookahead);
                                factor();
                                emit(t, NONE);
                                continue;
                        default:
                                return;
                }
        }
}

void expression() {
        int t;

        term();
        while(1) {
                switch(lookahead) {
                        case '+': case '-':
                                t = lookahead;
                                match(lookahead);
                                term();
                                emit(t, NONE);
                        default:
                                return;
                }
        }
}

/* parses & translates expression list */
void parse() {
        lookahead = lexical_analyzer();
        while(lookahead != DONE) {
                expression();
                match(';');
        }
}
