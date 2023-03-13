#include "lineTool.hpp"
void Line::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(line_pr, states);
}
Line::Line() {
    line_pr = sf::VertexArray(sf::Lines, 2);
    line_pr[0].color = sf::Color::Green;
    line_pr[1].color = sf::Color::Green;
}
// while the left button is pressed the position is getting set
void Line::set_points(sf::Window &window) // when moving don't forget to type in sf::RenderWindow &w
{
    if (sf::Mouse::getPosition(window).y < window.getSize().y &&
        sf::Mouse::getPosition(window).x < window.getSize().x) {
        line_pr[0].position = sf::Vector2f(sf::Mouse::getPosition(window));
        while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (sf::Mouse::getPosition(window).y < window.getSize().y &&
                sf::Mouse::getPosition(window).x < window.getSize().x)
                line_pr[1].position =
                    sf::Vector2f(sf::Mouse::getPosition(window));
        }
    }
}
void Line::set_color(sf::Color color_in) {
    line_pr[0].color = color_in;
    line_pr[1].color = color_in;
}
// void Line::paint_on_texture(sf::Texture &t) {
//     sf::FloatRect b_box = line_pr.getBounds();
//     sf::Color color_to_paint = line_pr[0].color;
//     sf::Uint8 pxl_buff[int(b_box.width) * int(b_box.height) * 4];
//     for (int u = 0; u < (int(b_box.width) * int(b_box.height) * 4) - 3;
//          u++) {
//         pxl_buff[u] = color_to_paint.r;
//         pxl_buff[u + 1] = color_to_paint.g;
//         pxl_buff[u + 2] = color_to_paint.b;
//         pxl_buff[u + 3] = color_to_paint.a;
//     }
//     t.update(pxl_buff, unsigned(b_box.width), unsigned(b_box.height),
//              unsigned(b_box.left), unsigned(b_box.top));
// }