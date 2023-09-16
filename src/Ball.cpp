#include "Ball.h"

#include <cmath>


/**
 * Constructor for the ball class. 
 * 
 * @param window_width_to_set Window width that will be considered for 
 *                            collisions.
 * @param window_height_to_set Window height that will be considered for 
 *                             collisions.
 */
Ball::Ball (int window_width_to_set, int window_height_to_set) {

    ball_sprite = new sf::CircleShape(BALL_RADIUS);

    ball_sprite->setFillColor(BALL_COLOR);

    window_width = window_width_to_set - (2 * BALL_RADIUS);
    window_height = window_height_to_set - (2 * BALL_RADIUS);

    resetScene();
}


/**
 * Frees all the resoursces used by the class.
 */
Ball::~Ball() {

    delete ball_sprite;
}


/**
 * Updates the position of the ball and resolves the collisions with the
 * walls.
 * 
 * @return The player that has scored this turn.
 */
WhoScored Ball::update() {

    WhoScored who_scored = NO_ONE_SCORED;

    ball_x += ball_x_speed;
    ball_y += ball_y_speed;

    if (ball_x < 0) {

        who_scored = AI_SCORED;
    }
    else if (ball_x > window_width) {

        who_scored = PLAYER_SCORED;
    }

    if (ball_y < 0) {

        ball_y = -ball_y;
        ball_y_speed = -ball_y_speed;
    }
    else if (ball_y > window_height) {

        int over_boundary = ball_y - window_height;
        ball_y = window_height - over_boundary;
        ball_y_speed = -ball_y_speed;
    }

    ball_sprite->setPosition({static_cast<float>(ball_x),
                              static_cast<float>(ball_y)});
    
    if (ball_x_speed < BALL_MAX_SPEED) {

        ball_x_speed *= 1.001;
    }
    if (ball_y_speed < BALL_MAX_SPEED) {        

        ball_y_speed *= 1.001;
    }

    return who_scored;
}


/**
 * It renders the sprite in the game window.
 * 
 * @param game_window A pointer to the game window so the sprite may be
 * rendered.
 */
void Ball::render(sf::RenderWindow* game_window) {

    game_window->draw(*ball_sprite);
}


/**
 * It resets the ball speed and position to the initial state. 
 */
void Ball::resetScene() {

    ball_x_speed = BALL_STARTING_SPEED;
    ball_y_speed = BALL_STARTING_SPEED; 

    ball_x = window_width / 2;  
    ball_y = window_height / 2;  
}

/**
 * This method returns the y position for the ball.
 */
int Ball::getY() {

    return ball_y;
}


/**
 * Checks and resolves collisions (if any) with the provided racket.
 * 
 * @param resolveRacketCollision A pointer to the racket that wants to be 
 *                               checked.
 */
void Ball::resolveRacketCollision(Racket* racket) {

    int ball_center_x = ball_x + BALL_RADIUS;
    int ball_center_y = ball_y + BALL_RADIUS;

    sf::FloatRect racket_box = racket->getCollisionBox();

    int x1_racket = racket_box.left;
    int x2_racket = racket_box.left + racket_box.width;

    int y1_racket = racket_box.top;
    int y2_racket = racket_box.top + racket_box.height;

    int closest_x = std::clamp(ball_center_x, x1_racket, x2_racket);
    int closest_y = std::clamp(ball_center_y, y1_racket, y2_racket);

    int x_vector = ball_center_x - closest_x;
    int y_vector = ball_center_y - closest_y;

    int vector_module = sqrt( pow(x_vector, 2) + pow(y_vector, 2));

    if (vector_module < BALL_RADIUS) {

        if (closest_x != ball_center_x || closest_y != ball_center_y) {
            
            float multiplication_factor = (BALL_RADIUS - vector_module);
            multiplication_factor /= vector_module;
            multiplication_factor *= 2;

            int x_correction = x_vector * multiplication_factor;
            int y_correction = y_vector * multiplication_factor;

            ball_x += x_correction;
            ball_y += y_correction;

            if (abs(x_correction) > 0) {

                ball_x_speed = -ball_x_speed;
            }
            if (abs(y_correction) > 0) {

                ball_y_speed = -ball_y_speed;
            }
        }
    }
}
