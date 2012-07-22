/**
 * ======================== legal notice ======================
 * 
 * File:      File.cc
 * Created:   21. Juli 2012, 12:41
 * Author:    <a href="mailto:geronimo013@gmx.de">Geronimo</a>
 * Project:   libfsScan: mediatypes and filesystem scanning
 * 
 * CMP - compound media player
 * 
 * is a client/server mediaplayer intended to play any media from any workstation
 * without the need to export or mount shares. cmps is an easy to use backend
 * with a (ready to use) HTML-interface. Additionally the backend supports
 * authentication via HTTP-digest authorization.
 * cmpc is a client with vdr-like osd-menues.
 * 
 * Copyright (c) 2012 Reinhard Mantey, some rights reserved!
 * published under Creative Commons by-sa
 * For details see http://creativecommons.org/licenses/by-sa/3.0/
 * 
 * The cmp project's homepage is at http://projects.vdr-developer.org/projects/cmp
 * 
 * --------------------------------------------------------------
 */
#include <File.h>
#include <FileSystem.h>
#include <FileRepresentation.h>
#include <StringBuilder.h>
#include <sys/stat.h>
#include <sys/dir.h>

cFileSystem *cFile::fs  = NULL;
static mode_t ReadMask  = S_IRUSR | S_IRGRP | S_IROTH;
static mode_t WriteMask = S_IWUSR | S_IWGRP | S_IWOTH;
static mode_t ExecMask  = S_IXUSR | S_IXGRP | S_IXOTH;


cFile::cFile(const char *Path)
 : rep(NULL)
{
  if (!fs) fs = new cFileSystem();
  rep = fs->representationOfFile(Path);
}

cFile::cFile(const cFile& Parent, const char* RelativePath)
 : rep(NULL)
{
  if (!fs) fs = new cFileSystem();
  rep = fs->representationOfFile(Parent, RelativePath);
}

cFile::cFile(const cFileRepresentation *fr)
 : rep(fr)
{
  if (!fs) fs = new cFileSystem();
}

cFile::~cFile()
{
}

char *cFile::AbsolutePath(void) const
{
  cStringBuilder *sb = rep->internalPath();
  char *rv = NULL;

  if (sb) {
     rv = sb->toString();
     delete sb;
     }
  return rv;
}

bool cFile::Exists(void) const
{
  return rep->exists;
}

bool cFile::IsDirectory(void) const
{
  return (rep->mode & S_IFMT) == S_IFDIR;
}

bool cFile::IsFile(void) const
{
  return (rep->mode & S_IFMT) == S_IFREG;
}

bool cFile::IsSymbolic(void) const
{
  return (rep->mode & S_IFMT) == S_IFLNK;
}

bool cFile::CanRead(void) const
{
  return rep->mode & ReadMask;
}

bool cFile::CanWrite(void) const
{
  return rep->mode & WriteMask;
}

bool cFile::CanExecute(void) const
{
  return rep->mode & ExecMask;
}

off64_t cFile::Size(void) const
{
  return rep->size;
}

ulong cFile::LastModified(void) const
{
  return rep->lastModified;
}

cFile *cFile::Parent(void) const
{
  return new cFile(rep->getParent());
}

const char *cFile::Name(void) const
{
  return rep->name;
}

void cFile::Cleanup(void)
{
  if (fs) delete fs;
}

void cFile::VisitFiles(int (*cb)(cFile *, const char *))
{
  struct dirent entryBuffer, *pE;
  char * path = AbsolutePath();
  DIR *dir = opendir(path);

  while (!readdir_r(dir, &entryBuffer, &pE) && pE) {
        if (*(pE->d_name) == '.') continue; // don't bother with hidden stuff
        cb(this, pE->d_name);
        }
  closedir(dir);
  free(path);
}
