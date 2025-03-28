#include "Game.h"
#include "Scene/TitleScene.h"
#include "Scene/GamePlayScene.h"

Game::Game() {
}

void Game::start(){
	mSceneManager.add("TitleScene", new TitleScene());
	mSceneManager.add("GamePlayScene", new GamePlayScene());

	mSceneManager.change("TitleScene");
}

void Game::update(){
	mSceneManager.update();
}

void Game::draw(){
	mSceneManager.draw();
}

void Game::end(){
	mSceneManager.end();
}
