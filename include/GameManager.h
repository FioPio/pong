#pragma once

#include <SFML/Graphics.hpp>

#include "Racket.h"
#include "Ball.h"


#define DEFAULT_SCREEN_WIDTH   640 /**< Default game window width. */
#define DEFAULT_SCREEN_HEIGHT  480 /**< Default game window height. */
#define DEFAULT_SCREEN_NAME "PONG" /**< Default game window name. */


#define GAME_FPS 60       /**< Controls the game frame rate. */

#define SCOREBOARD_Y 40   /**< Defines the Y position of the scoreboard. */


/**
 * This class is in charge of the logic behind the game and the resources
 * management.
 */
class GameManager {

    sf::Texture racket_texture; /**< Holds the texture for the rackets. */
    Racket* player_racket;  /**< The racket that the player will control. */
    Racket* ai_racket;      /**< The racket that the ai will control. */

    Ball* ball;             /**< The ball that will be used to play. */

    sf::RenderWindow* game_window; /**< The window that contains the game. */
    sf::VideoMode window_size;
    sf::Text scoreboard;  /**< This contains the score of the rackets. */
    sf::Font font; /**< This contains the font that will be used to write. */
 
    int player_score;  /**< Atribute that stores the player score. */
    int ai_score;      /**< Atribute that stores the ai score. */

    bool game_is_paused; /**< Control attribute to be able to pause the game. */


    /**
     * This method reads all the evetes (like mouse presses, key presses...) and
     * manages them.
     */
    void eventPolling();

    /**
     * This method updates the the state of the game, looks for collisions, 
     * etc... 
     */
    void update();

    /**
     * This method renders the sprites into the game window.
     */
    void render();

    /**
     * This method closes the game.
     */
    void closeGame();

    /**
     * This method manages the key pressed events.
     * 
     * @param pressed_key The key that has been pressed.
     */
    void manageKeyPressed(sf::Keyboard::Key key_pressed);

    /**
     * This method manages the key released events.
     * 
     * @param pressed_key The key that has been released.
     */
    void manageKeyReleased(sf::Keyboard::Key key_released);

    /**
     *  This method updates the scoreboard.
     */
    void updateScoreBoard();

    /**
     * Resets the scene to set the rackets and the ball to the inital state.
     */
    void resetScene();

public:

    /**
     * Default constructor that initializes all the variables and loads all the
     * resorces.
     */
    GameManager();

    /**
     * Destructor that frees all the used resources.
     */
    ~GameManager();

    /**
     * It runs the game and executes the game loop (event polling, update, 
     * render). 
     */
    void runGame();

};