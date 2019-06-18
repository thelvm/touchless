#ifndef GESTURE_PARSER_API_GESTURE_PARSER
#define GESTURE_PARSER_API_GESTURE_PARSER

#include <map>
#include <functional>

#include "Gesture.hpp"
#include "HandsParser.hpp"
#include "GestureParserListener.hpp"

namespace gesture_parser
{
/// Main parser class. Parses Gesture from a list directly from the Leap Motion Sensor
class GestureParser
{
private:
    /// Hands parser used in gesture detection
    HandsParser *m_handsParser;

    /// The list of gestures to detect
    std::map<char *, Gesture> m_gestures;

    GestureParserListener *m_listener;

    /// Parses hands to detect gestures.
    /// If a gesture is detected, calls onGesture on the listener
    void parseHands(const ParsedHands *t_parsedHands);

public:
    /// Starts attempting to connect to the Leap Motion Sensor.
    /// Once it is successful, starts processing the Leap Motion Sensor input.
    void start();

    /// Stops all processing and disconnects from the Leap Motion Sensor.
    void stop();

    /// Adds a gesture to the list of gestures to detect
    void addGesture(Gesture *t_gesture);

    /// Removes a Gesture with corresponding name from the list of gestures to detect
    void removeGesture(char *t_gestureName);
};
} // namespace gesture_parser

#endif