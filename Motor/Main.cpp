#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
int main()
{
    //Definicion de funciones--------------------------------------------------------------
    void framebuffer_size_callback(GLFWwindow * window, int width, int height);
    void processInput(GLFWwindow * window);
    void mouse_callback(GLFWwindow * window, double xpos, double ypos);
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //Hace que capture el cursor y lo vuelve invisible
    glfwSetCursorPosCallback(window, mouse_callback); //Da las coordenadas en pixeles del mouse y se las envia a mouse_callback para que las use
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






    //Como crear camara/como funciona:
    /*
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); //posicion de la camara
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); //Lado contrario al que uqiero que la camara mire
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget); //se normalza (al normalizar)
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); //Se crea un vector que mira para arriba
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection)); //se cruza con la direccion de la camara y se normaliza, el cruzado es para que pase de mirar para arriba al lado positivo de x
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight); //Para obtener arriba cruzamos otra vez esto, y como ya esta no rmalizado no hacemos nada mas
    glm::mat4 view; //Crea la vista
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));
        */
    //lookat toma 3 argumentos
    //Primero el vector de la posicion de la camara
    //Luego a donde tiene que mirar la camara
    //Luego un vector que mire hacia arriba (glm lo usa para crear un vector right)



    //Gestor de errores
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error before glClearColor: " << err << std::endl;
    }



    
    while (!glfwWindowShouldClose(window)) //glfwWindowShouldClose Checkea si window se quiere cerrar y mientras no se quiera cerrar da false.
    {
        //calculo del delta time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Cambia el color de la ventana.
         //Limpia el buffer de profundudad para cambiarlo en el siguiente frame.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();

        //Actualizacion de las matrices (se ponen aqui por si quieres mover algo a tiempo real)
            //Creacion de las matrices
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        glm::mat4 view;
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
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
            modelmatrix = glm::translate(modelmatrix, cubePositions[i]); //Usa glm transyoutulate para transladar la matriz usando el indice para usar los cubePosition definidos anteriormente
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



void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse) //esto es para que cuando metas el raton en la ventana el raton este en el 000 y no en una esquina de la pantalla, ya que daria un salto
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX; //calculamos cuanto se ha movido en la x
    float yoffset = lastY - ypos; //lo mismo en la y
    lastX = xpos; //guardamos la posicion actual para usarla en el siguiente frame
    lastY = ypos;

    float sensitivity = 0.1f; //Esto se multiplica con el offset para manejar cuanto queremos que se mueva la camara segun el raton
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset; //sumamos la diferenia
    pitch += yoffset;

    if (pitch > 89.0f) //que no se pase de 90 grados o podrias darte la vuelta sobre ti mismo
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction; //Contenedor para calcular la direccion
    //Ni idea de las mates que hace aqui pero pitch y yaw son los axis de las rotaciones
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction); //Lo normaliza para mandarlo hacia donde tiene que mirar la camara
}

void processInput(GLFWwindow* window) //Aqui proceso todos los inputs del teclado, raton etc (botones).
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //Si se presiona el escape se cierra la ventana (glfwSetWindowShouldClose para window pasa a true).
        glfwSetWindowShouldClose(window, true);
    float cameraSpeed = 2.5f * deltaTime; //velocidad
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) //Funcion para cambiar el Viewport al tamaño de la ventana.
{
    glViewport(0, 0, width, height);
}

