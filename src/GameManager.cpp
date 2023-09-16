#include "GameManager.h"



/**
 * Default constructor that initializes all the variables and loads all the
 * resorces.
 */
GameManager::GameManager() {

    window_size = sf::VideoMode(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);

    game_window = new sf::RenderWindow(window_size,
                                  DEFAULT_SCREEN_NAME);
    
    game_window->setFramerateLimit(GAME_FPS);

    racket_texture.loadFromFile("../resources/sprites/racket.png");
    player_racket = new Racket(&racket_texture, DEFAULT_SCREEN_HEIGHT, 60);
    int ai_racket_x = DEFAULT_SCREEN_WIDTH - 60;
    ai_racket = new Racket(&racket_texture, DEFAULT_SCREEN_HEIGHT, ai_racket_x);

    player_score = 0;
    ai_score = 0;

    font.loadFromFile("../resources/fonts/EASportsCovers.ttf");

    scoreboard.setFont(font);
    scoreboard.setCharacterSize(50);

    ball = new Ball(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);

    game_is_paused = false;
}


/**
 * Destructor that frees all the used resources.
 */
GameManager::~GameManager() {

    delete game_window;

    delete player_racket;
    delete ai_racket;

    delete ball;
}


/**
 * This method reads all the evetes (like mouse presses, key presses...) and
 * manages them.
 */
void GameManager::eventPolling() {

    sf::Event game_event;

    while (game_window->pollEvent(game_event))
    {
        switch (game_event.type)
        {
            case sf::Event::Closed:
                closeGame();
                break;

            case sf::Event::KeyPressed:
                manageKeyPressed(game_event.key.code);
                break;

            case sf::Event::KeyReleased:
                manageKeyReleased(game_event.key.code);
                break;
        }
    }
}


/**
 * This method updates the the state of the game, looks for collisions, 
 * etc... 
 */
void GameManager::update() {

    // Updates scoreboard
    updateScoreBoard();

    player_racket->update();
    ai_racket->update(ball->getY());

    ball->resolveRacketCollision(player_racket);
    ball->resolveRacketCollision(ai_racket);

    WhoScored who_scored = ball->update();

    if (who_scored == AI_SCORED) {

        ai_score++;
        resetScene();
    }
    else if (who_scored == PLAYER_SCORED){

        player_score++;
        resetScene();
    }
}


/**
 * This method renders the sprites into the game window.
 */
void GameManager::render() {

    game_window->clear();

    game_window->draw(scoreboard);

    ball->render(game_window);

    player_racket->render(game_window);
    ai_racket->render(game_window);

    game_window->display();
}


/**
 * This method closes the game.
 */
void GameManager::closeGame() {

    game_window->close();
}


/**
 * This method manages the key pressed events.
 * 
 * @param pressed_key The key that has been pressed.
 */
void GameManager::manageKeyPressed(sf::Keyboard::Key key_pressed) {

    switch (key_pressed)
    {
        case sf::Keyboard::Up:
            player_racket->setUpKeyPressed(true);
            break;
        
        case sf::Keyboard::Down:
            player_racket->setDownKeyPressed(true);
            break;
    }

}


/**
 * This method manages the key released events.
 * 
 * @param pressed_key The key that has been released.
 */
void GameManager::manageKeyReleased(sf::Keyboard::Key key_released) {

    switch (key_released)
    {
        case sf::Keyboard::Escape:
            closeGame();
            break;

        case sf::Keyboard::Up:
            player_racket->setUpKeyPressed(false);
            break;
        
        case sf::Keyboard::Down:
            player_racket->setDownKeyPressed(false);
            break;

        case sf::Keyboard::Space:
            game_is_paused = !game_is_paused;
            break;
    }
}


/**
 *  This method updates the scoreboard.
 */
void GameManager::updateScoreBoard() {

    scoreboard.setString(std::to_string(player_score) + 
                         " - " + 
                         std::to_string(ai_score));

    int text_width = scoreboard.getLocalBounds().width;

    int text_x = (DEFAULT_SCREEN_WIDTH - text_width) / 2;

    int text_y = SCOREBOARD_Y;

    scoreboard.setPosition({static_cast<float>(text_x),
                            static_cast<float>(text_y)});

}


/**
 * Resets the scene to set the rackets and the ball to the inital state.
 */
void GameManager::resetScene() {

    ball->resetScene();
    player_racket->resetScene();
    ai_racket->resetScene();

}


/**
 * It runs the game and executes the game loop (event polling, update, 
 * render). 
 */
void GameManager::runGame() {

    while(game_window->isOpen()) {
        
        // Processes the game events.
        eventPolling();

        // Update the states.
        if (!game_is_paused) {

            update();
        }

        // Render all the sprites and texts
        render();
    }
}

