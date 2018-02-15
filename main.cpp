#include <iostream>
#include <chrono>

#include <GLFW/glfw3.h>

#include "functional_extensions.h"

#include "graphics_system.h"
#include "entity.h"
#include "file_loader.h"
#include "buffer.h"
#include "model_loader.h"

int main()
{
    FileLoader fl;

    std::cout << "benchmarkin!" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Loading cube: ";
    auto cube_buffer = fl.load_file2("./HGkub.obj");
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "time: " << std::chrono::duration<double>(end - start).count() << "s size: " << cube_buffer.size << "B" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    std::cout << "Parsing model: ";
    auto model = parse(cube_buffer);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "time: " << std::chrono::duration<double>(end - start).count() << "s" << std::endl;

    return 0;
    GLFWwindow* window;

    glfwSetErrorCallback([] (int a, const char* c)
    {
        std::cout << "error: " << c << "\n";
    });

    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Atte Motor", NULL, NULL);
    if (!window)
    {
      glfwTerminate();
      return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GraphicsSystem graphics_system;

    Entity entity;

    auto component_id = graphics_system.create_component();

    entity.add_component(GRAPHICS_SYSTEM_ID, component_id);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
      graphics_system.update();
      auto kanske_modell = fmap(graphics_system.get_component(component_id), [] (auto c) { return c->model; });

      std::cout << kanske_modell.value_or(-1) << "\n";

      /* Render here */
      glClear(GL_COLOR_BUFFER_BIT);

      /* Swap front and back buffers */
      glfwSwapBuffers(window);

      /* Poll for and process events */
      glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
