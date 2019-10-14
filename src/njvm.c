#include <stdio.h>
#include <string.h>

const char *version = "0";
// Save Build Date & Time
const char *buildDT = __DATE__ ", " __TIME__;

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        // argument version:
        if (strcmp(argv[i], "--version") == 0)
        {
            printf("Ninja Virtual Machine Version %s (compiled %s)\n", version, buildDT);
            return 0;
        }
        // argument help:
        else if (strcmp(argv[i], "--help") == 0)
        {
            printf("usage: %s [options] ...\n"
                   "Options: \n"
                   "\t--version \t show version and exit\n"
                   "\t--help \t\t show this text and exit\n",
                   argv[0]);
            return 0;
        }
        // invalid argument
        else
        {
            printf("unknown command line argument '%s', try '%s --help'\n", argv[i], argv[0]);
            return 0;
        }
    }

    // Start Message
    printf("Ninja Virtual Machine started\n");

    // Stop Message
    printf("Ninja Virtual Machine stopped\n");
}