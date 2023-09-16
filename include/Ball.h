#pragma once

#include <SFML/Graphics.hpp>

#include "Racket.h"

#define BALL_STARTING_SPEED 2 /**< Speed at which the ball will be thrown. */
#define BALL_MAX_SPEED      5 /**< Max speed the ball is allowed to reach. */

#define BALL_RADIUS              10 /**< The radius of the ball. */
#define BALL_COLOR sf::Color::Green /**< The color of the ball. */



enum WhoScored {
    PLAYER_SCORED,
    AI_SCORED,
    NO_ONE_SCORED
};


/**
 * This class provides all the functionality and control for the ball of the
 * PONG game.
 */
class Ball {

    sf::CircleShape* ball_sprite; /**< This will be used as the ball sprite. */

    int ball_x;  /**< Ball position on x. */
    int ball_y;  /**< Ball position on y. */

    float ball_x_speed;  /**< Ball speed on x. */
    float ball_y_speed;  /**< Ball speed on y. */

    int window_width;
    int window_height;


public:

    /**
     * Constructor for the ball class. 
     * 
     * @param window_width_to_set Window width that will be considered for 
     *                            collisions.
     * @param window_height_to_set Window height that will be considered for 
     *                             collisions.
     */
    Ball (int window_width_to_set, int window_height_to_set);

    /**
     * Frees all the resoursces used by the class.
     */
    ~Ball();

    /**
     * Updates the position of the ball and resolves the collisions with the
     * walls.
     * 
     * @return The player that has scored this turn.
     */
    WhoScored update();

    /**
     * It renders the sprite in the game window.
     * 
     * @param game_window A pointer to the game window so the sprite may be
     * rendered.
     */
    void render(sf::RenderWindow* game_window);

    /**
     * It resets the ball speed and position to the initial state. 
     */
    void resetScene();

    /**
     * This method returns the y position for the ball.
     */
    int getY();

    /**
     * Checks and resolves collisions (if any) with the provided racket.
     * 
     * @param resolveRacketCollision A pointer to the racket that wants to be 
     *                               checked.
     */
    void resolveRacketCollision(Racket* racket);

};