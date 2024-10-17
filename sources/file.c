#include <vowframework/private/log.h>

#include <vowframework/file.h>
#include <vowframework/log.h>
#include <vowframework/memory.h>

#include <stdio.h>

char* vow_file_read(const char* path)
{
    FILE* handle = fopen(path, "r");
    if (!handle)
    {
        vow_log_print(VOW_LOG_LEVEL_ERROR, "Failed to read file: %s", path);
        return (void*) 0;
    }
    fseek(handle, 0, SEEK_END);
    const long length = ftell(handle);
    fseek(handle, 0, SEEK_SET);
    char* text = vow_memory_allocate(length + 1);
    fread(text, sizeof(char), length, handle);
    text[length] = '\0';
    fclose(handle);
    return text;
}