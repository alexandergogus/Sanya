#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML Moving Object with Camera");

    // Load the map texture
    sf::Texture mapTexture;
    if (!mapTexture.loadFromFile("map.png")) {
        std::cerr << "Failed to load map texture!" << std::endl;
        return -1;
    }

    // Load the object texture
    sf::Texture objectTexture;
    if (!objectTexture.loadFromFile("object.png")) {
        std::cerr << "Failed to load object texture!" << std::endl;
        return -1;
    }

    // Create the map sprite
    sf::Sprite mapSprite;
    mapSprite.setTexture(mapTexture);

    // Create the object sprite
    sf::Sprite objectSprite;
    objectSprite.setTexture(objectTexture);

    // Scale the object to make it smaller (e.g., 50% of its original size)
    objectSprite.setScale(0.5f, 0.5f);

    // Set the initial position of the object (center of the map)
    sf::Vector2f objectPosition(mapTexture.getSize().x / 2.0f, mapTexture.getSize().y / 2.0f);
    objectSprite.setPosition(objectPosition);

    // Set the origin of the object to its center (for proper centering)
    objectSprite.setOrigin(objectTexture.getSize().x / 2.0f, objectTexture.getSize().y / 2.0f);

    // Define the speed of the object
    float moveSpeed = 200.0f;

    // Define the view (camera)
    sf::View view = window.getDefaultView();

    // Track the object's direction for flipping
    bool isFlipped = false;

    // Main loop
    sf::Clock clock;
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Calculate delta time
        float deltaTime = clock.restart().asSeconds();

        // Handle movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            objectPosition.y -= moveSpeed * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            objectPosition.y += moveSpeed * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            objectPosition.x -= moveSpeed * deltaTime;
            // Flip the object when moving left
            if (!isFlipped) {
                objectSprite.setTextureRect(sf::IntRect(objectTexture.getSize().x, 0, -objectTexture.getSize().x, objectTexture.getSize().y));
                isFlipped = true;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            objectPosition.x += moveSpeed * deltaTime;
            // Restore the original texture when moving right
            if (isFlipped) {
                objectSprite.setTextureRect(sf::IntRect(0, 0, objectTexture.getSize().x, objectTexture.getSize().y));
                isFlipped = false;
            }
        }

        // Ensure the object stays within the map boundaries
        objectPosition.x = std::max(objectPosition.x, 0.0f);
        objectPosition.x = std::min(objectPosition.x, static_cast<float>(mapTexture.getSize().x));
        objectPosition.y = std::max(objectPosition.y, 0.0f);
        objectPosition.y = std::min(objectPosition.y, static_cast<float>(mapTexture.getSize().y));

        // Update the object's position
        objectSprite.setPosition(objectPosition);

        // Update the view (camera) to center on the object
        view.setCenter(objectPosition);

        // Clamp the view to the map boundaries
        sf::Vector2f viewSize = view.getSize();
        sf::Vector2f viewHalfSize(viewSize.x / 2.0f, viewSize.y / 2.0f);
        sf::Vector2f viewTopLeft = objectPosition - viewHalfSize;
        sf::Vector2f viewBottomRight = objectPosition + viewHalfSize;

        if (viewTopLeft.x < 0) {
            view.setCenter(viewHalfSize.x, view.getCenter().y);
        }
        if (viewTopLeft.y < 0) {
            view.setCenter(view.getCenter().x, viewHalfSize.y);
        }
        if (viewBottomRight.x > mapTexture.getSize().x) {
            view.setCenter(mapTexture.getSize().x - viewHalfSize.x, view.getCenter().y);
        }
        if (viewBottomRight.y > mapTexture.getSize().y) {
            view.setCenter(view.getCenter().x, mapTexture.getSize().y - viewHalfSize.y);
        }

        window.setView(view);

        // Clear the window
        window.clear();

        // Draw the map and the object
        window.draw(mapSprite);
        window.draw(objectSprite);

        // Display the window
        window.display();
    }

    return 0;
}
