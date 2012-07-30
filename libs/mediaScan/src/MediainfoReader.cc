/*
 * File:   MediainfoReader.cc
 * Author: django
 *
 * Created on 30. Juli 2012, 15:03
 */
#include <MediainfoReader.h>
#include <LineReader.h>
#include <stddef.h>
#include <pcrecpp.h>
#include <vector>

cMediainfoReader::cMediainfoReader(cLineReader *LineReader)
 : reader(LineReader)
{
}

cMediainfoReader::~cMediainfoReader()
{
  Close();
}

void cMediainfoReader::AddValuableKey(const char* Key)
{
  valuableKeys.push_back(Key);
}

void cMediainfoReader::Close(void)
{
  if (reader) {
     delete reader;
     reader = NULL;
     }
}

bool cMediainfoReader::IsValuable(std::string &key)
{
  for (size_t i=0; i < valuableKeys.size(); ++i) {
      if (!strcmp(key.c_str(), valuableKeys[i].c_str()))
         return true;
      }
  return false;
}

cMediainfoReader::InfoEntry *cMediainfoReader::ReadEntry()
{
  if (!reader) return NULL;
  const char *line = reader->ReadLine();
  static pcrecpp::RE comment("^\\s*#.*$");
  static pcrecpp::RE emptyLine("^\\s*$");
  static pcrecpp::RE entry("^\\s*(.+?)\\s*:\\s*(.+?)\\s*$");
  std::string name, value;
  InfoEntry *rv = NULL;

  while (line && (comment.FullMatch(line) || emptyLine.FullMatch(line)))
        line = reader->ReadLine();
  while (line && !entry.FullMatch(line, &name, &value))
        line = reader->ReadLine();
  while (line && entry.FullMatch(line, &name, &value)) {
        if (!IsValuable(name)) {
           line = reader->ReadLine();
           continue;
           }
        rv = new InfoEntry(name, value);
        break;
        }
  return rv;
}

