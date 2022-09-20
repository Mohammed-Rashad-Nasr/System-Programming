int myfact (int x)
{
	if (x==1) return 1 ;
	else return (x*myfact(x-1));
}
