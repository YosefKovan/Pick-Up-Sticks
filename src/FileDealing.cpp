#include "FileDealing.h"
#include <array>
#include <stdexcept>

//======================================
//           save to file
//======================================
void FileDealing::saveToFile(const std::list<std::shared_ptr<Stick>>& sticks, const TopBar& topBar)
{
	//make sure the vector is empty!
	m_fileRows.clear();

	getTopBarInfo(topBar);
	getSticksInfo(sticks);

	//this will create a file and will write all data that we need to store
	std::ofstream file("saveFile.txt");

	for (auto& row : m_fileRows)
		file << row;

	file.close();

}
//======================================
//           read stick info
//======================================
void FileDealing::getTopBarInfo(const TopBar& topBar)
{
	std::string row;

	row = std::to_string(topBar.getTimeLeft()) + " ";
	row += std::to_string(topBar.getTotalScore()) + " ";
	row += std::to_string(topBar.getSticksPickedUp()) + "\n";

	m_fileRows.push_back(row);
}
//======================================
//           read stick info
//======================================
void FileDealing::getSticksInfo(const std::list<std::shared_ptr<Stick>>& sticks)
{
	for (auto t = sticks.begin(); t != sticks.end(); t++)
	{
		m_fileRows.push_back(getRectInfo(*t));
	}

	std::cout << std::endl;
}
//======================================
//           get coordinates
//======================================
std::string FileDealing::getRectInfo(std::shared_ptr<Stick> stick)
{
	std::string row;
	sf::RectangleShape rect = stick->getStickRect();

	//size of the rectangle
	sf::Vector2f size = rect.getSize();
	//the center position of the rectangle
	sf::Vector2f origin = rect.getOrigin();
	//get position
	sf::Vector2f position = rect.getPosition();
	//rotation value of the rectangle
	int rotation = rect.getRotation();
	//color of the rectangle
	sf::Color color = rect.getFillColor();

	row = to_string(size.x) + " " + to_string(size.y) + " ";
	row += to_string(origin.x) + " " + to_string(origin.y) + " ";
	row += to_string(position.x) + " " + to_string(position.y) + " ";
	row += to_string(rotation) + " ";
	row += to_string(color.r) + " " + to_string(color.g) + " " + to_string(color.b) + "\n";

	return row;
}
//======================================
//           save to file
//======================================
Pair FileDealing::loadFile()
{
	std::ifstream file("saveFile.txt");
	int totalSticks = 0;
	std::string row;
	
	if(!file.is_open()) //need to change the exception type
		throw std::ios_base::failure("Unable to open file!");
	
	if (file.peek() == EOF)
		throw std::ios_base::failure("File is empty");

	std::getline(file, row);
	validateTopBar(row);

	while (std::getline(file, row))
	{
		validateStick(row);
		totalSticks++;
	}

	if (totalSticks > MAX_TOTAL_STICKS)
		throw std::out_of_range("too many sticks are in the file!");

	return Pair(m_sticks, m_topBar);
}
//======================================
//           validateTopBar
//======================================
void FileDealing::validateTopBar(const std::string& str)
{
	std::string s;
	unsigned int data;
	auto stream = std::istringstream(str);
	std::vector<int> topBarInfo;

	while (stream >> s)
	{
		//if the stoi does not work it will throw an exception and be caght by std::invalid_argument
		data = std::stoi(s);
		topBarInfo.push_back(data);
	}	 

	if (topBarInfo.size() == 3)
	{   
		if (topBarInfo[0] > MAX_TIME)
			throw std::out_of_range("The data within the file is out of range!");

		m_topBar = TopBar(topBarInfo[0], topBarInfo[1], topBarInfo[2]);
	}

}
//======================================
//          validate stick
//======================================
void FileDealing::validateStick(const std::string& str)
{
	
	auto stream = std::istringstream(str);
	std::string x, y;
	int data;

	vector<sf::Vector2f> rectXyInfo;
	vector<int> rectIntInfo;

	for (int i = 0; i < 3; i++)
	{	
		stream >> x >> y;
		rectXyInfo.push_back(sf::Vector2f(std::stof(x), std::stof(y)));
	}

	for (int i = 0; i < 4; i++)
	{
		stream >> x;
		rectIntInfo.push_back(std::stoi(x));
	}

	validateData(rectXyInfo, rectIntInfo);
	
	// Create and add rectangle
	setAndAddRectangle(rectXyInfo, rectIntInfo);
}
//======================================
//          check valid data
//======================================
void FileDealing::validateData(const vector<sf::Vector2f>& rectXyInfo, const vector<int>& rectIntInfo) const
{
	if (rectXyInfo[size].x < 0 || rectXyInfo[size].x > MAX_STICK_SIZE ||
		rectXyInfo[size].y < 0 || rectXyInfo[size].y > MAX_STICK_SIZE)
		throw std::out_of_range("the size data is out of range");

	if (rectIntInfo[0] < 0 || rectIntInfo[0] > 360 || rectIntInfo[0] == 270 || rectIntInfo[0] == 90)
		throw std::out_of_range("the degrees in the file are out of range!");

	if (rectIntInfo[r] < 0 || rectIntInfo[r] > 255 || rectIntInfo[g] < 0 || rectIntInfo[g] > 255
		|| rectIntInfo[b] < 0 || rectIntInfo[b] > 255)
		throw std::out_of_range("the colors in the file are out of the RGB range!");
}
//======================================
//       set and add rectangle
//======================================
void FileDealing::setAndAddRectangle(const vector<sf::Vector2f>& rectXyInfo, const vector<int>& rectIntInfo)
{
	sf::RectangleShape rectangle;
	rectangle.setOrigin(rectXyInfo[origin]);
	rectangle.setPosition(rectXyInfo[pos]);
	rectangle.setSize(rectXyInfo[size]);
	rectangle.rotate(rectIntInfo[rotation]);
	rectangle.setFillColor(sf::Color(rectIntInfo[r], rectIntInfo[g], rectIntInfo[b]));
	rectangle.setOutlineThickness(2.f);
	rectangle.setOutlineColor(sf::Color::Black);

	m_sticks.push_back(std::make_shared<Stick>(rectangle));
}
