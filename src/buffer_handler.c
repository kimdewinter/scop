#include "main.h"

bool load_buffers(t_app *app)
{
    glGenVertexArrays(1, &(app->VAO));
    glGenBuffers(1, &(app->VBO));
    glGenBuffers(1, &(app->EBO));
    // bind the Vertex Array Object first, then bind and set vertex buffer(s),
	// and then configure vertex attributes(s).
    glBindVertexArray(app->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, app->VBO);
    glBufferData(
		GL_ARRAY_BUFFER,
		app->vertices_length * sizeof(float),
		app->vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, app->EBO);
    glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		app->indices_length * sizeof(unsigned int),
		app->indices,
		GL_STATIC_DRAW);

    glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(float),
		(void *)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered
	// VBO as the vertex attribute's bound vertex buffer object so afterwards we
	// can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound
	// element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally
	// modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't
	// unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	return true;
}