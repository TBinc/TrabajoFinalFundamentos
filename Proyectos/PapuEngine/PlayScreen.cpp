#include "PlayScreen.h"
#include "Game.h"
#include "MyScreens.h"


PlayScreen::PlayScreen(Window* window):_window(window)
{
}


PlayScreen::~PlayScreen()
{
}

void PlayScreen::initGUI() {
	_hudBach.init();
	_hudCamera.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_hudCamera.setPosition(glm::vec2(
		_window->getScreenWidth() / 2.0f,
		_window->getScreenHeight() / 2.0f));
}

void PlayScreen::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

void PlayScreen::destroy() {
	
}

void PlayScreen::onExit() {}

void PlayScreen::onEntry() {
	initSystem();
	_camera2D.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_camera2D.setPosition(glm::vec2(
		_window->getScreenWidth() / 2.0f,
		_window->getScreenHeight() / 2.0f));
	_spriteBatch.init();


	randomX = uniform_int_distribution<int>(1, _window->getScreenWidth());
	randomY = uniform_int_distribution<int>(_window->getScreenHeight() / 2, _window->getScreenHeight());
	random100 = uniform_int_distribution<int>(1, 100);

	player = new Gamer(106, 79,
		glm::vec2(200, 200), "Textures/Player.png", 
		&_game->_inputManager);
	initGUI();

	sounds.push_back(_soundCache.getSound("Sounds/scratch.wav"));
	sounds.push_back(_soundCache.getSound("Sounds/high.wav"));
	sounds.push_back(_soundCache.getSound("Sounds/low.wav"));	
}

void PlayScreen::update() {
	_camera2D.update();
	player->update();
	if (random100(randomEngine) < 8)
	{
		enemies.push_back(new Enemy(100, 66,
			glm::vec2(randomX(randomEngine),randomY(randomEngine)), "Textures/Piedra.png"));
	}
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->update();
	}
	checkBoundaries();
	checkInput();
}

void PlayScreen::checkInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		_game->onSDLEvent(event);
	}
}

void PlayScreen::checkBoundaries()
{
	Enemy *eAux = nullptr;

	glm::vec2 pPos = player->getPosition();
	if (pPos.x > _window->getScreenWidth())
	{
		player->setPosition(glm::vec2(-104, pPos.y));
		sounds[2]->playSound();
	}
	else if (pPos.x < -105)
	{
		player->setPosition(glm::vec2(_window->getScreenWidth(), pPos.y));
		sounds[2]->playSound();
	}

	if (pPos.y > _window->getScreenHeight())
	{
		player->setPosition(glm::vec2(pPos.x,-59));
		sounds[1]->playSound();
	}
	else if (pPos.y < -60)
	{
		player->setPosition(glm::vec2(pPos.x,_window->getScreenHeight()));
		sounds[1]->playSound();
	}

	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->getPosition().y < 0)
		{
			eAux = enemies[i];
			enemies[i] = enemies.back();
			enemies.pop_back();
			sounds[0]->playSound();
			delete eAux;
			break;
		}
	}
}

void PlayScreen::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();
	glActiveTexture(GL_TEXTURE0);
	GLuint pLocation = _program.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	_spriteBatch.begin();;
	player->draw(_spriteBatch);

	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->draw(_spriteBatch);
	}
	_spriteBatch.end();
	_spriteBatch.renderBatch();
	drawHUD();
	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

void PlayScreen::drawHUD() {
	GLuint pLocation = _program.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	char buffer[256];
	_hudBach.begin();

	_hudBach.end();
	_hudBach.renderBatch();
}

void PlayScreen::build() {}

int PlayScreen::getPreviousScreen() const {
	return SCREEN_INDEX_MENU;
}

int PlayScreen::getNextScreen() const {
	return SCREEN_INDEX_OVER;
}
