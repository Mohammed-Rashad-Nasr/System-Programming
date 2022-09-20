int myfib (int x)
{
	if (x==1) return 1 ;
	else if (x==2) return 1 ;
	else return (myfib(x-1)+myfib(x-2));
}
