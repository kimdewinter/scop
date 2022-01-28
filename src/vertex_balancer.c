#include "main.h"

static float find_highest(
    const float *vertices,
    const unsigned int vertices_length,
    const unsigned int starting_index)
{
    float highest = vertices[starting_index];

    for (
        unsigned int i = starting_index;
        i < vertices_length;
        i += VERTEX_ATTRIBUTES)
    {
        if (vertices[i] > highest)
            highest = vertices[i];
    }
    return (highest);
}

static float find_lowest(
    const float *vertices,
    const unsigned int vertices_length,
    const unsigned int starting_index)
{
    float lowest = vertices[starting_index];

    for (
        unsigned int i = starting_index;
        i < vertices_length;
        i += VERTEX_ATTRIBUTES)
    {
        if (vertices[i] < lowest)
            lowest = vertices[i];
    }
    return (lowest);
}

static float find_center(
    const float *vertices,
    const unsigned int vertices_length,
    const unsigned int starting_index)
{
    float lowest;
    float highest;

    lowest = find_lowest(vertices, vertices_length, starting_index);
    highest = find_highest(vertices, vertices_length, starting_index);
    return ((highest + lowest) / 2);
}

static void shift_attribute(
    float *vertices,
    const unsigned int vertices_length,
    const unsigned int starting_index)
{
    const float center = find_center(vertices, vertices_length, starting_index);

    for (
        unsigned int i = starting_index;
        i < vertices_length;
        i += VERTEX_ATTRIBUTES)
    {
        vertices[i] -= center;
    }
}

void balance_vertices(t_app *app)
{
    for (int i = 0; i < VERTEX_ATTRIBUTES; i++)
    {
        shift_attribute(app->vertices, app->vertices_length, i);
    }
    glBindBuffer(GL_ARRAY_BUFFER, app->VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        app->vertices_length * sizeof(float),
        app->vertices,
        GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
