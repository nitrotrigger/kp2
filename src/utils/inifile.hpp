#ifndef INIFILE_HPP
#define INIFILE_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <vector>


class IniFile
{
	public:
		template<typename T>
		bool getValue(const std::string& key,T& value);
		bool getValue(const std::string& key,std::string& value);
			
		template<typename T>
		bool setValue(const std::string& key,const T& value);
		bool setValue(const std::string& key,const std::string& value);
		
		bool load(const std::string& filename);
		bool save(const std::string& filename);

		IniFile();
		IniFile(const std::string& filename);
				
	private:
		std::map<std::string,std::string> m_values;
		
		std::string m_filename;
	
};

template<typename T>
bool IniFile::setValue(const std::string& key,const T& value)
{
	std::string str;
	std::stringstream ss;
	ss << value;
	ss >> str;
	
	if (ss.fail())
	return false;
	
	m_values[key] = str;
	
	return true;
};

template<typename T>
bool IniFile::getValue(const std::string& key,T& value)
{
	if(m_values.find(key) == m_values.end())
	{
		std::cerr << "Requested key ";
		std::cerr << '"' << key << '"';
		std::cerr << " not found in IniFile originally loaded from ";
		std::cerr << '"' << m_filename << '"' << std::endl;
		return false;
	}
		
	T temp;
	
	std::stringstream ss;
	ss << m_values[key];
	
	ss >> temp;
	
	if (ss.fail())
		return false;
		
	value = temp;
	return true;
}

#endif // INIFILE_HPP
