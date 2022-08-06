#include <string>

#include "vectornd.h"
#include "geometry.h"
#include "importstl.h"
#include "exportobj.h"
#include "converter.h"
#include "check_mode.h"

using namespace std;

void convert(
    string src, 
    string dst, 
    bool debug = true,
    void(*callback)(int, void*) = NULL, 
    void* py_callback = NULL, 
    void* py_progress = NULL) {
    /*
    `src` - full path to stl file in binary format
    `dst` - full path to obj file
    `callback` - just function, that call pointer like `py_object`
    */

    int code;
    string mode = get_stl_mode(src);

    if (debug == false) {
        streambuf* old = cout.rdbuf();
        cout.rdbuf(0);
    }
    
    if (mode == "BIN") {
        //  create a geometry tesselation object
        Geometry tessel;

        //  fill up the tesselation object with STL data (load STL)
        tessel.visit(ImportSTL(src, callback, py_progress));

        //  write down the tesselation object into OBJ file (save OBJ)
        tessel.visit(ExportOBJ(dst));

        code = 0;
    }
    else {
        cout << "File must be in BIN format" << endl;
        code = -1;
    }

    if (callback && py_callback) {
        // for python lib `callback` written in c, `py_object` - pointer to python function
        callback(code, py_callback);
    }
}
