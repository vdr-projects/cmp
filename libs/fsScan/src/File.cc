/**
 * ======================== legal notice ======================
 *
 * File:      File.cc
 * Created:   21. Juli 2012, 12
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
  if (!Path) {
     Path = getcwd(NULL, 0);
     rep = fs->representationOfFile(Path);
     free((char *) Path);
     }
  else rep = fs->representationOfFile(Path);
}

cFile::cFile(const cFile &other)
 : rep(other.rep)
{
  if (!fs) fs = new cFileSystem();
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

cFile &cFile::operator =(const cFile &other)
{
  rep = other.rep;
  return *this;
}

const char *cFile::AbsolutePath(void) const
{
  if (rep) return rep->Path();
  return NULL;
}

bool cFile::Exists(void) const
{
  if (rep) return rep->exists;
  return false;
}

bool cFile::IsDirectory(void) const
{
  if (rep) return (rep->mode & S_IFMT) == S_IFDIR;
  return false;
}

bool cFile::IsFile(void) const
{
  if (rep) return (rep->mode & S_IFMT) == S_IFREG;
  return false;
}

bool cFile::IsSymbolic(void) const
{
  if (rep) return (rep->mode & S_IFMT) == S_IFLNK;
  return false;
}

bool cFile::CanRead(void) const
{
  if (rep) return rep->mode & ReadMask;
  return false;
}

bool cFile::CanWrite(void) const
{
  if (rep) return rep->mode & WriteMask;
  return false;
}

bool cFile::CanExecute(void) const
{
  if (rep) return rep->mode & ExecMask;
  return false;
}

off64_t cFile::Size(void) const
{
  if (rep) return rep->size;
  return 0;
}

ulong cFile::LastModified(void) const
{
  if (rep) return rep->lastModified;
  return 0;
}

cFile *cFile::Parent(void) const
{
  if (rep) return new cFile(rep->getParent());
  return NULL;
}

const char *cFile::Name(void) const
{
  if (rep) return rep->name;
  return NULL;
}

void cFile::Cleanup(void)
{
  if (fs) {
     delete fs;
     fs = NULL;
     }
}

void cFile::VisitFiles(int (*cb)(void *, cFile *, const char *), void *opaque)
{
  if (!Exists() || !IsDirectory()) return;
  struct dirent entryBuffer, *pE;
  DIR *dir = opendir(AbsolutePath());

  while (!readdir_r(dir, &entryBuffer, &pE) && pE) {
        if (*(pE->d_name) == '.') continue; // don't bother with hidden stuff
        cb(opaque, this, pE->d_name);
        }
  closedir(dir);
}

char *cFile::toURI() const
{
  if (rep) return rep->toURI();
  return NULL;
}

void cFile::SetVirtualRoot(bool isRoot)
{
  if (rep) ((cFileRepresentation *)rep)->SetVirtualRoot(isRoot);
}