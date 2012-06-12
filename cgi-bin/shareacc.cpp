/*
#
# Copyright (C) 2011 Timo Tomasini (timo[aat]tomasini-mail.de)
#
# License:
#       This program is free software; you can redistribute
#       it and/or modify it under the terms of the
#       GNU General Public License as published by the Free
#       Software Foundation; either version 2 of the License,
#       or (at your option) any later version.
#
#       This program is distributed in the hope that it will
#       be useful, but WITHOUT ANY WARRANTY; without even the
#       implied warranty of MERCHANTABILITY or FITNESS FOR A
#       PARTICULAR PURPOSE. See the GNU General Public
#       License for more details.
#
#       You should have received a copy of the GNU General
#       Public License along with this program; if not,
#       write to the Free Software Foundation, Inc., 59
#       Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
#       An on-line copy of the GNU General Public License can
#       be downloaded from the FSF web page at:
#       http://www.gnu.org/copyleft/gpl.html
#
# Name: shareacc
#
# Version: 0.1
#
#
# TODO:
# * you tell me
#
*/

#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <time.h>
#include "ini.h"

void table_td (std::string x)
{
	std::cout << "<td>" << x << "</td>" <<std::endl;
}

void table_tr ()
{
	std::cout << "<tr>" << std::endl;
}

void table_trr ()
{
	std::cout << "</tr>" << std::endl;
}

class Account
{
	public:
	static unsigned int last_nr;
	std::string nr;
	std::string type;
	std::string owner;
	std::string user;
	std::string password;
	std::string used;

	Account ()
	{
		nr = boost::lexical_cast<std::string>(++last_nr);
	}

	void out()  // print method
	{
		table_td(nr);
		table_td(type);
		table_td(owner);
		table_td(user);
		table_td(password);
		std::string checked=used=="Yes"?"checked=\"checked\" ":"";
		std::string image_path=used=="Yes"?"busy.png":"online.png";
		table_td(used=="Yes" || used=="No"?"<img src=\"/img/"+image_path+" width=\"16\" height=\"16\"> "+used:"ERROR!");
		std::cout << "<td>" << "<input type=\"checkbox\" onchange=\"document.forms[0].submit()\" name=\"" << nr << "\" " << checked << "/>" << "</td>" << std::endl;
	}
};

unsigned int Account::last_nr=0;

int main ()
{	
	ini config("shareacc.cfg");
	if (!(config.Good()))
	{
		std::cout << "Content-type: text/html\n" << std::endl;
		std::cout << "<h2>Could not open cfg!</h2>" << std::endl;
		return 1;
	}
	/*else  // only for debug
	{
		std::cout << "cfg good" << std::endl;
		std::cout << "count: " << config.CountSections() << std::endl;
		return 0;
	}*/

	Account *accounts = new Account [(config.CountSections()-1)];  // create as many accounts as necessary (-1 because of the main section)

	for (unsigned int k=0; k<(config.CountSections()-1); ++k)  // initialize objects
	{
		std::string section = boost::lexical_cast<std::string>(k+1);
		const char *s = section.c_str();
		if(((time(NULL))-(boost::lexical_cast<double>(config.Get(s, "last_modified"))))>43200)  // 43200s = 12h
		{
			config.Set(s, "used", "No");
			config.Set(s, "last_modified", "0");
		}
		accounts[k].type = config.Get(s, "type");
		accounts[k].owner = config.Get(s, "owner");
		accounts[k].user = config.Get(s, "user");
		accounts[k].password = config.Get(s, "password");
		accounts[k].used = config.Get(s, "used");
	}
	
	std::cout << "Content-type: text/html\n" << std::endl;
	std::cout << "<head>" << std::endl;
	std::cout << "<title>" << config.Get("main", "title") << "</title>" << std::endl;
	std::cout << "<link href=\"/style.css\" rel=\"stylesheet\" type=\"text/css\">" << std::endl;
	std::cout << "</head>\n" << std::endl;

	std::cout << "<body>" << std::endl;
	std::cout << "<h3>" << config.Get("main", "title") << "</h3>" << std::endl;

	std::cout << "<div class=\"main\">" << std::endl;
	std::cout << "<form method=\"post\" action=\"/cgi-bin/switch\">" << std::endl;

	// table start
	std::cout << "<table>" << std::endl;
	std::cout << "<tbody>" << std::endl;
	table_tr();
	table_td("<b>Nr</b>");
	table_td("<b>Type</b>");
	table_td("<b>Owner</b>");
	table_td("<b>User</b>");
	table_td("<b>Password</b>");
	table_td("<b>In Usage?</b>");
	table_trr();

	for (unsigned int k=0; k<(config.CountSections()-1); ++k)
	{
		table_tr();
		accounts[k].out();
		table_trr();
	}
	
	std::cout << "</tbody>" << std::endl;
	std::cout << "</table>" << std::endl;
	// table end

	std::cout << "<p><input type=\"submit\" value=\"Change value\" style=\"display: none;\" /></p>" << std::endl;
	std::cout << "</form>" << std::endl;
	std::cout << "</div>" << std::endl;

	std::cout << "<div class=\"footer\">Status will be reset every 12 hours.</div>" << std::endl;

	std::cout << "</body>" << std::endl;

	delete[] accounts;
	return 0;
}
