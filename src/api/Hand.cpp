//
// Created by lucas on 12/06/19.
//

#include <math.h>
#include "Hand.hpp"

touchless::Hand::Hand() : m_thumb(),
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

int touchless::Hand::cleanDegree(double t_degree)
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

double touchless::Hand::cleanRadian(double t_radian)
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

bool touchless::Hand::isThumbExtended() const
{
    return m_thumb;
}

bool touchless::Hand::isIndexExtended() const
{
    return m_index;
}

bool touchless::Hand::isMiddleExtended() const
{
    return m_midlle;
}

bool touchless::Hand::isRingExtended() const
{
    return m_ring;
}

bool touchless::Hand::isPinkyExtended() const
{
    return m_pinky;
}

unsigned int touchless::Hand::getRollDegree() const
{
    return m_roll;
}

double touchless::Hand::getRollRadian() const
{
    return (double)m_roll * (M_PI / 180.0);
}

unsigned int touchless::Hand::getPitchDegree() const
{
    return m_pitch;
}

double touchless::Hand::getPitchRadian() const
{
    return (double)m_pitch * (M_PI / 180.0);
}

unsigned int touchless::Hand::getYawDegree() const
{
    return m_yaw;
}

double touchless::Hand::getYawRadian() const
{
    return (double)m_yaw * (M_PI / 180.0);
}

bool touchless::Hand::isHandOpen() const
{
    return isThumbExtended() &&
           isIndexExtended() &&
           isMiddleExtended() &&
           isRingExtended() &&
           isPinkyExtended();
}

bool touchless::Hand::ishandClosed() const
{
    return !(isThumbExtended() ||
             isIndexExtended() ||
             isMiddleExtended() ||
             isRingExtended() ||
             isPinkyExtended());
}

void touchless::Hand::setThumbExtended(bool t_isExtended)
{
    m_thumb = t_isExtended;
}

void touchless::Hand::setIndexExtended(bool t_isExtended)
{
    m_index = t_isExtended;
}

void touchless::Hand::setMiddleExtended(bool t_isExtended)
{
    m_midlle = t_isExtended;
}

void touchless::Hand::setRingExtended(bool t_isExtended)
{
    m_ring = t_isExtended;
}

void touchless::Hand::setPinkyExtended(bool t_isExtended)
{
    m_pinky = t_isExtended;
}

void touchless::Hand::setRollDegree(double t_degree)
{
    m_roll = cleanDegree(t_degree);
}

void touchless::Hand::setRollRadian(double t_radian)
{
    t_radian = cleanRadian(t_radian);
    m_roll = (int)(t_radian * (180.0 / M_PI));
}

void touchless::Hand::setPitchDegree(double t_degree)
{
    m_pitch = cleanDegree(t_degree);
}

void touchless::Hand::setPitchRadian(double t_radian)
{
    t_radian = cleanRadian(t_radian);
    m_pitch = (int)(t_radian * (180.0 / M_PI));
}

void touchless::Hand::setYawDegree(double t_degree)
{
    m_yaw = cleanDegree(t_degree);
}

void touchless::Hand::setYawRadian(double t_radian)
{
    t_radian = cleanRadian(t_radian);
    m_yaw = (int)(t_radian * (180.0 / M_PI));
}

bool touchless::Hand::operator==(const touchless::Hand &rhs) const
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

bool touchless::Hand::operator!=(const touchless::Hand &rhs) const
{
    return !(rhs == *this);
}

nlohmann::json touchless::Hand::toJSON()
{
    nlohmann::json j;
    j["thumb"] = m_thumb;
    j["index"] = m_index;
    j["middle"] = m_midlle;
    j["ring"] = m_ring;
    j["pinky"] = m_pinky;
    j["roll"] = m_roll;
    j["pitch"] = m_pitch;
    j["yaw"] = m_yaw;
    return j;
}

void touchless::Hand::fromJSON(nlohmann::json j)
{
    m_thumb = j["thumb"];
    m_index = j["index"];
    m_midlle = j["middle"];
    m_ring = j["ring"];
    m_pinky = j["pinky"];
    m_roll = j["roll"];
    m_pitch = j["pitch"];
    m_yaw = j["yaw"];
}
