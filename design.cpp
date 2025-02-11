#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

using namespace sf;

const int WIDTH = 800;
const int HEIGHT = 600;
const int STAR_COUNT = 6;      // Number of rotating stars
const int TRIANGLE_COUNT = 6;  // Number of rotating triangles
float angle = 0;

struct RotatingShape {
    ConvexShape shape;
    float radius;
    float speed;
    float angleOffset;
};

int main() {
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Rotating Triangles & Stars");

    // Pulsating Circle
    CircleShape circle(50);
    circle.setFillColor(Color::Cyan);
    circle.setOrigin(50, 50);
    circle.setPosition(WIDTH / 2, HEIGHT / 2);

    // Rotating Rectangle
    RectangleShape rectangle(Vector2f(100, 50));
    rectangle.setFillColor(Color::Magenta);
    rectangle.setOrigin(50, 25);
    rectangle.setPosition(WIDTH / 2, HEIGHT / 2);

    // Central Triangle
    ConvexShape mainTriangle;
    mainTriangle.setPointCount(3);
    mainTriangle.setPoint(0, Vector2f(0, 0));
    mainTriangle.setPoint(1, Vector2f(40, 100));
    mainTriangle.setPoint(2, Vector2f(80, 0));
    mainTriangle.setFillColor(Color::Yellow);
    mainTriangle.setOrigin(40, 50);
    mainTriangle.setPosition(WIDTH / 2, HEIGHT / 3);

    // Additional rotating stars
    std::vector<RotatingShape> stars;
    for (int i = 0; i < STAR_COUNT; i++) {
        RotatingShape star;
        star.shape.setPointCount(5);
        float starSize = 20;
        for (int j = 0; j < 5; j++) {
            float theta = j * 2 * M_PI / 5;
            star.shape.setPoint(j, Vector2f(starSize * cos(theta), starSize * sin(theta)));
        }
        star.shape.setFillColor(Color::White);
        star.shape.setOrigin(starSize, starSize);
        star.radius = 120;
        star.speed = 50 + (i * 10);
        star.angleOffset = i * 60;
        stars.push_back(star);
    }

    // Additional rotating triangles
    std::vector<RotatingShape> triangles;
    for (int i = 0; i < TRIANGLE_COUNT; i++) {
        RotatingShape triangle;
        triangle.shape.setPointCount(3);
        triangle.shape.setPoint(0, Vector2f(0, -20));
        triangle.shape.setPoint(1, Vector2f(-20, 20));
        triangle.shape.setPoint(2, Vector2f(20, 20));
        triangle.shape.setFillColor(Color::Green);
        triangle.shape.setOrigin(0, 0);
        triangle.radius = 150;
        triangle.speed = 40 + (i * 8);
        triangle.angleOffset = i * 60;
        triangles.push_back(triangle);
    }

    Clock clock;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        // Update angle
        angle += 100 * time;

        // Pulsating effect for the circle
        float scale = 1.0f + 0.2f * sin(angle * 0.05);
        circle.setScale(scale, scale);

        // Rotating rectangle
        rectangle.setRotation(angle);

        // Moving main triangle
        float moveX = 100 * sin(angle * 0.02);
        mainTriangle.setPosition(WIDTH / 2 + moveX, HEIGHT / 3);

        // Rotating small stars around the center
for (size_t i = 0; i < stars.size(); i++) {  // Use classic for loop for compatibility
    RotatingShape &star = stars[i];  // Access each star object

    float starAngle = angle + star.angleOffset;

    star.shape.setPosition(
        WIDTH / 2 + star.radius * cos(starAngle * 0.02f),  // Ensure float literals are used
        HEIGHT / 2 + star.radius * sin(starAngle * 0.02f)
    );

    star.shape.setRotation(-starAngle);
}

        // Rotating additional triangles around the center
for (size_t i = 0; i < triangles.size(); i++) {  // Classic for-loop for compatibility
    RotatingShape &triangle = triangles[i];  // Access each triangle object

    float triangleAngle = angle + triangle.angleOffset;

    triangle.shape.setPosition(
        WIDTH / 2 + triangle.radius * cos(triangleAngle * 0.02f),  // Ensure float precision
        HEIGHT / 2 + triangle.radius * sin(triangleAngle * 0.02f)
    );

    triangle.shape.setRotation(triangleAngle);
}
 

       // Draw everything
window.clear(sf::Color::Black);  // Ensure proper namespace usage

// Draw main shapes
window.draw(circle);
window.draw(rectangle);
window.draw(mainTriangle);

// Draw stars
for (size_t i = 0; i < stars.size(); i++) {
    window.draw(stars[i].shape);
}

// Draw additional triangles
for (size_t i = 0; i < triangles.size(); i++) {
    window.draw(triangles[i].shape);
}

window.display();
}
return 0;
}  // Display all drawn elements


