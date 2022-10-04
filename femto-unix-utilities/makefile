all : bin/mcp bin/mpwd bin/mecho bin/mmv

bin/mcp : source/mcp.c
	gcc source/mcp.c -o bin/mcp


bin/mpwd : source/mpwd.c
	gcc source/mpwd.c -o bin/mpwd


bin/mecho : source/mecho.c
	gcc source/mecho.c -o bin/mecho

bin/mmv : source/mmv.c
	gcc source/mmv.c -o bin/mmv

clean : 
	rm bin/*
