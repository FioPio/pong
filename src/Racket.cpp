#include "Racket.h"


 /**
 * Default constructor that creates the object assigning the texture to the
 * sprite.
 * 
 * @param racket_texture The texture that will be displayed on the sprite.
 * @param window_height_to_set Window height to avoid the racket to go off 
 *                             limits.
 * @param x_racket The fixed x position at which the racket will be set.
 */
Racket::Racket(sf::Texture* racket_texture, 
               int window_height_to_set, 
               int x_racket) {

    racket_sprite.setTexture(*racket_texture);

    up_arrow_pressed = false;
    down_arrow_pressed = false;

    int sprite_width = racket_sprite.getTextureRect().width;
    int sprite_height = racket_sprite.getTextureRect().height;

    window_height = window_height_to_set - sprite_height;

    racket_x = x_racket - ( sprite_width / 2 );

    resetScene();

}


/**
 * This method checks for collisions and resolves them if any.
 */
void Racket::resolveCollisions() {

    if (racket_y < 0) {

        racket_y = 0;
    }

    if (racket_y > window_height) {

        racket_y = window_height;
    }
}


/**
 * Update the sate of the racket (move if necessary) and check/resolve 
 * collisions. 
 */
void Racket::update() {

    if (up_arrow_pressed) { // Move upwards

        racket_y -= RACKET_SPEED;
    }
    else if(down_arrow_pressed) { // Move downwards

        racket_y += RACKET_SPEED;
    }

    resolveCollisions();

    racket_sprite.setPosition({static_cast<float>(racket_x), 
                               static_cast<float>(racket_y)});
}


/**
 * Update the sate of the racket (move if necessary) and check/resolve 
 * collisions. This method is intented for the AI. 
 */
void Racket::update(int ball_y) {

    if (ball_y < racket_y) { // Move upwards

        racket_y -= RACKET_SPEED;
    }
    else { // Move downwards

        racket_y += RACKET_SPEED;
    }

    resolveCollisions();

    racket_sprite.setPosition({static_cast<float>(racket_x), 
                               static_cast<float>(racket_y)});
}


/**
 * It renders the sprite in the game window.
 * 
 * @param game_window A pointer to the game window so the sprite may be
 * rendered.
 */
void Racket::render(sf::RenderWindow* game_window) {

    game_window->draw(racket_sprite);
}


/**
 * This method sets the internal attribute up_arrow_pressed to manage the
 * movement.
 * 
 * @param pressed If the key is pressed.
 */
void Racket::setUpKeyPressed(bool pressed) {

    up_arrow_pressed = pressed;
}


/**
 * This method sets the internal attribute down_arrow_pressed to manage the
 * movement.
 * 
 * @param pressed If the key is pressed.
 */
void Racket::setDownKeyPressed(bool pressed) {

    down_arrow_pressed = pressed;
}



/**
 * It resets the racket position to the initial state. 
 */
void Racket::resetScene() {

    
    racket_y = window_height / 2;

    racket_sprite.setPosition({static_cast<float>(racket_x), 
                               static_cast<float>(racket_y)});

}

/**
 * This method returns the collision box of the racket.
 * 
 * @return Returns a sf::FloatRect that defines the collision box of the 
 *         racket. 
 */
sf::FloatRect Racket::getCollisionBox() {

    return racket_sprite.getGlobalBounds();
}