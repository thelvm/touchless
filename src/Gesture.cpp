//
// Created by lucas on 14/06/19.
//
#include <fstream>
#include <json.hpp>
#include <iostream>
#include "Gesture.hpp"

touchless::Gesture::Gesture() = default;

void touchless::Gesture::addKeyframe(touchless::GestureKeyframe *t_keyframe)
{
    m_keyframes.push_back(t_keyframe);
}

void touchless::Gesture::addKeyframe(touchless::GestureKeyframe *t_keyframe, unsigned int t_position)
{
    if (t_position < m_keyframes.size())
    {
        auto it = m_keyframes.begin();
        m_keyframes.insert(it + t_position, t_keyframe);
    }
}

void touchless::Gesture::removeKeyframe()
{
    m_keyframes.pop_back();
}

void touchless::Gesture::removeKeyframe(unsigned int t_position)
{
    if (t_position < m_keyframes.size())
    {
        auto it = m_keyframes.begin();
        m_keyframes.erase(it + t_position);
    }
}

touchless::GestureKeyframe *touchless::Gesture::getKeyframe(unsigned int t_position)
{
    if (t_position < m_keyframes.size())
    {
        return m_keyframes[t_position];
    }
    return nullptr;
}

bool touchless::Gesture::test(Hands *t_hands)
{
    clock_t timeSinceLastKeyframe = (clock() - m_lastKeyframeTimestamp) / CLOCKS_PER_SEC;
    if (m_currentKeyframe = 0 ||
                            (timeSinceLastKeyframe <= (m_keyframes[m_currentKeyframe]->maxDelay) &&
                             timeSinceLastKeyframe >= (m_keyframes[m_currentKeyframe]->minDelay)))
    {
        if (m_keyframes[m_currentKeyframe]->compare(t_hands, precision))
        {
            double leftDeltaX = fabs(m_keyframes[m_currentKeyframe]->hands->leftHand->position_x - t_hands->leftHand->position_x);
            double leftDeltaY = fabs(m_keyframes[m_currentKeyframe]->hands->leftHand->position_y - t_hands->leftHand->position_z);
            double leftDeltaZ = fabs(m_keyframes[m_currentKeyframe]->hands->leftHand->position_z - t_hands->leftHand->position_z);
            double rightDeltaX = fabs(m_keyframes[m_currentKeyframe]->hands->rightHand->position_x - t_hands->rightHand->position_x);
            double rightDeltaY = fabs(m_keyframes[m_currentKeyframe]->hands->rightHand->position_y - t_hands->rightHand->position_z);
            double rightDeltaZ = fabs(m_keyframes[m_currentKeyframe]->hands->rightHand->position_z - t_hands->rightHand->position_z);

            if ((m_keyframes[m_currentKeyframe]->leftDeltaX - precision) < leftDeltaX &&
                (m_keyframes[m_currentKeyframe]->leftDeltaX + precision) > leftDeltaX &&

                (m_keyframes[m_currentKeyframe]->leftDeltaY - precision) < leftDeltaY &&
                (m_keyframes[m_currentKeyframe]->leftDeltaY + precision) > leftDeltaY &&

                (m_keyframes[m_currentKeyframe]->leftDeltaZ - precision) < leftDeltaZ &&
                (m_keyframes[m_currentKeyframe]->leftDeltaZ + precision) > leftDeltaZ &&

                (m_keyframes[m_currentKeyframe]->rightDeltaX - precision) < rightDeltaX &&
                (m_keyframes[m_currentKeyframe]->rightDeltaX + precision) > rightDeltaX &&

                (m_keyframes[m_currentKeyframe]->rightDeltaY - precision) < rightDeltaY &&
                (m_keyframes[m_currentKeyframe]->rightDeltaY + precision) > rightDeltaY &&

                (m_keyframes[m_currentKeyframe]->rightDeltaZ - precision) < rightDeltaZ &&
                (m_keyframes[m_currentKeyframe]->rightDeltaZ + precision) > rightDeltaZ)
            {
                m_currentKeyframe++;
                if (m_currentKeyframe == m_keyframes.size())
                {
                    m_currentKeyframe = 0;
                    return true;
                }
                m_lastKeyframeTimestamp = clock();
                return false;
            }
        }
    }
    m_currentKeyframe = 0;
    return false;
}

nlohmann::json touchless::Gesture::toJSON()
{
    nlohmann::json j;

    j["name"] = name;
    j["precision"] = precision;
    j["keyframes"] = nlohmann::json::array();
    for(int i = 0; i < m_keyframes.size(); i++)
    {
        j["keyframes"][i] = m_keyframes[i]->toJSON();
    }

    return j;
}

void touchless::Gesture::fromJSON(nlohmann::json j)
{
    name = j["name"];
    precision = j["precision"];

    m_keyframes.clear();
    for (auto& JSONKeyframe : j["keyframes"])
    {
        auto keyframe = new GestureKeyframe();
        keyframe->fromJSON(JSONKeyframe);
        m_keyframes.push_back(keyframe);
    }
}

void touchless::Gesture::fromJSON(std::string t_file_name)
{
    std::ifstream fileStream(t_file_name.c_str());
    if (fileStream.fail())
    {
        std::cerr << "Error: " << strerror(errno);
    }
    nlohmann::json jsonGesture;
    fileStream >> jsonGesture;

    if (!jsonGesture.empty())
    {
        fromJSON(jsonGesture);
    }
    else
    {
        std::cout << t_file_name << " cannot be loaded. JSON is empty.\n";
    }
}