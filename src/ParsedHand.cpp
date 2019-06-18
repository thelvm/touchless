//
// Created by lucas on 12/06/19.
//

#include <math.h>
#include "ParsedHand.hpp"

gesture_parser::ParsedHand::ParsedHand() : m_thumb(),
                                           m_index(),
                                           m_midlle(),
                                           m_ring(),
                                           m_pinky(),
                                           m_roll(),
                                           m_pitch(),
                                           m_yaw(),
                                           position_x(),
                                           position_y(),
                                           position_z()
{
}

int gesture_parser::ParsedHand::cleanDegree(double t_degree)
{
    if (t_degree < 0)
    {
        t_degree = 180.0 - t_degree;
        if (t_degree < 0)
        {
            t_degree = -t_degree;
        }
    }

    return (int)t_degree % 360;
}

double gesture_parser::ParsedHand::cleanRadian(double t_radian)
{
    if (t_radian < 0)
    {
        t_radian = (M_PI)-t_radian;
        if (t_radian < 0)
        {
            t_radian = -t_radian;
        }
    }

    return fmod(t_radian, (2 * M_PI));
}

bool gesture_parser::ParsedHand::isThumbExtended() const
{
    return m_thumb;
}

bool gesture_parser::ParsedHand::isIndexExtended() const
{
    return m_index;
}

bool gesture_parser::ParsedHand::isMiddleExtended() const
{
    return m_midlle;
}

bool gesture_parser::ParsedHand::isRingExtended() const
{
    return m_ring;
}

bool gesture_parser::ParsedHand::isPinkyExtended() const
{
    return m_pinky;
}

unsigned int gesture_parser::ParsedHand::getRollDegree() const
{
    return m_roll;
}

double gesture_parser::ParsedHand::getRollRadian() const
{
    return (double)m_roll * (M_PI / 180.0);
}

unsigned int gesture_parser::ParsedHand::getPitchDegree() const
{
    return m_pitch;
}

double gesture_parser::ParsedHand::getPitchRadian() const
{
    return (double)m_pitch * (M_PI / 180.0);
}

unsigned int gesture_parser::ParsedHand::getYawDegree() const
{
    return m_yaw;
}

double gesture_parser::ParsedHand::getYawRadian() const
{
    return (double)m_yaw * (M_PI / 180.0);
}

bool gesture_parser::ParsedHand::isHandOpen() const
{
    return isThumbExtended() &&
           isIndexExtended() &&
           isMiddleExtended() &&
           isRingExtended() &&
           isPinkyExtended();
}

bool gesture_parser::ParsedHand::ishandClosed() const
{
    return !(isThumbExtended() ||
             isIndexExtended() ||
             isMiddleExtended() ||
             isRingExtended() ||
             isPinkyExtended());
}

void gesture_parser::ParsedHand::setThumbExtended(bool t_isExtended)
{
    m_thumb = t_isExtended;
}

void gesture_parser::ParsedHand::setIndexExtended(bool t_isExtended)
{
    m_index = t_isExtended;
}

void gesture_parser::ParsedHand::setMiddleExtended(bool t_isExtended)
{
    m_midlle = t_isExtended;
}

void gesture_parser::ParsedHand::setRingExtended(bool t_isExtended)
{
    m_ring = t_isExtended;
}

void gesture_parser::ParsedHand::setPinkyExtended(bool t_isExtended)
{
    m_pinky = t_isExtended;
}

void gesture_parser::ParsedHand::setRollDegree(double t_degree)
{
    m_roll = cleanDegree(t_degree);
}

void gesture_parser::ParsedHand::setRollRadian(double t_radian)
{
    t_radian = cleanRadian(t_radian);
    m_roll = (int)(t_radian * (180.0 / M_PI));
}

void gesture_parser::ParsedHand::setPitchDegree(double t_degree)
{
    m_pitch = cleanDegree(t_degree);
}

void gesture_parser::ParsedHand::setPitchRadian(double t_radian)
{
    t_radian = cleanRadian(t_radian);
    m_pitch = (int)(t_radian * (180.0 / M_PI));
}

void gesture_parser::ParsedHand::setYawDegree(double t_degree)
{
    m_yaw = cleanDegree(t_degree);
}

void gesture_parser::ParsedHand::setYawRadian(double t_radian)
{
    t_radian = cleanRadian(t_radian);
    m_yaw = (int)(t_radian * (180.0 / M_PI));
}

bool gesture_parser::ParsedHand::operator==(const gesture_parser::ParsedHand &rhs) const
{
    return m_thumb == rhs.m_thumb &&
           m_index == rhs.m_index &&
           m_midlle == rhs.m_midlle &&
           m_ring == rhs.m_ring &&
           m_pinky == rhs.m_pinky &&
           m_roll == rhs.m_roll &&
           m_pitch == rhs.m_pitch &&
           m_yaw == rhs.m_yaw;
}

bool gesture_parser::ParsedHand::operator!=(const gesture_parser::ParsedHand &rhs) const
{
    return !(rhs == *this);
}
