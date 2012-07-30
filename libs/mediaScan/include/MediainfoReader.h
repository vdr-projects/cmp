/*
 * File:   MediainfoReader.h
 * Author: django
 *
 * Created on 30. Juli 2012, 15:03
 */

#ifndef MEDIAINFOREADER_H
#define	MEDIAINFOREADER_H

#include <tuple>
#include <string>
#include <vector>

class cLineReader;
class cMediainfoReader {
public:
  typedef std::tuple <std::string, std::string> InfoEntry;

  cMediainfoReader(cLineReader *LineReader);
  virtual ~cMediainfoReader();

  void AddValuableKey(const char *Key);
  void Close(void);
  bool IsValuable(std::string &key);
  InfoEntry *ReadEntry(void);

private:
  cLineReader *reader;
  std::vector<std::string> valuableKeys;
  };

#endif	/* MEDIAINFOREADER_H */

