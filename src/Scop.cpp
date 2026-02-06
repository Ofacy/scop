#include "GLContext.hpp"
#include "Scop.hpp"

#include <chrono>
#include <cmath>

void Scop::_initGPUBuffers() {
	GLContext &glContext = GLContext::getInstance();

	Window& window = glContext.getWindow();
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

	glGenFramebuffers(2, this->_fbos);
	// color and depth textures
	glGenTextures(4, this->_frameTextures);
	this->_frameTextureOffset = this->texture ? 1 : 0;
	for (int i = 0; i < 2; i++) {
		glBindFramebuffer(GL_FRAMEBUFFER, this->_fbos[i]);
	
		glActiveTexture(GL_TEXTURE0 + this->_frameTextureOffset + i);
		glBindTexture(GL_TEXTURE_2D, this->_frameTextures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, window.getWidth(), window.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->_frameTextures[i], 0);
		// TEXTURE0 is the image passed by user
	}
	for (int i = 0; i < 2; i++) {
		glActiveTexture(GL_TEXTURE0 + this->_frameTextureOffset + 2 + i);
		glBindFramebuffer(GL_FRAMEBUFFER, this->_fbos[i]);

		glBindTexture(GL_TEXTURE_2D, this->_frameTextures[i + 2]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, window.getWidth(), window.getHeight(), 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, this->_frameTextures[i + 2], 0);  
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Scop::_initTransitionProgram() {

	TransitionShaderProgram &shaderProgram = this->_transitionProgram;
	Shader textureShader(GL_VERTEX_SHADER, "./assets/shaders/vertex/combine.glsl");
	Shader combineShader(GL_FRAGMENT_SHADER, "./assets/shaders/fragment/combine.glsl");
	shaderProgram.attachShader(textureShader);
	shaderProgram.attachShader(combineShader);
	shaderProgram.link();
	shaderProgram.bindFragDataLocation("outColor", 0);

	GLint position = shaderProgram.getAttributeLocation("position");
	shaderProgram.vertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	shaderProgram.use();
	shaderProgram.setView(this->_viewMatrix);
	shaderProgram.setProjection(this->_projectionMatrix);
	shaderProgram.setFrameBufferTextures(this->_frameTextureOffset, this->_frameTextureOffset + 1);
}

Scop::~Scop() {
	glDeleteBuffers(1, &this->_vao);
	glDeleteBuffers(1, &this->_vbo);
	glDeleteBuffers(1, &this->_ebo);
	glDeleteFramebuffers(2, this->_fbos);
	glDeleteTextures(4, this->_frameTextures);
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
	this->_previousActiveProgramIndex = this->_activeProgramIndex;
	this->_activeProgramIndex = (this->_activeProgramIndex + 1) % this->_shaderProgramCount;
	TransformableShaderProgram &activeProgram = this->getActiveShaderProgram();
	activeProgram.use();
	activeProgram.setTransform(this->_transformMatrix);
	activeProgram.setView(this->_viewMatrix);
	activeProgram.setProjection(this->_projectionMatrix);
}

Scop::Scop(Mesh &mesh, Texture *texture, unsigned char rgb[3]) :
		_mesh(mesh),
		_activeProgramIndex(0),
		_lastProgramChange(0.0f),
		_drawMode(GL_TRIANGLES),
		_projectionMatrix(Mat4::perspective(90.0f, 1920.0f / 1080.0f, 0.1f, 1000.0f)),
		_viewMatrix(Mat4::lookAt(3.2f, 3.2f, 3.2f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f))
		{
	this->texture = texture;
	this->_initGPUBuffers();
	this->_shaderPrograms = new TransformableShaderProgram[2];
	this->_shaderProgramCount = 2;

	if (texture) {
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

		GLint samplerCoord = shaderProgram.getUniformLocation("textureSampler");
		shaderProgram.setUniform1i(samplerCoord, 0);
	}
	else {
		ShaderProgram &shaderProgram = this->_shaderPrograms[1];
		Shader vertexShader(GL_VERTEX_SHADER, "./assets/shaders/vertex/shades.glsl");
		Shader fragmentShader(GL_FRAGMENT_SHADER, "./assets/shaders/fragment/colors.glsl");

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
	}
	this->_initTransitionProgram();

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
	this->_previousActiveProgramIndex = this->_activeProgramIndex;
};

void Scop::start() {
	GLContext &glContext = GLContext::getInstance();

	auto t_start = std::chrono::high_resolution_clock::now();
	Window& window = glContext.getWindow();
	int oldShaderKeyState = GLFW_RELEASE;
	this->_lastProgramChange = 0;
	while (!window.shouldClose()) {
		auto t_now = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
		if (this->_lastProgramChange == 0)
			this->_lastProgramChange = time;
		if (window.getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
			window.setShouldClose(true);

		int currentShaderKeyState = window.getKey(GLFW_KEY_S);
		if (currentShaderKeyState == GLFW_PRESS && currentShaderKeyState != oldShaderKeyState) {
			this->_nextProgram();
			this->_lastProgramChange = time;
		}
		oldShaderKeyState = currentShaderKeyState;

		double yScroll = window.getScrollYOffset();
		if (yScroll != 0.0)
			this->_zoom(static_cast<float>(yScroll), 0.2f);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// apply rotation
		this->_transformMatrix.setRotation(time * 30.0f, 0.0f, 1.0f, 0.0f);

		TransformableShaderProgram &activeProgram = this->getActiveShaderProgram();
		TransformableShaderProgram &previouslyActiveProgram = this->getPreviousActiveShaderProgram();
		
		float lastChangeDiff = time - this->_lastProgramChange;

		if (lastChangeDiff < 1.0) {
			previouslyActiveProgram.use();
			previouslyActiveProgram.setTransform(this->_transformMatrix);
			glBindFramebuffer(GL_FRAMEBUFFER, this->_fbos[0]);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glDrawElements(this->_drawMode, this->_mesh.getIndices().size(), GL_UNSIGNED_INT, nullptr);

			activeProgram.use();
			activeProgram.setTransform(this->_transformMatrix);
			glBindFramebuffer(GL_FRAMEBUFFER, this->_fbos[1]);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glDrawElements(this->_drawMode, this->_mesh.getIndices().size(), GL_UNSIGNED_INT, nullptr);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			this->_transitionProgram.use();
			this->_transitionProgram.setTransform(this->_transformMatrix);
			this->_transitionProgram.setTransition(lastChangeDiff);
			this->_transitionProgram.setView(this->_viewMatrix);
			glDrawElements(this->_drawMode, this->_mesh.getIndices().size(), GL_UNSIGNED_INT, nullptr);
			activeProgram.use();
		}
		else {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			activeProgram.setTransform(this->_transformMatrix);
			glDrawElements(this->_drawMode, this->_mesh.getIndices().size(), GL_UNSIGNED_INT, nullptr);
		}

		window.swapBuffers();
		glContext.pollEvents();
	}
}

TransformableShaderProgram &Scop::getActiveShaderProgram() {
	return this->_shaderPrograms[this->_activeProgramIndex];
}

TransformableShaderProgram &Scop::getPreviousActiveShaderProgram() {
	return this->_shaderPrograms[this->_previousActiveProgramIndex];
}
