#include "parser.h"


int main( int argc, char** argv )
{
    cout << "############################################" << endl;
    cout << "#              Global Routing              #" << endl;
    cout << "############################################" << endl;

    glob global;

    /////////////////////parser/////////////////////
    global.parser( argc, argv );
    cout << "............parser done!!!!!!.............." << endl;
//////
    ////////////////////////global route///////////////////////
//    global.routing( );//
//    cout << "............global routing done!!!!!!.............." << endl;
////
//    /////////////////////output/////////////////////
    global.output( argc, argv );
    cout << "............output done!!!!!!.............." << endl;


    return 0;
}

