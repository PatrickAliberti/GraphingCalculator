#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "shuntingYard.hpp" // Including the header file

// Function to evaluate the parsed equation
double evaluateEquation(const std::string &equation, double x) {
    Calculator calculator(equation);
    return calculator.calculateY(x);
}

// Function to draw the graph of the equation
void drawGraph(sf::RenderWindow &window, const std::string &equation, double xMin, double xMax, double step) {
    sf::VertexArray graph(sf::LineStrip);
    graph.setPrimitiveType(sf::LineStrip);
    
    // Evaluate and draw points
    for (double x = xMin; x <= xMax; x += step) {
        double y = evaluateEquation(equation, x);
        graph.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::Blue));
    }
    
    window.draw(graph);
}

int main() {
    // Set up window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Function Graph");

    std::string equation;
    double xMin, xMax, step;

    // Get equation and range from user
    std::cout << "Enter the function equation (use 'x' as the variable): ";
    std::getline(std::cin, equation);

    std::cout << "Enter the minimum value of x: ";
    std::cin >> xMin;

    std::cout << "Enter the maximum value of x: ";
    std::cin >> xMax;

    std::cout << "Enter the step size: ";
    std::cin >> step;

    // Event loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // Draw the graph
        drawGraph(window, equation, xMin, xMax, step);

        window.display();
    }

    return 0;
}
