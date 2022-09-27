/* generates error messages */
int error(char *msg)
{
        fprintf(stderr, "line %d: %s\n", line_number, msg);
        return 1;
}
