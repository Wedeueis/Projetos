// python functions from C code
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	if (system(NULL)) puts ("Ok");
	else exit (EXIT_FAILURE);
	std::string comand = "include/extract_text.py include/jornalnacional.png include/out_jornalnacional.png";
	std::string s = "python " + comand;
	system(s.c_str());
	s = "tesseract include/out_jornalnacional.png jornal";
	system(s.c_str());
	

    return 0;
}
