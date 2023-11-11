
ft: dynarray.o path.o nodeFT.o ft.o ft_client.o

dynarray.o: dynarray.c dynarray.h
	gcc217 -c dynarray.c

path.o: path.c dynarray.h path.h a4def.h
	gcc217 -c path.c

ft_client.o: ft_client.c ft.h a4def.h
	gcc217 -c ft_client.c

nodeFT.o: nodeFT.c dynarray.h nodeFT.h path.h a4def.h
	gcc217 -c nodeFT.c

ft.o: ft.c dynarray.h nodeFT.h ft.h path.h a4def.h
	gcc217 -c ft.c

