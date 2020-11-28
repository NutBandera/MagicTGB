#include "GameLayer.h"

GameLayer::GameLayer(Game *game)
	: Layer(game) {
	pause = false; // draw init message 
	messageDuel = new Actor("res/mensaje_duel.png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, game);
	messageWin = new Actor("res/mensaje_ganar.png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, game);
	messageLose = new Actor("res/mensaje_perder.png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, game);
	messagePause = new Actor("res/mensaje_pausa.png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, game);
	init();
}

void GameLayer::init() {
	pad = new Pad(WIDTH * 0.15, HEIGHT * 0.80, game);
	buttonJump = new Actor("res/boton_salto.png", WIDTH*0.9, HEIGHT*0.55, 100, 100, game);
	buttonShoot = new Actor("res/boton_disparo.png", WIDTH*0.75, HEIGHT*0.83, 100, 100, game);

	audioBackground = new Audio("res/background_music.mp3", true);
	//audioBackground->play();

	space = new Space(1);
	scrollX = 0;

	// Player manaCrystals
	textManaPlayer = new Text("20", WIDTH * 0.2, HEIGHT * 0.05, game);
	backgroundManaPlayer = new Actor("res/item.png", WIDTH * 0.25, HEIGHT * 0.06, 24, 24, game);

	// Enemy manaCrystals
	textManaEnemy = new Text("20", WIDTH * 0.81, HEIGHT * 0.05, game);
	backgroundManaEnemy = new Actor("res/item.png", WIDTH * 0.755, HEIGHT * 0.06, 24, 24, game);

	// Player life
	textPlayerLife = new Text("20", WIDTH * 0.1, HEIGHT * 0.05, game);
	backgroundPlayerLife = new Actor("res/icono_puntos.png", WIDTH * 0.15, HEIGHT * 0.05, 24, 24, game);

	// Enemy life
	textEnemyLife = new Text("20", WIDTH * 0.93, HEIGHT * 0.05, game);
	backgroundEnemyLife = new Actor("res/icono_puntos.png", WIDTH * 0.865, HEIGHT * 0.05, 24, 24, game);

	// Background
	background = new Background("res/fondo1.png", WIDTH*0.5, HEIGHT*0.5, game);

	tiles.clear();
	manaCrystals.clear();
	playerCreatures.clear();
	enemyCreatures.clear();

	loadMap("res/" + to_string(game->currentLevel) + ".txt");
}

void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_CONTROLLERBUTTONDOWN:
		case SDL_CONTROLLERAXISMOTION:
			game->input = GameInputType::GAMEPAD;
			break;
		case SDL_QUIT:
			game->loopActive = false;
			return;
		case SDL_MOUSEBUTTONDOWN:
			game->input = GameInputType::MOUSE;
			break;
		case SDL_KEYDOWN:
			game->input = GameInputType::KEYBOARD;
			break;
		}
		if (game->input == GameInputType::KEYBOARD) {
			keysToControls(event);
		}
		if (game->input == GameInputType::MOUSE) {
			mouseToControls(event);
		}

	}

	if (controlContinue) {
		pause = false;
		controlContinue = false;
	}

	if (controlMoveX > 0) {
		player->moveX(1);
	}
	else if (controlMoveX < 0) {
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}

	if (controlMoveY < 0) {
		player->jump();
	}

	if (controlShoot) {
		player->attack(enemyCreatures);
		controlShoot = false;
	}

	if (controlConjuro) {
		//player->conjuro(enemy);
		enemy->reduceLife(4); // FINISH 
		controlConjuro = false;
	}
	if (controlCriatura) {
		Creature* c = player->crearCriatura();
		if (c != NULL) {
			playerCreatures.push_back(c);
			space->addDynamicActor(c);
		}
		controlCriatura = false;
	}
	if (controlEncantamiento) {
		player->encantamiento(playerCreatures);
		controlEncantamiento = false;
	}

	textManaPlayer->content = to_string(player->getMana());
}

// añadir menú con controles

void GameLayer::loadMap(string name) {
	char character;
	string line;
	ifstream streamFile(name.c_str());
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		// Por línea
		for (int i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			mapWidth = line.length() * 40; // Ancho del mapa en pixels
			// Por carácter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				cout << character;
				float x = 40 / 2 + j * 40; // x central
				float y = 32 + i * 32; // y suelo
				loadMapObject(character, x, y);
			}

			cout << character << endl;
		}
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	case 'E': {
		enemy = new Enemy(x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		space->addDynamicActor(enemy);
		currentEnemyForPlayer = enemy;
		break;
	}

	case '1': {
		player = new RedPlayer(x, y, game);
		// modificación para empezar a contar desde el suelo.
		player->y = player->y - player->height / 2;
		space->addDynamicActor(player);
		currentEnemyForEnemy = player;
		break;
	}
	case '#': {
		Tile* tile = new Tile("res/suelo.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'M': {
		Tile* tile = new Tile("res/suelo-medio.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'R': {
		ManaCrystal* item = new ManaCrystal(x, y, game);
		item->y = item->y - item->height / 2;
		manaCrystals.push_back(item);
		space->addDynamicActor(item);
		break;
	}
	}
}


void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_d: {// derecha
			controlMoveX = 1;
			break;
		}
		case SDLK_a: {// izquierda
			controlMoveX = -1;
			break;
		}
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_p: // pausa
			pause = true;
			break;
		case SDLK_SPACE: // dispara
			controlShoot = true;
			break;
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
		}
	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_j:
			controlConjuro = true;
			break;
		case SDLK_k:
			controlCriatura = true;
			break;
		case SDLK_l:
			controlEncantamiento = true;
			break;
		case SDLK_SPACE: // dispara
			controlShoot = false;
			break;
		}
	}


}

void GameLayer::mouseToControls(SDL_Event event) {
	// Modificación de coordenadas por posible escalado
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;
	// Cada vez que hacen click
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		controlContinue = true;
		if (pad->containsPoint(motionX, motionY)) {
			pad->clicked = true;
			controlMoveX = pad->getOrientationX(motionX);
			if (controlMoveX > -20 && controlMoveX < 20) {
				controlMoveX = 0;
			}
		}
		if (buttonShoot->containsPoint(motionX, motionY)) {
			controlShoot = true;
		}
		if (buttonJump->containsPoint(motionX, motionY)) {
			controlMoveY = -1;
		}

	}
	// Cada vez que se mueve
	if (event.type == SDL_MOUSEMOTION) {
		if (pad->clicked && pad->containsPoint(motionX, motionY)) {
			controlMoveX = pad->getOrientationX(motionX);
		}
		else {
			pad->clicked = false;
			controlMoveX = 0;
		}
		if (buttonShoot->containsPoint(motionX, motionY) == false) {
			controlShoot = false;
		}
		if (buttonJump->containsPoint(motionX, motionY) == false) {
			controlMoveY = 0;
		}

	}
	// Cada vez que levantan el click
	if (event.type == SDL_MOUSEBUTTONUP) {
		if (buttonShoot->containsPoint(motionX, motionY)) {
			controlShoot = false;
		}
		if (buttonJump->containsPoint(motionX, motionY)) {
			controlMoveY = 0;
		}
		if (pad->containsPoint(motionX, motionY)) {
			pad->clicked = false;
			controlMoveX = 0;
		}
	}
}



void GameLayer::update() {
	if (pause || winGame || loseGame) {
		return;
	}

	textPlayerLife->content = to_string(player->getLife());
	textEnemyLife->content = to_string(enemy->getLife());

	// Generar cristales de maná
	newCrystalTime--;
	if (newCrystalTime <= 0) {
		int rX = rand() % (WIDTH - 50);
		int rY = rand() % (HEIGHT - 100) + 100;
		manaCrystals.push_back(new ManaCrystal(rX, rY, game));
		newCrystalTime = 300;
	}

	newEnemyAttack--;
	int option;
	if (newEnemyAttack <= 0) {
		option = rand() % 5;
		if (option == 0) {
			//enemy->conjuro(player);
			player->reduceLife(4);
		}
		else {
			Creature* c = enemy->createCreature();
			if (c != NULL) {
				enemyCreatures.push_back(c);
				space->addDynamicActor(c);
			}
		}
		newEnemyAttack = 300;
	}

	space->update();
	background->update();
	player->update();
	if (player->getLife() <= 0) {
		bool end = player->die();
		if (end) {
			loseGame = true;
		}
	}
	enemy->update(playerCreatures, manaCrystals);
	if (enemy->getLife() <= 0) {
		bool end = enemy->die();
		if (end) {
			winGame = true;
		}
	}


	textManaEnemy->content = to_string(enemy->getMana());

	if (player->x >= WIDTH / 2) { // usar x de la middle tile 
		player->reduceLife(1);
	}

	list<ManaCrystal*> deleteItems;
	list<Creature*> deletePlayerCreatures;
	list<Creature*> deleteEnemyCreatures;

	for (auto const& crystal : manaCrystals) {
		if (player->isOverlap(crystal)) {
			player->increaseMana(1);
			textManaPlayer->content = to_string(player->getMana());
			bool rInList = std::find(deleteItems.begin(),
				deleteItems.end(),
				crystal) != deleteItems.end();

			if (!rInList) {
				deleteItems.push_back(crystal);
			}
		}
		if (enemy->isOverlap(crystal)) {
			enemy->increaseMana(1);
			textManaEnemy->content = to_string(enemy->getMana());
			bool rInList = std::find(deleteItems.begin(),
				deleteItems.end(),
				crystal) != deleteItems.end();

			if (!rInList) {
				deleteItems.push_back(crystal);
			}
		}
	}

	// comprobar vida de cada criatura y eliminar si muerta 
	for (auto &const creature : playerCreatures) {
		if (creature->getLife() == 0) {
			bool cInList = std::find(deletePlayerCreatures.begin(),
				deletePlayerCreatures.end(),
				creature) != deletePlayerCreatures.end();

			if (!cInList) {
				deletePlayerCreatures.push_back(creature);
			}
			/*for (auto &const enemyCreature : enemyCreatures) {
				if (playerCreatures.size() > 0) {
					enemyCreature->setEnemy(playerCreatures.front());
				}
				else {
					enemyCreature->setEnemy(player);
				}
			}*/

			//updateCurrentEnemy();
		}
	}

	for (auto &const creature : enemyCreatures) {
		if (creature->getLife() == 0) {
			bool cInList = std::find(deleteEnemyCreatures.begin(),
				deleteEnemyCreatures.end(),
				creature) != deleteEnemyCreatures.end();

			if (!cInList) {
				deleteEnemyCreatures.push_back(creature);
			}
			/*for (auto &const playerCreature : playerCreatures) {
				if (enemyCreatures.size() > 0) {
					playerCreature->setEnemy(enemyCreatures.front());
				}
				else {
					playerCreature->setEnemy(enemy);
				}
			}*/
			//updateCurrentEnemy();
		}
	}

	for (auto const& delItem : deleteItems) {
		manaCrystals.remove(delItem);
		space->removeDynamicActor(delItem);
	}
	deleteItems.clear();

	for (auto const& delCreature : deletePlayerCreatures) {
		playerCreatures.remove(delCreature);
		space->removeDynamicActor(delCreature);
	}
	deletePlayerCreatures.clear();


	for (auto const& delCreature : deleteEnemyCreatures) {
		enemyCreatures.remove(delCreature);
		space->removeDynamicActor(delCreature);
	}
	deleteEnemyCreatures.clear();

	for (const auto& creature : playerCreatures) {
		if (enemyCreatures.size() > 0) {
			creature->update(enemyCreatures.front());
		}
		else {
			creature->update(enemy);
		}
	}

	for (const auto& creature : enemyCreatures) {
		if (playerCreatures.size() > 0) {
			creature->update(playerCreatures.front());
		}
		else {
			creature->update(player);
		}
	}

}


void GameLayer::calculateScroll() {
	if (player->x > WIDTH * .3) {
		if (player->x - scrollX < WIDTH * .3) {
			scrollX = player->x - WIDTH * .3;
		}
	}
	if (player->x < mapWidth - WIDTH * .3) {
		if (player->x - scrollX > WIDTH * .7) {
			scrollX = player->x - WIDTH * .7;
		}
	}
}

void GameLayer::draw() {
	calculateScroll();
	background->draw(0);
	backgroundManaPlayer->draw(0);
	textManaPlayer->draw();
	backgroundManaEnemy->draw(0);
	textManaEnemy->draw();
	textPlayerLife->draw();
	backgroundPlayerLife->draw(0);
	textEnemyLife->draw();
	backgroundEnemyLife->draw(0);

	for (const auto& tile : tiles) {
		tile->draw(0);
	}
	for (const auto& item : manaCrystals) {
		item->draw(0);
	}

	player->draw(0);
	enemy->draw(0);

	for (const auto& item : playerCreatures) {
		item->draw();
	}

	for (const auto& item : enemyCreatures) {
		item->draw();
	}

	if (pause) {
		messagePause->draw();
	}
	if (winGame) {
		messageWin->draw();
	}
	if (loseGame) {
		messageLose->draw();
	}

	SDL_RenderPresent(game->renderer); // Renderiza
}

