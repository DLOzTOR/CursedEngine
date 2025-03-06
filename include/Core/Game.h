#include "Core/Window.h"
namespace Core {
	class Game : public Window {
	private:
		virtual void Update() = 0;
		virtual void Exit() = 0;
	public:
		Game(int width, int height, const char* title);
		virtual void Start() = 0;
	};
}