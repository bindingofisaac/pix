#include <Shader.hpp>

namespace Pix{
    Shader::Shader(const std::string &vertPath, const std::string &fragPath) : m_VertPath(vertPath), m_FragPath(fragPath){
        m_ShaderProgram = f_Load();
    }

    Shader::~Shader(){
    }

    GLuint Shader::f_Load(){
        GLuint program  = glCreateProgram();
        GLuint vertex   = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

        std::string vertSrc = read_file(m_VertPath);
        std::string fragSrc = read_file(m_FragPath);

        const char *vertSrcPtr = vertSrc.c_str();
        const char *fragSrcPtr = fragSrc.c_str();

        glShaderSource(vertex, 1, &vertSrcPtr, NULL);
        glCompileShader(vertex);

        GLint result;
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
        if(result == GL_FALSE){
            GLint length;
            glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length);
            glGetShaderInfoLog(vertex, length, &length, &error[0]);
            logger<<&error[0];
        }

        glShaderSource(fragment, 1, & fragSrcPtr, NULL);
        glCompileShader(fragment);

        glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
        if(result == GL_FALSE){
            GLint length;
            glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length);
            glGetShaderInfoLog(fragment, length, &length, &error[0]);
            logger<<&error[0];
        }

        glAttachShader(program, vertex);
        glAttachShader(program, fragment);

        glLinkProgram(program);
        return program;
    }

    GLint Shader::f_GetUniformLocation(const std::string &uniformName){
        return glGetUniformLocation(m_ShaderProgram, uniformName.c_str());
    }

    void Shader::setUniformMat4(const std::string &name, const glm::mat4 &mat){
        glUniformMatrix4fv(f_GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void Shader::setUniform1iv(const std::string& name, int *value, int count){
        glUniform1iv(f_GetUniformLocation(name), count, value);
    }

    void Shader::enable(){
        glUseProgram(m_ShaderProgram);
    }

    void Shader::disable(){
        glUseProgram(0);
    }

    void Shader::setUniform2f(const std::string& name, const glm::vec2& vector){
        glUniform2f(f_GetUniformLocation(name), vector.x, vector.y);
    }
}
