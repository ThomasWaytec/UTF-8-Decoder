all: project_file.exe

project_file.exe: src/utf-8-decoder.c
	gcc src/utf-8-decoder.c -o project_file.exe

clean:
	rm project_file.exe