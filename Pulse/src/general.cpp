#include "general.h"

std::string getSetting(std::string const & category, std::string const & attribute)
{
	//Read file
	ofFile file;
	
	if (!file.open("settings.xml"))
	{
		EXCEPTION("Cannot open settings.xml");
		return std::string();
	}

	ofBuffer buffer = file.readToBuffer();
	ofXml xml;
	xml.loadFromBuffer(buffer.getText());
	file.close();

	//Verify xml
	if (xml.getName() != std::string("PulseSettings"))
	{
		EXCEPTION("Main node not found in settings file");
		return std::string();
	}

	//Get param and return content
	xml.setTo(category);
	const std::string res = xml.getAttribute(attribute);

	DEBUG_MSG("Returning param " << category << "/" << attribute << " : " << res);
	return res;
}