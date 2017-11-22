/*
 * Main.cpp
 *
 *  Created on: 20 nov. 2017
 *      Author: didier
 */

#include "menuH.h"
#include "ns1.nsmap"
#include <iostream>
#include <fstream>

void print(ns1__Menu* menu, int offset)
{
	for (std::vector<ns2__Item*>::const_iterator i = menu->item.begin(); i != menu->item.end(); ++i)
	{
		std::cout<<std::string(offset, ' ' ) << (*i)->label<<std::endl;
		if ((*i)->menu != NULL)
		{
			print((*i)->menu, offset + 3);
		}
	}
}

int main(int, char**)
{
	   // New soap struct engine context
	   // Use strict validation and indented canonicalized output
	   struct soap *soap = soap_new1(SOAP_XML_STRICT | SOAP_XML_INDENT | SOAP_XML_NOTYPE);

	   ns1__Menu *menu = soap_new_ns1__Menu(soap, -1);

	   std::fstream fs;

	   // Read the address book from address.xml (defined by address.xsd)
	   fs.open("Menu extension.xml", std::ios::in);
	   if (fs)
	   {
	     soap->is = &fs;
	     if (soap_read_ns1__Menu(soap, menu) != SOAP_OK)
	     {
	       std::cerr << "Error reading Menu extension.xml file" << std::endl;
	       soap_stream_fault(soap, std::cerr);
	       exit(1);
	     }
	     fs.close();
	   }
	   print(menu, 0);
}

