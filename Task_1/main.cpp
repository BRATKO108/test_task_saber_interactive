#include "include/list_rand.h"
#include <iostream>
#include <fstream>

int main()
{
    std::string path = "save.txt";
    
    ListRand listTest;
    std::fstream fs;
    
    listTest.init( { -1, 1, 4, 0, -1 } );
    fs.open( path, std::fstream::out );
    std::fstream clear_file( path, std::fstream::out );
    listTest.serialize( fs );
    fs.close();
    
    fs.open( path, std::fstream::in );
    listTest.deserialize( fs );
    fs.close();
    
    return 0;
}
