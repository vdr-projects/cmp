#!/usr/bin/perl
use strict;
use IO::Handle;
use File::Spec;
use File::Copy;
use File::Basename;

my $base = '.';
my $version = '0.2';
my $mode = 'unknown';
my $clean = 0;
my $force = 0;
my $verbose = 0;
my $ownProject = 0;
my $prefixFN = 'License.txt';
my $years = '1897';
my $licenseTime = 0;
my $testOnly = 0;
my $serialVersion = '713L';
my $realAuthor = '<a href="mailto:geronimo013@gmx.de">Geronimo</a>';
my $modeConfig = {
   'java' => { 'match' => '\.java$', 'key' => 'package ', 'cmt0' => '/**', 'cmt1' => ' * ', 'cmt2' => ' */' }
 , 'php'  => { 'match' => '\.php$', 'key' => 'use ', 'cmt0' => '/**', 'cmt1' => ' * ', 'cmt2' => ' */' }
 , 'c++'  => { 'match' => '\.(?:cc|h|cpp|hpp)$', 'key' => '#\s*(?:ifndef|include) ', 'cmt0' => '/**', 'cmt1' => ' * ', 'cmt2' => ' */' }
};
my $summaries = {};
my @license   = ();

sub startScan {
  my $basedir = File::Spec->rel2abs('.');
  my $pn = basename($basedir);
  my $localLicense = $basedir.'/doc/Legal.Note';

  if (-s $localLicense) {
     print('project has private license file: '.$localLicense."\n");
     prepare($localLicense);
     }
  else {
     prepare($prefixFN);
     }
  loadSummary($pn);
  tellSummary($pn) if $verbose;
  findFiles($base);
}

sub findFiles {
  my $path = shift;
  my $match = shift;
  my $pn = basename(File::Spec->rel2abs('.'));
  my $dp;

  opendir($dp, $path) or die "can't opendir $path: $!";
  while (my $entry = readdir($dp)){
        next if($entry =~ /^\./);
        if (-d $path.'/'.$entry) {
           findFiles($path.'/'.$entry);
           }
        if ($entry =~ /$modeConfig->{$mode}{'match'}/) {
           my @st = stat($path.'/'.$entry);
           my %file;

           $file{'name'} = $entry;
           $file{'path'} = $path.'/'.$entry;
           $file{'time'} = $st[9];
           $file{'nprj'} = $pn;

           processFile(\%file);
           }
        }
  closedir($dp);
}

sub containsCopyright {
  my $fn = shift;
  my $fp;
  my $own = 0;
  my $found = 0;

  open($fp, $fn) or die('Oups - can not open file '.$fn."\n");
  while (my $line = <$fp>) {
        last if $line =~ /$modeConfig->{$mode}{'key'}/;

        if ($line =~ /=== legal notice ===/) {
           $found = 1;
           $own = 1;
           last;
           }
        elsif ($line =~ /copyright/i) {
           $found = 1;
           if ($line =~ /copyright.+?Reinhard Mantey/i) { $own = 1; }
           else { $own = 0; }
           last;
           }
        }
  close($fp);
  $own = 1 if !$found && $ownProject;

  return ($own, $found);
}

sub processFile {
  my $fi = shift;
  my ($own, $found) = containsCopyright($fi->{'path'});

  if ($found && !$own) {
     print('file '.$fi->{'path'}.' is owned by foreign copyright, so don\'t touch it!'."\n");
     return;
     }
  print("\t".'process file '.$fi->{'path'}.' as '.($own ? 'own' : 'foreign').' source.'."\n") if $verbose;
  return if ($testOnly);
  my @tag = ('           '
           , 'File:      '
           , 'Author:    '
           , 'Project:   '
           , 'Created:   '
           , 'Copyright: ');
  my %tags;
  my @parts;
  my @cmt;
  my $appInfo;
  my $fileInfo;
  my $comment;
  my $line;
  my $prefix;
  my $first = 1;
  my ($sfp, $dfp);

  print('patch '.$fi->{'path'}."\n");
  $fi->{'bak'} = $fi->{'path'}.'.bak';
  move($fi->{'path'}, $fi->{'bak'});
  open($sfp, $fi->{'bak'})       or die('could not read source '.$fi->{'bak'}.' '.$!."\n");
  open($dfp, '> '.$fi->{'path'}) or die('could not write source '.$fi->{'path'}.' '.$!."\n");

  while ($line = <$sfp>) {
        last if $line =~ /$modeConfig->{$mode}{'key'}/;
        $line =~ s/^(?:\/\*+| \*+ |\/+ | \*+\/)(.*)$/$1/;
        next if $line =~ /^\s*$/;
        next if $line =~ /^ \*\n/;
        @parts = split(/\:\s*/, $line);

        if ($line =~ /Created on (.+)$/) {
           $tags{'Created'} = $1;
           }
        elsif ($line =~ /=== legal notice ===/) {
           $found = 1;
           $own = 1;
           }
        elsif ($line =~ /copyright/i) {
           $found = 1;
           if ($line =~ /copyright.+?Reinhard Mantey/i) { $own = 1; }
           else { $own = 0; }
           }
        elsif ($#parts > 0) {
           $parts[1] =~ s/\n//;
           $tags{$parts[0]} = $parts[1];
           }
        else {
           push(@cmt, $line);
           }
        }
  $prefix  = $modeConfig->{$mode}{'cmt0'}."\n";
  foreach (@license) {
          my $pl = $_;

          if ($pl =~ /\@\@AppInfo\@\@/) {
             foreach (@{$summaries->{$fi->{'nprj'}}{'content'}}) {
                     my $sl = $_;

                     if ($first) {
                        $first = 0;
                        $prefix .= $modeConfig->{$mode}{'cmt1'}.$tag[3].$sl;
                        }
                     else {
                        $prefix .= $modeConfig->{$mode}{'cmt1'}.$tag[0].$sl;
                        }
                     }
             }
          elsif ($pl =~ /\@\@Comment\@\@/) {
             foreach (@cmt) {
                     $prefix .= $modeConfig->{$mode}{'cmt1'}.$_;
                     }
             }
          elsif ($pl =~ /\@\@FileInfo\@\@/) {
             $prefix .= $modeConfig->{$mode}{'cmt1'}.$tag[1].$fi->{'name'}."\n";
             if ($ownProject && $own) {
                $prefix .= $modeConfig->{$mode}{'cmt1'}.$tag[4].$tags{'Created'}."\n";
                $prefix .= $modeConfig->{$mode}{'cmt1'}.$tag[2].$realAuthor."\n";
                }
             }
          else {
             $pl =~ s/\@\@YEAR\@\@/$years/;
             $prefix .= $modeConfig->{$mode}{'cmt1'}.$pl;
             }
          }
  $prefix .= $modeConfig->{$mode}{'cmt2'}."\n";

  print($dfp $prefix);
  print($dfp $line);

  while ($line = <$sfp>) {
        if ($line =~ /\@author\s+(.+)$/) {
           my $author = $1;

           if ($author =~ /^(?:reinhard|Reinhard Mantey|django)\s*$/) {
              print('have to patch author: '.$author." from line: ".$line) if $verbose;
              $line =~ s/^(.+?\@author\s+)(.+)$/\1$realAuthor/;
              }
           }
        if ($line =~ /^(.*?)\@author.+?Reinhard Mantey/) {
           print('have to patch author from line: '.$line) if $verbose;
           $line = $1.'@author '.$realAuthor."\n";
           }
        if ($line =~ /^(.+?)serialVersionUID(\s+)=(\s+)([+\-0-9L]+);(.*)$/) {
           print('have to patch serial version uid from line: '.$line) if $verbose;
           $line = $1.'serialVersionUID'.$2.'='.$3.$serialVersion.";\n".$5;
           }
        print($dfp $line);
        }
  close($sfp);
  close($dfp);

  if ($force) {
     utime($licenseTime, $licenseTime, $fi->{'path'});
     }
  elsif ($fi->{'time'} > $summaries->{$fi->{'nprj'}}{'time'}) {
     utime($fi->{'time'}, $fi->{'time'}, $fi->{'path'});
     }
  else {
     utime($summaries->{$fi->{'nprj'}}{'time'}, $summaries->{$fi->{'nprj'}}{'time'}, $fi->{'path'});
     }
  unlink($fi->{'bak'}) if ($clean);
}

sub loadSummary {
  my $pn = shift;

  if (not defined($summaries->{$pn})) {
     print('have to load summary for '.$pn.' ... ') if $verbose;
     my $fp;
     my $fn = './summary.txt';
     my @st = stat($fn);
     my @sum;

     if (-s $fn) {
        open($fp, $fn) or die('Oups, can not open summary file >'.$fn.'<'."\n");
        while (my $line = <$fp>) {
              push(@sum, $line);
              }
        close($fp);
        }
     $summaries->{$pn}{'content'} = [@sum];
     $summaries->{$pn}{'time'}    = $st[9];
     print(' DONE.'."\n") if $verbose;
     }
  else {
     print('summary already loaded for '.$pn."\n") if $verbose;
     }
}

sub tellSummary {
  my $pn = shift;

  if (defined($summaries->{$pn})) {
     foreach my $line (@{$summaries->{$pn}{'content'}}) {
             print("\t".$line);
             }
     }
  else {
     die('no summary for '.$pn." found.\n");
     }
}

sub prepare {
  my $licenseFile = shift;
  print('prepare: mode='.$mode."\n") if $verbose;
  print('prepare: prefix='.$licenseFile."\n") if $verbose;
  print('prepare: years='.$years."\n") if $verbose;
  my $fp;
  my $own = 0;

  sleep(1) if $verbose && !$testOnly;
  @license = ();
  open($fp, $licenseFile) or die('missing license-file >'.$licenseFile.'<!'."\n");
  while (my $line = <$fp>){
        $own = 1 if $line =~ /=== legal notice ===/;
        push(@license, $line);
        }
  close($fp);
  $ownProject = $own;
}

sub usage {
  my $cs = "\n".'known options:'."\n";
  $cs .= '  --mode <lang>             the language mode to work on'."\n";
  $cs .= '  --prefix <path>           the path to a file, used as copyright-prefix'."\n";
  $cs .= '  --years <time[-interval]> will substitute the year in copyright'."\n";
  $cs .= '  --clean                   don\'t keep backup-files'."\n";
  $cs .= '  --help                    this text'."\n";
  return $cs;
}

sub processArgs {
  while (my $arg = shift) {
        if ($arg =~ /^--?(.+)$/) {
           my $param = $1;

           for ($param) {
               /^mode$/    and do { $mode = shift; last; };
               /^force$/   and do { $force = 1; $licenseTime = time(); last; };
               /^prefix$/  and do { $prefixFN = shift; last; };
               /^years$/   and do { $years = shift; last; };
               /^clean$/   and do { $clean = 1; last; };
               /^verbose$/ and do { $verbose = 1; last; };
               { die('unsupported parameter: '.$arg."\n".usage()); };
               }
           }
        }
}

#
# main
#
autoflush STDOUT 1;
print('checkLicense.pl Version: '.$version."\n");
print(' scans source files for missing copyright-info.'."\n");
print(' Possible language-mode: java, php, c++'."\n\n");
processArgs(@ARGV);
die('unsupported mode >'.$mode.'<'."\n".usage()) if not defined($modeConfig->{$mode});
$prefixFN = File::Spec->rel2abs($prefixFN) if -s $prefixFN;
if (-s 'summary.txt') {
   startScan();
   }
else {
   checkDirectory(File::Spec->rel2abs('.'));
   }

sub checkDirectory {
   my $dir = shift;
   my $dp;

   opendir($dp, $dir) or die('could not read directory '.$dir.'! '.$!."\n");
   print('gonna check directory '.$dir."\n") if $verbose;
   while (my $entry = readdir($dp)) {
         next if $entry =~ /^\./;
         my $path = $dir.'/'.$entry;

         if (-d $path) {
            if (-s $path.'/summary.txt') {
               print('found summary at '.$path."\n");
               chdir $path;
               startScan();
               chdir $dir;
               }
            elsif ($entry =~ /^libs$/) {
               checkDirectory($path);
               }
            else {
               print('  skip '.$path.' (not a subproject)'."\n") if $verbose;
               }
            }
         }
   closedir($dp);
   }
