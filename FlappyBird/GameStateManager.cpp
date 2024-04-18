#include "GameStateManager.h"
#include <SDL/SDL.h>
#include "Constants.h"

#include <algorithm>
#include <iostream>

GameStateManager::GameStateManager(const std::string& bird_texture_path, 
								   const std::string& pipe_texture_path,
								   const std::string& upside_down_pipe_texture_path) : 
						 _game_state(GameState::OPENING_SCREEN),
						 _frame_count(0),
						 _score(0),
						 _is_player_between_pipes(false),
						 _is_leading_pipe_in_middle(false),
						 _is_second_pipe_in_middle(false),
						 _player(bird_texture_path, 
								 Consts::PLAYER_INITIAL_POSITION,
								 Consts::DEFAULT_COLOR) {

	_camera.Init(Consts::SCREEN_WIDTH, Consts::SCREEN_HEIGHT);
	std::srand(std::time(nullptr)); // use current time as seed for random generator
}

bool GameStateManager::IsPlaying() const {
	return _game_state != GameState::QUIT;
}

void GameStateManager::UpdateCamera(bool is_ai_controlling) {
	_camera.Update();
}

void GameStateManager::UpdateState(bool is_ai_controlling) {
	SDL_Keycode key_id;
	if (is_ai_controlling) {
		unsigned int input = _input_manager.AwaitInput();
		key_id = ConvertInputToKey(InputTypes(input));
		_input_manager.PressKey(key_id);
		PrintGameState();
	}

	_frame_count++;

	ProcessInputs();
	 
	switch (_game_state) {
		case GameState::PLAY:
			UpdatePlayer();
			UpdatePipes();
			UpdateScore();
			break;
		case GameState::DEAD:
			HandleDeadPlayer();
			break;
		case GameState::OPENING_SCREEN:
			HandleOpeningScreen();
			break;
		case GameState::QUIT:
			break;
	}

	if (IsPlayerColliding()) {
		_game_state = GameState::DEAD;
	}

	if (is_ai_controlling) {
		_input_manager.ReleaseKey(key_id);
	}
}

void GameStateManager::ProcessInputs() {
	SDL_Event sdl_event;

	while (SDL_PollEvent(&sdl_event)) {
		switch (sdl_event.type) {
		case SDL_QUIT:
			_game_state = GameState::QUIT;
			break;
		case SDL_MOUSEMOTION:
			_input_manager.SetMouseCoords((float) sdl_event.motion.x, (float) sdl_event.motion.y);
			break;
		case SDL_KEYDOWN:
			_input_manager.PressKey(sdl_event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_input_manager.ReleaseKey(sdl_event.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_input_manager.PressKey(sdl_event.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONUP:
			_input_manager.ReleaseKey(sdl_event.key.keysym.sym);
			break;
		}
	}
}

void GameStateManager::UpdatePipes() {
	if (ShouldAddPipes()) {
		AddPipes();
	}

	if (_pipes[0].IsOffScreen(Consts::SCREEN_WIDTH, Consts::SCREEN_HEIGHT)) {
		DeletePipes();
	}

	MovePipes();
}

void GameStateManager::AddPipes() {
	float pipe1_height = (float) (rand() % Consts::PIPE_HEIGHT_RANGE + Consts::MIN_PIPE_HEIGHT);
	glm::vec4 pipe1_initial_position(Consts::SCREEN_WIDTH - 1, 0, Consts::PIPE_WIDTH, pipe1_height);
	_pipes.emplace_back(Consts::PIPE_TEXTURE_PATH, pipe1_initial_position, Consts::DEFAULT_COLOR);

	float pipe2_height = pipe1_height + Consts::PIPE_DISTANCE;
	glm::vec4 pipe2_initial_position(Consts::SCREEN_WIDTH - 1, pipe2_height, Consts::PIPE_WIDTH, Consts::SCREEN_HEIGHT - pipe2_height);
	_pipes.emplace_back(Consts::UPSIDE_DOWN_PIPE_TEXTURE_PATH, pipe2_initial_position, Consts::DEFAULT_COLOR);
}

void GameStateManager::DeletePipes() {
 	std::vector<Pipe> new_pipes;

	for (size_t index = 2; index < _pipes.size(); index++) {
		new_pipes.emplace_back(_pipes[index]);
	}

	_pipes.clear();

	for (const auto& pipe : new_pipes) {
		_pipes.emplace_back(pipe);
	}

	_is_leading_pipe_in_middle = false;
	_is_second_pipe_in_middle = false;
}

void GameStateManager::MovePipes() {
	for (auto& pipe : _pipes) {
		pipe.MovePipe(Consts::PIPE_SPEED);
	}
}

bool GameStateManager::ShouldAddPipes() {
	if (_pipes.empty()) {
		return true;
	}

	bool should_add = false;

	// If pipe was in middle of screen, but not anymore, then new pipe should be added
	if (_is_leading_pipe_in_middle && !_pipes[0].IsCoordBetweenX(Consts::SCREEN_WIDTH / 2)) {
		should_add = true;
	}
	_is_leading_pipe_in_middle = _pipes[0].IsCoordBetweenX(Consts::SCREEN_WIDTH / 2);

	if (_pipes.size() == 2) {
		return should_add;
	}

	// If pipe was in middle of screen, but not anymore, then new pipe should be added
	if (_is_second_pipe_in_middle && !_pipes[2].IsCoordBetweenX(Consts::SCREEN_WIDTH / 2)) {
		should_add = true;
	}

	_is_second_pipe_in_middle = _pipes[2].IsCoordBetweenX(Consts::SCREEN_WIDTH / 2);

	return should_add;
}

bool GameStateManager::IsPlayerColliding() const {
	for (const auto& pipe : _pipes) {
		if (pipe.IsTouchingPlayer(_player)) {
			return true;
		}
	}

	return _player.GetPosition().y <= 0;
}

void GameStateManager::HandleDeadPlayer() {
	if (_input_manager.IsKeyPressed(SDLK_q)) {
		_score = 0;
		_player.SetInitialPosition();
		_game_state = GameState::OPENING_SCREEN;
		_pipes.clear();
		_is_player_between_pipes = false;
		_is_leading_pipe_in_middle = false;
		_is_second_pipe_in_middle = false;
	}
}

void GameStateManager::HandleOpeningScreen() {
	if (_input_manager.IsKeyPressed(SDLK_SPACE)) {
		_game_state = GameState::PLAY;
	}
}

void GameStateManager::UpdatePlayer() {
	_player.UpdatePosition(_input_manager);

	_player.PreventScreenClipping();
}

void GameStateManager::UpdateScore() {
	if (_pipes.empty()) {
		return;
	}

	// If player was between pipes, but not anymore, then player has passed pipes
	if (_is_player_between_pipes && !_pipes[0].IsCoordBetweenX(_player.GetX1())) {
		_score += 1;
	}

	_is_player_between_pipes = _pipes[0].IsCoordBetweenX(_player.GetX1());
}

void GameStateManager::PrintGameState() const {
	std::cout << Consts::START_MESSAGE;

	std::cout << "{";

	std::cout << "\"frame_count\": " << _frame_count << ", ";
	std::cout << "\"player_height\": " << _player.GetY1() << ", ";
	std::cout << "\"pipe_distance\": " << std::min(CalculatePipeDistance(), Consts::MAX_PIPE_DISTANCE) << ", ";
	std::cout << "\"pipe_height\": " << CalculatePipeHeight() << ", ";
	std::cout << "\"player_velocity\": " << _player.GetVelocity() << ", ";
	std::cout << "\"is_terminated\": " << IsPlayerColliding();

	std::cout << "}";

	std::cout << Consts::END_MESSAGE;
}

float GameStateManager::CalculatePipeDistance() const {
	// If no pipes, return distance from bird to edge of screen
	if (_pipes.empty()) {
		return Consts::MAX_PIPE_DISTANCE;
	}

	// If player is past first pipe, take distance from next pipe;
	if (_pipes[0].GetX2() < _player.GetX1()) {
		return _pipes[2].GetX2() - _player.GetX1();
	} else {
		return _pipes[0].GetX2() - _player.GetX1();
	}
}

float GameStateManager::CalculatePipeHeight() const {
	if (_pipes.empty()) {
		return Consts::MIN_PIPE_HEIGHT;
	}

	// If player is past first pipe, take height of next pipe;
	if (_pipes[0].GetX2() < _player.GetX1()) {
		return _pipes[2].GetY2();
	}
	else {
		return _pipes[0].GetY2();
	}
}

SDL_Keycode GameStateManager::ConvertInputToKey(InputTypes input_type) const {
	auto iterator = Consts::INPUT_TO_KEY.find(input_type);

	// If found, return SDL key
	if (iterator != Consts::INPUT_TO_KEY.end()) {
		return iterator->second;
	}

	return SDL_KeyCode::SDLK_0;
}