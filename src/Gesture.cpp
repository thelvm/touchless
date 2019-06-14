//
// Created by lucas on 14/06/19.
//
#include "Gesture.hpp"

void gesture_parser::Gesture::addKeyframe(gesture_parser::GestureKeyframe *t_keyframe) {
    m_keyframes.push_back(t_keyframe);
}

void gesture_parser::Gesture::addKeyframe(gesture_parser::GestureKeyframe *t_keyframe, unsigned int t_position) {
    if (t_position < m_keyframes.size()) {
        auto it = m_keyframes.begin();
        m_keyframes.insert(it + t_position, t_keyframe);
    }
}

void gesture_parser::Gesture::removeKeyframe() {
    m_keyframes.pop_back();
}

void gesture_parser::Gesture::removeKeyframe(unsigned int t_position) {
    if (t_position < m_keyframes.size()) {
        auto it = m_keyframes.begin();
        m_keyframes.erase(it + t_position);
    }
}




