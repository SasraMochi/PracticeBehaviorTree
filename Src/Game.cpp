#include "Game.h"
#include "Scene/TitleScene.h"
#include "Scene/GamePlayScene.h"

Game::Game() {
}

void Game::start(){
	scene_manager_.add("TitleScene", new TitleScene());
	scene_manager_.add("GamePlayScene", new GamePlayScene());

	scene_manager_.change("TitleScene");
}

void Game::update(){
	scene_manager_.update();
}

void Game::draw(){
	scene_manager_.draw();
}

void Game::end(){
	scene_manager_.end();
}
