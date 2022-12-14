#include "engine.hpp"

void Engine::update() {
    // Update snake positions
    if (timeSinceLastMove.asSeconds() >= seconds(1.f / float(speed)).asSeconds()) {
        Vector2f thisSectionPosition = snake[0].getPosition();
        Vector2f lastSectionPosition = thisSectionPosition;

        // Is there anything in the input queue?
        if (!directionQueue.empty()) {
            // Make sure we don't reverse direction
            switch (snakeDirection) {
            case Direction::UP:
                if (directionQueue.front() != Direction::DOWN) {
                    snakeDirection = directionQueue.front();
                }
                break;
            case Direction::DOWN:
                if (directionQueue.front() != Direction::UP) {
                    snakeDirection = directionQueue.front();
                }
                break;
            case Direction::LEFT:
                if (directionQueue.front() != Direction::RIGHT) {
                    snakeDirection = directionQueue.front();
                }
                break;
            case Direction::RIGHT:
                if (directionQueue.front() != Direction::LEFT) {
                    snakeDirection = directionQueue.front();
                }
                break;
            }
            directionQueue.pop_front();
        }

        // Update Score
        score += snake.size() * (StickmanEatenTotal + 1);
        scoreText.setString(to_string(score));
        FloatRect scoreTextBounds = scoreText.getLocalBounds();
        scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 15, -9));

        // Do we need to grow the snake
        if (sectionsToAdd) {
            addSnakeSection();
            sectionsToAdd--;
        }

        // Update the snake's head position
        switch (snakeDirection) {
        case Direction::RIGHT:
            snake[0].setPosition(Vector2f(thisSectionPosition.x + 20, thisSectionPosition.y));
            break;
        case Direction::DOWN:
            snake[0].setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y + 20));
            break;
        case Direction::LEFT:
            snake[0].setPosition(Vector2f(thisSectionPosition.x - 20, thisSectionPosition.y));
            break;
        case Direction::UP:
            snake[0].setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y - 20));
            break;
        }

        // Update the snake tail positions
        for (int s = 1; s < snake.size(); s++) {
            thisSectionPosition = snake[s].getPosition();
            snake[s].setPosition(lastSectionPosition);
            lastSectionPosition = thisSectionPosition;
        }

        // update snake sections
        for (auto& s : snake) {
            s.update();
        }

        // Collision detection - Apple
        if (snake[0].getShape().getGlobalBounds().intersects(stickman.getSprite().getGlobalBounds())) {
            // We hit the apple, add more sections to the snake, increase speed and move the apple
            StickmanEatenThisLevel += 1;
			StickmanEatenTotal += 1;
			StickmanEatenText.setString("StickMan " + to_string(StickmanEatenTotal));
            FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
			StickmanEatenText.setPosition(
                Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));

            bool beginningNewLevel = false;
            if (StickmanEatenThisLevel >= 10) {
                // Begin the next level if there are more,
                // otherwise, just stay on the last level and keep getting harder until we die.
                if (currentLevel < maxLevels) {
                    beginningNewLevel = true;
                    beginNextLevel();
                }
            }
            if (!beginningNewLevel) {
                sectionsToAdd += 4;
                speed++;
                moveStickman();
            }
        }

        // Collision detection - Snake Body
        for (int s = 1; s < snake.size(); s++) {
            if (snake[0].getShape().getGlobalBounds().intersects(snake[s].getShape().getGlobalBounds())) {
                // Game Over
                currentGameState = GameState::GAMEOVER;
            }
        }

        // Collision detection - Wall
        for (auto& w : wallSections) {
            if (snake[0].getShape().getGlobalBounds().intersects(w.getShape().getGlobalBounds())) {
                // Game Over
                currentGameState = GameState::GAMEOVER;
            }
        }

        // Reset the last move timer.
        timeSinceLastMove = Time::Zero;
    } // END update snake positions
}
