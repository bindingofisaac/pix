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
        //TODO: error check
        glShaderSource(fragment, 1, & fragSrcPtr, NULL);
        glCompileShader(fragment);
        //TODO: error check

        glAttachShader(program, vertex);
        glAttachShader(program, fragment);

        glLinkProgram(program);
        return program;
    }

    GLint Shader::f_GetUniformLocation(const std::string &uniformName){
        return glGetUniformLocation(m_ShaderProgram, uniformName.c_str());
    }

    void Shader::enable(){
        glUseProgram(m_ShaderProgram);
    }

    void Shader::disable(){
        glUseProgram(0);
    }
}
