#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
using namespace glm;

const char* vertexShaderSource =  //El vertex shader
"#version 460 core\n" //Version de openGL que usas
"layout (location = 0) in vec3 aPos;\n" //Le dice la posicion donde quiere guardar los datos y que datos quiere guardar del input.
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" //Transforma el vector 3 de entrada a un vetor 4 y se lo asigna a gl_Position
"}\0";

const char* fragmentShaderSource = 
"#version 460 core\n"
"out vec4 FragColor;\n" //Definimos la variable que queremos poner de output
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n" //naranja, literalmente es el color naranja en rgb y opaco (por eso es un vector 4)
"}\n\0";

int main()
{
    //Definicion de funciones--------------------------------------------------------------
    void framebuffer_size_callback(GLFWwindow * window, int width, int height);
    void processInput(GLFWwindow * window);
    //Definicion de funciones--------------------------------------------------------------







    if (!glfwInit()) //Si cuando se inicia no funciona da error (Ejecuta la funcion en el if xd)
    {
        fprintf(stderr, "Error al inicializar GLFW\n");
        return -1;
    }

    //Ventana
    //Opciones
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Queremos OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Para hacer feliz a MacOS ; Aunque no debería ser necesaria
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //No queremos el viejo OpenGL 

    //Contexto de la ventana----------------------------------------------------------------------
    //Contexto de la ventana----------------------------------------------------------------------
    GLFWwindow* window = glfwCreateWindow(800, 600, "Motor 0.00001", NULL, NULL); //Se definen los parametros de la ventana en la variable global GLFWwindow
    if (window == NULL) //Si no se define bien ventana, da error.
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //Inicia GLAD y si no pues da error
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600); //Define los pixeles en los que opengl va a renderizar cosas

    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //La usa en el contexto actual

    //Contexto de la ventana----------------------------------------------------------------------
    //Contexto de la ventana----------------------------------------------------------------------
    //Shaders-------------------------------------------------------------------------------------
    //Shaders-------------------------------------------------------------------------------------
    
    //Vertex shader (Posicion)
    unsigned int vertexShader; //Creo una variable int
    vertexShader = glCreateShader(GL_VERTEX_SHADER); //Le asigno a la variable un shader vertex
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //Metemos el shader (La varialbe global de arriba) a el shader vario recien creado.
    glCompileShader(vertexShader); //Lo compilas

    //Fragment shader (Color)
    unsigned int fragmentShader; //Variable para usarla como contenedor del shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //Le digo a open gl que voy a meter un shader tipo fragment a la variable
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); //Le meto el shader de la variable global de arriba
    glCompileShader(fragmentShader); //Y lo compilo

    //Shader program (Junta los shaders)
    unsigned int shaderProgram; //Contenedor
    shaderProgram = glCreateProgram(); //Le digo a opengl que voy a crear un programa aqui.
    glAttachShader(shaderProgram, vertexShader); //Mete el shader vertex
    glAttachShader(shaderProgram, fragmentShader); //Mete el fragment shader
    glLinkProgram(shaderProgram); //Los junta

    
    glDeleteShader(vertexShader); //Borra los shaders antes compilados, pues ya no tienen uso.
    glDeleteShader(fragmentShader);
    //Shaders-------------------------------------------------------------------------------------
    //Shaders-------------------------------------------------------------------------------------




   



    //En el siguiente procedimiento se preparan los buffers para hacer dos triangulos/ un cuadrado.
    //primero se definen los vertices e indices.
    //Se asigna un Vertex array object para gestionar la informacion
    //Se crea y asigna un vertex buffer object para almacenar los vertices a dibujar
    //Se crea y asigna un element buffer object y le asignas los indices para que sepa el orden en el que se dibujan
    //Le pasa los atributos de posicion en forma de vector 3 para que el shader los pase a vector 4
    //activa el uso de latributo


    float vertices[] = { //Los vertizes para nuetro objeto (En este caso un rectangulo)
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  //El orden en el que se dibujan los vertizes
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };


    unsigned int VAO; //crea un contenedor
    glGenVertexArrays(1, &VAO); //Crea un Vertex array
    glBindVertexArray(VAO); //Pone en uso el vertex array
    unsigned int VBO;//Crea una variable int llamada VBO (Vertex buffer object).
    glGenBuffers(1, &VBO); //glGenBuffers crea tantos buffers(Colas) en la variable definida como pongamos en el primer input.
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Metemos el VBO en el buffer que toca (GL_ARRAY_BUFFER == vertex).
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Pasa los datos del tercer argumento (vertizes) al buffer recien creado y le dice para que vamos a usar esos datos

    unsigned int EBO; //contenedor
    glGenBuffers(1, &EBO); //crea un buffer con el contenedor

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //Metes el EBO en el buffer que toca
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); //Metes la informacion de los indices del EBO al buffer


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //Con glVertexAttribPointer defino como se usa la infomacion de input del vertex shader.
    //El primer atributo, 0, defino donde quiero mandar la informacion, es la parte de "layout (location = 0) in vec3 aPos" del vertex shader.
    //El segundo atrtibuto dice el tamaño del input, en este caso 3 porque es un vector 3.
    //El tercer atributo consiste en el tipo de dato que vas a pasar como input, en este caso GLSL guarda los vector 3 en un float pointer.
    //Con el cuarto atributo decides si quieres normalizar los datos.
    //El quinto atributo define el espacio entre vertex atributes, en este caso como es un vector 3, pues 3 veces el espacio de un float.
    //El sexto parametro define donde tiene que empezar el atributo en el buffer.
    glEnableVertexAttribArray(0); //Permite el uso del primer atributo, se indexan en orden, empezando desde 0.







    while (!glfwWindowShouldClose(window)) //glfwWindowShouldClose Checkea si window se quiere cerrar y mientras no se quiera cerrar da false.
    {


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Cambia el color de la ventana.
        glClear(GL_COLOR_BUFFER_BIT); //Borra los pixeles negros del color base (negro).

        glUseProgram(shaderProgram); //Usa el shader program recien creado 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //Abajo comentarios :)
        //El primer argumento es que primitivos dibujar.
        //El segundo argumento es la cantidad de indices que usas, 6 en este caso.
        //El tercer argumento es el tipo de dato que usas para los vertices.
        //El cuarto es donde empieza el EBO, en 0 en este caso.


        processInput(window); //Comprueba los inputs en cada frame

        glfwSwapBuffers(window); //Cambia del buffer de renderizado al de color para mostrar la ventana.
        glfwPollEvents(); //Comprueba cosas como inputs del teclado etc, para actualizar la ventana cuando sea necesario.
    }





    glfwTerminate(); //Borra todos los recursos usados, para que dejen de usar espacio en tu ordenador mientras no se ejecuta.
    return 0;
}






void processInput(GLFWwindow* window) //Aqui proceso todos los inputs del teclado, raton etc (botones).
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //Si se presiona el escape se cierra la ventana (glfwSetWindowShouldClose para window pasa a true).
        glfwSetWindowShouldClose(window, true);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) //Funcion para cambiar el Viewport al tamaño de la ventana.
{
    glViewport(0, 0, width, height);
}

