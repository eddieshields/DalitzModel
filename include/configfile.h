#ifndef DALITZMODEL_CONFIGFILE_H
#define DALITZMODEL_CONFIGFILE_H

// STL.
#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <sstream>
#include <fstream>

// DalitzModel.
#include "msgservice.h"

namespace DalitzModel {

class ConfigFile
{
  enum Section {
    None,
    Resonances,
    Parameters,
    CorrelationMatrix,
    CovarianceMatrix
  };
public:
  ConfigFile() = default;
  ConfigFile(const std::string cfgfile ) { decodeConfigFile( cfgfile ); }
  virtual ~ConfigFile() {}

  std::string get(std::string key);
  template<typename T>
  T get(std::string key);

  // Operators.
  friend std::ostream& operator<<(std::ostream& os, const ConfigFile& config);
  friend std::istream& operator>>(std::istream& is, ConfigFile& config);

private:
  void decodeConfigFile(const std::string cfgfile);

  void decodeResonances       (const std::string line);
  void decodeParameters       (const std::string line);
  void decodeCorrelationMatrix(const std::string line);
  void decodeCovarianceMatrix (const std::string line);

  void addEntry(const std::string line);

  std::map<std::string,std::string> m_entries;
};

std::string ConfigFile::get(std::string key)
{
  std::string out;
  if ( m_entries.find(key) == m_entries.end() ) {
    WARNING(key << " not found!");
    return out;
  }

  // Pass string into object;
  out = m_entries[key];
  return out;
}

template<typename T>
T ConfigFile::get(std::string key)
{
  T out;
  if ( m_entries.find(key) == m_entries.end() ) {
    WARNING(key << " not found!");
    return out;
  }

  // Pass string into object;
  std::string str = m_entries[key];
  std::istringstream is(str);
  is >> out;
  return out;
}

void ConfigFile::decodeConfigFile(const std::string cfgfile)
{
  std::ifstream ifs(cfgfile);
  
  std::string line;
  ConfigFile::Section section = ConfigFile::None;
  while (std::getline(ifs, line)) {
    if (line.empty() || line.at(0) == '#') {
      continue;
    }

    if ( line == "Resonances" ) {
      section = ConfigFile::Resonances;
      continue;
    } else if ( line == "Parameters" ) {
      section = ConfigFile::Parameters;
      continue;
    } else if ( line == "CorrelationMatrix" ) {
      section = ConfigFile::CorrelationMatrix;
      continue;
    } else if ( line == "CovarianceMatrix" ) {
      section = ConfigFile::CovarianceMatrix;
      continue;
    } else {
      switch(section)
      {
      case ConfigFile::Resonances:
        decodeResonances( line );
        continue;
      case ConfigFile::Parameters:
        decodeParameters( line );
        continue;
      case ConfigFile::CorrelationMatrix:
        decodeCorrelationMatrix( line );
        continue;
      case ConfigFile::CovarianceMatrix:
        decodeCovarianceMatrix( line );
        continue;
      default:
        continue;
      }
    }
  }
}

void ConfigFile::addEntry(const std::string line)
{
  // Entry to go into map;
  std::pair<std::string,std::string> entry;

  // Add key to entry.
  std::stringstream ss(line);
  ss >> entry.first;

  // Get value corresponding to key.
  std::string value = line;
  int key_pos = value.find("=");
  if ( key_pos != std::string::npos ) {
    value.replace(0,key_pos+1,"");
  } else {
    key_pos = value.find(":");
    if ( key_pos != std::string::npos ) {
      value.replace(0,key_pos+1,"");
    }
  }

  // Remove leading and trailing white space.
  std::regex_replace(value, std::regex("^ +| +$|( ) +"), "$1");

  // Add line to entry.
  entry.second = value;

  // Add to entries.
  m_entries.insert( entry );
}

void ConfigFile::decodeResonances(const std::string line)
{
  addEntry( line );
  return;
}

void ConfigFile::decodeParameters(const std::string line)
{
  addEntry( line );
  return;
}

void ConfigFile::decodeCorrelationMatrix(const std::string line)
{
  return;
}

void ConfigFile::decodeCovarianceMatrix(const std::string line)
{
  return;
}

// I/O operators.
std::ostream& operator<<(std::ostream& os, const ConfigFile& config)
{
  // Start on new line:
  os << "Config file = \n";
  // Loop over all entries.
  for (auto& entry : config.m_entries) {
    os << entry.first << " : " << entry.second << "\n";
  }
  return os;
}

std::istream& operator>>(std::istream& is, ConfigFile& config)
{
  std::string file;;
  is >> file;
  config.decodeConfigFile( file );
  return is;
}

}

#endif