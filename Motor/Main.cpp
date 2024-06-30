#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
using namespace glm;

int main()
{
    //Definicion de funciones--------------------------------------------------------------
    void framebuffer_size_callback(GLFWwindow * window, int width, int height);
    void processInput(GLFWwindow * window);
    void checkOpenGLError(const char* stmt, const char* fname, int line);
    //Definicion de funciones--------------------------------------------------------------

    

#define CHECK_GL_ERROR(stmt) do { \
    stmt; \
    checkOpenGLError(#stmt, __FILE__, __LINE__); \
} while (0)



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
    glEnable(GL_DEPTH_TEST);//Hace que halla profundidad, esta se calcula cada frame
    glViewport(0, 0, 800, 600); //Define los pixeles en los que opengl va a renderizar cosas

    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //La usa en el contexto actual

    //Contexto de la ventana----------------------------------------------------------------------
    //Contexto de la ventana----------------------------------------------------------------------
    //Shaders-------------------------------------------------------------------------------------
    //Shaders-------------------------------------------------------------------------------------
    


    Shader shader("C:/Users/gutie/source/repos/Motor/Motor/shader.ver", "C:/Users/gutie/source/repos/Motor/Motor/shader.fr"); //Usa el compilador que hice como header y compila el fragment shader y el vertex shader
   



    //En el siguiente procedimiento se preparan los buffers para hacer dos triangulos/ un cuadrado.
    //primero se definen los vertices e indices.
    //Se asigna un Vertex array object para gestionar la informacion
    //Se crea y asigna un vertex buffer object para almacenar los vertices a dibujar
    //Se crea y asigna un element buffer object y le asignas los indices para que sepa el orden en el que se dibujan
    //Le pasa los atributos de posicion en forma de vector 3 para que el shader los pase a vector 4
    //activa el uso de latributo












    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int indices[] = {  //El orden en el que se dibujan los vertizes
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };


    unsigned int VAO; //crea un contenedor
    glGenVertexArrays(1, &VAO); //Crea un Vertex array
    glBindVertexArray(VAO); //Pone en uso el vertex array
    unsigned int VBO;//Crea una variable int llamada VBO (Vertex buffer object).
    glGenBuffers(1, &VBO); //glGenBuffers crea tantos buffers(Colas) en la variable definida como pongamos en el primer input.
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Metemos el VBO en el buffer que toca (GL_ARRAY_BUFFER == vertex).
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Pasa los datos del tercer argumento (vertizes) al buffer recien creado y le dice para que vamos a usar esos datos
    
    //Pilla los vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    //Esto es para los indices.
    /*
    unsigned int EBO; //contenedor
    glGenBuffers(1, &EBO); //crea un buffer con el contenedor

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //Metes el EBO en el buffer que toca
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); //Metes la informacion de los indices del EBO al buffer
    */

    //Con glVertexAttribPointer defino como se usa la infomacion de input del vertex shader.
    //El primer atributo, 0, defino donde quiero mandar la informacion, es la parte de "layout (location = 0) in vec3 aPos" del vertex shader.
    //El segundo atrtibuto dice el tamaño del input, en este caso 3 porque es un vector 3.
    //El tercer atributo consiste en el tipo de dato que vas a pasar como input, en este caso GLSL guarda los vector 3 en un float pointer.
    //Con el cuarto atributo decides si quieres normalizar los datos.
    //El quinto atributo define el espacio entre vertex atributes, en este caso como es un vector 3, pues 3 veces el espacio de un float.
    //El sexto parametro define donde tiene que empezar el atributo en el buffer.
 

    //Texturas
    //Sacas la informacion de la imagen.
    int width, height, nrChannels; //Creo contenedores para el alto largo y colores.
    stbi_set_flip_vertically_on_load(true); //Hago que las imagenes no esten volteadas (Opengl suele darles la vuelta)
    unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0); //Le digo la imagen que quiero usar y le doy los contenedores para que los rellene


    unsigned int texture; //Creo un contenedor
    glGenTextures(1, &texture); //Le digo el numero de texturas y el contenedor.
    glActiveTexture(GL_TEXTURE0); //Le digo el numer ode textura a la que le voy a mandar al shader. (si fuera la segunda textura pues seria glActiveTexture(GL_TEXTURE1);)
    glBindTexture(GL_TEXTURE_2D, texture); //Le asigno la textura (Le digo a opengl que la quiero configurar)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); //El primer parametro es el tipo de textura, el segundo es el axis (s,t,r == x,y,z) el tercero como queremos que se repita etc.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    //Si quisiera cambiar a que no se repita y tenga un borde, tendria que usar glTexParameterfv, que es el que admite floats y darle los colores de la siguiente manerag lTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//Esto cambia el filtro a tipo neares para los objetos pequeños (si tiene que decidir entre 4 pixeles se queda con el mas cercano)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //Esto para los grandes.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //Esto para los minmaps pequeños
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //Esto para los minmaps grandes

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //Esto genera la textura con toda la configuracion anterior
        //Primer argumento: El tipo de textura con el que tratas
        //Segundo argumento: El nivel de minmap que es la textura, 0 = a la maxima calidad
        //Tercer argumento: El formato de colores de la textura.
        //Cuarto argumento: Ancho
        //Quinto argumento: Alto
        //Sexto argumento: Siempre tiene que ser 0
        //Septimo argumento: El formato de colores de la imagen original.
        //Octavo argumento: El formato en el que esta guardada la imagen.
        //Noveno argumento: Los datos de la imagen generados con stbi_load.
        glGenerateMipmap(GL_TEXTURE_2D); //Genera el minmap a la que apunta opengl.

    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data); //Despues de usar los datos de la imagen y generada la textura, estos ya no son necesarios y se liberan de la memoria.
    unsigned int texture2; //Creo un contenedor
    glGenTextures(1, &texture2); //Le digo el numero de texturas y el contenedor.
    glActiveTexture(GL_TEXTURE1); //Le digo el numer ode textura a la que le voy a mandar al shader. (si fuera la segunda textura pues seria glActiveTexture(GL_TEXTURE1);)
    glBindTexture(GL_TEXTURE_2D, texture2); //Le asigno la textura (Le digo a opengl que la quiero configurar)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); //El primer parametro es el tipo de textura, el segundo es el axis (s,t,r == x,y,z) el tercero como queremos que se repita etc.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    //Si quisiera cambiar a que no se repita y tenga un borde, tendria que usar glTexParameterfv, que es el que admite floats y darle los colores de la siguiente manerag lTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//Esto cambia el filtro a tipo neares para los objetos pequeños (si tiene que decidir entre 4 pixeles se queda con el mas cercano)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //Esto para los grandes.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //Esto para los minmaps pequeños
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //Esto para los minmaps grandes

    data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }






    shader.use(); // don't forget to activate the shader before setting uniforms!  
    shader.setInt("texture1", 0); //Esto usa el header que hice de compilador.
    shader.setInt("texture2", 1); // Asigna al unidorm 1 la textura 2








    glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
    };





    //Gestor de errores
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error before glClearColor: " << err << std::endl;
    }



    
    while (!glfwWindowShouldClose(window)) //glfwWindowShouldClose Checkea si window se quiere cerrar y mientras no se quiera cerrar da false.
    {


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Cambia el color de la ventana.
         //Limpia el buffer de profundudad para cambiarlo en el siguiente frame.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();

        //Actualizacion de las matrices (se ponen aqui por si quieres mover algo a tiempo real)
            //Creacion de las matrices
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


        //RECUERDA INICIALIZAR VARIABLES AQUI
        unsigned int modelMatrixLoc = glGetUniformLocation(shader.ID, "modelmatrix");
        
        unsigned int viewMatrixLoc = glGetUniformLocation(shader.ID, "viewmatrix");
        glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(view));
        unsigned int projectMatrixLoc = glGetUniformLocation(shader.ID, "projectionmatrix");
        glUniformMatrix4fv(projectMatrixLoc, 1, GL_FALSE, glm::value_ptr(projection));
       
  
        //El primer argumento es que primitivos dibujar.
        //El segundo argumento es la cantidad de indices que usas, 6 en este caso.
        //El tercer argumento es el tipo de dato que usas para los vertices.
        //El cuarto es donde empieza el EBO, en 0 en este caso.

        
        processInput(window); //Comprueba los inputs en cada frame


        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 modelmatrix = glm::mat4(1.0f);
            modelmatrix = glm::translate(modelmatrix, cubePositions[i]); //Usa glm translate para transladar la matriz usando el indice para usar los cubePosition definidos anteriormente
            float angle = 20.0f * i; //Multiplica el angulo por el indice para que cada cubo este en un angulo distinto
            modelmatrix = glm::rotate(modelmatrix, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f)); //Cambia el modelmatrix
            glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelmatrix)); //Manda el modelo al uniform

            glDrawArrays(GL_TRIANGLES, 0, 36); //Lo dibuja
        }


        glfwSwapBuffers(window); //Cambia del buffer de renderizado al de color para mostrar la ventana.
        glfwPollEvents(); //Comprueba cosas como inputs del teclado etc, para actualizar la ventana cuando sea necesario.
    }





    glfwTerminate(); //Borra todos los recursos usados, para que dejen de usar espacio en tu ordenador mientras no se ejecuta.
    return 0;
}




void checkOpenGLError(const char* stmt, const char* fname, int line) { //Comprueba errores comunes
    GLenum err = glGetError();
    while (err != GL_NO_ERROR) {
        std::string error;
        switch (err) {
        case GL_INVALID_OPERATION:      error = "GL_INVALID_OPERATION";      break;
        case GL_INVALID_ENUM:           error = "GL_INVALID_ENUM";           break;
        case GL_INVALID_VALUE:          error = "GL_INVALID_VALUE";          break;
        case GL_OUT_OF_MEMORY:          error = "GL_OUT_OF_MEMORY";          break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "GL_INVALID_FRAMEBUFFER_OPERATION";  break;
        default:                        error = "Unknown error";             break;
        }
        std::cerr << "OpenGL error in file " << fname << " at line " << line << ": " << stmt << " - " << error << std::endl;
        err = glGetError();
    }
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

