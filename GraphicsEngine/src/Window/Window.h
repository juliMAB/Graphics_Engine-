#include <GLFW/glfw3.h>
#ifndef WINDOW_H
#define WINDOW_H

#ifdef GraficosEngine_Exports
#define GraficosEngine_API __declspec(dllexport) //Especifica clase para exportacion
#else
#define GraficosEngine_API __declspec(dllimport) //Especifica clase para importacion
#endif
namespace Graficos1 {

	class GraficosEngine_API Window {
		GLFWwindow* _window;
	public:
		Window();
		~Window();
		int MakeWindow(int width, int height, const char* windowName, GLFWmonitor* fullScreen);
		void InitWindow();
		int CheckIfWindowIsOpen();
		void ClearWindow(float r, float g, float b, float a);
		void SwapBuffers();
		void DestroyWindow();
		GLFWwindow* GetWindow();
	};

}

#endif