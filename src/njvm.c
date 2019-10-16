#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VERSION 0

// Handle version argument
static void version(const char *myself)
{
    printf("Ninja Virtual Machine Version %d (compiled %s, %s)\n", VERSION,
           __DATE__, __TIME__);
}

// Handle help argument
static void help(const char *myself)
{
    printf("usage: %s [options] ...\n"
           "Options: \n"
           "\t--version \t show version and exit\n"
           "\t--help \t\t show this text and exit\n",
           myself);
}

// Handle an invalid argument
static void invalid(const char *myself, const char *arg)
{
    printf("unknown command line argument '%s', try '%s --help'\n", arg, myself);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        // argument version
        if (strcmp(argv[i], "--version") == 0)
        {
            version(argv[0]);
            exit(0);
        }
        // argument help
        else if (strcmp(argv[i], "--help") == 0)
        {
            help(argv[0]);
            exit(0);
        }
        // handle an invalid argument
        else
        {
            invalid(argv[0], argv[i]);
            exit(0);
        }
    }

    // Start Message
    printf("Ninja Virtual Machine started\n");

    // Stop Message
    printf("Ninja Virtual Machine stopped\n");
}