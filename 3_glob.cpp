#include <iostream>
#include <string>
#include <glob.h>

using namespace std;

void print_gl(glob_t &gl)
{
    for(int i = 0;i < gl.gl_pathc;i++)
    {
        cout << gl.gl_pathv[i] << endl;
    }
}

void test_glob(int argc,char **argv)
{
    glob_t gl;

    for(int i = 1;i < argc;i++)
    {
        gl.gl_offs = 0;
        glob(argv[i],GLOB_TILDE,0,&gl);
        print_gl(gl);
        globfree(&gl);
    }
}

int main(int argc,char **argv)
{
    if(argc < 2){
        cout << "<filename>" << endl;
        return 0;
    }

    test_glob(argc,argv);

    return 0;
}