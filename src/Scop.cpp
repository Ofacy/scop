#include "GLContext.hpp"
#include "Scop.hpp"

#include <chrono>
#include <cmath>

void Scop::_initGPUBuffers() {
	glGenVertexArrays(1, &this->_vao);
	glBindVertexArray(this->_vao);
	
	glGenBuffers(1, &this->_vbo);

	glGenBuffers(1, &this->_ebo);

	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
	const std::vector<Vertex> &vertices = this->_mesh.getVertices();
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	const std::vector<unsigned int> &elements = this->_mesh.getIndices();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * elements.size(), elements.data(), GL_STATIC_DRAW);

}

void Scop::_zoom(float yScroll, float zoomMultiplier) {
	float zoomFactor = -yScroll * zoomMultiplier;
	Vec3 translation = this->_viewMatrix.getTranslation();
	Vec3 translationDelta = translation * zoomFactor;
	translation += translationDelta;
	// make sure translation is not too close to the origin or goes behind the model
	if (translation.length() < 0.1f) {
		translation = this->_viewMatrix.getTranslation().normalized() * 0.1f;
	}
	this->_viewMatrix.setTranslation(translation);
	this->getActiveShaderProgram().setView(this->_viewMatrix);
}

void Scop::_nextProgram() {
	this->_activeProgramIndex = (this->_activeProgramIndex + 1) % this->_shaderProgramCount;
	TransformableShaderProgram &activeProgram = this->getActiveShaderProgram();
	activeProgram.use();
	activeProgram.setTransform(this->_transformMatrix);
	activeProgram.setView(this->_viewMatrix);
	activeProgram.setProjection(this->_projectionMatrix);
}

Scop::Scop(Mesh &mesh, bool texture, unsigned char rgb[3]) :
		_mesh(mesh),
		_activeProgramIndex(0),
		_drawMode(GL_TRIANGLES),
		_projectionMatrix(Mat4::perspective(90.0f, 1920.0f / 1080.0f, 0.1f, 1000.0f)),
		_viewMatrix(Mat4::lookAt(3.2f, 3.2f, 3.2f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f))
		{
	this->_initGPUBuffers();
	this->_shaderProgramCount = 1;
	if (texture) {
		this->_shaderPrograms = new TransformableShaderProgram[2];
		this->_shaderProgramCount = 2;
		ShaderProgram &shaderProgram = this->_shaderPrograms[1];
		Shader vertexShader(GL_VERTEX_SHADER, "./assets/shaders/vertex/texture.glsl");
		Shader fragmentShader(GL_FRAGMENT_SHADER, "./assets/shaders/fragment/texture.glsl");

		shaderProgram.attachShader(vertexShader);
		shaderProgram.attachShader(fragmentShader);
		shaderProgram.link();
		shaderProgram.bindFragDataLocation("outColor", 0);
		GLint position = shaderProgram.getAttributeLocation("position");
		if (position != -1)
			shaderProgram.vertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
		GLint texCoord = shaderProgram.getAttributeLocation("texCoord");
		if (texCoord != -1)
			shaderProgram.vertexAttribPointer(texCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
		shaderProgram.use();
	}
	else
		this->_shaderPrograms = new TransformableShaderProgram();
	ShaderProgram &shaderProgram = this->_shaderPrograms[0];
	Shader vertexShader(GL_VERTEX_SHADER, "./assets/shaders/vertex/shades.glsl");
	Shader fragmentShader(GL_FRAGMENT_SHADER, "./assets/shaders/fragment/shades.glsl");

	shaderProgram.attachShader(vertexShader);
	shaderProgram.attachShader(fragmentShader);
	shaderProgram.link();
	
	shaderProgram.bindFragDataLocation("outColor", 0);
	
	GLint position = shaderProgram.getAttributeLocation("position");
	if (position != -1)
		shaderProgram.vertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	shaderProgram.use();
	
	GLint shadeCountLocation = shaderProgram.getUniformLocation("shadeCount");
	shaderProgram.setUniform3i(shadeCountLocation, rgb[0], rgb[1], rgb[2]);
	// use the texture shader first and initialise its uniforms
	this->_nextProgram();
};

void Scop::start() {
	GLContext &glContext = GLContext::getInstance();

	auto t_start = std::chrono::high_resolution_clock::now();
	Window& window = glContext.getWindow();
	int oldShaderKeyState = GLFW_RELEASE;
	while (!window.shouldClose()) {
		if (window.getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
			window.setShouldClose(true);

		int currentShaderKeyState = window.getKey(GLFW_KEY_S);
		if (currentShaderKeyState == GLFW_PRESS && currentShaderKeyState != oldShaderKeyState)
			this->_nextProgram();
		oldShaderKeyState = currentShaderKeyState;

		double yScroll = window.getScrollYOffset();
		if (yScroll != 0.0)
			this->_zoom(static_cast<float>(yScroll), 0.2f);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		auto t_now = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
		
		// apply rotation
		this->_transformMatrix.setRotation(time * 30.0f, 0.0f, 1.0f, 0.0f);

		// send the new transform matrix to the shader
		TransformableShaderProgram &activeProgram = this->getActiveShaderProgram();
		activeProgram.setTransform(this->_transformMatrix);

		glDrawElements(this->_drawMode, this->_mesh.getIndices().size(), GL_UNSIGNED_INT, nullptr);

		window.swapBuffers();
		glContext.pollEvents();
	}
}

TransformableShaderProgram &Scop::getActiveShaderProgram() {
	return this->_shaderPrograms[this->_activeProgramIndex];
}