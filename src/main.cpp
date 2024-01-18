#include <iostream>

#include <glad/gl.h>

#include <SDL2/SDL.h>

void handleWindowResize(int w, int h) {
  std::cout << "h: " << h << " w: " << w << '\n';
  glViewport(0, 0, w, h);
}

void handleInput(SDL_Window *window, SDL_Event &event, bool &quit) {
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      quit = true;
      break;
    case SDL_WINDOWEVENT:
      if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
        handleWindowResize(event.window.data1, event.window.data2);
      }
      break;
    }
  }
}

int main(void) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Failed to initialize the SDL2 library\n";
    return -1;
  }

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_Window *window{SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED, 1600, 1200, 0)};

  if (!window) {
    std::cout << "Failed to create GLFW window\n ";
    return -1;
  }

  SDL_SetWindowResizable(window, SDL_TRUE);

  SDL_GLContext context{SDL_GL_CreateContext(window)};

  if (!context) {
    std::cout << "Failed to create SDL2 context\n ";
    return -1;
  }

  // Load OpenGL functions per system.
  int version{gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)};

  printf("Vendor:   %s\n", glGetString(GL_VENDOR));
  printf("Renderer: %s\n", glGetString(GL_RENDERER));
  printf("Version:  %s\n", glGetString(GL_VERSION));

  SDL_Event event;

  bool quit{false};

  while (!quit) {
    // Render
    glClearColor(0.2f, 0.7f, 0.3f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Display
    SDL_GL_SwapWindow(window);
    SDL_Delay(1);

    // Input
    handleInput(window, event, quit);
  }

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
