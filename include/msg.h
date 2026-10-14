#pragma once

#define MSG_HELP "Usage: ls [OPTION]... [FILE]...\n\
List information about the FILEs (the current directory by default).\n\
Sort entries alphabetically if -t is not specified.\n\
\n\
  -a                         do not ignore entries starting with .\n\
  -l                         use a long listing format\n\
  -r, --reverse              reverse order while sorting\n\
  -R, --recursive            list subdirectories recursively\n\
  -t                         sort by time, newest first; see --time\n\
\n\
Exit status:\n\
 0  if OK,\n\
 1  if minor problems (e.g., cannot access subdirectory),\n\
 2  if serious trouble (e.g., cannot access command-line argument).\n\
"