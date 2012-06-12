#include <iostream>
#include <string>  
#include <boost/lexical_cast.hpp>
#include <cgicc/Cgicc.h> 
#include "ini.h"


int main ()
{
	cgicc::Cgicc formData;

    ini config("shareacc.cfg");
    if (!(config.Good()))
    {
        std::cout << "Content-type: text/html\n" << std::endl;
        std::cout << "<h2>Could not open cfg!</h2>" << std::endl;
        return 1;
    }

	
	if(formData.getEnvironment().getRequestMethod() == "POST")
	{
		for(unsigned int i=0; i<(config.CountSections()-1); ++i)  // write checkbox options into config
		{
			std::string nr = boost::lexical_cast<std::string>(i+1);
			const char *c_nr = nr.c_str();

			if(formData.queryCheckbox(c_nr))
			{
				config.Set(c_nr, "used", "Yes");
				std::string a_time = boost::lexical_cast<std::string>(time(NULL));
				const char *c_time = a_time.c_str();
				config.Set(c_nr, "last_modified", c_time);
			}
			else
			{
				config.Set(c_nr, "used", "No");
				config.Set(c_nr, "last_modified", "0");
			}
		}
	}

	std::cout << "Status: 302 Found" << std::endl;
	std::cout << "Location: /cgi-bin/shareacc\n" << std::endl;
	
	return 0;
}
