#include "main.h"
#include <assert.h>

//argument "file_extension" must include the period
static bool has_file_extension(
    char const *const file_extension,
    char const *const file_name)
{
    size_t file_len = strlen(file_name);
    size_t ext_len = strlen(file_extension);

    if (ext_len < 4)
        return (false);
    if (file_len < (ext_len + 1))
        return (false);
    if (strncmp(
            file_extension,
            &file_name[file_len - ext_len],
            ext_len) != 0)
        return (false);
    return (true);
}

bool parse_main_args(t_app *app, const int argc, char const **const argv)
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
        assert(app->texture_file_name);
    }
    return (true);
}
