/*
 * File:   MetaScanTest.cc
 * Author: django
 *
 * Created on 27.07.2012, 10:03
 */
#include <File.h>
#include <FileReader.h>
#include <LineReader.h>
#include <ConfigReader.h>
#include <CommandReader.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <tr1/tuple>
#include <util.h>

static void testPipe(const char *chk = NULL);

static void parseConfig(const char *FileName)
{
  cConfigReader *cr = new cConfigReader(new cLineReader(new cFileReader(new cFile(FileName))));
  cConfigReader::ConfigEntry *ce;

  while ((ce = cr->ReadValue())) {
        std::cout << "config entry [" << std::get<0>(*ce) << "] => " << std::get<1>(*ce) << std::endl;
        delete ce;
        }
  cr->Close();
  delete cr;
}

static void testMediaFiles(const char *FileName)
{
  cLineReader *lr = new cLineReader(new cFileReader(new cFile(FileName)));
  const char *line;

  while ((line = lr->ReadLine())) {
        std::cout << "media-test-file: " << line << std::endl;
        testPipe(line);
        }
  lr->Close();
  delete lr;
}

static const short BufferSize = 100;
enum PipeFileDescriptors {
  READ_FD = 0,
  WRITE_FD = 1
};

static void testCommandReader()
{
  cCommandReader *cr = new cCommandReader("/bin/ls");
  cLineReader *lr = new cLineReader(cr);
  const char *line;

  cr->AddCommandParameter("-al");
  cr->AddCommandParameter("--color");

  while ((line = lr->ReadLine())) {
        std::cout << "from command: " << line << std::endl;
        }
  delete lr;
};

static void testPipe(const char *chk)
{
  int parent2Child[2];
  int child2Parent[2];
  pid_t pid;
  std::string dataReadFromChild;
  char buffer[BufferSize + 1];
  ssize_t readResult;
  bool run = true;
  int status;

  ASSERT_IS(0, pipe(parent2Child));
  ASSERT_IS(0, pipe(child2Parent));

  switch (pid = fork()) {
    case -1:
         FAIL("fork failed");
         exit(-1);

    case 0: /* child */
         ASSERT_NOT(-1, dup2(parent2Child[READ_FD], STDIN_FILENO));
         ASSERT_NOT(-1, dup2(child2Parent[WRITE_FD], STDOUT_FILENO));
         ASSERT_NOT(-1, dup2(child2Parent[WRITE_FD], STDERR_FILENO));
         ASSERT_IS(0, close(parent2Child[WRITE_FD]));
         ASSERT_IS(0, close(child2Parent[READ_FD]));

         if (chk) {
            execlp("mediainfo", "mediainfo", chk, NULL);
            }
         else execlp("ls", "ls", "-al", "--color", NULL);
         FAIL("this line should never be reached!");
         exit(-1);

    default: /* parent */
         std::cout << "child " << pid << " process running ..." << std::endl;

         ASSERT_IS(0, close(parent2Child[READ_FD]));
         ASSERT_IS(0, close(child2Parent[WRITE_FD]));

         while (run) {
               switch (readResult = read(child2Parent[READ_FD], buffer, BufferSize)) {
                 case 0: /* end of file, or non-blocking read. */
                      std::cout << "End of File reached ..."        << std::endl
                                << "Data received was ("
                                << dataReadFromChild.size() << "):" << std::endl
                                << dataReadFromChild                << std::endl;
                      ASSERT_IS(pid, waitpid(pid, &status, 0));

                      std::cout << std::endl
                                << "child exit status is: " << WEXITSTATUS(status) << std::endl << std::endl;
//                      exit(0);
                      run = false;
                      break;

                 case -1:
                      if ((errno == EINTR) || (errno == EAGAIN)) {
                         errno = 0;
                         }
                      else {
                         FAIL("read() failed");
                         run = false;
                         } break;

                 default:
                      dataReadFromChild.append(buffer, readResult);
                      break;
                 }
               }
    }
}


// mediainfo ${media} | grep "Scan type"
// ffmpeg -i ${media}
int main()
{
  parseConfig("srclient.conf");

  std::cout << std::endl << "===========================================" << std::endl << std::endl;
  parseConfig("srserver.conf");

  std::cout << std::endl << "===========================================" << std::endl << std::endl;
  testCommandReader();

//  std::cout << std::endl << "===========================================" << std::endl << std::endl;
//  testMediaFiles("testMedia.files");

  cFile::Cleanup();
  return 0;
}
