// call_class.c - A sample of python embedding 

// (calling python classes from C code)

//

#include <Python.h>


int main(int argc, char *argv[])
{
    PyObject *pName, *pModule, *pDict, 
        *pClass, *pInstance, *pValue;
    int i, arg[2];

    if (argc < 4) 
    {
        printf(
            "Usage: exe_name python_fileclass_name function_name\n");
        return 1;
    }

    // Initialize the Python Interpreter
    Py_Initialize();

    // Build the name object
    pName = PyString_FromString(argv[1]);

    // Load the module object
    pModule = PyImport_Import(pName);

    // pDict is a borrowed reference 
    pDict = PyModule_GetDict(pModule);

   
    // Build the name of a callable class 
    pClass = PyDict_GetItemString(pDict, argv[2]);

    // Create an instance of the class

    if (PyCallable_Check(pClass))
    {
        pInstance = PyObject_CallObject(pClass, NULL); 
    }

    // Build the parameter list

    if( argc > 4 )
    {
        // pythonのメソッドに引数を渡す場合
        for (i = 0; i < argc - 4; i++)
        {
            arg[i] = atoi(argv[i + 4]);
        }
        // Call a method of the class with two parameters
        //   "(ii)"が、書式文字列で、後続の引数が２つの整数型であることを示しているとのこと
        pValue = PyObject_CallMethod(pInstance, 
                                     argv[3], "(ii)", arg[0], arg[1]);
    } else
    {
        // Call a method of the class with no parameters

        pValue = PyObject_CallMethod(pInstance, argv[3], NULL);
    }
    if (pValue != NULL) 
    {
        printf("Return of call : %d\n", PyInt_AsLong(pValue));
        Py_DECREF(pValue);
    }
    else 
    {
        PyErr_Print();
    }
   
    // Clean up

    Py_DECREF(pModule);
    Py_DECREF(pName);

    // Finish the Python Interpreter

    Py_Finalize();

    return 0;

}
