#pragma once

#include <vector>

#include <FlappyBird/Bird.h>
#include <FlappyBird/Pipe.h>

#include <GameEngine/InputManager.h>
#include <GameEngine/Camera2D.h>

enum class GameState {
	PLAY,
	OPENING_SCREEN,
	DEAD,
	QUIT
};

enum class InputTypes {
	JUMP,
	NOTHING,
	RESET
};

class GameStateManager {

public:

	GameStateManager(const std::string& bird_texture_path, 
					 const std::string& pipe_texture_path,
					 const std::string& upside_down_pipe_texture_path);

	bool IsPlaying() const;

	void ProcessInputs();

	void UpdateCamera(bool is_ai_controlling);

	void UpdateState(bool is_ai_controlling);

	const GameEngine::Camera2D& GetCamera() const { return _camera; }

	const Bird& GetPlayer() const { return _player; }

	const std::vector<Pipe>& GetPipes() const { return _pipes; }

	size_t GetScore() const { return _score; }

	size_t GetFrameCount() const { return _frame_count; }

	GameState GetGameState() const { return _game_state; }

private:

	bool ShouldAddPipes();

	void HandleDeadPlayer();

	void UpdatePlayer();

	void HandleOpeningScreen();

	void UpdatePipes();

	void UpdateScore();

	void PrintGameState() const;

	bool IsPlayerColliding() const;

	void DeletePipes();
	void AddPipes();
	void MovePipes();

	float CalculatePipeDistance() const;

	float CalculatePipeHeight() const;

	SDL_Keycode ConvertInputToKey(InputTypes input_type) const;

	// Is the leading pipe in the middle of the screen
	bool _is_leading_pipe_in_middle;

	// Is the second pipe going in the middle of the screen
	bool _is_second_pipe_in_middle;

	// Is the player inbetween a pair of pipes (i.e. one vertical and one horizontal
	bool _is_player_between_pipes;

	size_t _frame_count;

	GameState _game_state;
	Bird _player;
	std::vector<Pipe> _pipes;
	GameEngine::InputManager _input_manager;
	GameEngine::Camera2D _camera;
	size_t _score;
};

