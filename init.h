struct entry keywords[] = {
        "div", DIV,
        "mod", MOD,
        0,     0
};

/* loads keywords into symbol table */
void init() {
        struct entry *p;
        for(p = keywords; p->token; p++)
                insert(p->lexptr, p->token);
}
