#include <stdio.h>
#include "main.h"

// Funtion for help guide display
void id3_help_guide()
{
    printf("==========================================================\n");
    printf("         MP3 ID3v2.3 Tag Reader - Help Guide\n");
    printf("==========================================================\n\n");

    printf("Usage: ./a.out <filename.mp3> [option]\n\n");

    printf("Options:\n");
    printf("  -h   Show this help guide.\n");
    printf("  -v   View MP3 metadata (title, artist, album, year).\n");
    printf("  -e   Edit MP3 metadata (modify title, artist, album, year).\n\n");

    printf("Edit Modifiers:\n");
    printf("  -t    \"New Title\"     -> Change song title\n");
    printf("  -a    \"New Album\"     -> Change album name\n");
    printf("  -ar   \"New Artist\"    -> Change artist name\n");
    printf("  -y    \"2025\"          -> Change release year\n");
    printf("  -cm   \"New Comment\"   -> Change comment\n");
    printf("  -cn   \"New Content\"   -> Change content\n\n");

    printf("Example Usage:\n");
    printf("  ./a.out -h                -> Show help guide\n");
    printf("  ./a.out -v file.mp3       -> View ID3 details\n");
    printf("  ./a.out -e file.mp3 -t \"New title\"   -> Edit title\n");

    printf("==========================================================\n");
}

