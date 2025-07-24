#pragma once

#include <algorithm>
#include <SFML/Graphics.hpp>

class RectChecker {

public:
    bool rectanglesIntersect(const sf::RectangleShape& rect1, const sf::RectangleShape& rect2);

private:
    bool onSegment(const sf::Vector2f& p, const sf::Vector2f& q, const sf::Vector2f& r);
    int orientation(const sf::Vector2f& p, const sf::Vector2f& q, const sf::Vector2f& r);
    bool doIntersect(const sf::Vector2f& p1, const sf::Vector2f& q1, const sf::Vector2f& p2, const sf::Vector2f& q2);
    bool isPointInsideRectangle(const sf::Vector2f& point, const sf::RectangleShape& rect);
};

//=========================================
bool RectChecker::onSegment(const sf::Vector2f& p, const sf::Vector2f& q, const sf::Vector2f& r) {
    return (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
        q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y));
}
//=========================================
int RectChecker::orientation(const sf::Vector2f& p, const sf::Vector2f& q, const sf::Vector2f& r) {
    float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // collinear
    return (val > 0) ? 1 : 2; // clock or counterclockwise
}
//=========================================
bool RectChecker::doIntersect(const sf::Vector2f& p1, const sf::Vector2f& q1,
    const sf::Vector2f& p2, const sf::Vector2f& q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) return true;

    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}
//=========================================
bool RectChecker::isPointInsideRectangle(const sf::Vector2f& point, const sf::RectangleShape& rect) {
    sf::Transform transform = rect.getTransform();
    sf::Vector2f localPoint = transform.getInverse().transformPoint(point);
    return localPoint.x >= 0 && localPoint.x <= rect.getSize().x && localPoint.y >= 0 && localPoint.y <= rect.getSize().y;
}
//=========================================
bool RectChecker::rectanglesIntersect(const sf::RectangleShape& rect1, const sf::RectangleShape& rect2) {

    sf::Vector2f p1 = rect1.getTransform().transformPoint(rect1.getPoint(0));
    sf::Vector2f p2 = rect1.getTransform().transformPoint(rect1.getPoint(1));
    sf::Vector2f p3 = rect1.getTransform().transformPoint(rect1.getPoint(2));
    sf::Vector2f p4 = rect1.getTransform().transformPoint(rect1.getPoint(3));

    sf::Vector2f q1 = rect2.getTransform().transformPoint(rect2.getPoint(0));
    sf::Vector2f q2 = rect2.getTransform().transformPoint(rect2.getPoint(1));
    sf::Vector2f q3 = rect2.getTransform().transformPoint(rect2.getPoint(2));
    sf::Vector2f q4 = rect2.getTransform().transformPoint(rect2.getPoint(3));

    // Check all pairs of edges from both rectangles
    if (doIntersect(p1, p2, q1, q2) || doIntersect(p1, p2, q2, q3) || doIntersect(p1, p2, q3, q4) || doIntersect(p1, p2, q4, q1)) return true;
    if (doIntersect(p2, p3, q1, q2) || doIntersect(p2, p3, q2, q3) || doIntersect(p2, p3, q3, q4) || doIntersect(p2, p3, q4, q1)) return true;
    if (doIntersect(p3, p4, q1, q2) || doIntersect(p3, p4, q2, q3) || doIntersect(p3, p4, q3, q4) || doIntersect(p3, p4, q4, q1)) return true;
    if (doIntersect(p4, p1, q1, q2) || doIntersect(p4, p1, q2, q3) || doIntersect(p4, p1, q3, q4) || doIntersect(p4, p1, q4, q1)) return true;

    // Check if any point of rect1 is inside rect2 or vice versa
    if (isPointInsideRectangle(p1, rect2) || isPointInsideRectangle(p2, rect2) ||
        isPointInsideRectangle(p3, rect2) || isPointInsideRectangle(p4, rect2)) return true;
    if (isPointInsideRectangle(q1, rect1) || isPointInsideRectangle(q2, rect1) ||
        isPointInsideRectangle(q3, rect1) || isPointInsideRectangle(q4, rect1)) return true;

    return false;
}