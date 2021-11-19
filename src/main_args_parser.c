#include "main.h"
#include <assert.h>

bool parse_main_args(t_app *app, const int argc, char const ** const argv)
{
    //program must receive .obj object file (.bmp texture file optional)
    assert(argc == 2 || argc == 3);
    //ensure .obj filename is long enough (example: a.obj)
    assert(strlen(argv[1]) > 4);
    //ensure .obj filename ends with .obj extension
    assert(strncmp(".obj", &argv[1][strlen(argv[1]) - 4], 4) == 0);
    //program might receive .bmp texture file
    if (argc == 3)
    {
        //ensure .bmp filename is long enough (example: a.bmp)
        assert(strlen(argv[2]) > 4);
        //ensure .bmp filename ends with .bmp extension
        assert(strncmp(".bmp", &argv[2][strlen(argv[2]) - 4], 4) == 0);
    }

    //parsing complete, now store main args
    app->obj_file_name = strdup(argv[1]);
    assert(app->obj_file_name);
    if (argc == 3)
    {
        app->texture_file_name = strdup(argv[2]);
        assert(app->obj_file_name);
    }
    return (true);
}
