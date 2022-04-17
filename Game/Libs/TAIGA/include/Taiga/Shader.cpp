#include "Shader.h"
#include "vsglassert.h"

Shader::Shader() : m_ShaderID(0) {}
Shader::~Shader() {}

// SHADER LOADING
Shader::Programs Shader::loadShaderFile(const std::string& file_path) {
	std::ifstream file(file_path);
	std::string line;
	std::stringstream source[2];

	enum class SourceType {
		NONE = -1,
		VERTEX,
		FRAGMENT
	} source_type;

	unsigned int line_n = 0;
	while (getline(file, line)) {
		// parse shader types
		if (line.find("!shadertype") != std::string::npos) {
			if (line.find("vertex") != std::string::npos)
				source_type = SourceType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				source_type = SourceType::FRAGMENT;
			else
				std::cout << "WARNING: Shader file \"" << file_path << "\" line " << line_n+1 << std::endl << " \"" << line << "\" undefined shader type." << std::endl;
		}
		else 
			source[(int) source_type] << line << "\n";

		// Get all possible uniforms existing in the shader file
		std::string::size_type start = line.find("uniform", 0);
		if (line.find("uniform") != std::string::npos) {
			start += 7;
			while (line[start] == ' ')	start++;
			std::string::size_type end = start;
			while (line[end] != ' ') end++;
			//m_uniforms_types.push_back(line.substr(start, end - start)); <- Something i tried to gain flexibility. But i ditched it since its a waste on performance not being really that useful
			start = end;
			while (line[start] == ' ')	start++;
			while (line[end] != ';') end++;
			m_uniforms_names.push_back(line.substr(start, end - start));
		}

		line_n++;
	}

	return { source[0].str(), source[1].str() };
}


// SHADER COMPILATION
int Shader::compileShader(GLenum type, const std::string& _file) {
	GLuint id = glCreateShader(type);
	if (!id) {
		std::cout << "Failed to create Shader" << std::endl;
		return -1;
	}
	const char* file = _file.c_str();
	glShaderSource(id, 1, &file, nullptr);
	glCompileShader(id);

	// Error Handling
		int compiled;
		glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
		if (compiled == GL_FALSE) {
			int length = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* err = (char*) alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, err);

			std::cout << std::endl;
			std::cout << (type == GL_VERTEX_SHADER ? "OpenGL COMPILATION ERROR: Vertex Shader" : "OpenGL COMPILATION ERROR: Fragment Shader") << std::endl;
			std::cout << std::endl;
			std::cout << err << std::endl;

			glDeleteShader(id);
			std::cout << "Failed to compile Shader" << std::endl;
			return -1;
		}

	return id;
}

int Shader::linkShaders(const unsigned int& program, const unsigned int& vert_shader_id, const unsigned int& frag_shader_id) {
	glAttachShader(program, vert_shader_id);
	glAttachShader(program, frag_shader_id);
	glLinkProgram(program);
	glValidateProgram(program);

	// Error Handling
		int linked;
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		if (linked == GL_FALSE) {
			int length = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
			char* err = (char*) alloca(length * sizeof(char));
			glGetShaderInfoLog(program, length, &length, err);

			std::cout << "OpenGL LINKING ERROR" << std::endl;
			std::cout << std::endl;
			std::cout << err << std::endl;

			glDeleteShader(program);
			glDeleteProgram(program);
			glDeleteShader(vert_shader_id);
			glDeleteShader(frag_shader_id);
			std::cout << "Failed to link Shader" << std::endl;
			return -1;
		}
	
	// Delete intermediates after compilation
	glDeleteShader(vert_shader_id);
	glDeleteShader(frag_shader_id);

	// Delete Shaders from GPU's memory
	glDetachShader(program, vert_shader_id);
	glDetachShader(program, frag_shader_id);

	return program;
}


// UNIFORMS PRELOAD
// Once the shader is compiled, we ask OpenGL where all Uniforms we've seen during loading are.
// Then we can change them directly without having to query their location everytime we want them.
void Shader::loadUniformLocations() {
	for (unsigned int i = 0; i < m_uniforms_names.size(); i++) {
		int location = glGetUniformLocation(m_ShaderID, m_uniforms_names[i].c_str());
		m_uniforms_locat.push_back(location);
		m_uniforms_map.insert(std::pair<std::string, int>(m_uniforms_names[i], location));
	}
}


// SHADER CREATION
// makes a basic Vertex-Fragment shader based on a single tglsl file
void Shader::make(const std::string& file_path) {
	Shader::Programs programs = loadShaderFile(file_path);
	unsigned int program_id = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, programs.vertex_shader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, programs.fragment_shader);
	m_ShaderID = linkShaders(program_id, vs, fs);
	loadUniformLocations();
}

void Shader::bind() {
	glUseProgram(m_ShaderID);
}

void Shader::unbind() {
	glUseProgram(0);
}


// UNIFORM UTILITIES
// Ask our uniform list where a uniform is based on it's name.
// we could also acces them by found index if you feel brave enough... that will give us better performace for sure.
int Shader::getUniformLocation(const std::string& name) const {
	glUseProgram(m_ShaderID);
	auto location = m_uniforms_map.find(name);
	if (location == m_uniforms_map.end()) {
		std::cout << "Taiga - Shader Manager Warning!: Uniform \'" << name << "\' doesn't exist" << std::endl;
		return -1;
	}
	return location->second;
}

int Shader::getUniformLocation(const unsigned int index) const {
	glUseProgram(m_ShaderID);
	return m_uniforms_locat[index];
}



// PUBLIC UNIFORM HANDLERS
void Shader::setUniform1i(const std::string& name, int v0) {
	glUniform1i(getUniformLocation(name), v0);
}

void Shader::setUniform1f(const std::string& name, float v0) {
	glUniform1f(getUniformLocation(name), v0);
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
	glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& mat) {
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setUniformMat3f(const std::string& name, const glm::mat3& mat) {
	glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}
