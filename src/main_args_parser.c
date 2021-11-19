#include "main.h"
#include <assert.h>

//argument file_extension also requires the period
static bool has_file_extension(
    char const * const file_extension,
    char const * const file_name)
{
    size_t len = strlen(file_name);

    //ensure file name is long enough (shortest possible example: a.xyz)
    if (!(len > 4))
        return (false);
    //ensure file name ends in the file extension
    if (!(strncmp(file_extension, &file_name[len - 4], 4) == 0))
        return (false);
    return (true);
}

bool parse_main_args(t_app *app, const int argc, char const ** const argv)
{
    //program must receive .obj object file, and optionally a .bmp texture file
    assert(argc == 2 || argc == 3);
    assert(has_file_extension(".obj", argv[1]));
    if (argc == 3)
        assert(has_file_extension(".bmp", argv[2]));

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
