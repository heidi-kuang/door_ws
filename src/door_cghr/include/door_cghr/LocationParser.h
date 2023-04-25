#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <move_base_msgs/MoveBaseAction.h>

class LocationParser {
protected:
    std::vector<move_base_msgs::MoveBaseGoal> locations;
    std::ifstream fileStream;

public:
    LocationParser(std::string fileName);
    ~LocationParser();
    std::vector<move_base_msgs::MoveBaseGoal> getLocations();

};