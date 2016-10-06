myls:fileinfo.o showinfo.o main.o showinfo.h
	gcc fileinfo.o showinfo.o main.o -o myls
showinfo.o:showinfo.c showinfo.h fileinfo.h
	gcc -c showinfo.c -o showinfo.o
fileinfo.o:fileinfo.c fileinfo.h
	gcc -c fileinfo.c -o fileinfo.o
main.o:main.c fileinfo.h
	gcc -c main.c -o main.o
clean:
	rm -f *.o myls

	
		
