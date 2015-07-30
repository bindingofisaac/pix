#include <BatchRenderer2D.hpp>

namespace Pix{
    BatchRenderer2D::BatchRenderer2D() : m_IndexCount(0){
        init();
    }

    BatchRenderer2D::~BatchRenderer2D(){
        delete m_IBO;
        delete m_FTFont;
        delete m_FTAtlas;
        glDeleteBuffers(1, &m_VBO);
        glDeleteVertexArrays(1, &m_VAO);
    }

    void BatchRenderer2D::init(){
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, uv)));
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, tid)));
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, color)));

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        GLushort *indices = new GLushort[RENDERER_INDICES_SIZE];

        for(int i=0, offset=0;i<RENDERER_INDICES_SIZE;i+=6, offset += 4){
            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;
            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;
        }

        m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

        glBindVertexArray(0);
        m_FTAtlas = ftgl::texture_atlas_new(512, 512, 3);
        m_FTFont  = ftgl::texture_font_new_from_file(m_FTAtlas, 16, "arial.ttf");
    }

    void BatchRenderer2D::begin(){
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        m_Buffer = (VertexData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    }

    void BatchRenderer2D::submit(const Renderable2D* renderable){
        const glm::vec4 &position = glm::vec4(renderable->getPosition(), 1);
        const glm::vec2 &size     = renderable->getSize();
        const glm::vec4 &color    = renderable->getColor();
        const std::vector<glm::vec2> &uv       = renderable->getUV();
        const GLuint tid = renderable->getTID();
        glm::mat4 ts = m_TransformationStack.back();
        float tes = 0.0f;
        if(tid > 0){
            bool  found = false;
            for(int i=0; i<m_TextureSlots.size(); i++){
                if(m_TextureSlots[i] == tid){
                    tes = i+1;
                    found = true;
                    break;
                }
            }

            if(!found){
                if(m_TextureSlots.size() >= 32){
                    end();
                    flush();
                    begin();
                    m_TextureSlots.clear(); // TODO check with more than 32 different textures
                }
                m_TextureSlots.push_back(tid);
                tes = m_TextureSlots.size();
            }
        }

        m_Buffer->vertex = (ts * position).xyz();
        m_Buffer->uv     = uv[0];
        m_Buffer->tid    = tes;
        m_Buffer->color  = color;
        m_Buffer++;

        m_Buffer->vertex = (ts * glm::vec4(position.x, position.y + size.y, position.z, 1)).xyz();
        m_Buffer->uv     = uv[1];
        m_Buffer->tid    = tes;
        m_Buffer->color  = color;
        m_Buffer++;

        m_Buffer->vertex = (ts * glm::vec4(position.x + size.x, position.y + size.y, position.z, 1)).xyz();
        m_Buffer->uv     = uv[2];
        m_Buffer->tid    = tes;
        m_Buffer->color  = color;
        m_Buffer++;

        m_Buffer->vertex = (ts * glm::vec4(position.x + size.x, position.y, position.z, 1)).xyz();
        m_Buffer->uv     = uv[3];
        m_Buffer->tid    = tes;
        m_Buffer->color  = color;
        m_Buffer++;

        m_IndexCount += 6;
    }

    void BatchRenderer2D::end(){
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void BatchRenderer2D::flush(){
        for(int i=0;i<m_TextureSlots.size(); i++){
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
        }
        glBindVertexArray(m_VAO);
        m_IBO->bind();
        glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_SHORT, 0);
        m_IBO->unbind();
        glBindVertexArray(0);

        m_IndexCount = 0;
    }

    void BatchRenderer2D::drawString(const std::string &text, glm::vec3 position, glm::vec4 color){
        using namespace ftgl;

        float tes = 0.0f;
        bool  found = false;
        for(int i=0; i<m_TextureSlots.size(); i++){
            if(m_TextureSlots[i] == m_FTAtlas->id){
                tes = i+1;
                found = true;
                break;
            }
        }
        if(!found){
            if(m_TextureSlots.size() >= 32){
                end();
                flush();
                begin();
                m_TextureSlots.clear(); // TODO check with more than 32 different textures
            }
            m_TextureSlots.push_back(m_FTAtlas->id);
            tes = m_TextureSlots.size();
        }

        float scalex = 960.0f / 32.0f;
        float scaley = 960.0f / 18.0f;

        glm::mat4 ts = m_TransformationStack.back();

        float x = position.x;
        for(int i=0;i<text.length();i++){
            char c = text.at(i);
            texture_glyph_t *glyph = texture_font_get_glyph(m_FTFont, c);
            if(glyph){
                float x0 = x + glyph->offset_x/scalex;
                float y0 = position.y-glyph->offset_y/scaley+m_FTFont->height/scaley;
                float x1 = x0 + glyph->width/scalex;
                float y1 = y0 + glyph->height/scaley;

                float u0 = glyph->s0;
                float v0 = glyph->t0;
                float u1 = glyph->s1;
                float v1 = glyph->t1;

                m_Buffer->vertex = (ts*glm::vec4(glm::vec3(x0, y0, 0), 1)).xyz();
                m_Buffer->uv     = glm::vec2(u0, v0);
                m_Buffer->tid    = tes;
                m_Buffer->color  = color;
                m_Buffer++;

                m_Buffer->vertex = (ts*glm::vec4(glm::vec3(x0, y1, 0), 1)).xyz();
                m_Buffer->uv     = glm::vec2(u0, v1);
                m_Buffer->tid    = tes;
                m_Buffer->color  = color;
                m_Buffer++;

                m_Buffer->vertex = (ts*glm::vec4(glm::vec3(x1, y1, 0), 1)).xyz();
                m_Buffer->uv     = glm::vec2(u1, v1);
                m_Buffer->tid    = tes;
                m_Buffer->color  = color;
                m_Buffer++;

                m_Buffer->vertex = (ts*glm::vec4(glm::vec3(x1, y0, 0), 1)).xyz();
                m_Buffer->uv     = glm::vec2(u1, v0);
                m_Buffer->tid    = tes;
                m_Buffer->color  = color;
                m_Buffer++;

                m_IndexCount += 6;
                x += glyph->advance_x/scalex;
            }
        }
    }
}
