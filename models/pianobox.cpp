#include "pianobox.h"

namespace Models {

    PianoBox pianobox;

    PianoBox::PianoBox(){
    /*    vertices = PianoBoxInternal::vertices;
        normals = PianoBoxInternal::normals;
        vertexNormals = PianoBoxInternal::vertexNormals;
        texCoords = PianoBoxInternal::texCoords;
        colors = PianoBoxInternal::colors;
        vertexCount = PianoBoxInternal::vertexCount;

        std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
        unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
        //Wczytaj obrazek
        unsigned error = lodepng::decode(image, width, height, "wood.png");
        if(error != 0)
        printf("error\n");
        //Import do pamięci karty graficznej
        glGenTextures(1,&tex); //Zainicjuj jeden uchwyt
        glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
        glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
         GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());*/
        //Making VBO

            }
    PianoBox::~PianoBox(){
        delete shaderProgram;
        //glDeleteTextures(1,&tex);
        glDeleteBuffers(1,&bufVertices);
        glDeleteBuffers(1,&bufNormals);
        glDeleteBuffers(1,&bufColors);
    }
    void PianoBox::init(){
        shaderProgram=new ShaderProgram((char*)"vshader.txt",NULL,(char*)"fshader.txt");
        bufVertices = makeBuffer(PianoBoxInternal::vertices, PianoBoxInternal::vertexCount, sizeof(float)*4);
        bufNormals = makeBuffer(PianoBoxInternal::normals, PianoBoxInternal::vertexCount, sizeof(float)*4);
        bufColors = makeBuffer(PianoBoxInternal::colors, PianoBoxInternal::vertexCount, sizeof(float)*4);

        glGenVertexArrays(1,&vao); //Wygeneruj uchwyt na VAO i zapisz go do zmiennej globalnej

        glBindVertexArray(vao); //Uaktywnij nowo utworzony VAO
        assignVBOtoAttribute(shaderProgram,(char*)"vertex",bufVertices,4); //"vertex" odnosi się do deklaracji "in vec4 vertex;" w vertex shaderze
        assignVBOtoAttribute(shaderProgram,(char*)"color",bufColors,4); //"color" odnosi się do deklaracji "in vec4 color;" w vertex shaderze
        assignVBOtoAttribute(shaderProgram,(char*)"normal",bufNormals,4); //"normal" odnosi się do deklaracji "in vec4 normal;" w vertex shaderze
        glBindVertexArray(0); //Dezaktywuj VAO
    }
    void PianoBox::drawModel(glm::mat4 mP, glm::mat4 mV, glm::mat4 mM){
        shaderProgram->use();
        glUniformMatrix4fv(shaderProgram->getUniformLocation((char*)"P"),1, false, glm::value_ptr(mP));
    	glUniformMatrix4fv(shaderProgram->getUniformLocation((char*)"V"),1, false, glm::value_ptr(mV));
    	glUniformMatrix4fv(shaderProgram->getUniformLocation((char*)"M"),1, false, glm::value_ptr(mM));
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES,0,PianoBoxInternal::vertexCount);
        glBindVertexArray(0);
        shaderProgram->disable();
    }

    namespace PianoBoxInternal{
        unsigned int vertexCount = 72;

        float vertices[] = {
        //nieruchliwa góra
        -0.723f,0.602f,-0.275f,1.0f,
        -0.723f,0.602f,-0.1375f,1.0f,
        0.723f,0.602f,-0.275f,1.0f,

        -0.723f,0.602f,-0.1375f,1.0f,
        0.723f,0.602f,-0.275f,1.0f,
        0.723f,0.602f,-0.1375f,1.0f,

        //lewa sciana
        -0.723f,0.602f,-0.275f,1.0f,
        -0.723f,0.602f,-0.0f,1.0f,
        -0.723f,-0.602f,-0.275f,1.0f,

        -0.723f,-0.602f,0.0f,1.0f,
        -0.723f,0.602f,0.0f,1.0f,
        -0.723f,-0.602f,-0.275f,1.0f,

        //tylna ściana
        -0.723f,0.602f,-0.275f,1.0f,
        0.723f,0.602f,-0.275f,1.0f,
        -0.723f,-0.602f,-0.275f,1.0f,

        0.723f,-0.602f,-0.275f,1.0f,
        0.723f,0.602f,-0.275f,1.0f,
        -0.723f,-0.602f,-0.275f,1.0f,

        //prawy bok
        0.723f,0.602f,-0.275f,1.0f,
        0.723f,0.602f,-0.0f,1.0f,
        0.723f,-0.602f,-0.275f,1.0f,

        0.723f,-0.602f,0.0f,1.0f,
        0.723f,0.602f,0.0f,1.0f,
        0.723f,-0.602f,-0.275f,1.0f,

        //dolny bok
        -0.723f, -0.602f, -0.275f,1.0f,
        -0.723f, -0.602f, 0.0f,1.0f,
        0.723f, -0.602f, -0.275f,1.0f,

        0.723f, -0.602f, 0.0f,1.0f,
        -0.723f, -0.602f, 0.0f,1.0f,
        0.723f, -0.602f, -0.275f,1.0f,

        //przednia ściana
        -0.723f,0.602f,0.0f,1.0f,
        0.723f,0.602f,0.0f,1.0f,
        -0.723f,-0.602f,0.0f,1.0f,

        0.723f,-0.602f,0.0f,1.0f,
        0.723f,0.602f,0.0f,1.0f,
        -0.723f,-0.602f,0.0f,1.0f,

        //prawy bok klawiszy
        0.723f, 0.15f, 0.0f, 1.0f,
        0.723f, 0.15f, 0.27f, 1.0f,
        0.723f, -0.15f, 0.27f, 1.0f,

        0.723f, 0.15f, 0.0f, 1.0f,
        0.723f, -0.15f, 0.0f, 1.0f,
        0.723f, -0.15f, 0.27f, 1.0f,

        //lewy bok klawiszy
        -0.723f, 0.15f, 0.0f, 1.0f,
        -0.723f, 0.15f, 0.27f, 1.0f,
        -0.723f, -0.15f, 0.27f, 1.0f,

        -0.723f, 0.15f, 0.0f, 1.0f,
        -0.723f, -0.15f, 0.0f, 1.0f,
        -0.723f, -0.15f, 0.27f, 1.0f,

        //dół klawiszy
        -0.723f,-0.15f,0.27f,1.0f,
        0.723f,-0.15f,0.27f,1.0f,
        0.723f,-0.15f,0.0f,1.0f,

        -0.723f,-0.15f,0.27f,1.0f,
        -0.723f,-0.15f,0.0f,1.0f,
        0.723f,-0.15f,0.0f,1.0f,

        //front klawiszy
        -0.723f,0.05f,0.27f,1.0f,
        0.723f,0.05f,0.27f,1.0f,
        0.723f,-0.15f,0.27f,1.0f,

        -0.723f,0.05f,0.27f,1.0f,
        -0.723f,-0.15f,0.27f,1.0f,
        0.723f,-0.15f,0.27f,1.0f,

        };
        float colors[]={
                //nieruchliwa góra
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,

        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,

        //lewa sciana
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,

        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,

        //tylna ściana
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,

        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,

        //prawy bok
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,

        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,

        //dolny bok
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,

        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,

        //przednia ściana
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,

        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,

        //prawy bok klawiszy
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,

        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,

        //lewy bok klawiszy
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,

        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,

        //dół klawiszy
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,

        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,

        //front klawiszy
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,

        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,
        0.82f,0.74f,0.65f,1.0f,
			};
            float normals[]={
                //nieruchliwa góra
        0.0f,1.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,0.0f,

        0.0f,1.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,0.0f,

        //lewa sciana
        -1.0f,0.0f,0.0f,0.0f,
        -1.0f,0.0f,0.0f,0.0f,
        -1.0f,0.0f,0.0f,0.0f,

        -1.0f,0.0f,0.0f,0.0f,
        -1.0f,0.0f,0.0f,0.0f,
        -1.0f,0.0f,0.0f,0.0f,

        //tylna ściana
        0.0f,0.0f,-1.0f,0.0f,
        0.0f,0.0f,-1.0f,0.0f,
        0.0f,0.0f,-1.0f,0.0f,

        0.0f,0.0f,-1.0f,0.0f,
        0.0f,0.0f,-1.0f,0.0f,
        0.0f,0.0f,-1.0f,0.0f,

        //prawy bok
        1.0f,0.0f,0.0f,0.0f,
        1.0f,0.0f,0.0f,0.0f,
        1.0f,0.0f,0.0f,0.0f,

        1.0f,0.0f,0.0f,0.0f,
        1.0f,0.0f,0.0f,0.0f,
        1.0f,0.0f,0.0f,0.0f,
        //dolny bok
        0.0f,-1.0f,0.0f,0.0f,
        0.0f,-1.0f,0.0f,0.0f,
        0.0f,-1.0f,0.0f,0.0f,

        0.0f,-1.0f,0.0f,0.0f,
        0.0f,-1.0f,0.0f,0.0f,
        0.0f,-1.0f,0.0f,0.0f,

        //przednia ściana
        0.0f,0.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f,0.0f,

        0.0f,0.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f,0.0f,

        //prawy bok klawiszy
        1.0f,0.0f,0.0f,0.0f,
        1.0f,0.0f,0.0f,0.0f,
        1.0f,0.0f,0.0f,0.0f,

        1.0f,0.0f,0.0f,0.0f,
        1.0f,0.0f,0.0f,0.0f,
        1.0f,0.0f,0.0f,0.0f,

        //lewy bok klawiszy
        -1.0f,0.0f,0.0f,0.0f,
        -1.0f,0.0f,0.0f,0.0f,
        -1.0f,0.0f,0.0f,0.0f,

        -1.0f,0.0f,0.0f,0.0f,
        -1.0f,0.0f,0.0f,0.0f,
        -1.0f,0.0f,0.0f,0.0f,
        //dół klawiszy
        0.0f,-1.0f,0.0f,0.0f,
        0.0f,-1.0f,0.0f,0.0f,
        0.0f,-1.0f,0.0f,0.0f,

        0.0f,-1.0f,0.0f,0.0f,
        0.0f,-1.0f,0.0f,0.0f,
        0.0f,-1.0f,0.0f,0.0f,

        //front klawiszy
        0.0f,0.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f,0.0f,

        0.0f,0.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f,0.0f,
			};

			float vertexNormals[]={
                //nieruchliwa góra
                -0.723f,0.602f,-0.275f,1.0f,
                -0.723f,0.602f,-0.1375f,1.0f,
                0.723f,0.602f,-0.275f,1.0f,

                -0.723f,0.602f,-0.1375f,1.0f,
                0.723f,0.602f,-0.275f,1.0f,
                0.723f,0.602f,-0.1375f,1.0f,

                //lewa sciana
                -0.723f,0.602f,-0.275f,1.0f,
                -0.723f,0.602f,-0.0f,1.0f,
                -0.723f,-0.602f,-0.275f,1.0f,

                -0.723f,-0.602f,0.0f,1.0f,
                -0.723f,0.602f,0.0f,1.0f,
                -0.723f,-0.602f,-0.275f,1.0f,

                //tylna ściana
                -0.723f,0.602f,-0.275f,1.0f,
                0.723f,0.602f,-0.275f,1.0f,
                -0.723f,-0.602f,-0.275f,1.0f,

                0.723f,-0.602f,-0.275f,1.0f,
                0.723f,0.602f,-0.275f,1.0f,
                -0.723f,-0.602f,-0.275f,1.0f,

                //prawy bok
                0.723f,0.602f,-0.275f,1.0f,
                0.723f,0.602f,-0.0f,1.0f,
                0.723f,-0.602f,-0.275f,1.0f,

                0.723f,-0.602f,0.0f,1.0f,
                0.723f,0.602f,0.0f,1.0f,
                0.723f,-0.602f,-0.275f,1.0f,

                //dolny bok
                -0.723f, -0.602f, -0.275f,1.0f,
                -0.723f, -0.602f, 0.0f,1.0f,
                0.723f, -0.602f, -0.275f,1.0f,

                0.723f, -0.602f, 0.0f,1.0f,
                -0.723f, -0.602f, 0.0f,1.0f,
                0.723f, -0.602f, -0.275f,1.0f,

                //przednia ściana
                -0.723f,0.602f,0.0f,1.0f,
                0.723f,0.602f,0.0f,1.0f,
                -0.723f,-0.602f,0.0f,1.0f,

                0.723f,-0.602f,0.0f,1.0f,
                0.723f,0.602f,0.0f,1.0f,
                -0.723f,-0.602f,0.0f,1.0f,

                //prawy bok klawiszy
                0.723f, 0.15f, 0.0f, 1.0f,
                0.723f, 0.15f, 0.27f, 1.0f,
                0.723f, -0.15f, 0.27f, 1.0f,

                0.723f, 0.15f, 0.0f, 1.0f,
                0.723f, -0.15f, 0.0f, 1.0f,
                0.723f, -0.15f, 0.27f, 1.0f,

                //lewy bok klawiszy
                -0.723f, 0.15f, 0.0f, 1.0f,
                -0.723f, 0.15f, 0.27f, 1.0f,
                -0.723f, -0.15f, 0.27f, 1.0f,

                -0.723f, 0.15f, 0.0f, 1.0f,
                -0.723f, -0.15f, 0.0f, 1.0f,
                -0.723f, -0.15f, 0.27f, 1.0f,

                //dół klawiszy
                -0.723f,-0.15f,0.27f,1.0f,
                0.723f,-0.15f,0.27f,1.0f,
                0.723f,-0.15f,0.0f,1.0f,

                -0.723f,-0.15f,0.27f,1.0f,
                -0.723f,-0.15f,0.0f,1.0f,
                0.723f,-0.15f,0.0f,1.0f,

                //front klawiszy
                -0.723f,0.15f,0.27f,1.0f,
                0.723f,0.15f,0.27f,1.0f,
                0.723f,-0.15f,0.27f,1.0f,

                -0.723f,0.15f,0.27f,1.0f,
                -0.723f,-0.15f,0.27f,1.0f,
                0.723f,-0.15f,0.27f,1.0f
			};

			float texCoords[]={
                //nieruchliwa góra
                0.0f,0.0f, 0.0f,1.0f, 1.0f,0.0f,
                0.0f,1.0f, 1.0f,0.0f, 1.0f,1.0f,

                //lewa sciana
                1.0f,0.0f, 1.0f,1.0f, 0.0f,0.0f,
                0.0f,1.0f, 1.0f,1.0f, 0.0f,0.0f,

                //tylna ściana
                0.0f,1.0f, 1.0f,1.0f, 0.0f,0.0f,
                1.0f,0.0f, 1.0f,1.0f, 0.0f,0.0f,

                //prawy bok
                1.0f,0.0f, 1.0f,1.0f, 0.0f,0.0f,
                0.0f,1.0f, 1.0f,1.0f, 0.0f,0.0f,

                //dolny bok
                0.0f,0.0f, 0.0f,1.0f, 1.0f,0.0f,
                1.0f,1.0f, 0.0f,1.0f, 1.0f,0.0f,
                //przednia ściana
                0.0f,1.0f, 1.0f,1.0f, 0.0f,0.0f,
                1.0f,0.0f, 1.0f,1.0f, 0.0f,0.0f,

                //prawy bok klawiszy
                1.0f,0.0f, 1.0f,1.0f, 0.0f,1.0f,
                1.0f,0.0f, 0.0f,0.0f, 0.0f,1.0f,

                //lewy bok klawiszy
                1.0f,0.0f, 1.0f,1.0f, 0.0f,1.0f,
                1.0f,0.0f, 0.0f,0.0f, 0.0f,1.0f,

                //dół klawiszy
                0.0f,1.0f, 1.0f,1.0f, 1.0f,0.0f,
                0.0f,1.0f, 0.0f,0.0f, 1.0f,0.0f,

                //front klawiszy
                0.0f,1.0f, 1.0f,1.0f, 1.0f,0.0f,
                0.0f,1.0f, 0.0f,0.0f, 1.0f,0.0f,
			};
    }

}