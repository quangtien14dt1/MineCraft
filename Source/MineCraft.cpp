#include "Application.h"
#include <iostream>
#include <stdlib.h>

#undef APIENTRY


int main()
{
    std::cout << "Loading game... \n" << std::endl;
    Application app;
    app.RunLoop();

    return EXIT_SUCCESS;
}