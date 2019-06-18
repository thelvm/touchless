//
// Created by lucas on 14/06/19.
//

#ifndef GESTURE_PARSER_API_GESTURE_HPP
#define GESTURE_PARSER_API_GESTURE_HPP

#include <vector>
#include "GestureKeyframe.hpp"

namespace gesture_parser
{
class Gesture
{
private:
    std::vector<GestureKeyframe *> m_keyframes;

public:
    char *name;

    Gesture();

    Gesture(const char *t_file_name);

    void addKeyframe(GestureKeyframe *t_keyframe);

    void addKeyframe(GestureKeyframe *t_keyframe, unsigned int t_position);

    void removeKeyframe();

    void removeKeyframe(unsigned int t_position);
};
} // namespace gesture_parser

#endif //GESTURE_PARSER_API_GESTURE_HPP
