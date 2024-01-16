#include <iostream>
#define GL_SILENCE_DEPRECATION

#include <glad/gl.h>

#include <SDL2/SDL.h>

void handleWindowResize(SDL_Window *window) {
  int w{};
  int h{};
  SDL_GetWindowSize(window, &w, &h);
  glViewport(0, 0, w, h);
}

void handleInput(SDL_Window *window, SDL_Event &event, bool &quit) {
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      quit = true;
      break;
    case SDL_WINDOWEVENT_RESIZED:
    case SDL_WINDOWEVENT_SIZE_CHANGED:
      handleWindowResize(window);
      break;
    }
  }
}

int main(void) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Failed to initialize the SDL2 library\n";
    return -1;
  }

  SDL_GL_LoadLibrary(NULL);

  SDL_Window *window{SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED, 1600, 1200, 0)};

  SDL_SetWindowResizable(window, SDL_TRUE);

  if (!window) {
    std::cout << "Failed to create GLFW window\n ";
    return -1;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_GLContext maincontext{SDL_GL_CreateContext(window)};

  if (maincontext == NULL) {
    std::cout << "Failed to create SDL2 context\n ";
    return -1;
  }

  // Check OpenGL properties
  printf("OpenGL loaded\n");

  gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);

  printf("Vendor:   %s\n", glGetString(GL_VENDOR));
  printf("Renderer: %s\n", glGetString(GL_RENDERER));
  printf("Version:  %s\n", glGetString(GL_VERSION));

  handleWindowResize(window);

  SDL_Event event;

  bool quit{false};

  while (!quit) {
    glClearColor(0.2f, 0.3f, 1.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(window);
    handleInput(window, event, quit);
  }

  return 0;
}
