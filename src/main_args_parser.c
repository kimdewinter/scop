#include "main.h"

//Argument "file_extension" must include the period
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
    //Program must receive .obj object file, and optionally a .bmp texture file
    if (!(argc == 2 || argc == 3) ||
        !has_file_extension(".obj", argv[1]) ||
        (argc == 3 && !has_file_extension(".bmp", argv[2])))
    {
        fprintf(
            stdout,
            "Error: %s requires .obj filename and optionally .bmp filename\n",
            PROGRAM_NAME);
        return (false);
    }

    //Parsing complete, now store main args
    app->obj_file_name = strdup(argv[1]);
    if (argc == 3)
        app->texture_file_name = strdup(argv[2]);
    if (!app->obj_file_name ||
        (argc == 3 && !app->texture_file_name))
    {
        if (app->obj_file_name)
        {
            free(app->obj_file_name);
            app->obj_file_name = NULL;
        }
        if (argc == 3 && app->texture_file_name)
        {
            free(app->texture_file_name);
            app->texture_file_name = NULL;
        }
        fprintf(
            stdout,
            "Error: parse_main_args encountered misallocation\n");
        return (false);
    }
    return (true);
}
