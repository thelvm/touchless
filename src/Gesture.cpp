//
// Created by lucas on 14/06/19.
//
#include <fstream>
#include <json.hpp>
#include <iostream>
#include "Gesture.hpp"

gesture_parser::Gesture::Gesture() = default;

gesture_parser::Gesture::Gesture(const char *t_file_name)
{
    std::ifstream fileStream(t_file_name);
    if (fileStream.fail())
    {
        std::cerr << "Error: " << strerror(errno);
    }
    nlohmann::json jsonGesture;
    fileStream >> jsonGesture;

    if (!jsonGesture.empty())
    {
        ;
        for (const auto &keyframeJSON : jsonGesture["keyframes"]["keyframe"])
        {
            m_keyframes.push_back(new GestureKeyframe(keyframeJSON));
        }
    }
    else
    {
        printf("%s cannot be loaded. JSON is empty.", t_file_name);
    }
}

void gesture_parser::Gesture::addKeyframe(gesture_parser::GestureKeyframe *t_keyframe, unsigned int t_position)
{
    if (t_position < m_keyframes.size())
    {
        auto it = m_keyframes.begin();
        m_keyframes.insert(it + t_position, t_keyframe);
    }
}

void gesture_parser::Gesture::removeKeyframe()
{
    m_keyframes.pop_back();
}

void gesture_parser::Gesture::removeKeyframe(unsigned int t_position)
{
    if (t_position < m_keyframes.size())
    {
        auto it = m_keyframes.begin();
        m_keyframes.erase(it + t_position);
    }
}
