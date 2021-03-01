/*! \mainpage Computer Graphics Task 1
 *
 * \section intro_sec Introduction
 *
 * The goal of the task is to master the basics of developing interactive graphics applications and working with images. Material to be learned: 
 *    - working with images-overlay using alpha blending, filters;
 *    - working with the window system and the frame buffer;
 *    - processing user input / output.
 * 
 * As an interactive graphics application, you need to implement a simple 2D game in the roguelike genre according to the option.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Pre-checks
 * 
 * Make sure you're in the root directory of this project
 * 
 * \subsection step2 Step 2: Install dependencies
 * 
 * To install dependencies in Ubuntu, make executable and run following script:
 * ```
 *    chmod +x ./install.sh
 *    sudo ./install.sh
 * ```
 * \subsection step3 Step 3: Build the project
 * 
 * If you use CMake version 3.0 and newer, build the project this way:
 * ```
 *    cmake -B build
 *    make -C build
 * ```
 * If you use an older version:
 * ```
 *    mkdir build
 *    cd build
 *    cmake ..
 *    make
 *    cd ..
 * ```
 * \section run_sec Running
 * 
 * To run the project hit:
 * ```
 *    ./bin/main
 * ```
 * 
 * \section task_sec Task statement
 * 
## Brief

Rogue-like с лабиринтом из комнат (на подобие Hades, Binding of Isaac, подземелий в Legend of Zelda: A link to the past etc.)

## More

Игроку необходимо выбраться из лабиринта, состоящего из соединенных между собой квадратных/ прямоугольных комнат нескольких разных типов. Из очередной комнаты игроку доступно от 1 до 4 выходов (по одному возможному выходу в каждой из стен).

* **Обязательными элементами задания являются:**

- Чтение карты общего лабиринта и карты комнат разных типов из текстовых файлов. Лабиринт состоит минимум из 20 комнат 4 разных типов. Одна комната целиком помещается на экран.
- Каждый символ в текстовом файле общего лабиринта задаёт один из нескольких типов комнат - ‘A’, ‘B’, ‘C’, ...:
- Каждый символ в текстовом файле для комнаты задает один из нескольких вариантов тайла:
  - пустое пространство: ` ` (пробел)
  - стена: `#`
  - пол: `.`
  - игрок: `@`
  - выход из комнаты: `x`
  - выход из всего лабиринта: `Q`
  - ключи, которые позволяют открывать закрытые выходы из комнат: `K`
- Визуализация карты при помощи графики с обязательным отображением всех игровых элементов разными изображениями (тайлами/спрайтами). 
- Реализация движения и взаимодействия с окружения игрока при помощи управления с клавиатуры (например, W, A, S, D, пробел). Игрок не должен проходить сквозь стены.
- При попадании в пустоту/ловушку игрок должен умирать: с помощью графики необходимо вывести сообщение о проигрыше и завершить игру.
- Если игрок достиг выхода из лабиринта, необходимо при помощи графики вывести сообщение об успешном окончании игры.

* **Дополнительная часть (максимум - 15 баллов)**

- Реализовать врагов, которые перемещаются по лабиринту (вариант А) или по комнате (вариант Б) - патрулируют по маршруту (2 балл) и/или двигаются на игрока (4 балла).
- Более продвинутые реализации врагов: до 4 баллов. Например, противники атакуют с некоторой дистанции и отбегают от игрока, при его приближении.  
- Анимация статических объектов - например, сокровища и шипы ловушек блестят. (2 балла)
- Плавная спрайтовая анимация динамических объектов - походка игрока и врагов, открытие дверей и.т.д. (от 2 до 5 баллов)
- Реализовать графический эффект перехода между уровнями (вариант А) и комнатами (вариант Б) - постепенное “угасание” и появление игровой карты (fade out / fade in), эффект “мозаики”, плавное “перетекание” одного изображения в другое и т.п. (3 балла)
- Эффекты пост-обработки всего изображения - “дрожание” воздуха (heat haze), размытие/туман и т.п. (3 балла)
Источники света - факелы, лампы и т.д., которые “освещают” (=изменяют цвет) соседних тайлов в некотором радиусе. (4 балла)
  - анимация источников света (+1 балл)
  - bloom (+4 балла)
- Реализация и графическое отображение инвентаря (3 балла)
- Графическое отображение характеристик игрока и соответствующие им игровые механики - например, если выводится здоровье, то игрок может его потерять (ловушки, враги) и, возможно, восстановить. (2 балла)
- Механика ближнего боя с анимацией. (2 балла)
- Механика дальнего боя (стрелковое оружие и/или магия - огненные шары, волшебные стрелы и т.д.) с анимацией летящего снаряда. (от 3 до 6 баллов в зависимости от субъективно оцениваемого визуального качества и сложности)
Визуальные эффекты боя - “вылетающие” спрайты цифр повреждений, искры, “тряска” экрана и т.п. (от 2 до 4 баллов)
- Финальный босс игры: от 2 до 6 баллов. Боссы, отличающиеся от обычных врагов только числовыми параметрами(жизни, урон и тд.), оцениваются в 2 балла. Чтобы получить больше необходимо реализовать хотя бы одну оригинальную механику для босса. Этой механики не должно быть ни у одного другого противника. 
- Реализация большого лабиринта (вариант А): 5 баллов. В данном пункте предполагается, что карта уровня больше чем отображаемая в окне область. Необходимо реализовать отображение видимой области, которая располагается вокруг игрока и перемещается вместе с ним.
 
 * 
 * etc...
 */

#include <sstream>

#include "utilities/labirinth.h"
#include "graphics/screen.h"
#include "gameplay/Player.h"

#include "utilities/common.h"
#include "utilities/room.h"
#include "utilities/matrix.h"
#include "utilities/exceptions.h"

#include "graphics/Image.h"

#include "gameplay/input_processing.h"

extern GLfloat deltaTime;
extern GLfloat lastFrame;

class Game
{
private:
    mapping::Labirinth lab_;
    Player player_;
    Screen screen_buffer_;
    GLFWwindow* window_ = nullptr;
public:
    Game();
    ~Game();

    void initGL() const;

    void loop ();
};

Game::Game(): player_({WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}), 
              lab_("./res/labitinth.txt"),
              screen_buffer_(WINDOW_WIDTH, WINDOW_HEIGHT, 4) {
    if(!glfwInit())
    	throw utilities::GLException("Game initialization failed");

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window_ = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "task1 base project", nullptr, nullptr);
	if (window_ == nullptr) {
		glfwTerminate();
		throw utilities::GLException("Failed to create GLFW window");
	}
	
	glfwMakeContextCurrent(window_); 

	glfwSetKeyCallback          (window_, OnKeyboardPressed);  
	glfwSetCursorPosCallback    (window_, OnMouseMove); 
  	glfwSetMouseButtonCallback  (window_, OnMouseButtonClicked);
	glfwSetScrollCallback       (window_, OnMouseScroll);
	
	initGL();

  	// Reset any OpenGL errors which could be present for some reason
	GLenum gl_error = glGetError();
	while (gl_error != GL_NO_ERROR)
		gl_error = glGetError();

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);  GL_CHECK_ERRORS;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); GL_CHECK_ERRORS;
}

void Game::initGL() const
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw utilities::GLException("Failed to initialize OpenGL context");

	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	std::cout << "Controls: "<< std::endl;
	std::cout << "press right mouse button to capture/release mouse cursor  "<< std::endl;
	std::cout << "W, A, S, D - movement  "<< std::endl;
	std::cout << "press ESC to exit" << std::endl;
}

void Game::loop() {
    Room roomA{"./res/maps/roomA.txt"};

    //game loop
	while (!glfwWindowShouldClose(window_)) {
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
    	glfwPollEvents();

		processPlayerMovement(player_);
		roomA.DrawRoomOn(&screen_buffer_); // x grows from bottom to begining, y grows from left to right
		player_.Draw(screen_buffer_);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GL_CHECK_ERRORS;
	    glDrawPixels (WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screen_buffer_.Data()); GL_CHECK_ERRORS;

		glfwSwapBuffers(window_);
	}
}

Game::~Game () {
    glfwTerminate();
}

int main(int argc, char** argv)
{
	Game g;

	g.loop();

	return 0;
}
