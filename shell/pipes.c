int ispipe(char *s)
{
    int i = 0;
    while (s[i] != '\0') {

	if (s[i] == '|')
	    return 1;
	i++;
    }
    return 0;
}
