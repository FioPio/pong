#pragma once

#include <SFML/Graphics.hpp>

#define RACKET_SPEED 4  /**< Sets the racket speed. */

/**
 * This class provides all the functionality and control for a racket for the 
 * PONG game. 
 */
class Racket {

    sf::Sprite racket_sprite;  /**< Sprite of the racket. */

    int window_height;   /**< Window height for the racekt. */
    
    int racket_x; /**< Racket x position. */
    int racket_y; /**< Racket y position. */

    bool up_arrow_pressed;  /**< Attribute that stores if the key is pressed. */
    bool down_arrow_pressed;  /**< Attribute that stores if the key is pressed. */


    /**
     * This method checks for collisions and resolves them if any.
     */
    void resolveCollisions();


    public:

    /**
     * Default constructor that creates the object assigning the texture to the
     * sprite.
     * 
     * @param racket_texture The texture that will be displayed on the sprite.
     * @param window_height_to_set Window height to avoid the racket to go off 
     *                             limits.
     * @param x_racket The fixed x position at which the racket will be set.
     */
    Racket(sf::Texture* racket_texture, int window_height_to_set, int x_racket);

    /**
     * Update the sate of the racket (move if necessary) and check/resolve 
     * collisions. 
     */
    void update();

    /**
     * Update the sate of the racket (move if necessary) and check/resolve 
     * collisions. This method is intented for the AI. 
     */
    void update(int ball_y);

    /**
     * It renders the sprite in the game window.
     * 
     * @param game_window A pointer to the game window so the sprite may be
     * rendered.
     */
    void render(sf::RenderWindow* game_window);

    /**
     * This method sets the internal attribute up_arrow_pressed to manage the
     * movement.
     * 
     * @param pressed If the key is pressed.
     */
    void setUpKeyPressed(bool pressed);

    /**
     * This method sets the internal attribute down_arrow_pressed to manage the
     * movement.
     * 
     * @param pressed If the key is pressed.
     */
    void setDownKeyPressed(bool pressed);

    /**
     * It resets the racket position to the initial state. 
     */
    void resetScene();

    /**
     * This method returns the collision box of the racket.
     * 
     * @return Returns a sf::FloatRect that defines the collision box of the 
     *         racket. 
     */
    sf::FloatRect getCollisionBox();

};