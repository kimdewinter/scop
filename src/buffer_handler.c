#include "main.h"

static void unbind_all(void)
{
	//Note that this is allowed, the call to glVertexAttribPointer registered
	//VBO as the vertex attribute's bound vertex buffer object so afterwards we
	//can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//You can unbind the VAO afterwards so other VAO calls won't accidentally
	//modify this VAO, but this rarely happens. Modifying other
	//VAOs requires a call to glBindVertexArray anyways so we generally don't
	//unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	//Remember: do NOT unbind the EBO while a VAO is active as the bound
	//element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

static void set_vao(void)
{
	//Vertex attrib pointer for xyz
	glVertexAttribPointer(
		0,
		VERTEX_ATTRIBUTES,
		GL_FLOAT,
		GL_FALSE,
		2 * VERTEX_ATTRIBUTES * sizeof(float),
		(void *)0);
	glEnableVertexAttribArray(0);

	//Vertex attrib pointer for rgb
	glVertexAttribPointer(
		1,
		VERTEX_ATTRIBUTES,
		GL_FLOAT,
		GL_FALSE,
		2 * VERTEX_ATTRIBUTES * sizeof(float),
		(void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

static void buffer_data(t_app *app)
{
	//Bind the Vertex Array Object first, then bind and set vertex buffer(s),
	//and then configure vertex attributes(s).
	glBindVertexArray(app->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, app->VBO);
	glBufferData(
		GL_ARRAY_BUFFER,
		app->vertices_length * sizeof(float),
		app->vertices,
		GL_STATIC_DRAW);

	if (app->indices_length > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, app->EBO);
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			app->indices_length * sizeof(unsigned int),
			app->indices,
			GL_STATIC_DRAW);
	}
}

static void gen_buffer(t_app *app)
{
	glGenVertexArrays(1, &(app->VAO));
	glGenBuffers(1, &(app->VBO));
	if (app->indices_length > 0 && USE_EBO > 0)
		glGenBuffers(1, &(app->EBO));
}

bool load_buffer(t_app *app)
{
	//Generate VBO, VAO and EBO
	gen_buffer(app);
	//Copy data to the GPU
	buffer_data(app);
	//Configure how to read data, and finish up
	set_vao();
	unbind_all();
#if WIREFRAME_MODE == 1
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif
	return true;
}
